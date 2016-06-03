#include <stdio.h>
#include <stdlib.h>
#include "./woopFc.h"

/**************************************************************************/
#define LARGENUMBER 100000
/**************************************************************************/

/**************************************************************************/
#define p(x) printf(x); printf("\n");
#define p2(x, y) printf(x, y), printf("\n")
#define ps(x) printf("%s\n", x)
#define pc(x) printf("%c\n", x)
#define pd(x) printf("%d\n", x)
/**************************************************************************/

/**************************************************************************/
#define len(x) (sizeof(x) / sizeof(x[0]))
/**************************************************************************/

/**************************************************************************/
#define US(x) Uncertain_String(x)
#define ES(x, y) Exchange_String(x, y)
#define EI(x, y) Exchange_Integer(x, y)
#define MS(s1, s2) Multiplication_String(s1, s2)
#define DS(s1, s2) Division_String(s1, s2)
#define PS(s1, s2) Plus_String(s1, s2)
#define MuS(s1, s2) Minus_String(s1, s2)
#define MSF(s1, s2) Multiplication_String_Fraction(s1, s2)
#define DSF(s1, s2) Division_String_Fraction(s1, s2)
#define PSF(s1, s2) Plus_String_Fraction(s1, s2)
#define MuSF(s1, s2) Minus_String_Fraction(s1, s2)
#define C2I(ch) Char_to_Integer(ch)
#define I2C(in) Integer_to_Char(in)
#define L2U(x) Lowercase_to_Uppercase(x)
/**************************************************************************/

/*Functional Methods*/
void init();
void InputMethod();
void Wrong();
void Search_Engine(char *, int *, int *);
int Check(char *);
int Check_O(char);
int isFloatType(char **, char **);
void Uncertain_String(char **);
void Exchange_String(char **, char **);
void Exchange_Integer(int *, int *);
void Strcpy(char *, char **, int , int);
void Strdsc(char **, int , int, int);
void Strcut(char **, int, char **, int , int);
char *Strcat(char *, char *);
char *Lowercase_to_Uppercase(char *);
char *Plus_String(char *, char *);
char *Minus_String(char *, char *);
char *Multiplication_String(char *, char *);
//char *Division_String(char *, char *);
char *Plus_String_Fraction(char *, char *);
char *Minus_String_Fraction(char *, char *);
char *Multiplication_String_Fraction(char *, char *);
//char *Division_String_Fraction(char *, char *);
/*Functional Methods*/

int isFloatType(char **s1, char **s2){
    enum{NOT_FLOAT, FLOAT};
    int idx1, idx2, len1 = strlen(*s1), len2 = strlen(*s2);
    int i, j;
    idx1 = idx2 = 0;
    for (i = 0; i < len1; ++ i) if ((*s1)[i] == '.'){
        idx1 = i;
        break;
    }
    for (i = 0; i < len2; ++ i) if ((*s2)[i] == '.'){
        idx2 = i;
        break;
    }
    if (!idx1 && !idx2) return NOT_FLOAT;
    if (!idx1 || !idx2){
        if (!idx1) *s1 = Strcat(*s1, ".0");
        else *s2 = Strcat(*s2, ".0");
    }
    return FLOAT;
}

/*Universal Variable*/
char *S[LARGENUMBER], Operation[LARGENUMBER];
/*Universal Variable*/

int main()
{
    init();
    return 0;
}

void init(){
    p(L2U("welcome to woop's calculator"));
    p("\n");
    p(L2U("this can really helpful on your study, its my comsummate final exam work!"));
    p(L2U("it can do plus , minus and multi (pay a attention to this do not include devision !!!)"));
    p(L2U("for some examples:"))
    p(L2U("i'll illustrate the processing using simple calculas such that making you totally understand how it work.:)"));
    p(L2U("input 123456789 + 123456789, then you'll get a sum of them, 246913578."));
    p(L2U("minus and multi are the same case of before, so just try it, do not afraid to fail it, enjoy it buddy!!"));
    p("");
    p("Uncertain String to Integer 's Plus, Minus, Multiplication:");
    p("Please Enter You Function as Below.\n");

    InputMethod();
}

void Wrong(){
    p(L2U("there's some mistakes in your input, please check it again, or i'm stuck then forgive me.\n"));
    return;
}

/*Input API*/
void InputMethod(){
    int idx_S = 0, idx_O = 0, i, j;
    char *s, *result;
    //US(&s);
    s = "654 + 65546 + 132";

    Search_Engine(s, &idx_S, &idx_O);
    for (i = 0; i < idx_S; ++ i) if (*S[i] == '\000' && Operation[i] == '-') S[i] = "0";
    for (i = 0; i < idx_S || i < idx_O; ++ i)
        if((i < idx_S && !Check(S[i])) || (i < idx_O && !Check_O(Operation[i])) || !idx_O || !idx_S) {
            Wrong();
            return;
        }
    result = S[0];
    for (i = 0; i < idx_O; ++ i){
        switch(Operation[i]) {
            case '-':
                result = (isFloatType(&result, &S[i + 1])) ? MuSF(result, S[i + 1]) : MuS(result, S[i + 1]);
                break;
            case '+':
                result = (isFloatType(&result, &S[i + 1])) ? PSF(result, S[i + 1]) : PS(result, S[i + 1]);
                break;
            case '*':
                result = (isFloatType(&result, &S[i + 1])) ? MSF(result, S[i + 1]) : MS(result, S[i + 1]);
                break;
            default:
                Wrong();
                break;
        }
    }
    ps(result);
}
/*Input API*/

/*Search Engine*/
void Search_Engine(char *s, int *idx_S, int *idx_O){
    if(s == NULL) return;
    char Operator[3] = {'-', '+', '*'};
    int i, j, len = strlen(s), idO, idS;
    idO = idS = 0;
    for (i = 0; ; ++ i){
        if(i >= len) break;
        for (j = 0; j < 3; ++ j){
            if (s[i] == Operator[j]){
                Operation[idO ++] = s[i];
                Strcut(&s, 0, &(S[idS ++]), 0, i);
                Strdsc(&s, 0, 1, 0);
                i = 0;
                break;
            }
        }
        len = strlen(s);
    }
    S[idS ++] = s;
    *idx_O = idO;
    *idx_S = idS;
    for (i = 0; i < idS; ++ i){
        for (j = 0; j < strlen(S[i]); ++ j){
            if (S[i][j] != ' '){
                Strdsc(&S[i], 0, j, 1);
                break;
            }
        }
        for (j = strlen(S[i]) - 1; j >= 0; -- j){
            if (S[i][j] != ' '){
                Strdsc(&S[i], j + 1, strlen(S[i]) - j - 1, 0);
                break;
            }
        }
    }
    return;
}
/*Search Engine*/
