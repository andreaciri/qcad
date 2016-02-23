#ifndef __defs_h
#define __defs_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#define MW
#ifdef MW
#include "memwatch-2.71\memwatch.h"
#endif

#define EXIT_SUCCESS          0
#define EXIT_WRONGCOMMANDLINE 1
#define EXIT_MEMORY           2
#define EXIT_OPENFILE         3
#define EXIT_INCONSISTENCY    4

#define NAME_LENGTH 256
#define ROW_LENGTH  256

#define INFINITE 100000000.0
#define EPSILON 1E-8

//#ifndef boolean
//typedef enum _boolean boolean;
//enum _boolean {FALSE = 0, TRUE = 1};
//#endif

// #ifndef min
// #define min(x, y) ((x) < (y) ? (x) : (y))
// #endif

// #ifndef max
// #define max(x, y) ((x) < (y) ? (x) : (y))
// #endif


void CheckAllocation (void *p, char *s);

int Round (double r);

#endif
