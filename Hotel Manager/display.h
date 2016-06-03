#ifndef __DISPLAY_H
#define __DISPLAY_H

#define p(x) printf("%s\n", x)

#define DAY 24
#define EXIT 0
#define BACK EXIT
#define CHOOSE -1
#define NEW 1
#define DELETE 2
#define MODIFY 3
#define LOOP 4

extern unsigned int _RUN_FLAG_;
extern unsigned int _LOOP_FLAG_;

/*****************************************************************/
/*                     function declaration                      */
unsigned int validId(unsigned int id, char *catogery);
/*****************************************************************/

#endif
