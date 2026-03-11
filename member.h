#ifndef MEMBER_H
#define MEMBER_H
#include <time.h>
struct memberProfile{
    char memberId[16];
    char trainerId[32];
    char fullName[30];
    int birthYear;
    char memberType[30];
    time_t registerTime;
    int active; // 1 là có active, 0 là inactive
};
void addMember(int size, int* total, struct memberProfile **members);
void removeMember(struct memberProfile ** members, int * total);
void displayAllMember(int total, struct memberProfile* members);
void displayMember(int i, struct memberProfile * members);
int canRemove(struct memberProfile *members, int index);
void autoUpdateActive(struct memberProfile *members, int total);
void groupMemberByTrainerId(struct memberProfile *members, int total);


#endif