#include "Solver.h"

bool isValid(Maze& maze, int row, int col){
    if (row < 0 || row >= maze.getRows())
        return false;

    if (col < 0 || col >= maze.getCols())
        return false;

    if (maze.getCell(row, col) == '#')
        return false;

    return true;
}

bool samePosition(Position a, Position b){
    return a.row == b.row && a.col == b.col;
}

bool** createVisited(int rows, int cols){
    bool** visited = new bool*[rows];

    for (int i = 0; i < rows; i++)
    {
        visited[i] = new bool[cols];

        for (int j = 0; j < cols; j++)
        {
            visited[i][j] = false;
        }
    }

    return visited;
}


Position** createParent(int rows, int cols){
    Position** parent = new Position*[rows];

    for (int i = 0; i < rows; i++)
    {
        parent[i] = new Position[cols];

        for (int j = 0; j < cols; j++)
        {
            parent[i][j].row = -1;
            parent[i][j].col = -1;
        }
    }

    return parent;
}


void freeGrids(bool** visited, Position** parent, int rows){
    for (int i = 0; i < rows; i++)
    {
        delete[] visited[i];
        delete[] parent[i];
    }

    delete[] visited;
    delete[] parent;
}


Position* reconstructPath(
    Position** parent,
    Position start,
    Position exit,
    int rows,
    int cols,
    int& pathLength)
{
    int count = 1;
    Position current = exit;

    // Count path positions by moving backwards

    while (!samePosition(current, start)){
        Position previous =
            parent[current.row][current.col];

        if (previous.row < 0 || previous.col < 0)
            return NULL;

        current = previous;
        count++;

        if (count > rows * cols)
            return NULL;
    }

    // Allocate path array

    Position* path = new Position[count];

    current = exit;

    // Fill array backwards

    for (int i= count - 1; i >= 0; i--){
        path[i] = current;

        if (i > 0){
            current = parent[current.row][current.col];
        }
    }

    pathLength = count;

    return path;
}

SolveResult Solver::dfs(Maze& maze){
    int rows = maze.getRows();
    int cols = maze.getCols();

    bool** visited = createVisited(rows, cols);
    Position** parent = createParent(rows, cols);

    Position start = maze.getStart();
    Position exit = maze.getExit();

    Stack s(rows * cols);  //custo stack

    s.push(start);

    visited[start.row][start.col] = true;
    parent[start.row][start.col] = start;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    bool found = false;
    int explored = 0;

    Position* exploredList = new Position[rows * cols]; 

    while (!s.isEmpty()){
        Position current = s.pop();

        explored++;
        exploredList[explored - 1] = current; 

        if (samePosition(current, exit)){
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++){
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];

            if (isValid(maze, newRow, newCol) &&!visited[newRow][newCol]){
                Position next;

                next.row = newRow;
                next.col = newCol;

                visited[newRow][newCol] = true;

                parent[newRow][newCol] = current;

                s.push(next);
            }
        }
    }

    SolveResult result;

    result.found = found;
    result.exploredcells = explored;
    result.pathlength = 0;
    result.path = NULL;
    result.exploredList = exploredList; 

    if (found){
        result.path = reconstructPath(parent, start, exit,rows, cols, result.pathlength);
    }

    freeGrids(visited, parent, rows);

    return result;
}


SolveResult Solver::bfs(Maze& maze){
    int rows = maze.getRows();
    int cols = maze.getCols();

    bool** visited = createVisited(rows, cols);
    Position** parent = createParent(rows, cols);

    Position start = maze.getStart();
    Position exit = maze.getExit();

    Queue q(rows * cols);

    q.enqueue(start);

    visited[start.row][start.col] = true;
    parent[start.row][start.col] = start;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    bool found = false;
    int explored = 0;

    Position* exploredList = new Position[rows * cols]; 

    while (!q.isEmpty()){
        Position current = q.dequeue();

        explored++;
        exploredList[explored - 1] = current; 

        if (samePosition(current, exit)){
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++){
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];

            if (isValid(maze, newRow, newCol) &&!visited[newRow][newCol]){
                Position next;

                next.row = newRow;
                next.col = newCol;

                visited[newRow][newCol] = true;

                parent[newRow][newCol] = current;
                q.enqueue(next);
            }
        }
    }

    SolveResult result;

    result.found = found;
    result.exploredcells = explored;
    result.pathlength = 0;
    result.path = NULL;
    result.exploredList = exploredList; 

    if (found){
        result.path = reconstructPath(
            parent, start, exit,
            rows, cols, result.pathlength);
    }

    freeGrids(visited, parent, rows);

    return result;
}

