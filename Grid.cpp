#include "Grid.h"


//This is the constructor for the board, and it creates a 2D array of row x col, fills it with spaces, and puts constraints into the grid.
Grid::Grid(int row, int col, std::vector<int> &arowsOccupied, std::vector<int> &acolsOccupied, std::vector<std::string> &allships, const std::vector<Constraint> &constraintsList)
{
    rows = row;
    columns = col;
    ships = allships;
    maxLength = 0;

    grid = new char *[rows];

    rowsOccupied = arowsOccupied; //These are constants to use in printing/resetting rowsCount/colsCount
    colsOccupied = acolsOccupied;

    rowsCount = arowsOccupied; //Length will be subtracted from rowsCount[row] to keep track of space available
    colsCount = acolsOccupied;

    for (int i = 0; i < rows; i++)
    {
        grid[i] = new char[columns];
        for (int j = 0; j < columns; j++)
        {
            grid[i][j] = ' '; //Initialized grid from this nested for loop populated with ' '
        }
    }
    for (unsigned int i = 0; i < constraintsList.size(); i++)
    {
        grid[constraintsList[i].x][constraintsList[i].y] = constraintsList[i].type;
    }
}
//As this program uses coordinates to place ships, and each ship (custom struct) has a vector of all the points it occupies,
//the proper characters are placed at the starts and ends of each ship with X's between if it is not a submarine.
//Each point is accessed to find the coordinate of the occupied space, and then the character is placed.
void Grid::updateGrid()
{
    for (unsigned int i = 0; i < placedShips.size(); i++)
    {   
        if (placedShips[i].length == 1) //Submarines
        {
            grid[placedShips[i].points[0].x][placedShips[i].points[0].y] = 'o';
        }
        else
        { //Anything other than subs

            if (placedShips[i].horizontal) //Horizontal ships case
            {
                grid[placedShips[i].start.x][placedShips[i].start.y] = '<';
                for (int j = 1; j < placedShips[i].length - 1; j++)
                {
                    grid[placedShips[i].points[j].x][placedShips[i].points[j].y] = 'X';
                }
                grid[placedShips[i].points[placedShips[i].length - 1].x][placedShips[i].points[placedShips[i].length - 1].y] = '>';

            }
            else
            { //Vertical ships

                grid[placedShips[i].start.x][placedShips[i].start.y] = '^';
                for (int j = 1; j < placedShips[i].length - 1; j++)
                {
                    grid[placedShips[i].points[j].x][placedShips[i].points[j].y] = 'X';
                }
                grid[placedShips[i].points[placedShips[i].length - 1].x][placedShips[i].points[placedShips[i].length - 1].y] = 'v';

            }
        }
    }
}

