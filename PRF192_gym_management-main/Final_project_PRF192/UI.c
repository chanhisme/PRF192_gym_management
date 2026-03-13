#include "UI.H"
#include <stdio.h>
#include "utils.h"
//Hàm này chỉ display 1 member khi dùng search
void displayMenu(){
        printf("\n=====MENU====\n");
        printf("1. Member\n");
        printf("2. Trainer\n");
        printf("3. Display\n");
        printf("4. Export file\n");
        printf("0. Exit\n");
}
void displayMemberMenu(){
    printf("\n=====MEMBER MENU====\n");
    printf("1. Add member\n");
    printf("2. Remove member\n");
    printf("3. Sort member\n");
    printf("4. Search member\n");
    printf("0. Back to main menu\n");
}
void displayTrainerMenu(){
    printf("\n=====TRAINER MENU=====\n");
    printf("1. Assign trainer\n");
    printf("2. Revenue\n");
    printf("3. Group members\n");
    printf("4. Search\n");
    printf("0. Back to main menu\n");
}
void displaySortMenu(){
    printf("\n=====SORT MENU=====\n");
    printf("1. Youngest to oldest\n");
    printf("2. Oldest to youngest\n");
    printf("3. Lastest to oldest\n");
    printf("4. Oldest to lastest\n");
    printf("0. Back to main menu\n");
}
void displaySearchmenu(){
    printf("\n=====SEARCH MENU=====\n");
    printf("1. Search by id\n");
    printf("2. Search by name\n");
}
void displaySaveMenu(){
	printf("\n=====SAVE MENU=====\n");
	printf("1.Binary\n");
	printf("2.Text\n");
}
void displayFileMenu(){
    printf("\n===== FILE MENU =====\n");
    printf("1. Save data to file\n");
    printf("2. Load data from file\n");
    printf("0. Back to main menu\n");
    printf("0. Back to main menu\n");
}
void displayMenuLoadFile(){
	printf("\n====MENU LOAD FILE=====\n");
	printf("1. Binary file\n");
	printf("2. Text file\n");
}
int inputChoice(){
    int choice;
    printf("Enter your choice: ");
    scanf("%d",&choice);
    clearBuffer();
    return choice;
}
int inputMemberChoice(){
    int memberChoice;
    printf("Enter your choice: ");
    scanf("%d", &memberChoice);
    clearBuffer();
    return memberChoice;
}
int inputTrainerChoice(){
    int trainerChoice;
    printf("Enter your choice: ");
    scanf("%d", &trainerChoice);
    clearBuffer();
    return trainerChoice;
}
int inputSortChoice(){
    int sortChoice;
    printf("Enter your choice: ");
    scanf("%d", &sortChoice);
    clearBuffer();
    return sortChoice;
}
int inputSearchChoice(){
    int searchChoice;
    printf("Enter your choice: ");
    scanf("%d", &searchChoice);
    clearBuffer();
    return searchChoice;
}
int inputSaveChoice(){
	int saveChoice;
	printf("Enter your save choice: ");
	scanf("%d", &saveChoice);
	clearBuffer();
	return saveChoice;
}
int inputFileChoice(){
    int fileChoice;
    printf("Enter file choice: ");
    scanf("%d", &fileChoice);
    clearBuffer();
    return fileChoice;
}
void inputString(char str[], int size){
	fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}
void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}





