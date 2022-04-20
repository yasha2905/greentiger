#include <iostream>
#include <vector>
#include <cstdlib>
#include "SeeBattle.h"


void clear_screen(){
#ifdef WINDOWS
    std::system ("cls");
#else // Assume POSIX
    std::system("clear");
#endif
}

//////////////////////////////////////////////////////// Global structure and functions
struct setupShips{
    int nW1=0; int nW2=0; int nW3=0; int nW4=0; int nB1=0; int nB2=0; int nB3=0; int nB4=0;
};

setupShips counter; // global counter setup ships


//---------------------------------------------------------------------------------- checkWhiteCount
bool checkWhiteCount(){ // if all together whites less 10
    if ((counter.nW1 + counter.nW2 + counter.nW3 + counter.nW4) > 10) {
        std::cout << "White ships reached maximum \n";
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------------- checkBlackCount
bool checkBlackCount(){ // if all together blacks less 10
    if ((counter.nB1 + counter.nB2 + counter.nB3 + counter.nB4) > 10) {
        std::cout << "Black ships reached maximum \n";
        return false;
    }
    return true;
}
// -------------------------------------------------------------------------------- mainMenuCheck
bool mainMenuCheck(int select){
    if (select == 1 || select == 2 || select ==3 ) return true;
    std::cout << "only 1 or 2 or 3 allowed \n";
    return false;
}
//---------------------------------------------------------------------------------- checkSide12
bool checkSide12(int select){ // if side selection is correct
    if (select == 1 || select == 2) return true;
    std::cout << "only 1 or 2 allowed \n";
    return false;
}
//---------------------------------------------------------------------------------- checkq14
bool checkq14(int q){ // if ship range selection is correct
    if (q == 1 || q == 2 || q == 3 || q == 4) return true;
    std::cout << "only 1 2 3 or 4 allowed \n";
    return false;
}

bool checkWhite14(int side, int q){ // if white 1xRranged ship <= 4
    if (side == 1 && q == 1 && counter.nW1 >3) {
        std::cout << "White 1 x Ranged ships reached maximum 4 \n";
        return false;
    }
    return true;
}

bool checkBlack14(int side, int q){ // if Black 1xRanged ship <= 4
    if (side == 2 && q == 1 && counter.nB1 >3) {
        std::cout << "Black 1 x Ranged ships reached maximum 4 \n";
        return false;
    }
    return true;
}

bool checkWhite23(int side, int q){ //if White 2xRanged ship <= 3
    if (side == 1 && q == 2 && counter.nW2 >2) {
        std::cout << "White 2 x Ranged ships reached maximum 3 \n";
        return false;
    }
    return true;
}
bool checkBlack23(int side, int q){ //if black 2 ranged ship <= 3
    if (side == 2 && q == 2 && counter.nB2 >2) {
        std::cout << "Black 2 x Ranged ships reached maximum 3 \n";
        return false;
    }
    return true;
}

bool checkWhite32(int side, int q){ // if white 3 ranged ship <= 2
    if (side == 1 && q == 3 && counter.nW3 >1) {
        std::cout << "White 3 x Ranged ships reached maximum 2 \n";
        return false;
    }
    return true;
}
bool checkBlack32(int side, int q){ // if black 3 ranged ship <= 2
    if (side == 2 && q == 3 && counter.nB3 >1) {
        std::cout << "Black 3 x Ranged ships reached maximum 2 \n";
        return false;
    }
    return true;
}
bool checkWhite41(int side, int q){ // if white 4 ranged ship <= 1
    if (side == 1 && q == 4 && counter.nW4 >0) {
        std::cout << "White 4 x Ranged ships reached maximum 1 \n";
        return false;
    }
    return true;
}
bool checkBlack41(int side, int q){ // if black 4 ranged ship <= 1
    if (side == 2 && q == 4 && counter.nB4 >0) {
        std::cout << "Black 4 x Ranged ships reached maximum 1 \n";
        return false;
    }
    return true;
}

bool checkCoordinates(int x1,int y1,int x2,int y2, int q){ // to check 0-9 and Horiz Vert ships and coordinates according
    if (x1 < 0 || x1 > 9 || y1 < 0 || y2 >9){
        std::cout << "The ship is out of borders (0-9) or entered only 1 coordinate \n";
        return false;
    }

    // only next 2 combinations are allowed - horizontal or vertically
    // 1)
    int hintX = x1 + q - 1; // means horizontal q- means range of ship
    int hintY = y1;
    if (x2 == hintX && y2 == hintY) return true; // check if x2,y2 entered correctly

    // 2)
    hintX = x1;
    hintY = y1 + q -1; // means vertically
    if (x2 == hintX && y2 == hintY) return true; // check if x2,y2 entered correctly

    std::cout << "Entered either diagonals or not according with selected range\n";
    return false;
}


// ///////////////////////////////////////////////////////////////////////////// ship class methods
// --------------------------------------------- ship CONSTRUCTOR
ship::ship  (SIDE blackORwhite,
             int x1,int y1,int x2,int y2,
             STATUS shipstatus)
        :
        blackORwhite(blackORwhite),
        X1(x1), Y1(y1), X2(x2), Y2(y2),
        shipStatus(shipstatus){}

int ship::getX1()               {return X1;}
int ship::getX2()               {return X2;}
int ship::getY1()               {return Y1;}
int ship::getY2()               {return Y2;}
STATUS ship::GetShipStatus()    {return shipStatus;}
SIDE ship::GetShipSide()        {return blackORwhite;}

// --------------------------------------------- ship SetShipStatus
void ship::SetShipStatus(STATUS setStatus) {
    this->shipStatus = setStatus;
}

///////////////////////////////////////////////////////////////////////////////////  shipList class method
//----------------------------------------------------------- DESTRUCTOR
shipList::~shipList() {
    while (!vectPtrsShips.empty()){
        iter = vectPtrsShips.begin();
        delete *iter;
        vectPtrsShips.erase(iter);
    }
}

// --------------------------------------------------------------------- shipList::insertShip
void shipList::insertShip(ship* ptrShip) {
    vectPtrsShips.push_back(ptrShip);
}

// ---------------------------------------------------------------------- shipList::allWhitesDead
bool shipList::isAllWhitesDead() {
    iter = vectPtrsShips.begin(); // return 1 - All White are dead, 2 - All Black are dead, 0 - somebody alive ))

    while (iter != vectPtrsShips.end()){
        STATUS status = (*iter)->GetShipStatus();
        SIDE side = (*iter)->GetShipSide();
        if ((side == SIDE::WHITE) && (status == STATUS::ALIVE)) {
            return false;
        }
        iter++;
    }
    // if we are here - means all Whites are dead
    return true;
}

// ---------------------------------------------------------------------- shipList::allDead
bool shipList::isAllBlacksDead() {
    iter = vectPtrsShips.begin(); // return 1 - All White are dead, 2 - All Black are dead, 0 - somebody alive ))

    while (iter != vectPtrsShips.end()){
        STATUS status = (*iter)->GetShipStatus();
        SIDE side = (*iter)->GetShipSide();
        if ((side == SIDE::BLACK) && (status == STATUS::ALIVE)) {
            return false;
        }
        iter++;
    }
    // if we are here - means all Blacks are dead
    return true;
}

//--------------------------------------------------------------- Field::getCoord
int Field::getCoord(int j, int i){ // returns whats in this [j][i] cell
    return this->arr[j][i];
}

// -------------------------------------------------------------- shipList::checkShip()
void shipList::checkShip(Field* ptrField) {
    iter = vectPtrsShips.begin();
    int X1, Y1, X2, Y2;

    bool alive;
    while (iter != vectPtrsShips.end()) {
        X1          = (*iter)->getX1();
        Y1          = (*iter)->getY1();
        X2          = (*iter)->getX2();
        Y2          = (*iter)->getY2();

        alive = true;
        if ((X1 == X2) && (Y1 == Y2) && ptrField->getCoord(Y1,X1) == 3) { // 1 ranged ship got hit
            alive = false;
        }

        if ((X1 == X2) && (Y1 != Y2)) {
            alive = false;
            for (int j = Y1; j <= Y2; j++) {
                if (ptrField->getCoord(j,X1) != 3) {
                    alive = true; // at least one cell of ship is alive and that's enough
                    break;
                }
            }
        }

        if ((Y1 == Y2) && (X1 != X2)){
            alive = false;
            for (int j = X1; j <= X2; j++) {
                if (ptrField->getCoord(Y1, j) != 3) {
                    alive = true; // at least one cell of ship is alive and that's enough
                    break;
                }
            }
        }
        if (!alive)
            (*iter)->SetShipStatus(STATUS::DEAD);

        iter++; // next ship
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////////// Field class method
// -----------------------------------------  Field CONSTRUCTOR
Field::Field(int n_size, int m_size) {
    n = n_size; m = m_size;
    arr = new int*[n];
    for(int i = 0; i < n; i++)
        arr[i] = new int[m];
}

//--------------------------------------------------------- Field::ShowField
void Field::ShowField(){
    int h=0;
    std::cout << std::endl;
    std::cout << "   0 1 2 3 4 5 6 7 8 9\n";
    std::cout << "   _ _ _ _ _ _ _ _ _ _\n";
    for (int i = 0; i <10; i++){
        std::cout << h << "| ";
        for (int j = 0; j <10; j++){
            if(this->arr[j][i] == 0)
                std::cout << ". ";
            else if(this->arr[j][i] == 3)
                std::cout << "X ";
            else
            if(this->arr[j][i] == 1) std::cout << "W ";
            if(this->arr[j][i] == 2) std::cout << "B ";
        }
        std::cout << std::endl;
        h++;
    }
}

// ------------------------------------------------------------------------------- Field::SetFieldBusy
bool Field::SetFieldBusy(int side, int range, int x1, int y1, int x2, int y2){
    if (range == 1){
        if(this->arr[y1][x1] != 0) return false; // means Field already busy
        if (side == 1) this->arr[y1][x1] = 1;
        if (side == 2) this->arr[y1][x1] = 2;
    } else {
        if (side == 1) { // means WHITE
            if (x1 == x2) {
                for (int i = y1; i <= y2; i++) {
                    if (this->arr[i][x1] != 0) return false; // means Field already busy
                    this->arr[i][x1] = 1;
                }
            }
            if (y1 == y2) {
                for (int i = x1; i <= x2; i++) {
                    if (this->arr[y1][i] != 0) return false; // means Field already busy
                    this->arr[y1][i] = 1;
                }
            }
        }

        if (side == 2) { // means BLACK
            if (x1 == x2) {
                for (int i = y1; i <= y2; i++) {
                    if (this->arr[i][x1] != 0) return false; // means Field already busy
                    this->arr[i][x1] = 2;
                }
            }
            if (y1 == y2) {
                for (int i = x1; i <= x2; i++) {
                    if (this->arr[y1][i] != 0) return false; // means Field already busy
                    this->arr[y1][i] = 2;
                }
            }
        }
    }
    return true;
}


// ========================================================================= shipInputScreen class method
// -------------------------------------------------class shipInputScreen
void shipInputScreen::getShip(Field* field) {
    int ix1, iy1, ix2, iy2;
    int q;
    int side = 0;
    int nextShip = 1;

    while (true) {
        side = 0;
// ----------------------------------------------------------------------------
        std::cout << "Starting to setup the new ship\n";
        std::cout << "------------------------------\n";

// ----------------------------------------------------------------------
        std::cout << "Chose the side of new ship 1 - White, 2 - Black\n>";
        do
            std::cin >> side;
        while (!checkWhiteCount() || !checkBlackCount() || !checkSide12(side));

// -------------------------------------------------------------------------

        std::cout << "Chose the range of new ship  :\n";
        std::cout << " 1 - to setup 1 range ships\n"
                  << " 2 - to setup 2 range ships\n"
                  << " 3 - to setup 3 range ships\n"
                  << " 4 - to setup 4 range ships\n>";
        do {
            std::cin >> q;
        }while ( !checkWhite14(side,q) || !checkWhite23(side,q) || !checkWhite32(side,q) || !checkWhite41(side,q) ||
                 !checkBlack14(side,q) || !checkBlack23(side,q) || !checkBlack32(side,q) || !checkBlack41(side,q) || !checkq14(q));

        switch (q) {
            case 1:
                if (side == 1) counter.nW1 += 1;
                if (side == 2) counter.nB1 += 1;
                break;
            case 2:
                if (side == 1) counter.nW2 += 1;
                if (side == 2) counter.nB2 += 1;
                break;
            case 3:
                if (side == 1) counter.nW3 += 1;
                if (side == 2) counter.nB3 += 1;
                break;
            case 4:
                if (side == 1) counter.nW4 += 1;
                if (side == 2) counter.nB4 += 1;
                break;
            default:
                break;
        }

        //std::string coord;
        char char_x, char_y;
        std::string coord;
        do {
            std::cout << "Enter beginning (x,y) coordinates for the ship\n>";
            std::cin >> coord;
            char_x = coord[0];
            char_y = coord[2];
            ix1 = char_x - '0';
            iy1 = char_y - '0';
            ix2 = ix1;
            iy2 = iy1;
            if (q > 1) { // more than 1 range ship
                coord = "";
                std::cout << "Enter ending (x,y) coordinates for the ship\n";
                std::cout << "Hint: it can be only " << ix1 + q - 1 << "," << iy1 << " or " << ix1 << "," << iy1 + q - 1 << "\n>";
                std::cin >> coord;
                char_x = coord[0];
                char_y = coord[2];
                ix2 = char_x - '0';
                iy2 = char_y - '0';
            }
        }while (!checkCoordinates(ix1,iy1,ix2,iy2,q));

        SIDE WB;
        if (side == 1) WB = SIDE::WHITE;
        if (side == 2) WB = SIDE::BLACK;

        if (field->SetFieldBusy(side, q, iy1, ix1, iy2, ix2)) {
            ship *ptrShip = new ship(WB, iy1, ix1, iy2, ix2, STATUS::ALIVE);
            ptrShipList->insertShip(ptrShip);
        } else {
            std::cout << "\nShip has already busy coordinates\n";
        }
        field->ShowField();

        nextShip = 1;
        std::cout << " 0 - to Quit ship setup process\n "
                  << " 1 - to setup next ship\n>";
        std::cin >> nextShip;

        if (nextShip == 0)
            break;
    }
}

// ----------------------------------------------------- Field::Shot
void Field::Shot(){
    int i, j;
    char char_x, char_y;
    std::string coord;
    do {
        std::cout << "Enter SHOT coordinates (X,Y) \n>";
        std::cin >> coord;
        char_y = coord[0];
        char_x = coord[2];
        i = char_x - '0';
        j = char_y - '0';

    }while (i < 0 || i > 10 || j<0 || j >10);
    this->arr[j][i] = 3; // means shot marked with 3
}

//////////////////////////////////////////////////////////  Battle Screen methods
void BattleScreen::Battle(Field* field, shipList* sl){
    for(int shots =0 ; shots < 100 ; shots ++){
        clear_screen();
        field->ShowField();

        if (sl->isAllWhitesDead()){
            std::cout << "All Whites are dead, Black WON!!!\n";
            return;
        }
        if (sl->isAllBlacksDead()){
            std::cout << "All Blacks are dead, White WON!!!\n";
            return;
        }
        field->Shot();
        sl->checkShip(field);
    }
}

///////////////////////////////////////////////////////////////////userInterface class Methods
userInterface::userInterface() { // -------------------------------CONSTRUCTOR
    ptrShipList = new shipList;
    ptrField = new Field(10,10);
}

userInterface::~userInterface() { // ------------------------------ DESCTRUCTOR
    delete ptrShipList;
    delete ptrField;
}

void userInterface::interact() { // --------------------------------- userInterface::interact
    int Q;
    while (true)
    {
        do {
            std::cout << " 1 - to setup ships\n"
                      << " 2 - to start game\n"
                      << " 3 - to  quit\n>";
            std::cin >> Q;
        } while (!mainMenuCheck(Q));

        switch (Q) {
            case 1: ptrShipInputScreen= new shipInputScreen(ptrShipList,ptrField);
                ptrShipInputScreen->getShip(ptrField);
                delete ptrShipInputScreen;
                break;
            case 2:
                ptrBattleScreen = new BattleScreen(ptrShipList, ptrField);
                ptrBattleScreen->Battle(ptrField, ptrShipList);
                delete ptrBattleScreen;
                break;

            case 3:
                return;

            default: std::cout << "Unknown operation\n"; break;
        }
    }
}

int main() {

    userInterface theUserInterface;
    theUserInterface.interact();
    return 0;
}





