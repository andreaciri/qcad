#include <iostream>
#include <boost/unordered_set.hpp>
#include "localsearch.hpp"
#include "greedy.hpp"

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
using namespace boost;


void stupid(solution& sol, ostream& os){
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
				if(feasible /*&& le(bestMove.dCost,currMove.dCost)*/){
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

struct SearchState{
	int **currentMode;  //currentMode[c][t] represents the mode in which is the column c indexed by t
						//NOTE: if the corresponding value is 0 column (c,t) is not used
 	double ****arcCost; //arcCost[c1][t1][c2][t2] represents the cost of arc (c1,t1) -> (c2,t2)
	solution& sol;
	SearchState(solution& sol);
  ~SearchState();
	void init();
	void update();
	double computeArcCost(int c1,int t1,int c2, int t2);
};


SearchState::SearchState(solution& sol):
sol(sol)
{
	init();
}


SearchState::~SearchState()
{
	//deallocate the currentMode dataStructure
	for(int c=1;c<=sol.ins.nc;++c){
		delete[] currentMode[c];
	}
	delete[] currentMode;

	//Deallocate the arcCost matrix
	for(int c1=1;c1<=sol.ins.nc;++c1){
		for(int t1=1;t1<=sol.ins.b[c1];++t1){
			for(int c2=1;c2<=sol.ins.nc;++c2){
				delete[] arcCost[c1][t1][c2];
			}
			delete[] arcCost[c1][t1];
		}
		delete[] arcCost[c1];
	}
	delete[] arcCost;
}


void SearchState::init(){
	//initialize the currentMode dataStructure
	currentMode=new int*[sol.ins.nc+1];
	for(int c=1;c<=sol.ins.nc;++c){
		currentMode[c]=new int[sol.ins.b[c]+1];
		//initialize the currentMode structure
		for(int t=0;t<=sol.ins.b[c];++t) currentMode[c][t]=0;
		int t=1;
		for(Sint::iterator it=sol.cMode[c].begin();
			it!=sol.cMode[c].end();++it)
		{
			int m= *it;
			currentMode[c][t++]=m;
		}
	}




	//Initialize the arcCost matrix
	arcCost=new double***[sol.ins.nc+1];
	for(int c1=1;c1<=sol.ins.nc;++c1){
		arcCost[c1]=new double**[sol.ins.b[c1]+1];
		for(int t1=1;t1<=sol.ins.b[c1];++t1){
			arcCost[c1][t1]=new double*[sol.ins.nc+1];
			for(int c2=1;c2<=sol.ins.nc;++c2){
				arcCost[c1][t1][c2]=new double[sol.ins.b[c2]+1];
				for(int t2=1;t2<=sol.ins.b[c2];++t2){
					arcCost[c1][t1][c2][t2]=computeArcCost(c1,t1,c2,t2);
				}
			}
		}
	}
}

void SearchState::update(){
	//initialize the currentMode dataStructure
	for(int c=1;c<=sol.ins.nc;++c){
		//initialize the currentMode structure
		for(int t=0;t<=sol.ins.b[c];++t) currentMode[c][t]=0;
		int t=1;
		for(Sint::iterator it=sol.cMode[c].begin();
			it!=sol.cMode[c].end();++it)
		{
			int m= *it;
			currentMode[c][t++]=m;
		}
	}

	//Naive arcCost matrix update
	for(int c1=1;c1<=sol.ins.nc;++c1){
		for(int t1=1;t1<=sol.ins.b[c1];++t1){
			for(int c2=1;c2<=sol.ins.nc;++c2){
				for(int t2=1;t2<=sol.ins.b[c2];++t2){
					arcCost[c1][t1][c2][t2]=computeArcCost(c1,t1,c2,t2);
				}
			}
		}
	}
}

double SearchState::computeArcCost(int c1,int t1,int c2, int t2){
	static int *rowChange=new int[sol.ins.nr+1];
	for(int i=0;i<=sol.ins.nr;++i)
		rowChange[i]=0;
	int m1=currentMode[c1][t1];
	int m2=currentMode[c2][t2];
	if(m1==m2 || c1==c2) return -numeric_limits<double>::max();
	if(m2==0) return 0; //(c2,t2) is not currently used

	if(c1==1 && t1==1 && c2==20 && t2==1){
		int prova=10;
		prova=prova;
	}

	//see which rows will be uncovered if we remove (c2,m2)
	for(int k=1;k<=sol.ins.Copertura[m2][c2][0];++k){
		int r=sol.ins.Copertura[m2][c2][k];
		if(sol.usedMRC[m2][r].size()==1)
			rowChange[r]=-1;
	}

	//see which rows will be covered if we insert (c1,m2) after
	//the removal of (c2,m2)
	for(int k=1;k<=sol.ins.Copertura[m2][c1][0];++k){
		int r=sol.ins.Copertura[m2][c1][k];
		if(rowChange[r]==-1 || sol.usedMRC[m2][r].empty())
			rowChange[r]++;
	}

	double cost=0.0;
	for(int r=1;r<=sol.ins.nr;++r){
        cost+=rowChange[r]*sol.ins.weight[typeFromColumn(sol, MC(1, c1))][r];
	}



	return cost;
}

struct PathNode{
	int c;
	int t;
	PathNode():c(-1),t(-1){}
	PathNode(int c, int t):c(c),t(t){}
};

bool operator==(const PathNode& n1, const PathNode& n2){
	return n1.c==n2.c && n1.t==n2.t;
}

bool operator!=(const PathNode& n1, const PathNode& n2){
	return !(n1==n2);
}



struct Path{
	ProblemData& ins;
	int length;
	PathNode *nodes;
	double cost;
	bool* modes;
	Path(ProblemData& ins);
	Path(const Path& path);
	~Path();
	size_t hash() const;
};

Path::Path(ProblemData& ins):
ins(ins)
{
	nodes=new PathNode[ins.nm+1];
	length=0;
  cost=0.0;
	modes=new bool[ins.nm+1];
	for(int i=0;i<=ins.nm;++i)
		modes[i]=false;
}

Path::Path(const Path& p):
ins(p.ins)
{
	nodes=new PathNode[ins.nm+1];
	length=p.length;
	for(int i=0;i<length;++i)
		nodes[i]=p.nodes[i];
	cost=p.cost;
	modes=new bool[ins.nm+1];
	for(int m=0;m<=ins.nm;++m)
		modes[m]=p.modes[m];
}

Path::~Path(){
	delete[] nodes;
	delete[] modes;
}

size_t Path::hash() const{
//	assert(length>=2);
	size_t seed=0;
	hash_combine(seed,nodes[0].c);
	hash_combine(seed,nodes[0].t);
	hash_combine(seed,nodes[length-1].c);
	hash_combine(seed,nodes[length-1].t);
	for(int m=0;m<=ins.nm;++m)
		hash_combine(seed,modes[m]);
	return seed;
}

ostream& operator<<(ostream& os, const Path& p){
	for(int i=0;i<p.length; ++i){
		os<<"("<<p.nodes[i].c<<","<<p.nodes[i].t<<") ";
	}
	return os;
}

struct HashPathPtr{
	size_t operator()(const Path *pathPtr) const{
		return pathPtr->hash();
	}
};

struct EqPathPtr{
	bool operator()(const Path *p1,const Path *p2) const{
		if(p1->length != p2->length) return false;
		if(p1->nodes[p1->length-1] != p2->nodes[p1->length-1]) return false;
		if(p1->nodes[0] != p2->nodes[0]) return false;
		for(int m=0;m<=p1->ins.nm;++m)
			if(p1->modes[m] != p2->modes[m]) return false;
		return true;
	}
};

bool LexPrec (Path *P1, Path *P2, SearchState& state)
{
  int i;

  for (i = 0; (i < P1->length) && eq(P1->nodes[i].c,P2->nodes[i].c) && eq(P1->nodes[i].t,P2->nodes[i].t); i++);

  if (i == P1->length)
  {
    fprintf(stderr,"Two different paths are actually identical!\n");
    exit(-1);
  }
  if (le(P1->nodes[i].c,P2->nodes[i].c))
    return true;
  else if ( eq(P1->nodes[i].c,P2->nodes[i].c) &&
            le(state.currentMode[P1->nodes[i].c][P1->nodes[i].t],
               state.currentMode[P2->nodes[i].c][P2->nodes[i].t]) )
    return true;
  else
    return false;
}


Path *DP(SearchState& state, bool firstImprovement){
	const ProblemData& ins=state.sol.ins;
	int cont=0;
	typedef unordered_set<Path*,HashPathPtr,EqPathPtr> PSet;
	PSet *currSet=new PSet();
	PSet *nextSet=new PSet();
	Path *bestPath=0;

  // Verifica che ogni colonna sia usata al massimo una volta per ogni modo
  for(int c1=1;c1<=ins.nc;++c1)
		for(int t1=1;t1<=ins.b[c1];++t1)
      for(int t2=t1+1;t2<=ins.b[c1];++t2)
        if ( (state.currentMode[c1][t1] > 0) && (state.currentMode[c1][t1] == state.currentMode[c1][t2]) )
        {
          fprintf(stderr,"La colonna %d usa due volte il modo %d (posizioni %d e %d)",c1,state.currentMode[c1][t1],t1,t2);
          exit(-1);
        }

	//TODO: questa parte si può migliorare con una
	//struttura dati che mi fornisce l'outcut di (c1,t1)
	for(int c1=1;c1<=ins.nc;++c1){
		for(int t1=1;t1<=ins.b[c1];++t1){
			for(int c2=1;c2<=ins.nc;++c2){
				for(int t2=1;t2<=ins.b[c2];++t2){
					int m1=state.currentMode[c1][t1];
					int m2=state.currentMode[c2][t2];
					if (m1 == m2) continue;

          // Se i modi disponibili sono piu' di uno e uno dei nodi e' una colonna non usata
          // i suoi modi disponibili sono tutti = 0. Allora si considera solo il primo.
          if ((t1 > 1) && (m1 == 0)) continue;
          if ((t2 > 1) && (m2 == 0)) continue;

					double aCost=state.arcCost[c1][t1][c2][t2];
					if(leq(aCost,0.0)) continue;
					//Insert a new Path composed by the negative arc
					Path *pptr=new Path(state.sol.ins);
					pptr->nodes[0]=PathNode(c1,t1);
					pptr->nodes[1]=PathNode(c2,t2);
					pptr->length=2;
					pptr->cost=aCost;
					pptr->modes[m1]=pptr->modes[m2]=true;
					currSet->insert(pptr);
					++cont;
				}
			}
		}
	}

//	assert(currSet->size() == cont);
 //OUTPUT RIMOSSO DA NOI
 //cout<<"currSet.size()="<<currSet->size()<<endl;

	int iter=2;
	while(iter<=ins.nm +1 && !currSet->empty()){
 //ATTENZIONE: PER FARE LE PROVE CON LA VNS SEMPLICE, SOSTITUIRE LA RIGA PRECEDENTE CON LA SUCCESSIVA
 //if (!currSet->empty()){
		for(PSet::iterator pit=currSet->begin();pit!=currSet->end();++pit){
      Path *pptr= *pit;
			PathNode& tail=pptr->nodes[0];
			PathNode& head=pptr->nodes[pptr->length-1];
			double cycleCost=state.arcCost[head.c][head.t][tail.c][tail.t];
      if( gr(pptr->cost + cycleCost,0.0) ){
        //( (bestPath != NULL) ? bestPath->cost : 0.0 ) ) ){

				//INIZIO OUTPUT RIMOSSO DA NOI
        //cout<<"Solution Found!"<<endl;
        //cout<<(*pptr)<<endl;
				//for(int i=0;i<pptr->length; ++i)
        //{
				//	int c=pptr->nodes[i].c;
				//  int t=pptr->nodes[i].t;
				//	int m=state.currentMode[c][t];
        //  cout<<"("<<c<<","<<t<<") ["<<m<<"] ";
				//}
        //cout<<"cost="<<pptr->cost +cycleCost<<endl;
        //FINE OUTPUT RIMOSSO DA NOI

				if(bestPath==NULL || gr(pptr->cost+cycleCost,bestPath->cost) ||
          eq(pptr->cost+cycleCost,bestPath->cost) && LexPrec(pptr,bestPath,state) ){
					if(bestPath!=NULL) delete bestPath;
					bestPath=new Path(*pptr);
					bestPath->cost += cycleCost;
					if(firstImprovement){
						for(PSet::iterator pit=currSet->begin();pit!=currSet->end();++pit)
							delete *pit;
						for(PSet::iterator pit=nextSet->begin();pit!=nextSet->end();++pit)
							delete *pit;
						return bestPath;
					}
				}
			}

      //extend pptr
			int c1=head.c;
			int t1=head.t;
			for(int c2=1;c2<=ins.nc;++c2){
				for(int t2=1;t2<=ins.b[c2];++t2){
					int m2=state.currentMode[c2][t2];
          // Se i modi disponibili sono piu' di uno e il nodo toccato e' una colonna non usata
          // i suoi modi disponibili sono tutti = 0. Allora si considera solo il primo.
          if ((t2 > 1) && (m2 == 0)) continue;

					if(pptr->modes[m2]) continue;
					double aCost=state.arcCost[c1][t1][c2][t2];
					// cout<<"try to extend:"<<(*pptr)<<endl;
					// cout<<"with:"<<c2<<","<<t2<<endl;
					// cout<<"cost:"<<(pptr->cost + aCost)<<endl;
				  if(le(pptr->cost + aCost,0.0)) continue;

					Path *npptr=new Path(*pptr);
					//cout<<npptr->length<<endl;
//					assert(npptr->length <= ins.nm);
					npptr->nodes[npptr->length]=PathNode(c2,t2);
					npptr->modes[m2]=true;
					npptr->length++;
					npptr->cost+=aCost;

					PSet::iterator it=nextSet->find(npptr);
					if(it==nextSet->end()){
						nextSet->insert(npptr);
					}
					else{
						Path *cpptr = *it; //conflicting path
						if(gr(npptr->cost,cpptr->cost)){
							nextSet->erase(cpptr);
							delete cpptr;
							nextSet->insert(npptr);
						}
						else{
							delete npptr;
						}
					}
				}
			}


		}
		//cout<<"nextSet.size()=="<<nextSet->size()<<endl;

		//clear memory used in CurrSet
		for(PSet::iterator pit=currSet->begin();pit!=currSet->end();++pit)
			delete *pit;
		currSet->clear();

		PSet *tmp=currSet;
		currSet=nextSet;
		nextSet=tmp;
		++iter;
	}
	return bestPath;
}

void localsearch(solution& sol, int& iter, bool FirstBest, double timeout)
{
  long start;

  start = clock();
	SearchState state(sol);
  iter = 0;
	while (((double) (clock()-start)/ (double)CLOCKS_PER_SEC) < timeout)
  {
		Path *p=DP(state,FirstBest);
		if(p==0) break;
		int index=0;
		double newCost=state.sol.cost + p->cost;
		while(index < p->length-1){
			PathNode& orig=p->nodes[index];
			PathNode& dest=p->nodes[index+1];
			int m1=state.currentMode[orig.c][orig.t];
			int m2=state.currentMode[dest.c][dest.t];
			if(m1!=0)
				makeDelMove(state.sol,MC(m1,orig.c));
			if(m2!=0)
				makeAddMove(state.sol,MC(m2,orig.c));
			++index;
		}

		PathNode& orig=p->nodes[p->length-1];
		PathNode& dest=p->nodes[0];
		int m1=state.currentMode[orig.c][orig.t];
		int m2=state.currentMode[dest.c][dest.t];
		if(m1!=0)
			makeDelMove(state.sol,MC(m1,orig.c));
		if(m2!=0)
			makeAddMove(state.sol,MC(m2,orig.c));
		//assert(eq(newCost, state.sol.cost));
		//cout<<"i="<<iter<<" COST="<<sol.cost<<endl;
    //sol.print();

    if ( (m1 != 0) || (m2 != 0) ) iter++;

		state.update();
	}

}
