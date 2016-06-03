#ifndef __RECORD_H
#define __RECORD_H

#define SAVE 1
#define READ 2

void balance(char *fileName, unsigned int mode);
char *append(char *a, char *b);
void fileOperation(unsigned int position, unsigned int mode);
void modifyFilePath(unsigned int position);
double totalMoney();

#endif // __RECORD_H
