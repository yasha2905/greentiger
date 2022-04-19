#ifndef SEEBATTLE_SEEBATTLE_H
#define SEEBATTLE_SEEBATTLE_H

#endif //SEEBATTLE_SEEBATTLE_H
#include <iostream>
#include <vector>

enum class SIDE {BLACK=0, WHITE, UNKNOWN};
enum class STATUS {DEAD =0, ALIVE, UNKNOWN};

// =================================================== class ship
class ship{
private:
    SIDE blackORwhite; // ship is BLACK or WHITE
    int X1, Y1, X2, Y2; // coordinates
    STATUS shipStatus; //ship is DEAD or ALIVE
public:
    ship(SIDE, int,int,int,int,STATUS);
    SIDE GetShipSide();
    int getX1();
    int getX2();
    int getY1();
    int getY2();
    STATUS GetShipStatus();
    void SetShipStatus(STATUS);
};

// =================================================== class Field
class Field{ // Field of battle array(10x10)
private:
    int n, m;
    int** arr;
public:
    Field(int, int);
    void ShowField(); // to represent
    bool SetFieldBusy(int,int,int,int,int,int); // to set up new ship on the field
    int getCoord(int,int);
    void Shot();
};

// =================================================== class shipList
class shipList{ // list of ships to use iteration for all requests
private:
    std::vector<ship*> vectPtrsShips;
    std::vector<ship*>::iterator iter;
    Field* ptrField;
public:
    ~shipList();
    void insertShip(ship*); // new ship to add in ship list
    bool isAllWhitesDead(); // check if all whites are dead in list
    bool isAllBlacksDead(); // check if all blacks  are dead in list
    void checkShip(Field*); // to check if the new shot hit the ship and set it DEAD if all cells damaged
};

// ================================================== class ButtleScreen
class BattleScreen{ // interaction with user during battle
private:
    shipList* ptrShipList;
    Field* ptrField;

public:
    BattleScreen(shipList* ptrSL, Field* ptrF):ptrShipList(ptrSL),ptrField(ptrField){}
    void Battle (Field*, shipList*);
};

// =================================================== class shipInputScreen
class shipInputScreen{ // interaction with user main menu
private:
    shipList* ptrShipList;
    Field* ptrField;

    std::string sName;
public:
    shipInputScreen(shipList* ptrSL, Field* ptrF):ptrShipList(ptrSL),ptrField(ptrField){}
    void getShip(Field*);
};

// =================================================== class userInterface
class userInterface{
private:
    shipList*           ptrShipList;
    Field*              ptrField;
    shipInputScreen*    ptrShipInputScreen;
    BattleScreen*       ptrBattleScreen;

public:
    userInterface();
    ~userInterface();
    void interact();
};
