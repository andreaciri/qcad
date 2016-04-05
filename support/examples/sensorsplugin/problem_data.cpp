#include <math.h>
#include "problem_data.hpp"


ProblemData *LoadData (int boundingBox[4][2], QVector<int> range, QVector<int> cost, bool onlyCandidates, QList<RVector> candidates, QList<Room> rooms)
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
    int nt = range.length();
    int nr = locations.length();
    int nc;
    int truenc;
    if (onlyCandidates){
        truenc = candidates.length();
    }
    else {
        truenc = nr;
    }

    pPD = (ProblemData *) calloc(1,sizeof(ProblemData));

    nc = truenc * nt;
    pPD->nr = nr;
    pPD->nc = nc;
    pPD->truenc = truenc;
    pPD->nm = 1;
    pPD->nt = nt;

    pPD->rows = (int **) calloc(pPD->nr+1,sizeof(int *));
    pPD->columns = (int **) calloc((pPD->nc+1),sizeof(int *));
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
        i=0;
        for (c = 0; c < candidates.length(); c++){
            pPD->columns[c+1][0] = candidates[i].getX();
            pPD->columns[c+1][1] = candidates[i].getY();
            i++;
            if(i >= candidates.length()){
                i=0;
            }
        }
    }

    else{
        //No candidates from user so rows and columns are the entire locations set
        i=0;
        for (r = 1; r <= pPD->nr; r++)
        {
            pPD->rows[r] = (int *) calloc(2,sizeof(int));
            pPD->rows[r][0] = locations[i][0];
            pPD->rows[r][1] = locations[i][1];
            i++;
        }
        i=0;
        for(c = 1; c <= pPD->nc; c++){
            pPD->columns[c] = (int *) calloc(2,sizeof(int));
            pPD->columns[c][0] = locations[i][0];
            pPD->columns[c][1] = locations[i][1];
            i++;
            if(i >= locations.length()){
                i=0;
            }
        }
    }



    pPD->card = (int *) calloc(pPD->nm+1,sizeof(int));
    pPD->card[1] = 10;

    pPD->b = (int *) calloc(pPD->nc+1,sizeof(int));
    pPD->b[1] = 1;

    pPD->weight = (double **) calloc(pPD->nt+1,sizeof(double *));

    for (int t = 1; t <= pPD->nt; t++)
    {
        pPD->weight[t] = (double *) calloc(pPD->nr+1,sizeof(double));

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
    int currentType;
    for (m = 1; m <= pPD->nm; m++)
        for (c = 1; c <= pPD->nc; c++)
        {
            currentType = ((c-1) - ((c-1) % truenc)) / truenc;
            count = 0;
            for (r = 1; r <= pPD->nr; r++){

                if (distance(pPD->columns[c], pPD->rows[r]) <= range[currentType]){
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

    for (int t = 1; t <= pPD->nt; t++)
        for (r = 1; r <= pPD->nr; r++)
            pPD->weight[t][r] = (1/cost[t-1]);

    for (c = 1; c <= pPD->nc; c++)
        pPD->b[c] = 1;

    pPD->bMax = -1;
    //for (c = 1; c <= pPD->nc; c++)
    //    if (pPD->b[c] > pPD->bMax) pPD->bMax = pPD->b[c];


    pPD->wtot = 0.0;
    for (int t = 1; t <= pPD->nt; t++)
        for (r = 1; r <= pPD->nr; r++)
            pPD->wtot += pPD->weight[t][r];

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

  for (int t = 1; t <= (*pPD)->nt; t++)
    free((*pPD)->weight[t]);
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
