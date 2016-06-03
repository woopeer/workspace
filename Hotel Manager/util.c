#include "util.h"
#include "room.h"
#include "guest.h"
#include <time.h>
#include <stdio.h>

#ifndef __UTIL_V
#define __UTIL_V

char buffer[256] = {};
unsigned int len = 0;

#endif // __UTIL_V

void delay(int seconds) {
    clock_t start = clock();
    clock_t lay = (clock_t)seconds * CLOCKS_PER_SEC;
    while ((clock()-start) < lay);
}

int getAnsweri(int *retrict, unsigned int len){
    unsigned int i;
    char ans = validInputOne(_VALID_NUM_);
    if (ans >= '0' && ans < (char)('0' + len))
        return retrict[ans - '0'];

    p("type beyong the accepted range of input ... ...");
    p("\nEnter again:");
    return getAnsweri(retrict, len);
}

char *getPath(){
    if (inputValidProcess()){
        return;
    }

    char *path = (char *)malloc(sizeof(char) * (len + 1));
    unsigned int i;
    for (i = 0; i < len; ++ i)
        path[i] = buffer[i];

    path[len] = '\0';
    return path;
}

char validInputOne(unsigned int mode){
    //scanf("%s", buffer);
    if (inputValidProcess()){
        return;
    }
    unsigned int flag = 0;
    if (len > 1) flag = 1;
    switch (mode){
    case _VALID_NUM_: if (!validInputElementNum(buffer[0])) flag = 1; break;
    case _VALID_NUM_ALPHA_: if (!validInputElementNumAlpha(buffer[0])) flag = 1; break;
    case _VALID_ALPHA_: if (!validInputElementAlpha(buffer[0])) flag = 1; break;
    }
    if (flag){
        p("type wrong, try again ... ...");
        p("\nEnter again:");
        return validInputOne(mode);
    } else {
        return buffer[0];
    }
}

int getAge(){
    char *age = validInput(_VALID_NUM_);

    if (len > 3 || len < 2 || (len == 3 && age[0] > '1') || (len == 2 && age[0] == '1' && age[1] < '8')){
        p("type wrong, try again ... ...");
        p("\nEnter a accepted age:");
        return getAge();
    }

    unsigned int input = 0, i;
    for (i = 0; i < len; ++ i){
        input *= 10;
        input += age[i] - '0';
    }

    return input;
}

char *getName(){
    char *name = validInput(_VALID_ALPHA_);

    if (len > 8 || len < 3){
        p("type wrong, try again ... ...");
        p("\nEnter a accepted name:");
        return getName();
    }

    return name;
}

unsigned int getTypeAns(){
    char input = validInputOne(_VALID_NUM_);
    if (!(input > '0' && input <= (char)('0' + idType))){
        p("type wrong, try again ... ...");
        p("\nEnter a accepted type:");
        return getTypeAns();
    }

    return input - '0';
}

int getTime(){
    char *time = validInput(_VALID_NUM_);
    unsigned int i;

    if (len > 6){
        p("type wrong, try again ... ...");
        p("\nEnter a accepted range:");
        return getTime();
    }

    int input = 0;
    for (i = 0; i < len; ++ i){
        input *= 10;
        input += (time[i] - '0');
    }
    return input;
}

double getMoney(){
    char *money = validInputFloat();
    unsigned int pos = 0, i;

    for (i = 0; i < len; ++ i)
        if (money[i] == '.')
            pos = i;

    double input = 0.0, j = 10.0;
    if (!pos){
        for (i = 0; i < len; ++ i){
            input *= 10;
            input += (money[i] - '0');
        }
    } else {
        for (i = 0; i < pos; ++ i){
            input += (money[i] - '0');
            input *= 10;
        }
        for (i = pos + 1; i < len; ++ i){
            input += (money[i] - '0') / j;
            j *= 10.0;
        }
    }

    return input;
}

char *validInputFloat(){
    //scanf("%s", buffer);
    if (inputValidProcess()){
        return;
    }
    unsigned int i, cnt = 1;

    if (len > 6){
        p("type too too long ... ...");
        p("\nEnter a accepted range:");
    }

    for (i = 0; i < len; ++ i)
        if (!validInputElementNum(buffer[i]) || buffer[0] == '.' || (buffer[i] == '.' && -- cnt)){
            p("type wrong, try again ... ...");
            p("\nEnter a accepted range:");
        }

    char *input = (char *)malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len; ++ i)
        input[i] = buffer[i];

    input[len] = '\0';
    return input;
}

char *validInput(unsigned int mode){
    //scanf("%s", buffer);
    if(inputValidProcess()){
        return;
    }
    unsigned int i, flag = 0;
    for (i = 0; i < len; ++ i){
        switch (mode){
        case _VALID_NUM_: if (!validInputElementNum(buffer[i])) flag = 1; break;
        case _VALID_NUM_ALPHA_: if (!validInputElementNumAlpha(buffer[i])) flag = 1; break;
        case _VALID_ALPHA_: if (!validInputElementAlpha(buffer[i])) flag = 1; break;
        }
        if (flag){
            p("type wrong, try again ... ...");
            p("\nEnter again:");
            return validInput(mode);
        }
    }

    char *input = (char *)malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len; ++ i)
        input[i] = buffer[i];

    input[len] = '\0';
    return input;
}

unsigned int validInputElementNumAlpha(char input){
    if (!(input <= '9' && input >= '0') && !(input <= 'z' && input >= 'a')) return 0;

    return 1;
}

unsigned int validInputElementNum(char input){
    if (!(input <= '9' && input >= '0')) return 0;

    return 1;
}

unsigned int validInputElementAlpha(char input){
    if (!(input <= 'z' && input >= 'a')) return 0;

    return 1;
}

unsigned int inputValidProcess(){
    char ch;
    len = 0;
    memset(buffer, 0, 256);
    while ((ch=getchar()) != EOF){
        switch(ch){
        case ESC: return 1;
        case 10:
        case 32: return 0;
        }

        buffer[len ++] = ch;
    }

    return 0;
}

unsigned int charToInt(){
    char *ans = validInput(_VALID_NUM_);

    if (len > 6){
        p("tooooo long, i don't think have so much guest in your hotel ... ... he he");
        p("\nEnter a accepted range:");
        return charToInt();
    }

    unsigned int input = 0, i;
    for (i = 0; i < len; ++ i){
        input *= 10;
        input += ans[i] - '0';
    }

    return input;
}
