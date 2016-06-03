#include "display.h"
#include "menu.h"
#include "record.h"
#include "room.h"
#include "util.h"
#include <stdlib.h>

#ifndef __DISPLAY_V
#define __DISPLAY_V
unsigned int _RUN_FLAG_ = 0;
unsigned int _LOOP_FLAG_ = 0;
#endif // __DISPLAY_V

void window(void){
    init();
    run();
}

void start(void){
    delay(1);
    p("********************************************************************************");
    p("*                                                                              *"); // hotel management system
    p("*                                                                              *"); // welcome to the hotel
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("*                                                                              *");
    p("********************************************************************************");
    delay(10);
#ifdef linux
    system("clear");
#endif // linux
#ifdef _WIN32
    system("cls");
#endif
}

void init(void){
    initRoom();
    initGuest();
    initRetrict();
}

void run(void){
    show();
}

void printCurrentRoomInfo(void){
    updateList();
    printRoom();
}

void deleteExitedGuestbyRoomId(unsigned int id){
    linkGuest currentGuest = headGuest;
    while (currentGuest->next != NULL){
        currentGuest = currentGuest->next;

        if (currentGuest->g->idRoom == id){
            deleteGuest(currentGuest->g->id);
        }
    }
}
