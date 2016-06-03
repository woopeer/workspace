#include "record.h"
#include "menu.h"
#include "guest.h"
#include "room.h"
#include <time.h>
#include <stdio.h>

#ifdef linux
char *filePath = "/home/woop/Desktop/";
#elif _WIN32
char *filePath = "C:\\Users\\woop\\Desktop\\";
#endif // linux

char *roomRecordFileName = "ROOM";
char *guestRecordFileName = "GUEST";
char *typeRecordFileName = "TYPE";
char *balanceFileName = "balance.txt";

void modifyFilePath(unsigned int position){
    p("please type correct path of folder of files ... ...");
    p("if you have any questions, u maybe should read the help page first");
    printf("Your current file path is [ %s ]\n", filePath);
    p("\nEnter a new path:");

    char *path = getPath();
    if (strlen(path) > 0){
        filePath = path;

        p("process had been successfully finished ... ...");
        printf("Your current file path is [ %s ]\n", filePath);
    } else {
        p("process had been failed ... ...");
        p("file path is not changed ... ...");
    }
    delay(3);
}

void fileOperation(unsigned int position, unsigned int mode){
    if (position == _RECORD_){
        fileModify(append(filePath, roomRecordFileName), append(filePath, guestRecordFileName), append(filePath, typeRecordFileName), mode);
    } else if (position == _BALANCE_){
        balance(append(filePath, balanceFileName), mode);
    }
}

void balance(char *fileName, unsigned int mode){
    time_t t = time(NULL);
    if (mode == _READ_){
#ifdef linux
        system("clear");
#elif _WIN32
        system("cls");
#endif // linux
        printf("*****************************************************************************\n");
        printf("* Current Total Room Number :                                 \n");
        printf("*                            %d                               \n", idRoom);
        printf("*                                                             \n");
        printf("* Current Total Guest Number:                                 \n");
        printf("*                            %d                               \n", idGuest);
        printf("*                                                             \n");
        printf("* Current Total Type Number :                                 \n");
        printf("*                            %d                               \n", idType);
        printf("*                                                             \n");
        printf("*                                                             \n");
        printf("*                                                             \n");
        printf("* How Much You'll earn until all rooms rent deadline is up:   \n");
        printf("*                                                             \n");
        printf("*                                                             \n");
        printf("*                                                   %lf$      \n", totalMoney());
        printf("*                                                             \n");
        printf("*              Current Time: %s                               \n", ctime(&t));
        printf("*****************************************************************************\n");
        delay(10);
    } else if (mode == _SAVE_){
        FILE *fp = fopen(fileName, "a");
        if (!fp){
            printf("files cannot open ... ... save failed ... ...");
            return;
        }

        fprintf(fp, "1) Current Total Room Number : %d\n", idRoom);
        fprintf(fp, "2) Current Total Guest Number: %d\n", idGuest);
        fprintf(fp, "3) Current Total Type Number : %d\n", idType);
        fprintf(fp, "*How Much You'll earn until all rooms rent deadline is up: %lf$*\n", totalMoney());
        fprintf(fp, "Current Time: %s\n", ctime(&t));

        printf("files had been successfully saved in [ %s ] ... ...\n", filePath);
        p("please have a look");
        delay(2);

        fclose(fp);
    }
}

