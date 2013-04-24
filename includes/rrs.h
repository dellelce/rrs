/*
 * generate a random readable string
 *
 */

#ifndef __RRS_H
#define __RRS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _charweight
{
  char Ch;
  int  Type;
  int  Weight;
  int  Class;
};

#define T_VOWEL   1
#define T_CONS    2


#ifndef RRS_DEFAULT_STRINGSNO
#define RRS_DEFAULT_STRINGSNO 10
#endif

extern struct _charweight charweights[];

/* Protos */

char *random_readable_string (int targetweight, int stringsize);


/* we are doing a cgi program  

#define _CGI_

*/


#endif /* __RRS_H */
