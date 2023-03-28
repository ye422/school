#!/usr/bin/python3
import sys, os, subprocess
from os import path
from subprocess import PIPE


CONFIG_FILE = "config"
TIMEOUT = 3
DELAY_PENALTY = 0.8
ALL_TARGET = "all"
TESTCASE_DIRNAME = "testcase"
VALIDATOR_NAME = "validate"
EXECUTABLE_NAME = "main.bin"


def bytes_to_str(bytes):
    return "".join(map(chr, bytes))


def run_cmd(cmd_str):
    cmd_args = cmd_str.split()
    try:
        p = subprocess.Popen(cmd_args, stdin=PIPE, stdout=PIPE, stderr=PIPE)
        output, err = p.communicate()
        return output
    except Exception as e:
        print(e)
        exit(1)


def run_make(problem_dir, target):
    try:
        orig_cwd = os.getcwd()
        os.chdir(problem_dir)
        run_cmd("make %s" % target)
        os.chdir(orig_cwd)
    except FileNotFoundError:
        print("Failed to move into %s (maybe deleted)" % problem_dir)
        exit(1)


def check(problem_dir, src_file, tc_num, point, is_delay):
    src_path = path.join(problem_dir, src_file)
    if not path.isfile(src_path): # Not submitted
        return (" ", 0.0)

    validator = path.join(problem_dir, VALIDATOR_NAME)
    if path.isfile(validator): # Skip if validator does not exist
        try:
            cmd = [validator, src_path]
            result = subprocess.run(cmd, check=True, stdout=PIPE, stderr=PIPE)
            output = result.stdout
            if bytes_to_str(output).strip() != "":
                return ("I" * tc_num, 0.0)
        except Exception as e:
            # Validator raised an error.
            return ("I" * tc_num, 0.0)

    # Build the problem directory.
    run_make(problem_dir, "clean")
    run_make(problem_dir, "")
    executable = path.join(problem_dir, EXECUTABLE_NAME)
    if not path.isfile(executable):
        return ("C" * tc_num, 0.0)

    grading_str = ""
    # Now start the grading with each testcase file.
    tc_dir = path.join(problem_dir, TESTCASE_DIRNAME)
    for i in range(tc_num):
        tc_path = path.join(tc_dir, "tc-%d" % (i + 1))
        ans_path = path.join(tc_dir, "ans-%d" % (i + 1))
        f = open(ans_path)
        ans = f.read()
        f.close()
        try:
            cmd = [executable, tc_path]
            result = subprocess.run(cmd, check=True, timeout=TIMEOUT,
                                    stdout=PIPE, stderr=PIPE)
            output = result.stdout
            if ans.strip() == bytes_to_str(output).strip():
                grading_str += "O"
            else:
                grading_str += "X"
        except subprocess.TimeoutExpired:
            grading_str += "T"
        except subprocess.CalledProcessError as e:
            print(e)
            grading_str += "E"

    ratio = float(grading_str.count("O")) / tc_num
    obtained_point = point * ratio
    if is_delay:
        grading_str += "(Delay)"
        obtained_point *= DELAY_PENALTY
    return grading_str, obtained_point


def parse_config():
    f = open(CONFIG_FILE)
    problem_list = []
    for line in f:
        tokens = line.strip().split(" ")
        problem_dir = tokens[0]
        src_file = tokens[1]
        tc_num = int(tokens[2])
        point = int(tokens[3])
        problem_list.append((problem_dir, src_file, tc_num, point))
    f.close()
    return problem_list


def main():
    if len(sys.argv) not in [2, 3]:
        # --delay option is hidden.
        print("Usage: %s < %s | 1-1 | 1-2 | ... >" % (sys.argv[0], ALL_TARGET))
        exit(1)

    target = sys.argv[1]
    if target.endswith("/"):
        print("[*] Fixing %s into %s" % (target, target[:-1]))
        target = target[:-1]

    delay_flag = False
    csv_flag = False
    if len(sys.argv) == 3:
        csv_flag = True
        if sys.argv[2] == "--delay":
            delay_flag = True
        elif sys.argv[2] != "--normal": # Nothing to do if it's --normal.
            print("Invalid option: %s" % sys.argv[2])
            exit(1)

    problem_list = parse_config()
    total_point = 0.0
    for (problem_dir, src_file, tc_num, point) in problem_list:
        if target == ALL_TARGET or problem_dir == target:
            if not csv_flag:
                print("[*] Grading %s ..." % problem_dir)
            grading_str, obtained_point = \
                check(problem_dir, src_file, tc_num, point, delay_flag)
            total_point += obtained_point
            if csv_flag:
                print("%s, %.1f, " % (grading_str, obtained_point), end="")
            else:
                print("[*] Result: %s" % grading_str)
    if csv_flag:
        print("%.1f," % total_point)


if __name__ == "__main__":
    main()
