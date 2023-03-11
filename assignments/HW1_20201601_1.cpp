#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;

int roman_to_arabic(string str);
string arabic_to_roman(int arabic);

int romancheck = 0;

int main()
{
    int n;
    cin >> n;
    string * pstring = new string [n * 2];

    int str_count = 0;
    for(int i = 0; i < n; i++)
    {

        cin >> pstring[str_count];
        str_count++;
        cin >> pstring[str_count];
        str_count++;
    }

    int str_count2 = 0;
    for(int i = 0; i < n; i++)
    {
        string addition;
        int num1 = roman_to_arabic( pstring[str_count2] );
        int num2 = roman_to_arabic( pstring[str_count2 + 1] );
        
        if(romancheck == 1)
        {
            cout << "Error. (Not a roman number)\n";
            break;
        }
        
        addition = arabic_to_roman( num1 + num2 );
        cout << pstring[str_count2] << "+" << pstring[str_count2 + 1];
        cout << "=" << addition << "\n";

        cout << num1 << "+" << num2 << "=" << num1 + num2 <<"\n";

        str_count2 += 2;

    }

	delete [] pstring;

    return 0;
}

int roman_to_arabic(string roman)
{
    int result = 0;
    int length = roman.length();
    int * arabic = new int [length];
    
        for(int i = 0;i < length ;i++)
        {
            switch ( roman[i] )
            {
                case 'M':
                    arabic[i] = 1000;
                    break;
                case 'D':
                    arabic[i] = 500;
                    break;
                case 'C':
                    arabic[i] = 100;
                    break;
                case 'L':
                    arabic[i] = 50;
                    break;
                case 'X':
                    arabic[i] = 10;
                    break;
                case 'V':
                    arabic[i] = 5;
                    break;
                case 'I':
                    arabic[i] = 1;
                    break;

                default:
                    romancheck = 1;
                    break;
            }
        }    
    if(romancheck == 1)
        return 0;
    

    for(int i = 0; i < length - 1 ; i++)
    {
        if( arabic[i] < arabic[i+1])
                result -= arabic[i];
        else result += arabic[i];
    }
    result += arabic[length - 1]; 

	delete[] arabic; 
	
    return result;
}

string arabic_to_roman(int arabic)
{
    string result = "";
    int digit[4] = {0};
    int i = 3;

    while( arabic > 0 )
    {
        digit[i] = arabic % 10;
        arabic = arabic / 10;

        i--;
    }

    if (digit[0] == 1) result += "M";

    if (digit[1] == 9) result += "CM";
    else if (digit[1] == 4) result += "CD";
    else if (digit[1] == 5) result += "D";
    else if (digit[1] > 5) 
    {    
        result += "D";
        for(int j = 0; j < digit[1] - 5;j++ )
            result += "C";
            
    } 
    else 
        for(int j = 0; j < digit[1];j++ )
            result += "C";
    
        


    if (digit[2] == 9) result += "XC";
    else if (digit[2] == 4) result += "XL";
    else if (digit[2] == 5) result += "L";
    else if (digit[2] > 5) 
    {    
        result += "L";
        for(int j = 0; j < digit[2] - 5;j++)
            result += "X";
    }        
    else 
        for(int j = 0; j < digit[2];j++)
            result += "X";
    
    if (digit[3] == 9) result += "IX";
    else if (digit[3] == 4) result += "IV";
    else if (digit[3] == 5) result += "V";
    else if (digit[3] > 5)
    {    
        result += "V";
        for( int j = 0; j < digit[3] - 5; j++)
            result += "I";
            
    }
    else 
        for( int j = 0; j < digit[3]; j++)
            result += "I";
        

    return result;
}

