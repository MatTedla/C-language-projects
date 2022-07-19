#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{ 
    // specifies that there must be two strings, 1st the program name, 2nd the keyword
    if (argc == 2)
    {
        // declare array representing the shift values of the keyword
        int n = strlen(argv[1]);
        int key[n];
        
        // loops as many times as there are characters in the keyword string
        for (int i = 0; i < n; i++)
        {
            // converting a character into an integer by using circle brackets to surround the data type you'd like to convert to
            // also known as casting
            int c = (int) argv[1][i];
            if (c < 65 || (c > 90 && c < 97) || c > 122)
            {
                // program error message
                printf("Usage: ./vigenere keyword\n");
                return 1;
                break;
            }
            // converts numbers in the key to the appropriate shift value
            if (c >= 65 && c <= 90)
            {
                c = c - 65;
            }
            else if (c >= 97 && c <= 122)
            {
                c = c - 97;
            }
            key[i] = c;
        }
        
        // prompt user input
        string s = get_string("plaintext: ");
        int o = strlen(s);
        if (o < 1)
        {
            return 1;
        }
        // declare necessary variables
        char ciphertext[o];
        int keycounter = 0;

        // implement numerical values of keyword into string input
        for (int counter = 0; counter < o; counter++)
        {
            // skips spaces
            if (s[counter] < 65 || s[counter] > 122 || (s[counter] > 90 && s[counter] < 97))
            {
                if (counter == 0)
                {
                    printf("ciphertext: ");
                }
                printf("%c", s[counter]);
                if (counter + 1 == o)
                {
                    break;
                }
            }
            else
            {
                // assigns integer equivalent of character in string
                int plaintext = (int) s[counter]; 
                // encryption of plaintext with key
                int cipher = plaintext + key[keycounter];

                // check for inappropriate character changes
                if ((plaintext > 64 && plaintext < 91 && cipher > 90) ||
                    (plaintext > 97 && plaintext < 123 && cipher > 122))
                {
                    cipher = cipher - 26;
                }
                // prints the word "ciphertext"
                if (counter == 0)
                {
                    printf("ciphertext: ");
                }
                // prints cipher
                ciphertext[counter] = (char) cipher;
                printf("%c", ciphertext[counter]);

                // counter resets
                if (keycounter == n - 1)
                {
                    keycounter = 0;
                }
                else
                {
                    keycounter++;
                }
            }
        }
        printf("\n");
    }
    else
    {
        // program error message
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }  
}
