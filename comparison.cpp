#include <iostream>
#include <chrono>
#include "Comparison.h"
#include "analysis.h"

using namespace std;
using namespace chrono;  //we used chrono here to calculate time durations for bfs dfs

void Comparison::run(Maze& maze){
    auto dfsStart=high_resolution_clock::now();

    SolveResult dfsResult=Solver::dfs(maze);

    auto dfsEnd=high_resolution_clock::now();

    double dfsTime=
        duration<double,milli>(dfsEnd-dfsStart).count();


    auto bfsStart=high_resolution_clock::now();

    SolveResult bfsResult=Solver::bfs(maze);

    auto bfsEnd=high_resolution_clock::now();

    double bfsTime=
        duration<double,milli>(bfsEnd-bfsStart).count();


    // Display DFS results

    cout<<"\n\tDFS RESULTS \t"<<endl;

    cout<<"Path found=>  ";

    if(dfsResult.found)
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    cout<<"Explored cells=>  "<<dfsResult.exploredcells<<endl;

    cout<<"Path length=>  "<<dfsResult.pathlength<<endl;

    cout<<"Execution time=> "<<dfsTime<<" ms"<<endl;


    cout<<"\n\t BFS RESULTS \t"<<endl;

    cout<<"Path found=> ";

    if(bfsResult.found)
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    cout<<"Explored cells=> "<<bfsResult.exploredcells<<endl;

    cout<<"Path length=> "<<bfsResult.pathlength<<endl;

    cout<<"Execution time=> "<<bfsTime<<" ms"<<endl;

    cout<<"\n\t COMPARISON \t"<<endl;

    if(dfsResult.found && bfsResult.found){
        if(bfsResult.pathlength<=dfsResult.pathlength)
            cout<<"BFS found a path that is no longer than DFS path."<<endl;

        cout<<"BFS guarantees shortest path in an unweighted maze."<<endl;
    }

    cout<<"\nDFS explored cells=>  "<<dfsResult.exploredcells<<endl;
    cout<<"BFS explored cells=>  "<<bfsResult.exploredcells<<endl;

    cout<<"DFS time= "<<dfsTime<<" ms"<<endl;
    cout<<"BFS time= "<<bfsTime<<" ms"<<endl;


    cout<<"\nDFS path verified: "<<(verifyPath(maze,dfsResult)?"Yes":"No")<<endl;
    cout<<"BFS path verified: "<<(verifyPath(maze,bfsResult)?"Yes":"No")<<endl;


    ResultLog ranking;

    if(dfsResult.found){
        RunRecord r={"DFS",maze.getRows(),maze.getCols(),dfsResult.exploredcells,dfsResult.pathlength,dfsTime};
        ranking.add(r);
    }

    if(bfsResult.found){
        RunRecord r={"BFS",maze.getRows(),maze.getCols(),bfsResult.exploredcells,bfsResult.pathlength,bfsTime};
        ranking.add(r);
    }


    cout<<"\n\t DFS VISUALIZATION \t"<<endl;
    displaySolution(maze,dfsResult);

    cout<<"\n\t BFS VISUALIZATION \t"<<endl;
    displaySolution(maze,bfsResult);

    ranking.displayRanked();

    delete[] dfsResult.path;
    delete[] bfsResult.path;
    delete[] dfsResult.exploredList; 
    delete[] bfsResult.exploredList; 
}

