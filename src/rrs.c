/*
 * generate a random readable string
 *
 */

#include "rrs.h"

#ifndef LOCAL_RRS_BUFFER_SIZE
#define LOCAL_RRS_BUFFER_SIZE 256
#endif /* LOCAL_RRS_BUFFER_SIZE */

struct _charweight charweights [] =
  {
//                           Weight  Class
    {'a', 	T_VOWEL, 	-5,	1},
    {'b', 	T_CONS, 	 5,	6},
    {'c', 	T_CONS, 	 5,	5},
    {'d', 	T_CONS, 	 5,	7},
    {'e', 	T_VOWEL, 	-4,	1},
    {'f', 	T_CONS, 	 5,	9},
    {'g', 	T_CONS, 	 4,	5},
    {'h', 	T_CONS, 	 3,	10},
    {'i', 	T_VOWEL, 	-3,	1},
    {'j', 	T_CONS, 	 5,	5},
    {'k', 	T_CONS, 	 5,	5},
    {'l', 	T_CONS, 	 1,	4},
    {'m', 	T_CONS, 	 3,	3},
    {'n', 	T_CONS, 	 1,	3},
    {'o', 	T_VOWEL, 	-4,	1},
    {'p', 	T_CONS, 	 5,	6},
    {'q', 	T_CONS, 	 5,	5},
    {'r', 	T_CONS, 	 1,	4},
    {'s', 	T_CONS, 	 3,	8},
    {'t', 	T_CONS, 	 4,	7},
    {'u', 	T_VOWEL, 	-3,	1},
    {'v', 	T_CONS, 	 5,	9},
    {'w', 	T_CONS, 	 4,	2},
    {'x', 	T_CONS, 	 8,	2},
    {'y', 	T_CONS, 	 6,	2},
    {'z', 	T_CONS, 	 6,	8}
  };

/* Description of the 'ClassWeight' column:

   Class is the type of character:

   0.  'null' class - start of word
   1.   a, e, i, o, u - vowels
   2.   w, y, x
   3.   m, n
   4.   r, l
   5.   c, k, g, j, q
   6.   p, b
   7.   t, d
   8.   s, z
   9.   f, v
   10.  h

  Relationship matrix (BASE)

   xxx    | null    vowels   w-x    c-q    p-b    t-d    s-z    f-v    h
   -------+
   vowels     0      1        -2     -1     0      0     -1     -1     0
   w-x        8      1         5      5     x      x      x      x     5
   c-q       10      x         x      x     x      x      x      x     5
   p-b        9      x         x      x     x      x      x      x     5
   t-d        9      x         x      x     x      x      x      x     5
   s-z        2      x         x      x     x      x      x      x     5
   f-v        5      x         x      x     x      x      x      x     5
   h          1      x         x      x     x      x      x      x     7
*/

/*
 * Generate real random character
 */

int urandom_int()
{
  int fd;
  int randomValue = 0;
  int maxTry = 128;
  ssize_t result;

  fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0) return 0;

  while (randomValue == 0)
  {
    result = read(fd, &randomValue, sizeof(randomValue));

    // Failed: just close and return 0
    if (result < 0) { close(fd); return 0; }

    // this will never happen... but just in case...
    maxTry -= 1;
    if (maxTry == 0) { close(fd); return 0; }
  }

  close(fd);

  return randomValue;
}

/*
 * Generate a random character
 */
static unsigned long SeedStatus;
static unsigned long T;

int
yasgr_randomchar (void)
{
  if (SeedStatus == 0 || (SeedStatus % 9) == 0)
  {
    srandom(urandom_int());
  }

  SeedStatus += 1;

  /* yet another stupid random generator - YASGR ! */
  T += random() - ((random() & 0xFFFFL) << 8) + (time(0) & 0xFFL) +
       ((time(0) & 0x01FFF000) >> 12);

  T = ((T & 0x00FFL) + ((T & 0xFF00L) >> 8) - 1) % 26;

  return T;
}

/*
 * Use randomchar() to generate a pseudo-random string
 *
 */
char *
random_readable_string (int targetweight, int stringsize)
{
  int  Cnt        = stringsize; /* stringsize might be used directly */
  int  BufCnt     = 0;
  int  weight     = 5; // initial weight: higher to avoid double consonants at beginning
  int  conscnt    = 0;
  int  vowelcnt   = 0;
  int  oldweight;
  int  Container;

  static char Buf[LOCAL_RRS_BUFFER_SIZE];

  if (Cnt == 0) Cnt = 10;
  if (Cnt > sizeof (Buf)) Cnt = sizeof (Buf);

  while (Cnt)
  {
     Container = yasgr_randomchar();

     /* Save weight and calculate new weight */

     oldweight = weight;
     weight += charweights[Container].Weight;

     /* Check if the coin would add an acceptable weight
        if not we keep the previous weight
      */

     if ((weight > targetweight) || (weight <= 0))
     {
        weight = oldweight;
        continue;
     }

      /* check if it we already have three consonants or vowels */

     if ((charweights[Container].Type) == T_VOWEL)
     {
        conscnt = 0;

        /* we don't allow more than 2 vowels */
        if (vowelcnt == 2) continue;

        vowelcnt += 1;
     }
     else
     {
        vowelcnt = 0;

	/* already enough consonants -- keep looking */
        if (conscnt == 2) continue;

        conscnt += 1;
     }

     Buf[BufCnt]   = charweights[Container].Ch;
     Buf[BufCnt+1] = 0;

     BufCnt += 1;
     Cnt -= 1;
  }

  return Buf;
}


/* EOF */
