#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//Convert a number from decimal to Binary

void decimalToBinary(int number, char* bits)
{
 
  int index = 0;
  int result = number;

  while(result != 0)
  {
    // divide by 2 
    int remainder = result % 2;
    //If remainder then set a bit in output Binary Bits Array
    if (remainder > 0)

        bits[index] = '1';

    //Setup for next binary bits, div here
    result = result/2;

    ++index;
  }
}
  /*
      Clear the Binary Bits to all 0's'
  */
  void clearBinaryBits(char* bits)
  {
    decimalToBinary(0, &bits[0]);
  }
  /*
      Display array of 32 Bits to the console.
  */
  void printBinary(char* bits)
  {
    //Print all Binary Bits 
    for(int x = 31; x >= 0; --x)
    {
      printf("%c", bits[x]);
    }
    printf("\n");
  }
  /*
      Convert number from Decimal to Binary and Print the Binary to console
  */
  void convertPrintBinary(int number, char* bits)
  {
    clearBinaryBits(&bits[0]);
    decimalToBinary(number, &bits[0]);
    printBinary(&bits[0]);
  }

/**
Main program to work with decimal, 
Binary
Hexadecimal number systems
@return 0 if OK else non zero
*/
int main(int argc, const char * argv[])
{
  int number = 0;
  bool ok = false;
  char bits[32] = {
                    '0','0','0','0','0','0','0','0',
                    '0','0','0','0','0','0','0','0',
                    '0','0','0','0','0','0','0','0',
                    '0','0','0','0','0','0','0','0'
                  };

  // Prompt user for a number between 0 and 1000
  while(!ok)
  {
    printf("\n Please choose a number between 0 - 1000:  ");
    scanf("%d", &number);
    if(number < 0|| number > 1000)
    {
      //wrong input recieved 
      printf("Please choose numbers between 0 and 1000\n");
    }
    else
    {
      ok = true;
    }
  }
  //Display number as a 32 bit binary number
  printf("The number in binary is: ");
  convertPrintBinary(number, &bits[0]);

  //Display the number as a 32 bit hexadecimal number
  printf("The number in hexadecimal is 0x%08X\n", number);

  //shift the number 10 bits to the left, mask out the lower 10 bits, and or in the number 0x03FF
  int result = ((number << 10) & 0xFFFFFC00) | 0x03FF;

  //Display the result in decimal, binary and Hexadecimal
  printf("The result in decimal is: %d\n", result);
  printf("The result in hexadecimal is: 0x%08X\n", result);
  printf("The result in binary is:");
  convertPrintBinary(result, &bits[0]);

  //Return OK
  return 0;
}