#pragma once
#include <iostream>

using namespace std;

class Map
{
public:
    //Constructor
    Map();

    //Manipulate Position
    void movePos(const char);
    const bool encounter();
    void home();

    //Getters
    const int getPos(const char) const;
    const char* getMap() const;

    //Gameplay Status
    const bool witchFound() const;
    const bool completed() const;

    //Reset Map
    void reset();

    friend ostream& operator<<(ostream&, const Map&);
private:
    char map[10][10];                   //Forest Map
    int xPos;                           //X-coordinate
    int yPos;                           //Y-coordinate
    bool enc_state;                     //Story Tracker

    bool witch;
    int witch_xPos, witch_yPos;         //Healer X,Y-coordinates

    bool complete;                      //Game completion Status

    void invResponse(char&) const;      //Checks for invalid responses
    const bool outOfBounds(const char); //Checks if out of bounds
};