#include "types.hpp"

using namespace std;

ostream& operator<<(ostream& os, const MC& mc){
	return os<<"("<<mc.mode<<","<<mc.column<<")";
}

ostream& operator<<(ostream& os, const MR& mr){
	return os<<"("<<mr.mode<<","<<mr.row<<")";
}