#ifndef __UTIL_H
#define __UTIL_H

#define p(x) printf("%s\n", x)

#define ESC 27

enum{
    _VALID_NUM_, _VALID_NUM_ALPHA_, _VALID_ALPHA_,

    _NUM_VALID_
};

typedef struct link{
    unsigned int value;
    struct link *next;
}link;

extern char buffer[256];

void delay(int seconds);
char *validInput(unsigned int mode);
char validInputOne(unsigned int mode);
int getAnsweri(int *retrict, unsigned int len);
unsigned int validInputElementNumAlpha(char input);
unsigned int validInputElementNum(char input);
unsigned int validInputElementAlpha(char input);
unsigned int inputValidProcess();
char *validInputFloat();
int getAge();
char *getName();
int getTime();
double getMoney();
char *getPath();
unsigned int charToInt();

#endif // __UTIL_H
