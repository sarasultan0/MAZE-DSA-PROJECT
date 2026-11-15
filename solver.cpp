
#include "Solver.h"

// ========================================
// HELPER 1: CHECK VALID POSITION
// ========================================

bool isValid(Maze& maze, int row, int col)
{
    if (row < 0 || row >= maze.getRows())
        return false;

    if (col < 0 || col >= maze.getCols())
        return false;

    if (maze.getCell(row, col) == '#')
        return false;

    return true;
}


// ========================================
// HELPER 2: COMPARE POSITIONS
// ========================================

bool samePosition(Position a, Position b)
{
    return a.row == b.row && a.col == b.col;
}


// ========================================
// HELPER 3: ALLOCATE VISITED GRID
// ========================================

bool** createVisited(int rows, int cols)
{
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


// ========================================
// HELPER 4: ALLOCATE PARENT GRID
// ========================================

Position** createParent(int rows, int cols)
{
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


// ========================================
// HELPER 5: FREE GRIDS
// ========================================

void freeGrids(bool** visited, Position** parent, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] visited[i];
        delete[] parent[i];
    }

    delete[] visited;
    delete[] parent;
}


// ========================================
// HELPER 6: RECONSTRUCT PATH
// ========================================

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

    while (!samePosition(current, start))
    {
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

    for (int i = count - 1; i >= 0; i--)
    {
        path[i] = current;

        if (i > 0)
        {
            current = parent[current.row][current.col];
        }
    }

    pathLength = count;

    return path;
}


// ========================================
// PART 1: DEPTH FIRST SEARCH
// ========================================

SolveResult Solver::dfs(Maze& maze)
{
    int rows = maze.getRows();
    int cols = maze.getCols();

    bool** visited = createVisited(rows, cols);
    Position** parent = createParent(rows, cols);

    Position start = maze.getStart();
    Position exit = maze.getExit();

    // Create custom Stack

    Stack s(rows * cols);

    s.push(start);

    visited[start.row][start.col] = true;
    parent[start.row][start.col] = start;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    bool found = false;
    int explored = 0;

    // DFS traversal

    while (!s.isEmpty())
    {
        Position current = s.pop();

        explored++;

        // Check exit

        if (samePosition(current, exit))
        {
            found = true;
            break;
        }

        // Explore neighbors

        for (int i = 0; i < 4; i++)
        {
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];

            if (isValid(maze, newRow, newCol) &&
                !visited[newRow][newCol])
            {
                Position next;

                next.row = newRow;
                next.col = newCol;

                visited[newRow][newCol] = true;

                parent[newRow][newCol] = current;

                s.push(next);
            }
        }
    }

    // Prepare result

    SolveResult result;

    result.found = found;
    result.exploredcells = explored;
    result.pathlength = 0;
    result.path = NULL;

    if (found)
    {
        result.path = reconstructPath(
            parent, start, exit,
            rows, cols, result.pathlength);
    }

    freeGrids(visited, parent, rows);

    return result;
}


// ========================================
// PART 2: BREADTH FIRST SEARCH
// ========================================

SolveResult Solver::bfs(Maze& maze)
{
    int rows = maze.getRows();
    int cols = maze.getCols();

    bool** visited = createVisited(rows, cols);
    Position** parent = createParent(rows, cols);

    Position start = maze.getStart();
    Position exit = maze.getExit();

    // Create custom Queue

    Queue q(rows * cols);

    q.enqueue(start);

    visited[start.row][start.col] = true;
    parent[start.row][start.col] = start;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    bool found = false;
    int explored = 0;

    // BFS traversal

    while (!q.isEmpty())
    {
        Position current = q.dequeue();

        explored++;

        // Check exit

        if (samePosition(current, exit))
        {
            found = true;
            break;
        }

        // Explore neighbors

        for (int i = 0; i < 4; i++)
        {
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];

            if (isValid(maze, newRow, newCol) &&
                !visited[newRow][newCol])
            {
                Position next;

                next.row = newRow;
                next.col = newCol;

                // Mark visited when enqueued

                visited[newRow][newCol] = true;

                // Store parent

                parent[newRow][newCol] = current;

                q.enqueue(next);
            }
        }
    }

    // Prepare result

    SolveResult result;

    result.found = found;
    result.exploredcells = explored;
    result.pathlength = 0;
    result.path = NULL;

    if (found)
    {
        result.path = reconstructPath(
            parent, start, exit,
            rows, cols, result.pathlength);
    }

    freeGrids(visited, parent, rows);

    return result;
}

