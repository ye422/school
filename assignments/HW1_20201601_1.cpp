
int main()
{
    int n;
    cin >> n;
    string * pstring = new string [n];
    
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
        
        addition = arabic_to_roman( add(num1, num2) );
        cout << pstring[str_count2] << " + " << pstring[str_count2 + 1];
        cout << "=" << addition << "\n";
        
        cout << num1 << " + " << num2 << "=" << add(num1,num2) <<"\n";
        
        str_count2 += 2;
        
    }
    
    
    
    return 0;
}

int roman_to_arabic(string roman)
{
    int result;
    int length = strlen(roman);
    for(int i = 0;i < length ;i++)
    {
        switch ( roman[i] )
        {
            case 'M':
                
            case 'D':
                
            case 'C':
                
            case 'L':
                
            case 'X':
            
            case 'V':
            
            case 'I':
            
            default: 
                cout << "Error\n";
                break;
        }
        
        
    }
    
    
    
    return result;
}

string arabic_to_roman(int arabic)
{
    string result;
    return result;
}

int add(int n1, int n2)
{
    int result = 0;
    
    return result;
}