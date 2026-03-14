#ifndef UTILS_H
#define UTILS_H
#include "member.h"
int canRemove(struct memberProfile *members, int index);
int isValidId(char id[]);
int worldCouting(char *name);
int isValidName(char *name);
int isValidBirthYear(int year);
int isValidMemberShipType(int choice);
#endif