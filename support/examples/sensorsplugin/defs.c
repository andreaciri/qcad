#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

void CheckAllocation (void *p, char *s)
{
  if (p == NULL)
  {
    fprintf(stderr,"Not enough memory to allocate %s!\n",s);
    exit(EXIT_MEMORY);
  }
}


int Round (double r)
{
  return (int) ( (r - (int) r > 0.5) ? ceil(r) + EPSILON : floor(r) + EPSILON );
}
