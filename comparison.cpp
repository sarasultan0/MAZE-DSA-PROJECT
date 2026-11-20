
#include <iostream>
#include <chrono>
#include "Comparison.h"

using namespace std;
using namespace chrono;

void Comparison::run(Maze& maze)
{
    // Run DFS and calculate its execution time

    auto dfsStart=high_resolution_clock::now();

    SolveResult dfsResult=Solver::dfs(maze);

    auto dfsEnd=high_resolution_clock::now();

    double dfsTime=
        duration<double,milli>(dfsEnd-dfsStart).count();


    // Run BFS and calculate its execution time

    auto bfsStart=high_resolution_clock::now();

    SolveResult bfsResult=Solver::bfs(maze);

    auto bfsEnd=high_resolution_clock::now();

    double bfsTime=
        duration<double,milli>(bfsEnd-bfsStart).count();


    // Display DFS results

    cout<<"\n========== DFS RESULTS =========="<<endl;

    cout<<"Path found: ";

    if(dfsResult.found)
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    cout<<"Explored cells: "<<dfsResult.exploredcells<<endl;

    cout<<"Path length: "<<dfsResult.pathlength<<endl;

    cout<<"Execution time: "<<dfsTime<<" ms"<<endl;


    // Display BFS results

    cout<<"\n========== BFS RESULTS =========="<<endl;

    cout<<"Path found: ";

    if(bfsResult.found)
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    cout<<"Explored cells: "<<bfsResult.exploredcells<<endl;

    cout<<"Path length: "<<bfsResult.pathlength<<endl;

    cout<<"Execution time: "<<bfsTime<<" ms"<<endl;


    // Final comparison

    cout<<"\n========== COMPARISON =========="<<endl;

    if(dfsResult.found && bfsResult.found)
    {
        if(bfsResult.pathlength<=dfsResult.pathlength)
            cout<<"BFS found a path that is no longer than DFS path."<<endl;

        cout<<"BFS guarantees shortest path in an unweighted maze."<<endl;
    }

    cout<<"\nDFS explored cells: "<<dfsResult.exploredcells<<endl;
    cout<<"BFS explored cells: "<<bfsResult.exploredcells<<endl;

    cout<<"DFS time: "<<dfsTime<<" ms"<<endl;
    cout<<"BFS time: "<<bfsTime<<" ms"<<endl;


    // Free dynamically allocated paths

    delete[] dfsResult.path;
    delete[] bfsResult.path;
}

