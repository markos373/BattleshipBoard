#ifndef _GRID_H_
#define _GRID_H_
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <sstream>

struct Constraint
{
        int x;
        int y;
        char type;
};
struct Coordinate
{
    int x;
    int y;
};
//struct, which makes a Ship with the properties below
struct Ship
{
        Coordinate start;
        int length;
        std::vector<Coordinate> points;
        bool horizontal;
};
class Grid
{
    
    public:
        Grid(int row, int col, std::vector<int>& arowsOccupied, std::vector<int>& acolsOccupied, std::vector<std::string>& allships, const std::vector<Constraint>& constraintsList);
        void updateGrid();
        void printGrid();
        const bool isValid();
        void createShip(int x, int y, int length, bool isHorizontal);
        bool placeShipsHorizontal(int row, int col, int length);
        bool placeShipsVertical(int row, int col, int length);
        void getLengths();
        const std::string getName(int l);
        const bool checkRowSpaces();
        const bool checkColSpaces();
        const bool spacesSatisfied();
        void clearBoard();
        void placeShips();

    private:
        int rows;
        int columns;
        std::vector<int> rowsOccupied;
        std::vector<int> colsOccupied;
        std::vector<int> rowsCount;
        std::vector<int> colsCount;
        char** grid;
        std::vector<std::string> ships;
        std::vector<int> lengths;
        std::vector<Ship> placedShips;
        std::vector<std::vector<Ship> > solutions;
        unsigned int maxLength;

};
#endif