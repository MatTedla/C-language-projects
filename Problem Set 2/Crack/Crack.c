// purpose of program "crack"; reverse engineering a printed password (max. 5 characters) from a hash input

#include <cs50.h>
#include <stdio.h>
#include <crypt.h>  
#include <string.h>

// declaration of small function "letter_bank"
char letter_bank(int i);
char num_bank(int n);

// defining the "main" function
int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string password = argv[1];
     
        int check = 1;
        string passwordCrypt = " ";
        string code = " ";
        int a = 0;
        int b = 0;
        int c = 0;
        int d = 0;
        int n = 0;

        // establishes key; making it static prevents local array from getting destroyed upon completion of the loop
        // currently, this string is 1 character long since a null appears after 1st character
        static char key[6];
        key[0] = letter_bank(0);
        key[1] = '\0'; 
        key[2] = '\0'; 
        key[3] = '\0'; 
        key[4] = '\0'; 
        key[5] = '\0';    
        
        static char salt[3];
        salt[0] = num_bank(0);
        salt[1] = num_bank(0);
        salt[2] = '\0'; 

        for (int i = 0; i <= 51; i++)
        {
            // establishing the first character of key before the next loop
            key[0] = letter_bank(i);
            // establishing the second character of salt before the next loop
            salt[1] = num_bank(0);
            
            // loops all possible combinations of salt for a given key string
            for (int j = 0; j <= 99; j++)
            {
                if ((j % 10 == 0) && (j > 0))
                {
                    salt[1] = num_bank(j / 10);
                    n = 0;
                }
                salt[0] = num_bank(n);
                
                // cast key variable as string to use crypt;correct string makes matching hash
                passwordCrypt = crypt((string) key, (string) salt);

                // compare passwordCrypt to hash argument;leaves loop when matching hash found 
                check = strcmp(password, passwordCrypt);  
                if (check == 0)
                {
                    break;
                }

                n++;
            }
            // resets counter for salt after cycling all combinations for a given key string
            n = 0;
            
            if (check == 0)
            {
                break;
            }
        

            // once 1 character reaches the end of alphabet, the next character is placed in the array; 
            // all characters then go back to the beginning of alphabet
            if (key[0] == letter_bank(51))
            {
                key[1] = letter_bank(a);
                key[0] = letter_bank(0);
                a = a + 1;
                i = -1;
            }
            if (key[1] == letter_bank(51))
            {
                key[2] = letter_bank(b);
                key[1] = letter_bank(0);
                key[0] = letter_bank(0);
                b = b + 1;
                a = 0;
                i = -1;
            }
            if (key[2] == letter_bank(51))
            {
                key[3] = letter_bank(c);
                key[2] = letter_bank(0);
                key[1] = letter_bank(0);
                key[0] = letter_bank(0);
                c = c + 1;
                b = 0;
                a = 0;
                i = -1;
            }
            if (key[3] == letter_bank(51))
            {
                key[4] = letter_bank(d);
                key[3] = letter_bank(0);
                key[2] = letter_bank(0);
                key[1] = letter_bank(0);
                key[0] = letter_bank(0);
                d = d + 1;
                c = 0;
                b = 0;
                a = 0;
                i = -1;
            }
            
            // loop breaks once the key string is "zzzzz"
            if (key[4] == letter_bank(51) && key[3] == letter_bank(51) && key[2] == letter_bank(51) && 
                key[1] == letter_bank(51) && key[0] == letter_bank(51))
            {
                break;
            }
        }
        
        // output in the events the check is successful or a failure
        if (check == 0)
        {
            code = (string) key;
            printf("%s\n", code);
            return 0;
        }
        if (check != 0)
        {
            printf("Usage: ./crack hash\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
}

// defining the smaller function "letter_bank"
char letter_bank(int i)
{
    // establishes alphabet 
    char alphabet[52];
    for (int k = 0; k < 26; k++)
    {
        alphabet[k] = 65 + k;
    }
    for (int l = 0; l < 26; l++)
    {
        alphabet[l + 26] = 97 + l;
    }
    return alphabet[i];
}

// defining the smaller function "num_bank"
char num_bank(int n)
{
    // establishes salt 
    char numbers[10];
    for (int m = 0; m < 10; m++)
    {
        numbers[m] = 48 + m;
    }
    
    return numbers[n];
}
