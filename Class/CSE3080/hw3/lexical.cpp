#include <iostream>
#include <cstdlib>
#define MAX 100
using std::cout;
using std::cin;

struct Word
{
    char * content;
    Word * link;
    int index;
    int length;
};

void insert_word(char * tempword, Word *& first, int location, int * word_count);
void print_word(Word * first);
void case_change(char * tempword, int cnt);
int compare_word(Word * first, char * tempword);
bool check_exit(char * tempword);

int main()
{
    Word * first = nullptr;
    char * tempword = new char[MAX];
    int *word_cnt = new int;
    *word_cnt = 0;
    cin.getline(tempword,MAX);
	if( cin.fail())
	{
		cout <<	"Error, Invaild input.\n";
		exit(1);
	}
	
    while ( check_exit(tempword))
    {
        int location = 0;
        if  ( *word_cnt > 0)
            location = compare_word( first, tempword );
        insert_word( tempword, first, location, word_cnt);
        print_word(first);
                (*word_cnt)++;
        cin.getline(tempword, MAX);
		if ( cin.fail() )
		{
			cout << "Error, Invaild input.\n";
			exit(1);
		}
    }

    Word * clean;
    for (clean = first; clean != nullptr; clean = clean->link)
        delete[] clean->content;
    delete[] tempword;
    while (first != nullptr)
    {
        clean = first;
        first = first->link;
        delete clean;
    }
	
	delete word_cnt;
    return 0;
}

void insert_word(char *tempword, Word *&first, int location, int * word_count)
{
    int cnt;
    Word *newword = new Word;
    newword->content = new char[MAX];
    Word *temp_add = first;

    for (int i = 0;; i++)
    {
        if (tempword[i] == '\0')
        {
            cnt = i;
            break;
        }
    }

    for (int i = 0; i < cnt; i++)
        newword->content[i] = tempword[i];

    if (location == 0)
    {
        newword->link = first;
        first = newword;
    }
    else if ( location == *word_count + 1)
    {
        for (int i = 0; ; i++)
        {    
			if (temp_add->link == nullptr)
            {
                newword->link = nullptr;
                temp_add ->link = newword;
                break;
            }
            temp_add = temp_add-> link;
        }
    }

    else
    {
    for (int i = 0; i < location - 1 ; i++)
    {
        temp_add = temp_add ->link;
    }
    	newword->link = temp_add->link;
        temp_add->link = newword;
    }

    if (location == *word_count + 1)
        newword->index = location - 1;
    else
        newword->index = location;
    newword->length = cnt;

    return;
}

int compare_word(Word * first, char * tempword)
{
    int cnt, result = 0;
    int bflag = 0;
	int same_flag = 0;
    int word_cnt = 0;
    Word * ptr;
    char * target_word = new char[MAX];
    char * compare_word = new char[MAX];
    for ( int i = 0; ; i++)
    {
        if ( tempword[i] == '\0')
        {
            cnt = i;
            break;
        }
    }
    for (int i =0; i < cnt; i++)
        target_word[i] = tempword[i];

    case_change( target_word, cnt);
    for (ptr = first; ptr != nullptr; ptr = ptr->link )
    {
		
        if( bflag == 1) 
			break;
		
		for( int i =0; i < ptr -> length; i++)
			compare_word[i] = ptr -> content[i];		
		case_change( compare_word, ptr -> length);	

        if( compare_word[0] != target_word[0] )
        {
            if (compare_word[0] > target_word[0])
            {
                bflag = 1;
                result = word_cnt;
                break;
            }
        }
        else
		{
			same_flag = 1;
            for ( int i =1; i < cnt ; i++)
            {
        		if (compare_word[i] != target_word[i])
                {
					same_flag = 0;
                    if (compare_word[i] > target_word[i])
                    {
                    	bflag = 1;
                        result = word_cnt;
                        break;
                    }
                }
            }
        }
				
		if ( same_flag == 1)
		{
			bflag = 1;
			if ( ptr-> length > cnt )
				result = word_cnt;
			else 
				result = word_cnt + 1;
		}

        word_cnt++;
    }

	if ( bflag == 0)
        result = word_cnt + 1;

    delete [] compare_word;
	delete [] target_word;
    return result;
}

void case_change(char * tempword, int cnt)
{
    for (int i =0; i < cnt ; i++)
    {
        if ( tempword[i] >= 'A' && tempword[i] <= 'Z')
            tempword[i] += 32;
    }
    return;
}


void print_word(Word * first)
{
		int first_flag = 0;
        Word * ptr;
        for(ptr = first; ptr != nullptr ; ptr=ptr->link)
        {
			if ( first_flag != 0)
				cout << ", ";				

            for( int i =0; i < ptr->length ; i++)
                cout << ptr->content[i];
			first_flag = 1;
        }
        cout << "\n";
        return;
}

bool check_exit( char * tempword)
{
        bool result = true;
        if( tempword[0] == 'e')
        {
            if(tempword[1] == 'x')
                if (tempword[2] == 'i')
                    if(tempword[3] == 't')
                        result = false;
        }
        else
            result = true;
        return result;
}
