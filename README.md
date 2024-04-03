# rrs

Random Readable Strings

This is some old code I used years ago to generate readable strings.

* The weight concept could be reused in graphics & other areas.

TODO:
* Improve randomness.
* Add password-mode: for example: generate multiple strings separated by hyphen or similar.

NOTES:
* targetweight (first argument of rrstest) less then 6 can generate endless loops.

EXAMPLE:

```bash

$ make
CC src/main.c
CC src/rrs.c
LINK  rrstest
$ make run
irredelref
$ make run
ihoberlumu
```