void fileModify(char *roomFileName, char *guestFileName, char *typeFileName, unsigned int mode){
    unsigned int len, type;
    char *name = NULL;

    if (mode == _SAVE_){

    } else if (mode == _READ_){
        deleteAll();
    }

    linkGuest currentGuest = headGuest;
    linkRoom currentRoom = headRoom;
    linkType currentType = headType;

    FILE *fpRoom = NULL;
    FILE *fpGuest = NULL;
    FILE *fpType = NULL;

    linkGuest g_ = NULL;
    linkRoom r_  = NULL;
    linkType t_  = NULL;

    if (mode == _SAVE_){
        fpRoom = fopen(roomFileName, "wb");
        fpGuest = fopen(guestFileName, "wb");
        fpType = fopen(typeFileName, "wb");
    } else {
        fpRoom = fopen(roomFileName, "rb");
        fpGuest = fopen(guestFileName, "rb");
        fpType = fopen(typeFileName, "rb");
    }

    if (!fpRoom || !fpGuest || !fpType){
        printf("files cannot open ... ... save failed ... ...");
        return;
    }
    if (mode == _SAVE_){
        fwrite(&idType, sizeof(unsigned int), 1, fpType);
        fwrite(&idRoom, sizeof(unsigned int), 1, fpRoom);
        fwrite(&idGuest, sizeof(unsigned int), 1, fpGuest);
    } else {
        fread(&idType, sizeof(unsigned int), 1, fpType);
        fread(&idRoom, sizeof(unsigned int), 1, fpRoom);
        fread(&idGuest, sizeof(unsigned int), 1, fpGuest);
    }

    unsigned int tmp_idRoom  = idRoom;
    unsigned int tmp_idGuest = idGuest;
    unsigned int tmp_idType  = idType;



    if (mode == _SAVE_){
        while (tmp_idType --){
            currentType = currentType->next;
            fwrite(currentType, sizeof(_linkType), 1, fpType);
        }
        while (tmp_idRoom --){
            currentRoom = currentRoom->next;
            fwrite(currentRoom, sizeof(_linkRoom), 1, fpRoom);
            fwrite(currentRoom->r, sizeof(_Room), 1, fpRoom);
            fwrite(&currentRoom->r->type->type, sizeof(unsigned int), 1, fpGuest);
        }
        while (tmp_idGuest --){
            currentGuest = currentGuest->next;
            fwrite(currentGuest, sizeof(_linkGuest), 1, fpGuest);
            fwrite(currentGuest->g, sizeof(_Guest), 1, fpGuest);
            len = 0;
            name = currentGuest->g->name;
            while (name[len] != '\0') ++ len;
            fwrite(&len, sizeof(unsigned int), 1, fpGuest);
            fwrite(name, sizeof(char), len, fpGuest);
        }

        printf("files had been successfully saved in [ %s ] ... ...\n", filePath);
        p("please have a look");
        delay(2);
    } else {
        while (tmp_idType --){
            t_ = (linkType)malloc(sizeof(_linkType));
            currentType->next = t_;
            currentType = currentType->next;
            fread(currentType, sizeof(_linkType), 1, fpType);
            currentType->next = NULL;
        }
        while (tmp_idRoom --){
            r_ = (linkRoom)malloc(sizeof(_linkRoom));
            currentRoom->next = r_;
            currentRoom = currentRoom->next;
            fread(currentRoom, sizeof(_linkRoom), 1, fpRoom);
            currentRoom->r = (Room)malloc(sizeof(_Room));
            fread(currentRoom->r, sizeof(_Room), 1, fpRoom);
            fread(&type, sizeof(unsigned int), 1, fpRoom);
            currentRoom->r->type = getType(type);
            currentRoom->next = NULL;
        }
        while (tmp_idGuest --){
            g_ = (linkGuest)malloc(sizeof(_linkGuest));
            currentGuest->next = g_;
            currentGuest = currentGuest->next;
            fread(currentGuest, sizeof(_linkGuest), 1, fpGuest);
            currentGuest->g = (Guest)malloc(sizeof(_Guest));
            fread(currentGuest->g, sizeof(_Guest), 1, fpGuest);
            fread(&len, sizeof(unsigned int), 1, fpGuest);
            currentGuest->g->name = (char *)malloc(sizeof(char) * len);
            fread(currentGuest->g->name, sizeof(char), len, fpGuest);
            currentGuest->next = NULL;
        }

        printf("files had been successfully readed from [ %s ] ... ...\n", filePath);
        p("please have a check to make everything right");
        delay(2);
    }

    fclose(fpRoom);
    fclose(fpGuest);
    fclose(fpType);
}

void deleteAll(void){
    deleteAllRoom();
    deleteAllGuest();
    deleteAllType();
}

void deleteAllGuest(void){
    while (idGuest){
        deleteGuest(idGuest --);
    }
}

void deleteAllRoom(void){
    while (idRoom){
        deleteRoom(idRoom --);
    }
}

void deleteAllType(void){
    while (idType){
        deleteType(idType --);
    }
}

char *append(char *a, char *b){
    unsigned int len_a = strlen(a), len_b = strlen(b), i;
    char *output = (char *)malloc(sizeof(char) * (len_a + len_b + 1));

    for (i = 0; i < len_a; ++ i)
        output[i] = a[i];
    for (i = len_a; i < len_a + len_b; ++ i)
        output[i] = b[i - len_a];

    output[len_a + len_b] = '\0';
    return output;
}

double totalMoney(){
    double total = 0;

    linkRoom currentRoom = headRoom;
    while (currentRoom->next != NULL){
        currentRoom = currentRoom->next;

        total += currentRoom->r->type->money * currentRoom->r->type->time;
    }

    return total;
}
