#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include "problem_data.hpp"
#include "defs.h"
#include "types.hpp"
#include "util.hpp"
#include "moves.hpp"
#include "solution.hpp"

using namespace std;


void greedy(solution& sol, ostream& os){
	const int w=10;
	bool moveFound=true;

	//Print log header
	os<<right<<setw(w)<<"ITER";
	os<<right<<setw(w)<<"UNC";
	os<<right<<setw(w)<<"OBJ";
	os<<right<<setw(w)<<"MODE";
	os<<right<<setw(w)<<"COL"<<endl;

	while(moveFound){		
		MoveEvaluation bestMove, currMove;
		bestMove.dCost=(-numeric_limits<double>::max());
		
		//consider all the unused mc pairs
		for(int m=1;m<=sol.ins.nm;++m){
			for(int c=1;c<=sol.ins.nc;++c){
				if(sol.denseMC[m][c]) continue;
				bool feasible=evaluateAdd(sol,MC(m,c),currMove);
				if(feasible && le(bestMove.dCost,currMove.dCost)){
					bestMove=currMove;
				}
			}
		}

		//if the best move does not improve the objective function, exit.
		if(le(bestMove.dCost,0.0)) break;
		
		//execute the best move
		makeAddMove(sol,bestMove.add);		
		os<<right<<setw(w)<<sol.sparseMC.size();
		os<<right<<setw(w)<<sol.uncoveredMR.size();
		os<<right<<setw(w)<<sol.cost;
		os<<right<<setw(w)<<bestMove.add.mode;
		os<<right<<setw(w)<<bestMove.add.column<<endl;
	}


}