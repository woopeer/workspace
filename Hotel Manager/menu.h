#ifndef __MENU_H
#define __MENU_H

enum{
    _WINDOW_, _GUEST_, _ROOM_, _TYPE_, _RECORD_, _BALANCE_,
    _NUM_MENU_,

    _NEW_, _DELETE_, _MODIFY_, _SAVE_, _READ_, _BACK_,
    _NUM_choice_,

    _CHOOSE_, _EXIT_
};

enum{
    _NAME_, _NUMBER_,

    _NUM_RETRICTALPHA_
};

/*****************************************************************/
/*                     function declaration                      */
void menu(unsigned int mode);
void show(void);
void initRetrict(void);
/*****************************************************************/

#endif // __MENU_H
