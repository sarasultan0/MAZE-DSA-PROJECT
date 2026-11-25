#include <iostream>
#include "analysis.h"
using namespace std;

bool verifyPath(Maze& maze, const SolveResult& r){
    if (!r.found || r.path == NULL || r.pathlength <= 0)
        return false;

    Position s = maze.getStart();
    Position e = maze.getExit();

    if (r.path[0].row != s.row || r.path[0].col != s.col)
        return false;

    Position last = r.path[r.pathlength - 1];

    if (last.row != e.row || last.col != e.col)
        return false;

    for (int i= 0; i< r.pathlength; i++){
        int row= r.path[i].row;
        int col= r.path[i].col;

        if (row< 0 || row >= maze.getRows() || col < 0 || col >= maze.getCols())
            return false;

        if (maze.getCell(row, col) == '#')
            return false;

        if (i > 0){
            int dr = row - r.path[i - 1].row;
            int dc = col - r.path[i - 1].col;

            if (dr < 0) dr = -dr;
            if (dc < 0) dc = -dc;

            if (dr + dc != 1)
                return false;
        }
    }

    return true;
}

void displaySolution(Maze& maze, const SolveResult& r){
    int rows = maze.getRows();
    int cols = maze.getCols();

    char** g = new char*[rows];

    for (int i= 0; i < rows; i++){
        g[i]= new char[cols];

        for (int j = 0; j < cols; j++)
            g[i][j] = maze.getCell(i, j);
    }

    if (r.exploredList != NULL){
        for (int i = 0; i < r.exploredcells; i++){
            Position p = r.exploredList[i];
            if (g[p.row][p.col] == '.')
                g[p.row][p.col] = '+';
        }
    }

    if (r.path != NULL) //mark final path{
        for (int i = 0; i < r.pathlength; i++){
            Position p = r.path[i];
            if (g[p.row][p.col] == '.' || g[p.row][p.col] == '+')
                g[p.row][p.col] = '*';
        }
    }

    cout << endl;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++)
            cout << g[i][j] << " ";

        cout << endl;
    }

    cout << "\nLegend:  # wall   S start   E exit   + explored   * final path" << endl;

    for (int i = 0; i < rows; i++)
        delete[] g[i];

    delete[] g;
}

static int countDigits(int value){ //helper functions
    int digits = 1;

    while (value >= 10){
        digits++;
        value /= 10;
    }

    return digits;
}

static void printPadded(int value, int width){
    cout << value;

    for (int i = countDigits(value); i < width; i++)
        cout << " ";
}

static void printPadded(const char* text, int width){
    cout << text;

    int len = 0;

    while (text[len] != '\0')
        len++;

    for (int i = len; i < width; i++)
        cout << " ";
}


ResultLog::ResultLog(){
    capacity = 5;
    count = 0;
    data = new RunRecord[capacity];
}

ResultLog::~ResultLog()
{
    delete[] data;
}

void ResultLog::add(RunRecord r)
{
    if (count == capacity)
    {
        int newCapacity = capacity * 2;
        RunRecord* newData = new RunRecord[newCapacity];

        for (int i = 0; i < count; i++)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    data[count++] = r;
}

int ResultLog::getCount()
{
    return count;
}

bool ResultLog::isBetter(const RunRecord& a, const RunRecord& b)
{
    if (a.exploredCells != b.exploredCells)
        return a.exploredCells < b.exploredCells;

    return a.pathLength < b.pathLength;
}

void ResultLog::displayRanked(){
    if (count == 0)
    {
        cout << "No results recorded yet. Solve a maze first." << endl;
        return;
    }

    RunRecord* sorted = new RunRecord[count];

    for (int i = 0; i < count; i++)
        sorted[i] = data[i];

    for (int i = 1; i < count; i++){ //insertion sort
        RunRecord key = sorted[i];
        int j = i - 1;

        while (j >= 0 && isBetter(key, sorted[j]))
        {
            sorted[j + 1] = sorted[j];
            j--;
        }

        sorted[j + 1] = key;
    }

    cout << "\n---------- RANKING (fewest explored cells first) ----------" << endl;
    printPadded("Rank", 6);
    printPadded("Algo", 7);
    printPadded("Maze", 10);
    printPadded("Explored", 10);
    printPadded("Path", 8);
    cout << "Time (ms)" << endl;

    for (int i = 0; i < count; i++)
    {
        printPadded(i + 1, 6);
        printPadded(sorted[i].algorithm, 7);

        // "RxC" column: print it, then pad manually
        cout << sorted[i].rows << "x" << sorted[i].cols;

        int used = countDigits(sorted[i].rows) + 1 + countDigits(sorted[i].cols);
        for (int k = used; k < 10; k++) cout << " ";

        printPadded(sorted[i].exploredCells, 10);
        printPadded(sorted[i].pathLength, 8);
        cout << sorted[i].timeMs << endl;
    }

    delete[] sorted;
}

