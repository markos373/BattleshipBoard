#include "Grid.h"

int main(int argc, char* argv[]){
    std::ifstream in_str(argv[1]);
    if(!in_str.good()){
        std::cerr << "Failed to open " << argv[1] << " to read.\n";
    }
    int rows;
    int columns;
    std::string temp;
    in_str >> temp >> rows >> columns;

    std::vector<int> rowOccupied(rows);
    std::vector<int> colOccupied(columns);
    
    in_str >> temp;
    for(int i = 0; i < rows; i++)
    {
        in_str >> rowOccupied[i];
    }
    in_str >> temp;
    for(int i = 0; i < columns; i++)
    {
        in_str >> colOccupied[i];
    }
    std::vector<std::string> ships;
    std::vector<Constraint> constraints;
    Constraint temp1;

    while(in_str >> temp)
    {
        if(temp == "constraint")
        {
            in_str >> temp1.x >> temp1.y >> temp1.type;
            constraints.push_back(temp1);
        }else
        {
        ships.push_back(temp);
        }
    }
    Grid test(rows, columns, rowOccupied, colOccupied, ships, constraints);
    test.placeShips();
    
}