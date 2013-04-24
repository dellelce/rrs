/* 

   File:    main.c
   Created: 0117 240413

*/

// includes

#include <stdio.h>
#include "rrs.h"

// main

int
main (int argc, char **argv)
{
  // insert code here
  unsigned int v; 
  unsigned int len;

  if (argc < 2) { v = 6; } else { v = atoi(argv[1]); }
  if (argc < 3) { len = 10; } else { len = atoi(argv[2]); }

  printf("%s\n", random_readable_string (v, len));

  // generic return

  return 0;
}


// ** EOF **