//Gets name of ship based on length
const std::string Grid::getName(int length){
        if (length == 1)
        {
            return "submarine";
        }
        if (length == 2)
        {
            return "destroyer";
        }
        if (length == 3)
        {
            return "cruiser";
        }
        if (length == 4)
        {
            return "battleship";
        }
        if (length == 5)
        {
            return "carrier";
        }
        if (length == 6)
        {
            return "cargo";
        }
        if (length == 7)
        {
            return "tanker";
        }
}
//This function mimics the demonstrated output from the homework PDF, and loops through
//every index of "grid" and prints its value. 
void Grid::printGrid()
{
    std::cout << "Solution: \n";
    std::string temp;
    for(unsigned int i = 0; i < placedShips.size(); i++){
         temp = getName(placedShips[i].length);
        while(temp.size() < maxLength+1){
            temp.append(" ");
        }
        std::cout << temp << placedShips[i].start.x << " " << placedShips[i].start.y;
        if(placedShips[i].length > 1){
            if(placedShips[i].horizontal){
                std::cout << " horizontal";
            }else{
                std::cout << " vertical";
            }
        }
        std::cout << "\n";
    }

    std::cout << "+";
    for (int i = 0; i < columns; i++)
    {
        std::cout << "-";
    }
    std::cout << "+"
              << "\n";
    for (int i = 0; i < rows; i++)
    {
        std::cout << "|";
        for (int j = 0; j < columns; j++)
        {
            std::cout << grid[i][j];
        }
        std::cout << "|" << rowsOccupied[i] << "\n";
    }
    std::cout << "+";
    for (int i = 0; i < columns; i++)
    {
        std::cout << "-";
    }
    std::cout << "+" << "\n ";
    for(unsigned int i = 0; i < colsOccupied.size(); i++){
        std::cout << colsOccupied[i];
    }
}
//This function compares all the currently placed ships, and ensures that they do not touch in any direction (including diagonals).
//This is done by subtracting each coordinate from one ship from each coordinate from the other ship, and I found that
//the resulting absolute value of the coordinate must be (0,1), (1,0), or (1,1) if it one of the points on a ship is adjacent to the other.
//If none of the coordinate subtractions result in those coordinates specified, then the current version of the grid is valid.
const bool Grid::isValid()
{
    for (unsigned int i = 0; i < placedShips.size(); i++) //Grabs index of first ship to use in comparisons
    {
        for (unsigned int j = i + 1; j < placedShips.size(); j++) //Grabs index of second ship
        {
            for (unsigned int k = 0; k < placedShips[i].points.size(); k++) //First ship's points to be iterated through
            {
                for (unsigned int l = 0; l < placedShips[j].points.size(); l++) //Second ship's points to be compared against first ships
                {

                    if (placedShips[i].points[k].x == placedShips[j].points[l].x && placedShips[i].points[k].y == placedShips[j].points[l].y)
                    {
                        //Check for if the two ships have any points overlapping
                        return false;
                    }
                    //These next three if statements are used to check if the difference between any two points between
                    //the two ships are (0,1) (1,0) or (1,1)
                    if (abs(placedShips[i].points[k].x - placedShips[j].points[l].x) == 1 && abs(placedShips[i].points[k].y - placedShips[j].points[l].y) == 0)
                    {
            
                        return false;
                    }
                    if (abs(placedShips[i].points[k].x - placedShips[j].points[l].x) == 0 && abs(placedShips[i].points[k].y - placedShips[j].points[l].y) == 1)
                    {
                        return false;
                    }
                    if (abs(placedShips[i].points[k].x - placedShips[j].points[l].x) == 1 && abs(placedShips[i].points[k].y - placedShips[j].points[l].y) == 1)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

//This function initializes a ship, given the initial coordinate, length, and whether it's horizontal.  
//The coordinates of the created Ship are generated based on if the ship is horizontal, and the for loop simply
//adds each coordinate to coords to be passed to the Ship points.
void Grid::createShip(int x, int y, int length, bool isHorizontal)
{
    std::vector<Coordinate> coords; //Asign Ship struct properties
    Coordinate temp;
    temp.x = x;
    temp.y = y;
    Ship aShip;
    aShip.horizontal = isHorizontal;
    aShip.length = length;
    aShip.start = temp;

    for (int i = 0; i < length; i++)
    {
        coords.push_back(temp);
        if (isHorizontal) //If ship is horizontal, add to y coordinate
        {                 //with constant x value
            temp.y++;
        }
        else
        {               //Vice-versa to get coordinates of vertical ship
            temp.x++;
        }
    }

    aShip.points = coords;
    placedShips.push_back(aShip);
}


//This is the final check on the board to ensure
//that the row space requirements are met for the solution.
//Lengths are subtracted from rowsCount and colsCount 
//to make both vectors only have values of 0 remaining.
const bool Grid::spacesSatisfied(){

    for(unsigned int i = 0; i < rowsCount.size(); i++){
        if(rowsCount[i] != 0)
            return false;
    }
    for(unsigned int i = 0; i < colsCount.size(); i++){
        if(colsCount[i] != 0)
            return false;
    }
    return true;
}

//This is a simple check to make sure there is enough space in the column
//to place the next ship into.
const bool Grid::checkColSpaces(){
    for(unsigned int i = 0; i < colsCount.size(); i++){
        if(colsCount[i] < 0){
            return false;
        }
    }
    return true;
}
//Same as checkColSpaces but adjusted to check rows.
const bool Grid::checkRowSpaces(){
    for(unsigned int i = 0; i < rowsCount.size(); i++){
        if(rowsCount[i] < 0){
            return false;
        }
    }
    return true;
}

//This is the recursive function which places a boat at (row, col) horizontally, and if it is valid, the boat will remain in place.
//If it is not a valid placement, then the ship will be removed from the board and tested again at (row, col+1).
//The base cases are simply to move the ship to (row+1, 0) when it can no longer fit in the current row.  If it reaches the end
//without placing the ship, it attempts to place it vertically.
bool Grid::placeShipsHorizontal(int row, int col, int length)
{
    if (row == rows && col+length >= columns) //The end case
    {
        return placeShipsVertical(0, 0, length); //Vertical call
    }
    if (col+length > (columns-1)) //if this statement is true,
    {                                //the current ship being placed cannot fit in the row                    
        return placeShipsHorizontal(row + 1, 0, length); //Increment row
    }

    createShip(row, col, length, true); //Create ship and place on board
    rowsCount[row] -= length; 

    for(int i = col; i < (length+col); i++){
        colsCount[i]--; //Remove one from each column the ship occupies
    } 

    if (isValid() && rowsCount[row] >= 0 && checkColSpaces())
    { //There must be space in each column, the row, and it cannot be
        //adjacent to any other ship
        return true;
    }
    else
    {
        rowsCount[row] += length;
        for(int i = col; i < (length+col); i++){
            colsCount[i]++; //Undo column/row counts
        }
        placedShips.pop_back(); //Remove placed ship
        return placeShipsHorizontal(row, col + 1, length); //Try again at next position
    }

}

//This is a copy and paste of placeShipsHorizontal, but instead it places ships vertically, and increments
//columns when the ship cannot fit in the current column.
bool Grid::placeShipsVertical(int row, int col, int length)
{
    if (col == columns && row+length >= (rows))
    {
        return false;
    }

    if (row+length > (rows+1))
    {
        return placeShipsVertical(0, col + 1, length);
    }

    createShip(row, col, length, false);
    for(int i = row; i < (length+row); i++){
        rowsCount[i]--;
    }
    colsCount[col] -= length;
    
    if (isValid() && checkRowSpaces() && colsCount[col] >= 0)
    {
        return true;
    }
    else
    {
        for(int i = row; i < (length+row); i++){
        rowsCount[i]++;
        }
        colsCount[col] += length;
        placedShips.pop_back();
        return placeShipsVertical(row + 1, col, length);
    }
}

//This handles placing the ships on the boards.  It clears the board, resets
//rows and cols Count, and begins placing each ship.
void Grid::placeShips()
{
    getLengths();
        rowsCount = rowsOccupied;
        colsCount = colsOccupied;
        clearBoard();
        std::sort(lengths.rbegin(), lengths.rend());
        for (unsigned int i = 0; i < lengths.size(); i++)
        {
            placeShipsHorizontal(0,0, lengths[i]);
        }
    if(!spacesSatisfied()){
        std::cout << "No solutions.";
    }else{
        updateGrid();
        printGrid();
    }
}

//Clears grid[][] characters, and removes all ships from the board
void Grid::clearBoard()
{
    while (placedShips.size() > 0)
    {
        placedShips.pop_back();
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            grid[i][j] = ' ';
        }
    }
}

//This is used to set lengths into the lengths vector of each ship
//that is going to be used.
void Grid::getLengths()
{
    for(unsigned int i = 0; i < ships.size(); i++){
        if(ships[i].size() > maxLength){
            maxLength = ships[i].size();
        }
    }
    for (unsigned int i = 0; i < ships.size(); i++)
    {
        if (ships[i] == "submarine")
        {
            lengths.push_back(1);
        }
        if (ships[i] == "destroyer")
        {
            lengths.push_back(2);
        }
        if (ships[i] == "cruiser")
        {
            lengths.push_back(3);
        }
        if (ships[i] == "battleship")
        {
            lengths.push_back(4);
        }
        if (ships[i] == "carrier")
        {
            lengths.push_back(5);
        }
        if (ships[i] == "cargo")
        {
            lengths.push_back(6);
        }
        if (ships[i] == "tanker")
        {
            lengths.push_back(7);
        }
    }
}

