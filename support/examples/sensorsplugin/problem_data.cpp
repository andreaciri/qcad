#include "problem_data.hpp"




ProblemData *LoadData (int boundingBox[4][2])
{
    ProblemData *pPD;
    int r,c, m, i;

    int boxLenght = boundingBox[1][0] - boundingBox[0][0];
    int boxHeight = boundingBox[2][1] - boundingBox[1][1];
    int nr = boxLenght * boxHeight;
    int nc = boxLenght * boxHeight;

    int rows[nr][2]; // Demand centers: array of [x,y] coordinates
    int columns[nc][2]; // Facility sites: array of [x,y] coordinates

    m = 1;

    i = 0;
    for (int y = boundingBox[1][1]; y<= boundingBox[2][1]; y++){
        for (int x = boundingBox[0][0]; x<= boundingBox[1][0]; x++){
            rows[i][0] = x;
            rows[i][1] = y;
            columns[i][0] = x;
            columns[i][1] = y;
            i++;
        }
    }


    pPD = (ProblemData *) calloc(1,sizeof(ProblemData));

    pPD->nr = nr;
    pPD->nc = nc;
    pPD->nm = 1;


    pPD->card = (int *) calloc(pPD->nm+1,sizeof(int));
    pPD->card[1] = 4;

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


    for (m = 1; m <= pPD->nm; m++)
        for (c = 1; c <= pPD->nc; c++)
        {

//            pPD->Copertura[m][c] = (int *) calloc(cont+1,sizeof(int));






//            pPD->Copertura[m][c][0] = cont;
//            for (i = 0; i < cont; i++)
//            {
//                pPD->Copertura[m][c][i+1] = V[i];
//                pPD->row_deg[m][V[i]]++;
//            }
        }


    for (m = 1; m <= pPD->nm; m++)
        for (r = 1; r <= pPD->nr; r++)
            pPD->weight[m][r] = 1.0;


    for (c = 1; c <= pPD->nc; c++)
        pPD->b[c] = 1;


    pPD->bMax = -1;
    //for (c = 1; c <= pPD->nc; c++)
    //    if (pPD->b[c] > pPD->bMax) pPD->bMax = pPD->b[c];



    // set here pPD->card[m])


    pPD->wtot = 0.0;
    for (m = 1; m <= pPD->nm; m++)
        for (r = 1; r <= pPD->nr; r++)
            pPD->wtot += pPD->weight[m][r];

    return pPD;
}

