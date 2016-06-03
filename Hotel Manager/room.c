#include "room.h"
#include "guest.h"
#include <stdlib.h>


#ifndef __ROOM_V
#define __ROOM_V

unsigned int idRoom = 0;
unsigned int idType = 0;

#endif // __ROOM_V

void initRoom(void){
    headRoom = (linkRoom)malloc(sizeof(_linkRoom));
    headRoom->next = NULL;

    headList = (roomList)malloc(sizeof(_RoomList));
    headList->guest = NULL;
    headList->next = NULL;

    headType = (linkType)malloc(sizeof(_linkType));
    headType->next = NULL;
}

Room createRoom(unsigned int type){
    linkRoom currentRoom = headRoom;
    while (currentRoom->next != NULL){
        currentRoom = currentRoom->next;
    }
    linkRoom r_ = (linkRoom)malloc(sizeof(_linkRoom));
    currentRoom->next = r_;

    Room r = (Room)malloc(sizeof(_Room));
    r->id = ++ idRoom;
    r->type = getType(type);

    r_->r = r;
    r_->next = NULL;

    return r;
}

void modifyRoom(unsigned int type, unsigned int id){
    unsigned int i = id;

    linkRoom currentRoom = headRoom;
    while (currentRoom->next != NULL && i --){
        currentRoom = currentRoom->next;
    }

    Room r = currentRoom->r;
    r->type = getType(type);
}

void deleteRoom(unsigned int id){
    unsigned int i = id - 1;

    linkRoom currentRoom = headRoom;
    while (currentRoom->next != NULL && i --){
        currentRoom = currentRoom->next;
    }

    linkRoom deletedRoom = currentRoom->next;
    currentRoom->next = currentRoom->next->next;
    free(deletedRoom->r);
    free(deletedRoom);

    while(currentRoom->next != NULL){
        currentRoom = currentRoom->next;
        -- currentRoom->r->id;
    }

    -- idRoom;
}

void createType(unsigned int time, double money){
    linkType currentType = headType;
    while (currentType->next != NULL){
        currentType = currentType->next;
    }

    linkType t = (linkType)malloc(sizeof(_linkType));
    currentType->next = t;

    t->type = ++ idType;
    t->time = time;
    t->money = money;
    t->next = NULL;
}

void modifyType(unsigned int time, double money, unsigned int id){
    unsigned int i = id;

    linkType currentType = headType;
    while (currentType->next != NULL && i --){
        currentType = currentType->next;
    }

    currentType->time = time;
    currentType->money = money;
}

void deleteType(unsigned int id){
    unsigned int i = id - 1;

    linkType currentType = headType;
    while (currentType->next != NULL && i --){
        currentType = currentType->next;
    }

    linkType deletedType = currentType->next;
    currentType->next = currentType->next->next;
    free(deletedType);

    while(currentType->next != NULL){
        currentType = currentType->next;
        -- currentType->type;
    }

    -- idType;
}

void updateList(void){
    unsigned int i = idRoom;
    unsigned int tmp_id = 0;

    roomList currentList = headList;
    linkGuest currentGuest = NULL;
    Guest c_guest = NULL;

    if (!i){
        currentList->next = NULL;
        return;
    }

    while(i --){
        ++ tmp_id;
        roomList l = (roomList)malloc(sizeof(_RoomList));
        c_guest = (Guest)malloc(sizeof(_Guest));

        currentList->next = l;
        currentList = currentList->next;
        currentList->next = NULL;
        currentList->guest = c_guest;
        currentList->guest->roommate = NULL;

        currentGuest = headGuest;
        while (currentGuest->next != NULL){
            currentGuest = currentGuest->next;

            if (currentGuest->g->idRoom == tmp_id){
                c_guest->roommate = currentGuest->g;
                c_guest = c_guest->roommate;
                c_guest->roommate = NULL;
            }
        }
    }
}

void printRoom(void){
    unsigned int i = idRoom, tmp_id = 0, cnt = 0;

    roomList currentList = headList;
    linkGuest currentGuest = NULL;
    Guest c_guest = NULL;

    printf("Current guests list: ");
    printf("\n  Room Id\tNumber of Guest\t\tCharge");

    while (currentList->next != NULL){
        ++ tmp_id;
        cnt = 0;
        currentList = currentList->next;

        c_guest = currentList->guest;
        while (c_guest->roommate != NULL){
            c_guest = c_guest->roommate;

            ++ cnt;
            //printf("[ %d ] ", c_guest->id);
        }

        printf("\n\t%d\t\t%d\t\t%lf", tmp_id, cnt, getRoom(tmp_id)->r->type->money);
    }
    printf("\n\n");
}

void printType(void){
    linkType currentType = headType;
    printf("  Type Id\tTime(hour)\tMoney");
    while (currentType->next != NULL){
        currentType = currentType->next;

        printf("\n\t%d\t%dh\t\t%lf", currentType->type, currentType->time, currentType->money);
    }
    printf("\n\n");
}

linkType getType(unsigned int id){
    unsigned int i = id;

    linkType currentType = headType;
    while (currentType->next != NULL && i --){
        currentType = currentType->next;
    }

    return currentType;
}

linkRoom getRoom(unsigned int id){
    unsigned int i = id;

    linkRoom currentRoom = headRoom;
    while (currentRoom->next != NULL && i --){
        currentRoom = currentRoom->next;
    }

    return currentRoom;
}
