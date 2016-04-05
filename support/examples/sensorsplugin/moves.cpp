#include <cstdlib>
#include <sstream>
#include "moves.hpp"

using namespace std;
int kCoverage = 1;

MoveEvaluation::MoveEvaluation() : add(-1,-1)
{}

string MoveEvaluation::rep() const{
	stringstream sstr;
	sstr<<add<<":"<<dCost;
	return sstr.str();
}

MoveEvaluation& MoveEvaluation::operator=(const MoveEvaluation& eval){
	dCost=eval.dCost;
	add=eval.add;
	return (*this);
}

bool evaluateAdd(const solution& sol, const MC& mc, MoveEvaluation& eval){
	if(sol.cMode[mc.column].size() == sol.ins.b[mc.column] ||
	   sol.mCol[mc.mode].size() == sol.ins.card[mc.mode]) return false;

	eval.add=mc;
	eval.dCost=0.0;
	for(int i=1;i<=sol.ins.Copertura[mc.mode][mc.column][0];++i){
		int row=sol.ins.Copertura[mc.mode][mc.column][i];
        // Reward evaluation
        if(sol.usedMRC[mc.mode][row].empty())
            eval.dCost+=sol.ins.weight[mc.mode][row];
	}
	return true;
}

void makeAddMove(solution& sol, const MC& mc){
	assert(sol.denseMC[mc.mode][mc.column]==false);
	assert(sol.sparseMC.find(mc)==sol.sparseMC.end());

	sol.denseMC[mc.mode][mc.column]=true;
	sol.sparseMC.insert(mc);
	for(int i=1;i<=sol.ins.Copertura[mc.mode][mc.column][0];++i){
		int row=sol.ins.Copertura[mc.mode][mc.column][i];		
        if(sol.usedMRC[mc.mode][row].empty()){
			MR mr(mc.mode,row);
            //assert(sol.sparseMR.find(mr) == sol.sparseMR.end());
            //assert(sol.uncoveredMR.find(mr) != sol.uncoveredMR.end());
            // single point covering
			sol.sparseMR.insert(mr);
			sol.uncoveredMR.erase(mr);
            sol.kCoverage[row]++;
            //Reward computation
			sol.cost+=sol.ins.weight[mc.mode][row];
		}
		assert(sol.usedMRC[mc.mode][row].find(mc.column) == sol.usedMRC[mc.mode][row].end());
		sol.usedMRC[mc.mode][row].insert(mc.column);
	}

	assert(sol.cMode[mc.column].find(mc.mode)==sol.cMode[mc.column].end());
	assert(sol.mCol[mc.mode].find(mc.column)==sol.mCol[mc.mode].end());
	sol.cMode[mc.column].insert(mc.mode);
	sol.mCol[mc.mode].insert(mc.column);
}


void makeDelMove(solution& sol, const MC& mc){
	assert(sol.denseMC[mc.mode][mc.column]==true);
	assert(sol.sparseMC.find(mc)!=sol.sparseMC.end());

	sol.denseMC[mc.mode][mc.column]=false;
	sol.sparseMC.erase(mc);
	for(int i=1;i<=sol.ins.Copertura[mc.mode][mc.column][0];++i){
		int row=sol.ins.Copertura[mc.mode][mc.column][i];		
        if(sol.usedMRC[mc.mode][row].size()==1){
			MR mr(mc.mode,row);
            //assert(sol.sparseMR.find(mr) != sol.sparseMR.end());
            //assert(sol.uncoveredMR.find(mr) == sol.uncoveredMR.end());
            //single point uncovering
			sol.sparseMR.erase(mr);
			sol.uncoveredMR.insert(mr);
			sol.cost-=sol.ins.weight[mc.mode][row];
		}
		assert(sol.usedMRC[mc.mode][row].find(mc.column) != sol.usedMRC[mc.mode][row].end());
		sol.usedMRC[mc.mode][row].erase(mc.column);
        sol.kCoverage[row]--;
	}

	assert(sol.cMode[mc.column].find(mc.mode)!=sol.cMode[mc.column].end());
	assert(sol.mCol[mc.mode].find(mc.column)!=sol.mCol[mc.mode].end());
	sol.cMode[mc.column].erase(mc.mode);
	sol.mCol[mc.mode].erase(mc.column);
}
