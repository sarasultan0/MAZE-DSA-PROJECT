# include <iostream>
# include "maze.h"
#include "Position.h"
using namespace std;

int main(){

    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;

    cout << "Enter number of columns: ";
    cin >> cols;

    Maze m(rows, cols);
    m.generateMaze();

    cout << "\nGenerated Maze:\n";
    m.displayMaze();

    if (m.hasValidPath())
    {
        cout << "A valid path exists from Start to Exit!";
    }
    else
    {
        cout << "No valid path exists!";
    }

    return 0;
}
