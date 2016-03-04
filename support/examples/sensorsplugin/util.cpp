#include "util.hpp"

using namespace std;

boost::iostreams::stream< boost::iostreams::null_sink > nullostream( ( boost::iostreams::null_sink() ) );

boost::mt19937 rng;
boost::mt19937& getRng(){
	return rng;
}

int runiform(int min,int max){
	return boost::uniform_int<>(min,max)(rng);
}

void setSeed(int seed){
	rng.seed(seed);
}