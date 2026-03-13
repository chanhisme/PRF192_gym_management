#ifndef SEARCH_SORT_H
#define SEARCH_SORT_H
#include "member.h"
int searchMemberById(char findId[16], int total, struct memberProfile * members);
int searchMemberByName(char findName[30], int total, struct memberProfile * members);
void sortMemberByBirthYearYoung_to_old(struct memberProfile * members, int total);
void sortMemberByBirthYearOlder_to_young(struct memberProfile *members, int total);
void sortByDateLastest(struct memberProfile * members, int total);
void sortByDateOldest(struct memberProfile * members, int total);





#endif