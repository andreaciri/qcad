#ifndef __problem_data_h
#define __problem_data_h

#include "defs.h"

struct _problemdata
{
  int nr;
  int nc;
  int nm;
  int ***Copertura; // Sparse vector including the indexes of the rows covered by each mode and column
                    // Copertura[m][c][0] provides the number of rows covered in mode m by column c
  double **weight;  // Weight in each mode of each row
  double wtot;      // Sum of all weights
  int *b;           // Maximum number of modes for each column
  int bMax;         // Maximum of all b[cj]
  int *card;        // Number of columns that can be used in each mode
  int **row_deg;    // Number of columns covering each mode-row
};

typedef struct _problemdata ProblemData;



ProblemData *LoadData (int boundingBox[4][2], int range);


#endif
