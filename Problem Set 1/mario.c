// users inputs integer from 1 to 8, outputs a pyramid of height equal to input

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    while(true)
    {  
	// takes height of pyramid
        int pyramid = get_int("Height: ");

	// checks height of pyramid
        if (pyramid >= 1 && pyramid <= 8)
        {
	    // counts number of repetitions based on height of pyramid, also initializes pyramidnumber
            for (int counter = 1; counter <= pyramid; counter++)
            {
                int pyramidnumber = pyramid - counter;
		
		// counts number of # necessary, also re-initializes pyramidnumber, also uses patch for 2nd & 3rd repeats
                for (int repeats = 1; repeats <= counter; repeats++)
                {
		    // counts number of spaces necessary
                    for(int spacerepeats = 1; spacerepeats <= pyramidnumber; spacerepeats++)
                    {
                        printf(" ");
                    }
                    printf("#");
                    pyramidnumber = pyramidnumber - counter - 1;
                    if (counter == 2 || counter == 3)
                    {
                        pyramidnumber = pyramidnumber + counter - 5;
                    }
                }
                printf("\n");
            }
                break; 
        }
        else
        {
            printf("");
        }
    }
}
