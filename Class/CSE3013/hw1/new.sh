echo "Enter directory name:"
read dirname

cd "$dirname" || exit

for dir in *
do
     newname=$(echo "$dir" | tr '[:lower:][:upper:]' '[:upper:][:lower:]')
     mv "$dir" "$newname"
done
