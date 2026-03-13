#ifndef TRAINER_H
#define TRAINER_H
#include "member.h"
struct trainerProfile{
    char trainerId[10];
    char trainerName[32];
    char specialty[20];
    char assignedMemberId[10];
    int monthlyFee;
    int memberCnt;
    long long total; //do đơn vị tiền tệ VN lớn nên dùng long long
};
extern struct trainerProfile trainers[]; 
extern int numberOfTrainer;
void displayAllTrainer(struct trainerProfile *trainers, int numberOfTrainer);
void displayTrainer(int i, struct trainerProfile trainerList[]);
void assignTrainer(int trainerIndex,int memberIndex, struct memberProfile **members, struct trainerProfile *trainers);
void caculateTotalRevenue(struct trainerProfile *trainers, int numberOfTrainer);
void displayRevenue(struct trainerProfile *trainer, int numberOfTrainer);
int searchTrainerById(char findId[10], int size, struct trainerProfile trainerList[]);
int searchTrainerByName(char findName[30], struct trainerProfile trainers[], int numberOfTrainer);






















#endif