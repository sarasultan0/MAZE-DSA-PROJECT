#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "maze.h"
#include "solver.h"

bool verifyPath(Maze& maze, const SolveResult& r);
void displaySolution(Maze& maze, const SolveResult& r);

struct RunRecord{
    const char* algorithm;   
    int rows;
    int cols;
    int exploredCells;
    int pathLength;
    double timeMs;
};

class ResultLog{
private:
    RunRecord* data;
    int count;
    int capacity;

    ResultLog(const ResultLog&);             
    ResultLog& operator=(const ResultLog&);

    static bool isBetter(const RunRecord& a, const RunRecord& b);

public:
    ResultLog();
    ~ResultLog();

    void add(RunRecord r);
    int  getCount();
    void displayRanked();
};

#endif
