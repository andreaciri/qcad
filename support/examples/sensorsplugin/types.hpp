#ifndef TYPES_HPP
#define TYPES_HPP
#include <iostream>
#include <set>
#include <cmath>
#include <vector>
#include <boost/unordered_set.hpp>
#include "problem_data.hpp"
#include "defs.h"


//Mode-Column pair
struct MC{
	int mode;
	int column;
	MC(int mode, int column):mode(mode),column(column){}
	bool operator==(const MC& other) const{
		return mode==other.mode && column==other.column;
	}
};

//operator to print a MC
std::ostream& operator<<(std::ostream& os, const MC& mc);

//Function Object to hash a MC
struct HashMC{
	size_t operator()(const MC& mc) const{
		size_t seed = 0;                
        boost::hash_combine(seed, mc.mode);
        boost::hash_combine(seed, mc.column);       
        return seed;
	}
};

//Mode-Row pair
struct MR{
	int mode;
	int row;
	MR(int mode, int row):mode(mode),row(row){}
	bool operator==(const MR& other) const{
		return mode==other.mode && row==other.row;
	}
};

//operator to print a MR
std::ostream& operator<<(std::ostream& os, const MR& mc);

//Function Object to hash a MR
struct HashMR{
	size_t operator()(const MR& mr) const{
		size_t seed = 0;                
        boost::hash_combine(seed, mr.mode);
        boost::hash_combine(seed, mr.row);       
        return seed;
	}
};


//hashset of integers
typedef boost::unordered_set<int> Sint;

//bidimensional matrix of sint
typedef std::vector< std::vector< Sint >  > MatSint;

//hashset of MC
typedef boost::unordered_set<MC,HashMC> SMC;

//hashset of MR
typedef boost::unordered_set<MR,HashMR> SMR;

//bidimensional matrix of booleans
typedef std::vector< std::vector<bool> > MatBool;

//bidimensional matrix of integers
typedef std::vector< std::vector<int> > MatInt;

//bidimensional matrix of double
typedef std::vector< std::vector<double> > MatDouble;

//bidimensional matric of Sint
typedef std::vector< std::vector< Sint > > MatSint;

//Initialize with element val a generic bidimensional matrix defined by vector< vector<T> > 
template<class T > void initializeMatrix(std::vector< std::vector<T> >& d, int m, int n,T val=T()){	
	d.resize(m+1);
	for(int i=1;i<=m;++i){
		d[i].assign(n+1,val);
	}
}


#endif
