#ifndef SOLVER_H
#define SOLVER_H
#include "maze.h"
#include "Queue.h"
#include "Position.h"
struct SolveResult{
	bool found;
	int exploredcells;
	int pathlength;
	Position* path;
	Position* exploredList; 
};

class Solver{
	public:
		//were solving with two methods bfs and dfs
		static SolveResult dfs(Maze& maze);
		static SolveResult bfs(Maze& maze);
};

#endif
