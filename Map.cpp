#include "Map.h"

//Map Constructor
Map::Map() : enc_state(false), witch(false),complete(false),
    xPos(5), yPos(9)
{
    /*
      Generates generic map
      with Player located at
      foot of forest
    */

    //Check if Player is not spawned on same location as witch
    do {
        witch_xPos = rand() % 10;
        witch_yPos = rand() % 10;
    } while (witch_xPos != xPos && witch_yPos != yPos);

    //Generate generic map
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            if (x == xPos && y == yPos) {
                map[y][x] = '.'; //Location Marker
            }
            else {
                map[y][x] = '#'; //Trees Marker
            }
        }
    }

    map[9][5] = 'T';

    //Uncomment for Testing purposes
    cout << witch_xPos << "," << witch_yPos << endl;
}

//Reset entire map
void Map::reset() {
    enc_state = false;
    xPos = 5;
    yPos = 9;
    
    if (!witch) {
        witch_xPos = rand() % 10;
        witch_yPos = rand() % 10;
    }
    else {
        witch_xPos = -1, witch_yPos = -1;
    }

    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            if (x == xPos && y == yPos) {
                map[y][x] = '.'; //Location Marker
            }
            else {
                map[y][x] = '#'; //Trees Marker
            }
        }
    }

    map[9][5] = 'T';
}

//Checks if anticipated direction goes out of bounds
const bool Map::outOfBounds(const char c) {
    if ((xPos == 0 && c == 'l') ||
        (xPos == 9 && c == 'r') ||
        (yPos == 9 && c == 'd') ||
        (yPos == 0 && c == 'u')) {
        if (xPos != 5 && yPos != 9) {
            cerr << "Out of Bounds" << endl;
        }
        return true;
    }
    else {
        return false;
    }
}

//Returns status of witch bool
const bool Map::witchFound() const {
    return witch;
}

//Returns true if Player moved, else false
void Map::movePos(const char c) {
    //If argument is invalid...
    if (c != 'l' && c != 'r' && c != 'u' && c != 'd') {
        cerr << "Invalid input..." << endl;
    }
    //else...
    else {
        //If anticipated movement DOES NOT goes out of bounds
        if (!outOfBounds(c)) {
            /*
              y-coordinate = 9
              implies Player at foot
              of forest
            */

            //If spot is not discovered, spot become ' '
            if (map[yPos][xPos] != ' ' && 
                map[yPos][xPos] != '*' &&
                map[yPos][xPos] != 'T') {
                map[yPos][xPos] = ' ';
            }

            //Modify coordinate positions appropriately
            if (c == 'l') {
                --xPos;
            }
            else if (c == 'r') {
                ++xPos;
            }
            else if (c == 'u') {
                --yPos;
            }
            else if (c == 'd') {
                ++yPos;
            }
            
            //Checks if enemy is encountered if spot on map
            // is a '#'
            if (map[yPos][xPos] == '#') {
                enc_state = true;
            }
            else {
                enc_state = false;
            }

            //Sets current position with '.'
            if (map[yPos][xPos] != 'T' && map[yPos][xPos] != '*') {
                map[yPos][xPos] = '.';
            }
            
            //Checks if witch is found at location
            if (xPos == witch_xPos && yPos == witch_yPos) {
                //Update witch bool
                witch = true;

                //Set witch Marker,'*', on Position
                map[yPos][xPos] = '*';
            }
        }
        else{
          enc_state = false;
        }
        
    }
}

//Returns true if an enemy is encountered on coordinate position
const bool Map::encounter() {
    return enc_state;
}

//Return home; resets entire map if 
void Map::home() {
    if (complete) {
        reset();
    }
    cout << "Heading back home..." << endl;
}

//Get X or Y-Coordinate
const int Map::getPos(const char arg) const
{
    if (arg == 'x')
        return xPos;
    else
        return yPos;
}

//Get a Pointer to the map member variable
const char* Map::getMap() const
{
    return *map;
}

const bool Map::completed() const{
    return complete;
}

//Display Map of Forest
ostream& operator<<(ostream& os, const Map& m) {
    for (auto& yMap : m.map) {
        for (const auto& xyMap : yMap) {
            os << xyMap;
        }
        cout << endl;
    }
    cout << "You are currently located ";
    switch (m.yPos) {
    case 10:
        os << "in the Town" << endl;
        break;
    default:
        os << "in the Forest at position (" << m.xPos << "," << m.yPos << ")\n" << endl;
    }
    return os;
}

//Checks if Player Response is Valid
void Map::invResponse(char& choice) const {
    while (choice != 'Y' &&
        choice != 'y' &&
        choice != 'N' &&
        choice != 'n') {
        cerr << "Invalid argument. Try again: ";
        cin >> choice;
    }
}