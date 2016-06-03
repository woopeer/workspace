#include "util.h"
#include "guest.h"

#ifndef __ROOM_H
#define __ROOM_H

/*****************************************************************/
/*                         structure                             */
typedef struct LINKTYPE{
    unsigned int type;
    unsigned int time;
    double money;
    struct LINKTYPE *next;
}LINKTYPE;
typedef LINKTYPE* linkType;
typedef LINKTYPE _linkType;

typedef struct ROOM{
    unsigned int id;
    linkType type;
}ROOM;
typedef ROOM* Room;
typedef ROOM _Room;

typedef struct LINKROOM{
    Room r;
    struct LINKROOM *next;
}LINKROOM;
typedef LINKROOM* linkRoom;
typedef LINKROOM _linkRoom;

typedef struct ROOMLIST{
    Guest guest;
    struct ROOMLIST *next;
}ROOMLIST;
typedef ROOMLIST* roomList;
typedef ROOMLIST _RoomList;
/*****************************************************************/

extern unsigned int idRoom;
extern unsigned int idType;
linkRoom headRoom;
roomList headList;
linkType headType;

/*****************************************************************/
/*                     function declaration                      */
void initRoom(void);
Room createRoom(unsigned int type);
void modifyRoom(unsigned int type, unsigned int id);
void deleteRoom(unsigned int id);
void createType(unsigned int time, double money);
void modifyType(unsigned int time, double money, unsigned int id);
void deleteType(unsigned int id);
void updateList(void);
void printRoom(void);
void printType(void);
linkType getType(unsigned int id);
linkRoom getRoom(unsigned int id);
/*****************************************************************/

#endif // __ROOM_H
