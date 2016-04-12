#include <boost/unordered_set.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <QMenuBar>

#include "problem_data.hpp"
#include "RMainWindowQt.h"
#include "defs.h"
#include "types.hpp"
#include "util.hpp"
#include "moves.hpp"
#include "solution.hpp"
#include "heuristic.hpp"
#include "greedy.hpp"
#include "localsearch.hpp"

using namespace std;
using namespace boost;



void ConfigureParameters (HeuristicParam *pHP, int nc);
solution shaking(solution& sol, int k, int mIn);
void VNS (solution& sol, ProblemData& ins, int kMin, int kMax, int kDelta, int MaxRestart,
          int MaxIter, bool FirstBest, int& bestIter, int& bestRestart, int& kBest,
          int& totRestart, int& totalIter, double timeout);


solution vnsheuristic(ProblemData& ins)
{
    HeuristicParam HP;
    long start, end;
    double tempo;
    int totIter, bestIter;
    int totRestart, bestRestart;
    int m, kBest;
    double MaxTime;


    ConfigureParameters(&HP, ins.nc);
    MaxTime = HP.MaxTime;

    solution sol(ins);


    if (HP.kMax < 0)
    {
        HP.kMax = ins.nc;
        for (m = 1; m <= ins.nm; m++)
            if (HP.kMax > ins.card[m]) HP.kMax = ins.card[m];
    }

    qDebug("Greedy: ");
    start = clock();
    greedy(sol,nullostream);

    end = clock();
    tempo = (double) (end-start)/ (double)CLOCKS_PER_SEC;
    MaxTime -= tempo;
    //assert(isFeasible(ins,sol.sparseMC,sol.cost,true));
    qDebug("Obj= %8ld Iter= %8d Uncov= %8d Time= %8.3lf\n",(long) sol.cost,sol.sparseMC.size(),sol.uncoveredMR.size(),tempo);

    if(ins.technique == 1){
        return sol;
    }

    qDebug("LS    : ");
    start = clock();
    localsearch(sol,totIter,HP.FirstBest,MaxTime);
    end = clock();
    tempo = (double) (end-start)/ (double)CLOCKS_PER_SEC;
    MaxTime -= tempo;
    //assert(isFeasible(ins,sol.sparseMC,sol.cost,true));
    qDebug("Obj= %8ld Iter= %8d Uncov= %8d Time= %8.3lf\n",(long) sol.cost,totIter,sol.uncoveredMR.size(),tempo);
    //sol.print();

    qDebug("VNS   : ");
    bestIter = bestRestart = 0;
    start = clock();
    VNS(sol,ins,HP.kMin,HP.kMax,HP.kDelta,HP.MaxVNSRestarts,HP.MaxIter,HP.FirstBest,bestIter,bestRestart,kBest,totRestart,totIter,MaxTime);
    end = clock();
    tempo = (double) (end-start)/ (double)CLOCKS_PER_SEC;
    //  assert(isFeasible(ins,sol.sparseMC,sol.cost,true));

    qDebug("Obj= %8ld Iter= %8d Restart= %8d Uncov= %8d Time= %8.3lf iBest= %8d rBest= %8d kBest= %8d\n",
           (long) sol.cost,totIter,totRestart,sol.uncoveredMR.size(),tempo,bestIter,bestRestart,kBest);

    return sol;
}




solution shaking(solution& sol, int k, int mIn)
{
    int m, m2, c, contadd, contdel, kShake, i;
    int *AddCol, *DelCol;
    MC MCcol(0,0);

    AddCol = new int[sol.ins.nc+1];
    DelCol = new int[sol.ins.nc+1];

    for (m2 = mIn; m2 < mIn + sol.ins.nm; m2++)
    {
        m = (m2 > sol.ins.nm ? m2-sol.ins.nm : m2);

        contadd = contdel = 0;
        for (c = 1; c <= sol.ins.nc; c++)
            if (sol.denseMC[m][c] == true)
                DelCol[++contdel] = c;
            else if ((int) sol.cMode[c].size() < sol.ins.b[c])
                AddCol[++contadd] = c;

        kShake = k;
        if (kShake > contadd) kShake = contadd;
        if (kShake > contdel) kShake = contdel;

        //destroying phase
        for (i = 1; i <= kShake; ++i)
        {
            int pos = runiform(1,contdel);
            c = DelCol[pos];
            DelCol[pos] = DelCol[contdel];
            contdel--;

            MCcol.mode = m;
            MCcol.column = c;
            makeDelMove(sol,MCcol);
        }

        //constructing phase
        for (i = 1; i <= kShake; ++i)
        {
            int pos = runiform(1,contadd);
            c = AddCol[pos];
            AddCol[pos] = AddCol[contadd];
            contadd--;

            MCcol.mode = m;
            MCcol.column = c;
            makeAddMove(sol,MCcol);
        }
    }

    delete[] AddCol;
    delete[] DelCol;

    return sol;
}


void VNS (solution& sol, ProblemData& ins, int kMin, int kMax, int kDelta, int MaxRestart,
          int MaxIter, bool FirstBest, int& bestIter, int& bestRestart, int& kBest,
          int& totRestart, int& totalIter, double timeout)
{
    int k;
    int iter, iterLS;
    int mIn;
    solution bestSolution(ins);
    long start;


    bestSolution = sol;

    mIn = 1;
    iter = 0;
    k = kMin;
    kBest = 0;
    totRestart = 0;
    start = clock();
    while ( (totRestart < MaxRestart) && (iter < MaxIter) && ((double) (clock()-start)/ (double)CLOCKS_PER_SEC <= timeout) )
    {

        shaking(sol,k,mIn);

        localsearch(sol,iterLS,FirstBest,timeout - ((double) (clock()-start)/ (double)CLOCKS_PER_SEC));
        iter += iterLS;
        totRestart++;

        mIn++;
        if (mIn > ins.nm) mIn -= ins.nm;
        if (sol.cost > bestSolution.cost)
        {
            bestSolution = sol;
            bestIter = iter;
            bestRestart = totRestart;
            kBest = k;
            k = kMin;
        }
        else
        {
            k += kDelta;
            if (k > kMax) k = kMin;
        }
        sol = bestSolution;

        if (fabs(bestSolution.cost - ins.wtot) == 0) break;
        //cout<<"Value: " << bestSolution.cost<< " Iter: " << iter<<" k: "<<k<<endl;
    }

    totalIter += iter;
}


void ConfigureParameters (HeuristicParam *pHP, int nc)
{
    int c;

    pHP->MaxTime = 2;
    //pHP->LST = NONE;
    pHP->LST = LS_TYPE_VNS;
    pHP->MaxVNSRestarts = 15;
    pHP->MaxIter = 15;
    pHP->kMin = 1;
    pHP->kMax = (nc/2)+1; // Default is nc, which is not known yet
    pHP->kDelta = 1;
    pHP->FirstBest = false;

    pHP->seed = -1;



}
