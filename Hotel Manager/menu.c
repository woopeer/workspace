#include "menu.h"
#include "room.h"
#include "guest.h"
#include "display.h"
#include "record.h"

unsigned int **retrict;
char **retrictAlpha;

int retrict_1[6] = { _EXIT_, _ROOM_, _GUEST_,  _TYPE_, _RECORD_, _BALANCE_ };
int retrict_2[4] = { _BACK_, _NEW_,   _DELETE_, _MODIFY_ };
int retrict_3[4] = { _BACK_, _SAVE_, _READ_, _MODIFY_ };

char retrictAlpha_1[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
char retrictAlpha_2[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

void makeChange(unsigned int position, unsigned int mode) {
    switch (mode) {
    case _WINDOW_: return menu(_WINDOW_);
    case _GUEST_ : return menu(_GUEST_);
    case _ROOM_  : return menu(_ROOM_);
    case _TYPE_  : return menu(_TYPE_);
    case _RECORD_: return menu(_RECORD_);
    case _BALANCE_: return menu(_BALANCE_);
    case _NEW_   : break;
    case _DELETE_: break;
    case _MODIFY_: if (position == _RECORD_ || position == _BALANCE_) return modifyFilePath(position); break;
    case _SAVE_  : return fileOperation(position, mode);
    case _READ_  : return fileOperation(position, mode);
    case _BACK_  : goto _JMP_BACK;
    case _EXIT_  : exit(0);
    }
    switch (position) {
    case _WINDOW_: break;
    case _GUEST_ :
    case _ROOM_  :
    case _TYPE_  : return change(position, mode);
    case _RECORD_: break;
    case _BALANCE_: break;
    }

    _JMP_BACK:
        menu(_WINDOW_);
}

void change(unsigned int catogery, unsigned int mode){
    unsigned int id, time, age, type, m, c;
    double money;
    char *name;

    if (mode == _NEW_ && catogery == _ROOM_ && !idType){
        p("type wrong, please set up a charge type first");
        p("type wrong, please set up a charge type first");
        p("type wrong, please set up a charge type first");
        delay(2);
        return menu(catogery);
    }

    if (mode != _NEW_ || catogery == _GUEST_)
        if ((catogery == _ROOM_ && !idRoom) || (catogery == _GUEST_ && !idGuest && !idRoom) || (catogery == _TYPE_ && !idType)){
            p("type wrong, are you trying make operation on one Non-exited object?");
            delay(1);
            return menu(catogery);
        }
    if (mode == _NEW_ && catogery == _GUEST_){
#ifdef linux
        system("clear");
#elif _WIN32
        system("cls");
#endif // linux
        printCurrentRoomInfo();
        p("Please enter the id of room that you want to make the guest set in");
        p("\nEnter the id of the room: ");
    } else {
        pleaseEnter(catogery, mode);
    }

    if (mode != _NEW_ || catogery == _GUEST_){
        id = charToInt();
        if ((catogery == _ROOM_ && !(id > 0 && id <= idRoom)) || (catogery == _GUEST_ && mode != _NEW_ && !(id > 0 && id <= idGuest)) || (catogery == _TYPE_ && !(id > 0 && id <= idType))){
            p("type wrong, are you trying make operation on one Non-exited object?");
            delay(1);
            return menu(catogery);
        }
        if (mode == _NEW_ && catogery == _GUEST_ && !(id > 0 && id <= idRoom)){
            p("type wrong, are you trying make operation on one Non-exited object?");
            delay(1);
            return menu(catogery);
        }
    }

    if (mode == _NEW_ && catogery == _GUEST_){
        pleaseEnter(catogery, mode);
    }

    switch(catogery * mode){
    case _ROOM_ * _NEW_ :
        type = getTypeAns();
        createRoom(type);
        break;
    case _ROOM_ * _DELETE_:
        deleteRoom(id);
        break;
    case _ROOM_ * _MODIFY_:
        pleaseEnter(catogery, _CHOOSE_);
        type = getTypeAns();
        modifyRoom(type, id);
        break;
    case _GUEST_ * _NEW_   :
        age = getAge();
        name = getName();
        createGuest(age, name, id);
        break;
    case _GUEST_ * _DELETE_:
        deleteGuest(id);
        break;
    case _GUEST_ * _MODIFY_:
        pleaseEnter(catogery, _CHOOSE_);
        age = getAge();
        name = getName();
        modifyGuest(age, name, id);
        break;
    case _TYPE_ *_NEW_   :
        time = getTime();
        money = getMoney();
        createType(time, money);
        break;
    case _TYPE_ * _DELETE_:
        deleteType(id);
        break;
    case _TYPE_ * _MODIFY_:
        pleaseEnter(catogery, _CHOOSE_);
        time = getTime();
        money = getMoney();
        modifyType(time, money, id);
        break;
    }
}

void menu(unsigned int position){
#ifdef linux
    system("clear");
#endif // linux
#ifdef _WIN32
    system("cls");
#endif // _WIN32
    switch (position){
    case _WINDOW_:{
            printCurrentRoomInfo();
            p("\n1) create(delete or modify) a new(or exited) room");
            p("2) create(delete or modify) a new(or exited) guest");
            p("3) create(delete or modify) a new(or exited) charge type");
            p("4) record");
            p("5) balance");
            p("0) exit");
            p("\nEnter choice: ");
            makeChange(_WINDOW_, getAnsweri(retrict[_WINDOW_], _NUM_MENU_));
        }
        break;
    case _GUEST_:{
            printGuest();
            p("\n1) create a new guest");
            p("2) delete a exited guest");
            p("3) modify a exited guest");
            p("0) back");
            p("\nEnter choice: ");
            makeChange(_GUEST_, getAnsweri(retrict[_GUEST_], 4));
        }
        break;
    case _ROOM_:{
            printCurrentRoomInfo();
            p("\n1) create a new room");
            p("2) delete a exited room");
            p("3) modify a exited room");
            p("0) back");
            p("\nEnter choice: ");
            makeChange(_ROOM_, getAnsweri(retrict[_ROOM_], 4));
        }
        break;
    case _TYPE_:{
            printType();
            p("1) create a new type");
            p("2) delete a exited type");
            p("3) modify a exited type");
            p("0) back");
            p("\nEnter choose: ");
            makeChange(_TYPE_, getAnsweri(retrict[_TYPE_], 4));
        }
        break;
    case _RECORD_:{
            p("\n1) saved the record to a file with predefined path");
            p("2) recall the record from exited file of predefined path");
            p("3) modify the path of folder of record that u want to save");
            p("0) back");
            p("\nEnter choice: ");
            makeChange(_RECORD_, getAnsweri(retrict[_RECORD_], 4));
        }
        break;
    case _BALANCE_:{
            p("\n1) saved the balance to a file with predefined path");
            p("2) have a look at the current balance");
            p("3) modify the path of folder of balance that u want to save");
            p("0) back");
            p("\nEnter choice: ");
            makeChange(_BALANCE_, getAnsweri(retrict[_BALANCE_], 4));
        }
        break;
    }

    return menu(_WINDOW_);
}

void initRetrict(void){
    retrict = (int **)malloc(sizeof(int *) * _NUM_MENU_);
    retrictAlpha = (char **)malloc(sizeof(char *) * _NUM_RETRICTALPHA_);

    int *_w = retrict_1;
    int *_g = retrict_2;
    int *_r = retrict_2;
    int *_t = retrict_2;
    int *_rec = retrict_3;
    int *_b = retrict_3;

    retrict[_WINDOW_] = _w;
    retrict[_GUEST_]  = _g;
    retrict[_ROOM_]   = _r;
    retrict[_TYPE_]   = _t;
    retrict[_RECORD_] = _rec;
    retrict[_BALANCE_] = _b;

    retrictAlpha[_NAME_] = retrictAlpha_1;
    retrictAlpha[_NUMBER_] = retrictAlpha_2;
}

void pleaseEnter(unsigned catogery, unsigned int mode){
    char *c, *m;
#ifdef linux
    system("clear");
#endif // linux
#ifdef _WIN32
    system("cls");
#endif
    switch(catogery){
    case _ROOM_ : printType();  c = "room";  break;
    case _GUEST_: printGuest(); c = "guest"; break;
    case _TYPE_ : printType();  c = "type";   break;
    }
    switch(mode){
    case _NEW_:    m = "create"; break;
    case _DELETE_: m = "delete"; break;
    case _CHOOSE_:
    case _MODIFY_: m = "modify"; break;
    }
    if (mode != _CHOOSE_ && mode != _NEW_){
        printf("\nPlease enter the id of %s that you want to %s", c, m);
        printf("\n\nEnter the id of the %s: ", c);
    } else {
        switch(catogery){
        case _ROOM_ : {
                printf("Please enter the type of room that you want to %s", m);
                p("\nEnter the new type of the room: ");
            } break;
        case _GUEST_: {
                printf("Please enter the age and name of guest that you want to %s", m);
                p("\nEnter the new age and name of the guest: (separated by blank space or \\n)");
            } break;
        case _TYPE_ : {
                if (mode == _NEW_){
                    p("Please set up the routin of charge mode:");
                    p("Enter time(HOUR) for how long you are going to get money");
                    p("Enter money for every routin how much money you are going to get\n");
                }
                printf("Please enter the time(HOUR) and money of type that you want to %s", m);
                p("\nEnter the new time and money of the type: (separated by blank space or \\n)");
            } break;
        }
    }
}

void show(void){
    menu(_WINDOW_);
}
