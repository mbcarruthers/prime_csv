#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmalloc.h"

/*
 *  Basic CSV parsing to read prime number and test is_prime
 */
#define SIZE 512

static unsigned long lbuffer[SIZE] = {0};


unsigned int is_digit(char * str) {
    return (*str >= '0' && *str <= '9') ? 1 : 0;
}

void mcpy__(void * dest, void * src, size_t len) {
    unsigned char * dest__ = (unsigned char*)(dest);
    const unsigned char * src__ = (const unsigned char*)(src);
    while(len--) {
        *dest__++ = *src__++;
    }
}

// is_prime
unsigned int is_prime(unsigned long value) {
    if(value <= 1) {
        return 0;
    }
    if(value <=3) {
        return 1;
    } else if(value % 2 == 0 || value % 3 == 0) {
        return 0;
    } else {
        for(int i = 5; i * i <= value;i+=6) {
            if(value % i == 0 || value % (i+2) == 0)
                return 0;
        }
        return 1;
    }
}


// takes all primes from file and transers them to a
// buffer of unsigned long values
void parse_csv(unsigned long * dest, char * src, size_t len)
{

   size_t count = 0;
   const char * curr = src;

   while(*curr != '\n' && count < len) {
       size_t reject = strcspn(curr, ",");
       if(reject == 0) {
           curr++;
           continue;
       }
       dest[count] = strtoul(curr, NULL, 10);

       printf("Is %lu prime? %s", dest[count], // todo remove
              ((is_prime(dest[count])) ? ("true\n") : ("false\n")));

       count++;
       curr += reject;
       if(*curr == ',')
           curr++;
       else if(*curr == EOF || *curr == '\0')
           return;
   }
}



int main(int argc , char ** argv)
{
  if(argc > 2) {
      fprintf(stderr, "error: pass a file in \n");
      return EXIT_FAILURE;
  }

  FILE * fp = fopen(argv[1], "r");

  if(fp == NULL) {
      fprintf(stderr, "error opening file \n");
      fprintf(stderr, "%s \n", argv[1]);
      return 1;
  }

  char buffer[SIZE] = {0}; // may as well be static too


  while(fgets(buffer, SIZE, fp)) {
      parse_csv(lbuffer, buffer, SIZE);
  }

  fclose(fp);
  printf("Program finished \n");
  return EXIT_SUCCESS;
}
