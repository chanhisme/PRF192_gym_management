#ifndef UTILS_H
#define UTILS_H
int canRemove(struct memberProfile *members, int index);
int isValidId(char id[]);
int worldCouting(char *name);
int isValidName(char *name);
int isValidBirthYear(int year);
int isValidMemberShipType(int choice);
#endif