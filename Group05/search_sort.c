#include "search_sort.h"
#include "member.h"
#include "trainer.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
int searchMemberById(char findId[16], int total, struct memberProfile * members){
    int i = 0;
    for(; i < total;i++){
        if(strcmp(findId, members[i].memberId) == 0){
            return i;
        }
    }
    return -1;
}
int searchMemberByName(char findName[30], int total, struct memberProfile * members){
    int i = 0;
    for(; i < total; i++){
        if(strcmp(findName, members[i].fullName)==0){
            return i;
        }
    }
    return -1;
}
void sortMemberByBirthYearYoung_to_old(struct memberProfile * members, int total){
    if(total == 0 || members == NULL){
        printf("This is a empty list\n");
    }
    else{
        int i =0;
        for(; i < total - 1; i++){
            int j = 0;
            for(; j < total - 1 - i; j++){
                if(members[j].birthYear < members[j+1].birthYear){
                    struct memberProfile temp = members[j];
                    members[j] = members[j+1];
                    members[j+1] = temp;
                }
            }
        }
        printf("Sort succesfully\n");
    }

}
void sortMemberByBirthYearOlder_to_young(struct memberProfile *members, int total){
    if(total == 0 || members == NULL){
        printf("It is a empty list\n");
    }
    else{
        int i =0;
        for(; i < total - 1; i++){
            int j = 0;
            for(; j < total - 1 - i; j++){
                if(members[j+1].birthYear < members[j].birthYear){
                    struct memberProfile temp = members[j];
                    members[j] = members[j+1];
                    members[j+1] = temp;
                }
            }
        }
        printf("Sort succesfully\n");
    }
}
void sortByDateLastest(struct memberProfile * members, int total){
    for(int i = 0; i < total - 1; i++){
        for(int j = 0; j < total - i - 1; j++){
            if( members[j].registerTime < members[j+1].registerTime ){
                struct memberProfile temp = members[j];
                    members[j] = members[j+1];
                    members[j+1] = temp;
            }
        }
    }
    printf("Sort succesfully\n");
}
void sortByDateOldest(struct memberProfile * members, int total){
    for(int i = 0; i < total - 1; i++){
        for(int j = 0; j < total - i - 1; j++){
            if( members[j].registerTime > members[j+1].registerTime ){
                struct memberProfile temp = members[j];
                    members[j] = members[j+1];
                    members[j+1] = temp;
            }
        }
    }
    printf("Sort succesfully\n");
}















