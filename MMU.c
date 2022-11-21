#include <stdlib.h>

#include <stdio.h>

#include <unistd.h>

#include <errno.h>

#include <signal.h>

#include <semaphore.h>

#include <pthread.h>

#include <sys/mman.h>

#include <stdbool.h>

#include <string.h>



int GetPageSizeFromUser(void);

int InitializePageTable(int pageSize);

int GetVirtualAddressFromUser(void);



#define PHYSICAL_RAM_SIZE (512 * 1024)

#define NUM_4K_PAGES (PHYSICAL_RAM_SIZE / 4096)

#define NUM_8K_PAGES (PHYSICAL_RAM_SIZE / 8192)



int pageTable_4kPages[NUM_4K_PAGES];

int pageTable_8kPages[NUM_8K_PAGES];





int main(int argc, const char * argv[])

{


  int pageSize;

  int userEnteredVirtualAddress;

     

  pageSize = GetPageSizeFromUser();



  InitializePageTable(pageSize);



  userEnteredVirtualAddress = GetVirtualAddressFromUser();



  printf("0x%08X is in page %d\n", userEnteredVirtualAddress, userEnteredVirtualAddress >> 12);



  


  return 0;

}

int GetPageSizeFromUser(void)

{

  int pageSize;
  //int pageSize = 4096;
  printf("Enter page size: ");
  scanf("%d", &pageSize);

  char binaryPageSize[33]; // 32 character plus null termination

  memset(&binaryPageSize, 0, sizeof(binaryPageSize)); // If you do not put a null character in at least the first location, strcat will not work right



  for (int currentBit = 0; currentBit < 32; currentBit++) //Looping until we hit the end of the number

  {

   

    if ((pageSize >> (32 - currentBit)) & 0x1)

    {

      strcat(binaryPageSize,"1");

    }

    else

    {

      strcat(binaryPageSize,"0");

    }

  }



  printf("Page size = %d\n", pageSize);

  printf("Page size (binary) = %s\n", binaryPageSize);

   

  return pageSize;

}



int GetVirtualAddressFromUser(void)

{

  int vAddress = 0x2345;
 
  return vAddress;

  

}

int InitializePageTable(int pageSize)

{

  printf("page size passed in = %d\n", pageSize);

  int maxPages = NUM_4K_PAGES;

  for (int i = 0; i < maxPages; ++i)

  {

    int physicalRamPageBaseAddress;

    physicalRamPageBaseAddress = i * pageSize;

    pageTable_4kPages[i] = physicalRamPageBaseAddress;

    printf("pageTable_4kPages[%d] = 0x%08X\n", i, pageTable_4kPages[i]);

  }



}