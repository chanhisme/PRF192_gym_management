#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "member.h"
#include "utils.h"
void addMember(int size, int*total, struct memberProfile **members){
    struct memberProfile * tmp = realloc(*members, (*total +size) * sizeof(struct memberProfile));
    if(tmp == NULL){
        printf("Memory allocation failed!\n");
        return;
    }
    *members = tmp;
    for(int i = 0; i < size; i++){
        //tạo index mới trong mảng
        int idx = (*total) + i; 
        char inputID[16];
        //kiểm tra ID
        do{
            printf("Enter the #%d member ID: ", idx+1);
            fgets(inputID, sizeof(inputID), stdin);
            inputID[strcspn(inputID, "\n")] = '\0';
            if (!isValidId(inputID)) {
                printf("Invalid ID format. Must start with GYM.\n");
            }
            else if (searchMemberById(inputID, *total, *members) != -1) {
                printf("This ID already exists.\n");
            }
        }
        while(!isValidId(inputID) || searchMemberById(inputID, *total, *members) != -1);
        strcpy((*members)[idx].memberId, inputID);

        char inputName[30];
        //kiểm tra tên
        do{
            printf("Enter the name of #%d member: ", idx+1);
            fgets(inputName, sizeof(inputName), stdin);
            inputName[strcspn(inputName, "\n")] = '\0';
            if(!isValidName(inputName)){
                printf("This name is not valid\n");
            }
            if(searchMemberByName(inputName, *total, *members) != -1){
                printf("This name already exists.\n");
            }
            if(worldCouting(inputName) < 2){
                printf("This name must be 2 worlds\n");
            }
            
        }
        while(!isValidName(inputName) || worldCouting(inputName) < 2|| searchMemberByName(inputName, *total, *members) != -1);
        strcpy((*members)[idx].fullName, inputName);
        int inputYear;
        //Kiểm tra năm sinh 
        do{
            printf("Enter the birthYear of #%d member: ", idx+1);
            scanf("%d", &inputYear);
            clearBuffer();
            if(!isValidBirthYear(inputYear)){
                printf("This birth year is not valid\n");
            }
        }
        while(!isValidBirthYear(inputYear));
        (*members)[idx].birthYear = inputYear;

        int type;
        do{
            printf("Enter the type membership (1. Standard / 2. VIP): ");
            scanf("%d", &type);
            clearBuffer();
            if(isValidMemberShipType(type) != 1){
                printf("Your choice is not valid, please choose 1 or 2\n");
            }
        }
        while(isValidMemberShipType(type) != 1);

        if(type == 1) strcpy((*members)[idx].memberType, "Standard");
        else if(type == 2) strcpy((*members)[idx].memberType, "VIP");
        (*members)[idx].registerTime = time(NULL);
        (*members)[idx].active = 1;
    }
    (*total) += size;
}
void removeMember(struct memberProfile ** members, int * total){
    int i;
    char removeId[16];
    printf("Enter the id: ");
    inputString(removeId, sizeof(removeId));
    int index = searchMemberById(removeId, *total, *members);
    //tìm thấy nên index ko âm và nó ko active
    if(index != -1 && canRemove(*members, index) != 0){
        for(i = index; i < (*total)-1; i++){
            (*members)[i] = (*members)[i+1];
        }
        struct memberProfile *tmp = 
            realloc(*members, (*total -1) * sizeof(struct memberProfile));
        if(tmp != NULL){
            *members = tmp;
            (*total)--;
        }
        else {
            printf("Memory reallocation failed!\n");
        }
        
        printf("Remove successfully\n");
    }
    else{
        if(index == -1){
            printf("Cannot find this id\n");
        }
        else if(canRemove(*members, index) ==0){
            printf("This id is still active\n");
        }
        
    }

}
void displayAllMember(int total, struct memberProfile*members){
    if(total == 0 || members == NULL){
        printf("This list is empty");
    }
    else{
        printf("\n===== MEMBER LIST =====\n");
        for(int i = 0; i < total; i++){
            // displayAllMember(i, members);
            struct tm *t = localtime(&members[i].registerTime);
            printf("%-10s | %-10s | %-15s | %-6d | %-10s | %02d/%02d/%04d | %-6d\n",
                    members[i].memberId,
                    members[i].trainerId,
                    members[i].fullName,
                    members[i].birthYear,
                    members[i].memberType,
                    t->tm_mday,
                    t->tm_mon + 1,
                    t->tm_year + 1900,
                    members[i].active);
        }
    }
}
void displayMember(int i, struct memberProfile * members){
    struct tm *t = localtime(&members[i].registerTime);
    printf("%-12s | %-12s | %-18s | %6d | %-10s | %02d/%02d/%04d\n",
                members[i].memberId,
                members[i].trainerId,
                members[i].fullName,
                members[i].birthYear,
                members[i].memberType,
                t->tm_mday,
                t->tm_mon + 1,
                t->tm_year + 1900);
    
}
void autoUpdateActive(struct memberProfile *members, int total){
    time_t currTime = time(NULL);
    for(int i = 0; i < total; i++){
        double deltaTime = currTime - members[i].registerTime;
        deltaTime /= 86400.0;
        //dòng lệnh test xem khoảng cách số ngày
        // printf("%lf\n", deltaTime);
        if(deltaTime > 60){
            members[i].active = 0;
            printf("%s has been inactive after 60 days since registration.\n",
                members[i].fullName);
        }
    }
    printf("Update successfully\n");
}
void groupMemberByTrainerId(struct memberProfile *members, int total){
    for(int i = 0; i < total-1; i++){
        for(int j = 0; j < total - 1 - i; j ++){
            if(strlen(members[j].trainerId) == 0){
                continue;
            }
            //để vế trái lớn hơn vế phải thì vế trái trừ vế phải phải ra số dương
            if(strcmp(members[j].trainerId, members[j+1].trainerId) > 0){
                struct memberProfile tmp = members[j];
                members[j] = members[j+1];
                members[j+1] = tmp;
            }
        }
    }
    printf("Group succesfully\n");
}

