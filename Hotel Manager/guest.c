#include "guest.h"
#include <stdlib.h>

#ifndef __GUEST_V
#define __GUEST_V

unsigned int idGuest = 0;

#endif // __GUEST_V

void initGuest(void){
    headGuest = (linkGuest)malloc(sizeof(_linkGuest));
    headGuest->next = NULL;
}

void createGuest(unsigned int age, char name[8], unsigned int id){
    unsigned int len = 0;
    while (name[len] != '\0') ++ len;
    char *name_ = (char *)malloc(sizeof(char) * len);
    len = 0;
    while (name[len] != '\0'){
        name_[len] = name[len];
        ++ len;
    }

    linkGuest currentGuest = headGuest;
    while (currentGuest->next != NULL){
        currentGuest = currentGuest->next;
    }
    linkGuest g_ = (linkGuest)malloc(sizeof(_linkGuest));
    currentGuest->next = g_;

    Guest g = (Guest)malloc(sizeof(_Guest));
    g->id = ++ idGuest;
    g->idRoom = id;
    g->age = age;
    g->name = name_;
    g->roommate = NULL;

    g_->g = g;
    g_->next = NULL;

    //return g;
}

void modifyGuest(unsigned int age, char name[8], unsigned int id){
    unsigned int i = id;

    linkGuest currentGuest = headGuest;
    while (currentGuest->next != NULL && i --){
        currentGuest = currentGuest->next;
    }

    Guest g = currentGuest->g;
    g->idRoom = id;
    g->age = age;
    g->name = name;
}

void deleteGuest(unsigned int id){
    unsigned int i = id - 1;

    linkGuest currentGuest = headGuest;
    while (currentGuest->next != NULL && i --){
        currentGuest = currentGuest->next;
    }

    linkGuest deletedGuest = currentGuest->next;
    currentGuest->next = currentGuest->next->next;
    free(deletedGuest->g->name);
    free(deletedGuest->g);
    free(deletedGuest);

    while(currentGuest->next != NULL){
        currentGuest = currentGuest->next;
        -- currentGuest->g->id;
    }

    -- idGuest;
}

void printGuest(void){
    linkGuest currentGuest = headGuest;
    printf("Guest Id\tRoom Id\tage\tname");
    while (currentGuest->next != NULL){
        currentGuest = currentGuest->next;

        printf("\n\t%d\t%d\t%d\t%s", currentGuest->g->id, currentGuest->g->idRoom, currentGuest->g->age, currentGuest->g->name);
    }
    printf("\n\n");
}
