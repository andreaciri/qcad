#include "solution.hpp"
#include "util.hpp"
#include <vector>

using namespace std;

solution::solution(ProblemData& ins):
	ins(ins),denseMC(ins.nm+1),
	usedMRC(ins.nm+1),cMode(ins.nc+1),
	mCol(ins.nm+1),cost(0.0)
{
	for(int m=1;m<=ins.nm;++m){
		usedMRC[m].assign(ins.nr+1,Sint());
		denseMC[m].assign(ins.nc+1,false);	
		for(int r=1;r<=ins.nr;++r)	
			uncoveredMR.insert(MR(m,r));
	}
}


solution& solution::operator=(const solution& sol){
  ins = sol.ins;
	denseMC=sol.denseMC; 
  sparseMC=sol.sparseMC; 
  usedMRC=sol.usedMRC; 
  sparseMR=sol.sparseMR;
	uncoveredMR=sol.uncoveredMR; 
  cMode=sol.cMode;
  mCol=sol.mCol;
  cost=sol.cost;
	return *this;
}


bool isFeasible(ProblemData& ins, const SMC& sparseMC, double obj, bool verbose){
	vector<int> cMode(ins.nc+1,0);
	vector<int> mCol(ins.nm+1,0);
	SMR coveredMR;
	for(SMC::const_iterator it=sparseMC.begin();it!=sparseMC.end();++it){
		const MC& mc=(*it);
		cMode[mc.column]++;
		mCol[mc.mode]++;
		for(int i=1;i<=ins.Copertura[mc.mode][mc.column][0];++i){
			int row=ins.Copertura[mc.mode][mc.column][i];
			coveredMR.insert(MR(mc.mode,row));
		}
	}
	double realObj=0.0;
	for(SMR::iterator it=coveredMR.begin();it!=coveredMR.end();++it){
		realObj+=ins.weight[it->mode][it->row];
	}

	bool feasible=true;
	if(!eq(obj,realObj)){
		if(verbose){

		}
		feasible=false;
	}
	for(int m=1;m<=ins.nm;++m){
		if(mCol[m] != ins.card[m]){
			feasible=false;
			if(verbose){

			}
		}
	}

	for(int c=1;c<=ins.nc;++c){
		if(cMode[c] > ins.b[c]){
			feasible=false;
			if(verbose){

			}
		}
	}

	return feasible;
}


void solution::print()
{
  int m, c;

  printf("cost: %.lf\n",cost);
  for (m = 1; m <= ins.nm; m++)
  {
    printf("mode %d: ",m);
    for (c = 1; c <= ins.nc; c++)
      if (denseMC[m][c] == true)
        printf("%3d ",c);
    printf("\n");
  }
}
