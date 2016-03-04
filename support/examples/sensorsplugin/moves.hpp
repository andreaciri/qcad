#ifndef MOVES_HPP
#define MOVES_HPP
#include "solution.hpp"
#include "types.hpp"
#include <string>

struct MoveEvaluation{
	double dCost;	
	MC add;
	std::string rep() const;
	MoveEvaluation();
	MoveEvaluation& operator=(const MoveEvaluation& eval);
};

bool evaluateAdd(const solution& sol, const MC& mc, MoveEvaluation& eval);

void makeAddMove(solution& sol, const MC& mc);

void makeDelMove(solution& sol, const MC& mc);

#endif