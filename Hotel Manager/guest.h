#ifndef __GUEST_H
#define __GUEST_H
/*****************************************************************/
/*                         structure                             */
typedef struct GUEST{
    unsigned int id;
    unsigned int idRoom;
    unsigned int age;
    char* name;
    struct GUEST *roommate;
}GUEST;
typedef struct GUEST* Guest;
typedef struct GUEST _Guest;

typedef struct LINKGUEST{
    Guest g;
    struct LINKGUEST *next;
}LINKGUEST;
typedef LINKGUEST* linkGuest;
typedef LINKGUEST _linkGuest;
/*****************************************************************/


extern unsigned int idGuest;
linkGuest headGuest;

/*****************************************************************/
/*                     function declaration                      */
void initGuest(void);
void createGuest(unsigned int age, char name[8], unsigned int id);
void modifyGuest(unsigned int age, char name[8], unsigned int id);
void deleteGuest(unsigned int id);
/******************************************************************/

#endif // __GUEST_H
