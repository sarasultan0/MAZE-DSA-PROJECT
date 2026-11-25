#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Position.h"

using namespace std;

class Stack{
private:
    Position* arr;
    int top;
    int capacity;

public:

    Stack(int size){
        top = -1;
        capacity = size;
        arr = new Position[capacity];
    }

    void push(Position p){
        if (isFull()){
            resize();
        }
        arr[++top] = p;
    }

    Position pop(){
        if (isEmpty()){
            Position p;
            p.row = -1;
            p.col = -1;
            return p;
        }

        return arr[top--];
    }

    bool isEmpty(){
        return top == -1;
    }

    bool isFull(){
        return top == capacity - 1;
    }

    void resize(){
        int newCapacity = capacity * 2;

        Position* newArr = new Position[newCapacity];

        for (int i = 0; i <= top; i++){
            newArr[i] = arr[i];
        }

        delete[] arr;

        arr = newArr;
        capacity = newCapacity;
    }

    Position peek(){
        if (isEmpty()){
            Position p;
            p.row = -1;
            p.col = -1;
            return p;
        }

        return arr[top];
    }

    ~Stack(){
        delete[] arr;
    }
};


class Maze{
private:

    char** grid;

    int rows;
    int cols;

    int startRow;
    int startCol;

    int exitRow;
    int exitCol;


public:

    Maze(int r, int c){
        rows = r;
        cols = c;

        startRow = 1;
        startCol = 1;

        exitRow = rows - 2;
        exitCol = cols - 2;

        if (exitRow % 2 == 0)
            exitRow--;

        if (exitCol % 2 == 0)
            exitCol--;

        grid = new char*[rows];

        for (int i = 0; i< rows; i++){
            grid[i] = new char[cols];
        }

        initializeMaze();

        srand(time(0));
    }


    void initializeMaze(){
        for (int i= 0; i< rows; i++){
            for (int j= 0; j< cols; j++)
            {
                grid[i][j] = '#';
            }
        }
    }


    void generateMaze(){
        initializeMaze();
        carvePassages(startRow, startCol);
        setStartAndExit();
    }

    void createLoops(){
        for (int i= 1; i< rows- 1; i++){
            for (int j= 1; j < cols - 1; j++){
                if (grid[i][j] != '#')
                    continue;

                bool horizontalWall= (i % 2 == 1 && j % 2 == 0);
                bool verticalWall   = (i % 2 == 0 && j % 2 == 1);

                bool separatesTwoPassages = false;

                if (horizontalWall && grid[i][j - 1] != '#' && grid[i][j + 1] != '#')
                    separatesTwoPassages = true;

                if (verticalWall && grid[i - 1][j] != '#' && grid[i + 1][j] != '#')
                    separatesTwoPassages = true;

                if (separatesTwoPassages && rand() % 10 == 0)
                    grid[i][j] = '.';
            }
        }
    }


    void carvePassages(int row, int col){
        grid[row][col] = '.';

        int directions[4] = {0, 1, 2, 3};

        for (int i = 3; i > 0; i--){
            int j = rand() % (i + 1);

            int temp = directions[i];
            directions[i] = directions[j];
            directions[j] = temp;
        }

        for (int i = 0; i < 4; i++){
            int newRow = row;
            int newCol = col;

            if (directions[i] == 0)
                newRow -= 2;       // UP

            else if (directions[i] == 1)
                newRow += 2;       // DOWN

            else if (directions[i] == 2)
                newCol -= 2;       // LEFT

            else if (directions[i] == 3)
                newCol += 2;       // RIGHT

            if (isValid(newRow, newCol)){
                if (grid[newRow][newCol] == '#'){
                    // Removing wall between cells
                    grid[(row + newRow) / 2][(col + newCol) / 2] = '.';

                    carvePassages(newRow, newCol);
                }
            }
        }
    }

    bool isValid(int row, int col){
        if (row > 0 && row < rows - 1 &&col > 0 && col < cols - 1){
            return true;
        }
        return false;
    }

    void setStartAndExit(){
        grid[startRow][startCol] = 'S';
        grid[exitRow][exitCol] = 'E';
    }


    bool hasValidPath(){
        bool** visited = new bool*[rows];

        for (int i = 0; i < rows; i++){
            visited[i] = new bool[cols];

            for (int j = 0; j < cols; j++){
                visited[i][j] = false;
            }
        }

        Stack s(rows * cols);

        Position start;
        start.row = startRow;
        start.col = startCol;

        s.push(start);

        visited[startRow][startCol] = true;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        bool found = false;

        while (!s.isEmpty()){
            Position current = s.pop();

            int row = current.row;
            int col = current.col;

            if (row == exitRow && col == exitCol){
                found = true;
                break;
            }

            for (int i = 0; i < 4; i++){
                int newRow = row + dr[i];
                int newCol = col + dc[i];

                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols){
                    if (grid[newRow][newCol] != '#' && !visited[newRow][newCol]){
                        visited[newRow][newCol] = true;

                        Position next;
                        next.row = newRow;
                        next.col = newCol;

                        s.push(next);
                    }
                }
            }
        }

        for (int i = 0; i < rows; i++){
            delete[] visited[i];
        }

        delete[] visited;
        return found;
    }


    void displayMaze(){
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                cout << grid[i][j] << " ";
            }

            cout << endl;
        }
    }

    int getRows(){
        return rows;
    }
    int getCols(){
        return cols;
    }
    char getCell(int row, int col){
        return grid[row][col];
    }

    Position getStart(){
        Position p;
        p.row = startRow;
        p.col = startCol;
        return p;
    }

    Position getExit(){
        Position p;
        p.row = exitRow;
        p.col = exitCol;
        return p;
    }


    ~Maze(){
        for (int i = 0; i < rows; i++){
            delete[] grid[i];
        }

        delete[] grid;
    }

};

#endif

