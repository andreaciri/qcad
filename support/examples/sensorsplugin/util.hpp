#ifndef UTIL_HPP
#define UTIL_HPP
#include <iostream>
#include <cmath>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/random.hpp>

const double epsv=1e-6;

inline bool le(double a, double b){
	return a + epsv < b;
}

inline bool gr(double a, double b){
	return a - epsv > b;
}

inline bool eq(double a, double b){
	return fabs(b-a)<epsv;
}

inline bool leq(double a, double b){
	return le(a,b) || eq(a,b);
}

inline bool geq(double a, double b){
	return gr(a,b) || eq(a,b);
}


extern boost::iostreams::stream< boost::iostreams::null_sink > nullostream;

int runiform(int min,int max);

#endif