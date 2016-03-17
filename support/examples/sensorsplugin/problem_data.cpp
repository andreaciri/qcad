#include <math.h>
#include "problem_data.hpp"


ProblemData *LoadData (int boundingBox[4][2], int range, bool onlyCandidates, QList<RVector> candidates, QList<Room> rooms)
{
    ProblemData *pPD;
    int r,c, m, i;
    int *V;
    int count;
    QVector<QVector <int> > locations;
    QVector<int> coo;

    for (int y = boundingBox[1][1]; y<= boundingBox[2][1]; y++){
        for (int x = boundingBox[0][0]; x<= boundingBox[1][0]; x++){
            // For each point in the bounding box

            for(i = 0; i < rooms.length(); i++){
                if(rooms[i].isInside(x, y)){
                    coo = QVector<int>() << x << y;
                    locations.append(coo);
                    break;
                }
            }
        }
    }

    int nr = locations.length();
    int nc;
    if (onlyCandidates){
        nc = candidates.length();
    }
    else {
        nc = nr;
    }

    pPD = (ProblemData *) calloc(1,sizeof(ProblemData));

    pPD->nr = nr;
    pPD->nc = nc;
    pPD->nm = 1;

    pPD->rows = (int **) calloc(pPD->nr+1,sizeof(int *));
    pPD->columns = (int **) calloc(pPD->nc+1,sizeof(int *));
    if(onlyCandidates){
        //User wants a solution only from the specified candidates sites
        for (r = 1; r <= pPD->nr; r++)
        {
            pPD->rows[r] = (int *) calloc(2,sizeof(int));
        }
        for (c = 1; c <= pPD->nc; c++)
        {
            pPD->columns[c] = (int *) calloc(2,sizeof(int));
        }

        r = 1;
        for(i = 0; i < locations.length(); i++){
            pPD->rows[r][0] = locations[i][0];
            pPD->rows[r][1] = locations[i][1];
            r++;
        }

        for (c = 0; c < candidates.length(); c++){
            pPD->columns[c+1][0] = candidates[c].getX();
            pPD->columns[c+1][1] = candidates[c].getY();
        }
    }

    else{
        //No candidates from user so rows and columns are the entire locations set
        for (r = 1; r <= pPD->nr; r++)
        {
            pPD->rows[r] = (int *) calloc(2,sizeof(int));
            pPD->columns[r] = (int *) calloc(2,sizeof(int));
        }
        r = 1;
        for(i = 0; i < locations.length(); i++){
            pPD->rows[r][0] = locations[i][0];
            pPD->rows[r][1] = locations[i][1];
            pPD->columns[r][0] = locations[i][0];
            pPD->columns[r][1] = locations[i][1];
            r++;
        }
    }



    pPD->card = (int *) calloc(pPD->nm+1,sizeof(int));
    pPD->card[1] = 10;

    pPD->b = (int *) calloc(pPD->nc+1,sizeof(int));
    pPD->b[1] = 1;

    pPD->weight = (double **) calloc(pPD->nm+1,sizeof(double *));

    for (m = 1; m <= pPD->nm; m++)
    {
        pPD->weight[m] = (double *) calloc(pPD->nr+1,sizeof(double));

    }

    pPD->Copertura = (int ***) calloc(pPD->nm+1,sizeof(int **));

    for (m = 1; m <= pPD->nm; m++)
    {
        pPD->Copertura[m] = (int **) calloc(pPD->nc+1,sizeof(int *));

    }

    pPD->row_deg = (int **) calloc(pPD->nm+1,sizeof(int *));

    for (m = 1; m <= pPD->nm; m++)
    {
        pPD->row_deg[m] = (int *) calloc(pPD->nr+1,sizeof(int));
    }

    // V: temporary array that holds covered centers
    V = (int *) calloc(pPD->nr+1,sizeof(int));

    for (m = 1; m <= pPD->nm; m++)
        for (c = 1; c <= pPD->nc; c++)
        {
            count = 0;
            for (r = 1; r <= pPD->nr; r++){

                if (distance(pPD->columns[c], pPD->rows[r]) <= range){
                    // Position r is covered by forniture c
                    // cont = number of positions covered by c in mode m
                    V[count] = r;
                    count++;
                }
            }
            pPD->Copertura[m][c] = (int *) calloc(count+1,sizeof(int));
            pPD->Copertura[m][c][0] = count;

            for (i = 0; i < count; i++)
            {
                pPD->Copertura[m][c][i+1] = V[i];
                pPD->row_deg[m][V[i]]++;
            }
        }

    free(V);

    for (m = 1; m <= pPD->nm; m++)
        for (r = 1; r <= pPD->nr; r++)
            pPD->weight[m][r] = 1.0;

    for (c = 1; c <= pPD->nc; c++)
        pPD->b[c] = 1;

    pPD->bMax = -1;
    //for (c = 1; c <= pPD->nc; c++)
    //    if (pPD->b[c] > pPD->bMax) pPD->bMax = pPD->b[c];


    pPD->wtot = 0.0;
    for (m = 1; m <= pPD->nm; m++)
        for (r = 1; r <= pPD->nr; r++)
            pPD->wtot += pPD->weight[m][r];

    return pPD;
}

double distance(int p1[2], int p2[2]){
    return sqrt(pow((p2[0] - p1[0]), 2) + (pow((p2[1] - p1[1]), 2)));
}


void DestroyProblemData (ProblemData **pPD)
{
  int m, c;

  free((*pPD)->b);
  free((*pPD)->card);

  for (m = 1; m <= (*pPD)->nm; m++)
    free((*pPD)->weight[m]);
  free((*pPD)->weight);

  if ((*pPD)->row_deg != NULL)
  {
    for (m = 1; m <= (*pPD)->nm; m++)
      free((*pPD)->row_deg[m]);
    free((*pPD)->row_deg);
  }

  for (m = 1; m <= (*pPD)->nm; m++)
  {
    for (c = 1; c <= (*pPD)->nc; c++)
      free((*pPD)->Copertura[m][c]);
    free((*pPD)->Copertura[m]);
  }
  free((*pPD)->Copertura);
  free(*pPD);
  *pPD = NULL;
}
