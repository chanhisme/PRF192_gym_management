#include "trainer.h"
#include "member.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

struct trainerProfile trainers[] = {
    {"T001", "An","Strength", "", 10000000, 0, 0},
    {"T002", "Binh", "Hypertrophy", "", 7000000, 0, 0},
    {"T003", "Lan", "Endurance", "", 5000000, 0, 0}
};
int numberOfTrainer = sizeof(trainers)/sizeof(trainers[0]);

void displayAllTrainer(struct trainerProfile *trainers, int numberOfTrainer){
    printf("\n===== TRAINER LIST =====\n");
    printf("%-10s | %-15s | %-15s | %-12s | %-10s\n",
       "ID", "Name", "Specialty", "MonthlyFee", "Members");
    for(int i = 0; i < numberOfTrainer; i++){
        printf("%-10s | %-15s | %-15s | %-12d | %-10d\n",
            trainers[i].trainerId,
            trainers[i].trainerName,
            trainers[i].specialty,
            trainers[i].monthlyFee,
            trainers[i].memberCnt);
    }
}
void displayTrainer(int i, struct trainerProfile trainers[]){
	printf("\n===== TRAINER LIST =====\n");
    printf("%-10s | %-15s | %-15s | %-12s | %-10s\n",
       "ID", "Name", "Specialty", "MonthlyFee", "Members");
    printf("%-10s | %-15s | %-15s | %-12d | %-10d\n",
       trainers[i].trainerId,
       trainers[i].trainerName,
       trainers[i].specialty,
       trainers[i].monthlyFee,
       trainers[i].memberCnt);
}
void assignTrainer(int trainerIndex,int memberIndex, struct memberProfile **members, struct trainerProfile *trainers){
    if(strlen((*members)[memberIndex].trainerId) != 0){
        printf("This member already has a trainer\n");
        return;
    }
    strcpy((*members)[memberIndex].trainerId, 
    trainers[trainerIndex].trainerId);
    trainers[trainerIndex].memberCnt ++;
    printf("Assign succesfully\n");
}
void caculateTotalRevenue(struct trainerProfile *trainers, int numberOfTrainer){
    for(int i = 0; i < numberOfTrainer; i++){
        trainers[i].total = (long long)trainers[i].monthlyFee * trainers[i].memberCnt;
    }
    printf("Calculate successfully\n");
}
void displayRevenue(struct trainerProfile *trainers, int numberOfTrainer){
    for(int i = 0; i < numberOfTrainer; i++){
        printf("%-10s %-15s %8d %15d %15lld\n",
            trainers[i].trainerId,
            trainers[i].trainerName,
            trainers[i].memberCnt,
            trainers[i].monthlyFee,
            trainers[i].total);
    }
}
int searchTrainerById(char findId[16], int size, struct trainerProfile trainerList[]){
    int i = 0;
    for(; i < size; i++){
        if(strcmp(findId, trainerList[i].trainerId) == 0){
            return i;
        }
    }
    return -1;
}










