#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include "problem_data.hpp"
#include "defs.h"
#include "types.hpp"
#include <vector>

struct solution{
	ProblemData& ins;	
	MatBool denseMC;					//usedMC[mode][column]=true iff (mode,column) is in the solution
	SMC sparseMC;						//set of the used MC
	MatSint usedMRC;					//for each row r and mode m MRCused[m][r] is the list of columns covering (m,r)	
	SMR sparseMR;						//set of the covered MR
	SMR uncoveredMR;		        	//set of uncovered MR
	std::vector< Sint > cMode;		    //cMode[c] is the set of modes in which column c is used 
	std::vector< Sint > mCol;		    //mCol[m] is the set of columns in which mode m is used	
    std::vector< int > kCoverage;       //kCoverage[r] is the number of facilities that, independently by the mode, cover r
    double cost;						//solution cost

	//constructor
	solution(ProblemData& ins);
	solution& operator=(const solution& sol);

  void print();
};

bool isFeasible(ProblemData& ins, const SMC& sparseMC, double obj, bool verbose=false);

#endif
