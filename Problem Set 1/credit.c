#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // to hold sums and digits
    int OddSum = 0; 
    int EvenSum = 0;
    int OddNumFirstDigit; 
    int EvenNumFirstDigit;
    // for counter
    int i = 0; 
    int j = 0;

    // gets large positive number
    long int CardNum = get_long("Number:  ");
    long int digitcounter = CardNum;
    while (CardNum > 9)
    {
        // for counting digits of user input
        while (digitcounter > 0)
        {
            digitcounter /= 10;
            j++;
        }
        // checks exact number of digits available
        int CredDigiCheck = j;
        j /= 2;
        int isolated[j];
        if (!(CredDigiCheck > 12) && !(CredDigiCheck < 17))
        {
            printf("INVALID\n");
        }
        else
        {
            // checks CardNum, isolates every other digit
            // divides by 10 to move to next numerical column
            while (CardNum > 0)
            {
                i++;
                int digit = CardNum % 10;
               
                if (i % 2 != 0)
                {
                    OddSum = OddSum + digit;
                    if (digit > 0 && digit < 10)
                    {
                        OddNumFirstDigit = digit;
                    }
                }
                    
                else
                {      
                    digit *= 2;
                    // forumla for beginning array at 0 for isolated numbers
                    isolated[(i / 2) - 1] = digit;
                    if (digit > 0 && digit < 20)
                    {
                        EvenNumFirstDigit = digit / 2;
                    }
                }
                CardNum /= 10;
            }
            
            // adds up all components of array
            // seperates large #'s into individual digits, adds them up
            for (int k = 0; k < j; k++)
            {
                if (isolated[k] > 9)
                {
                    EvenSum = EvenSum + (isolated[k] / 10) + (isolated[k] % 10);         
                }
                else
                {
                    EvenSum = EvenSum + isolated[k];
                }
            }         
            // for making final sum and checking its modulo
            int FinalSum = EvenSum + OddSum;
            if (FinalSum % 10 == 0)
            {
                if (CredDigiCheck == 15 && OddNumFirstDigit == 3 && (EvenNumFirstDigit ==                          4 || EvenNumFirstDigit == 7))
                {
                    printf("AMEX\n");
                }
                if (CredDigiCheck == 13 && OddNumFirstDigit == 4)
                {
                    printf("VISA\n");
                }
                if (CredDigiCheck == 16)
                { 
                    if (EvenNumFirstDigit == 5 && (OddNumFirstDigit == 1                                                || OddNumFirstDigit == 2 
                                                   || OddNumFirstDigit == 3                                            || OddNumFirstDigit == 4  || OddNumFirstDigit == 5))
                    {
                        printf("MASTERCARD\n");
                    }
                    if (EvenNumFirstDigit == 4)
                    {
                        printf("VISA\n");
                    }
                    else
                    {
                        printf("INVALID\n");
                    }
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            { 
                printf("INVALID\n");
            }
        }
    }
}
