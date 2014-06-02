/* File: life.cpp
 * ---------------
 *  This program implements the game of life.
 *           
 * By            : Jingxin Zhu
 * Last Modified : 06/02/2014
 */
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
using namespace std;

void printIntro();
void fileInput(Grid<string> &);
void printGrid(Grid<string> &);
void nextGen(Grid<string> &);
int getNeighbors(Grid<string> &, int, int);
string nextCell(string, int);
void animate(Grid<string> &);

int main() {
    setConsoleSize(700, 400);

    Grid<string> game;

    printIntro();

    fileInput(game);

    printGrid(game);

    while (true) {
        string command;
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> command;
        if (command == "q") { 
            // quit program
            break;
        } else if (command == "a") {
            // animate lifecycle
            animate(game);
        } else {
            // update to next generation
            nextGen(game);
            printGrid(game);
        }
    }
    cout << "Have a nice Life!" << endl;
    return 0;
}

void printIntro() {
    cout << "Welcome to the CS 106B Game of Life," << endl
         << "a simulation of the lifecycle of a bacteria colony." << endl
         << "Cells (X) live and die by the following rules:" << endl
         << "- A cell with 1 or fewer neighbors dies." << endl
         << "- Locations with 2 neighbors remain stable." << endl
         << "- Locations with 3 neighbors will create life." << endl
         << "- A cell with 4 or more neighbors dies." << endl
         << endl;
}

/* Read in input file, first line of which indicates row numbers,
 * second line of which indicates column numbers.
 * Assume file exists and filenames are correctly input.
 */
void fileInput(Grid<string>& grid) {
    string filename;
    cout << "Grid input file name? ";
    cin >> filename;

    ifstream input;
    input.open(filename.c_str());
    string line;
    getline(input, line);
    int nRows = stringToInteger(line);
    getline(input, line);
    int nCols = stringToInteger(line);
    grid.resize(nRows, nCols);
    for (int r = 0; r < nRows; r++) {
        getline(input, line);
        for (int c = 0; c < nCols; c++) {
            grid[r][c] = line[c];
        }
    }
    input.close();
}

void printGrid(Grid<string> &grid) {
    for (int r = 0; r < grid.numRows(); r++) {
        for (int c = 0; c < grid.numCols(); c++) {
            cout << grid[r][c];
        }
        cout << endl;
    }
}

/* update to next generation based on the number of 
 * each cell's nNeighbors.
 */
void nextGen(Grid<string> &grid) {
    Grid<string> tempGrid(grid.numRows(), grid.numCols());
    int nNeighbors;
    for (int r = 0; r < grid.numRows(); r++) {
        for (int c = 0; c < grid.numCols(); c++) {
            nNeighbors = getNeighbors(grid, r, c);
            tempGrid[r][c] = nextCell(grid[r][c],nNeighbors);
        }
    }
    grid = tempGrid;
}

int getNeighbors(Grid<string> &grid, int row, int col) {
    int count = 0;
    for (int i = row - 1; i < row + 2; i++) {
        for (int j = col -1; j < col + 2; j++) {
            if (grid.inBounds(i, j)){
                if (grid[i][j] == "X") {
                    count++;
                }
            }
        }
    }
    if (grid[row][col] == "X") {
        count--;
    }
    return count;
}

/* update each cell based on following rules:
 *  - A cell with 1 or fewer neighbors dies.
 *  - Locations with 2 neighbors remain stable.
 *  - Locations with 3 neighbors will create life.
 *  - A cell with 4 or more neighbors dies.
 */
string nextCell(string curr, int n) {
    string result;
    if (n <= 1) {
        result = "-";
    } else if (n == 2) {
        result = curr;
    } else if (n == 3) {
        result = "X";
    } else if (n >= 4) {
        result = "-";
    }
    return result;
}

void animate(Grid<string>& grid) {
    string nFrames;
    cout << "How many frames? ";
    cin >> nFrames;
    int n = stringToInteger(nFrames);
    for (int i = 0; i < n; i++) {
        clearConsole();
        nextGen(grid);
        printGrid(grid);
        pause(100);
    }
}
