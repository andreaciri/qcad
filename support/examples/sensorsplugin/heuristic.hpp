#ifndef __heuristic_h
#define __heuristic_h


enum _ls_type {LS_TYPE_NONE = 0, /*TS = 1, */LS_TYPE_VNS = 2/*, GRASP = 3*/};
typedef enum _ls_type ls_type;


typedef struct _HeuristicParam HeuristicParam;
struct _HeuristicParam
{
  ls_type LST;      // Type of improvement procedure (Tabu Search or Variable Neighbourhood Search; default is TS)
  bool FirstBest;   // first-best neighborhood exploration
  double MaxTime;   // Maximum execution time for the local search heuristics (default is INFINITE)
  int MaxVNSRestarts;  // Number of restarts for VNS (default is 0)
  int MaxIter;      // Number of neighbourhood explorations (default is 0)
  int kMin;         // Minimum neighbourhood index for Variable Neighbourhood Search (default is 1)
  int kMax;         // Maximum neighbourhood index for Variable Neighbourhood Search (default is "max card[m]")
  int kDelta;       // Neighbourhood index step for Variable Neighbourhood Search (default is 1)
  long seed;        // Current value of the random seed (used in RandomHeuristic3bis and in the restarts of TS and VNS)
};


#endif
