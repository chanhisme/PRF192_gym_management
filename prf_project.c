#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct memberProfile{
    char memberId[10];
    char fullName[30];
    int birthYear;
    char memberType[30];
    time_t registerTime;
};
struct trainerProfile{
    char trainerID[10];
    char trainerName[30];
    // char specialty[20];
    // char assignedMemberId[10];
    // double monthlyFee;
};
int numberOfTrainer = 10;
struct trainerProfile trainerList[10] = {
    {"T001", "An"},
    {"T002", "Binh"}
};
void displayMenu();
int inputChoice();
void displayMemberMenu();
void addMember(int size, int*total, struct memberProfile **members);
void displayAllMember(int total, struct memberProfile*members);
int searchMemberById(char findId[10], int total, struct memberProfile* members);
int searchMemberByName(char findName[30], int total, struct memberProfile * members);
int searchTrainerById(char findId[10], int size, struct trainerProfile trainerList[]);
void displayMember(int i, struct memberProfile * members);
void displaySortMenu();
int inputMemberChoice();
int inputSortChoice();
void sortMemberByBirthYearYoung_to_old(struct memberProfile * members, int total);
void sortMemberByBirthYearOlder_to_young(struct memberProfile * members, int total);
void displayFileMenu();
int inputFileChoice();
void displayTrainerMenu();
int inputTrainerChoice();
void displaySearchmenu();
int inputSearchChoice();
void displayTrainer(int idx, struct trainerProfile trainerList[]);
int main(){
    int choice;
    int total = 0;
    struct memberProfile * members = NULL;
    do{
        displayMenu();
        choice = inputChoice();
        if(choice == 1){
            int memberChoice;
            displayMemberMenu();
            memberChoice = inputMemberChoice();
            if(memberChoice == 1){
                int n;
                printf("How many members: ");
                scanf("%d",&n);
                getchar(); 
                addMember(n, &total, &members);
            }
            else if(memberChoice == 3){
                int sortChoice;
                displaySortMenu();
                sortChoice = inputSortChoice();
                if(sortChoice ==1){
                    sortMemberByBirthYearYoung_to_old(members, total);
                }
                else if(sortChoice == 2){
                    sortMemberByBirthYearOlder_to_young(members, total);
                }
                else if(sortChoice == 0){}
                else{
                    printf("***PLEASE select 1 or 2, try again!\n");
                }

            }
            else if(memberChoice == 4){
                int searchChoice;
                displaySearchmenu();
                searchChoice = inputSearchChoice();
                if(searchChoice == 1){
                    char findId[10];
                    printf("Enter ID you want to find: ");
                    fgets(findId, sizeof(findId), stdin);
                    findId[strcspn(findId, "\n")] = '\0';
                    //Linear search với findId
                    int index = searchMemberById(findId, total, members);
                    if(index!= -1){
                        displayMember(index, members);
                    }
                    else{
                        printf("This id is not exist\n");
                    }
                }
                else if(searchChoice == 2){
                    char findName[30];
                    printf("Enter the name you want to find: ");
                    fgets(findName, sizeof(findName), stdin);
                    findName[strcspn(findName, "\n")]= '\0';
                    int index = searchMemberByName(findName, total, members);
                    if(index != -1){
                        displayMember(index, members);
                    }
                    else{
                        printf("This name is not exist\n");
                    }
                }
                
            }
            else if(memberChoice == 0){

            }
            else{
                printf("***PLEASE choose 1 of options in menu, try again!\n");
            }
        
        }
        else if(choice == 2){
            int trainerChoice;
            displayTrainerMenu();
            trainerChoice = inputTrainerChoice();
            if(trainerChoice == 1){

            }
            else if(trainerChoice == 4){
                int searchChoice;
                displaySearchmenu();
                searchChoice = inputSearchChoice();
                if(searchChoice == 1){
                    char findId[10];
                    printf("Enter ID you want to find: ");
                    fgets(findId, sizeof(findId), stdin);
                    findId[strcspn(findId, "\n")] = '\0';
                    int index = searchTrainerById(findId, numberOfTrainer, trainerList);
                    if(index!= -1){
                        displayTrainer(index, trainerList);
                    }
                    else{
                        printf("This id is not exist\n");
                    }
                }
            }
            
            
        }
        else if(choice == 3){
            displayAllMember(total, members);
        }
        else if(choice == 4){
            int fileChoice;
            displayFileMenu();
            fileChoice = inputFileChoice();
            if(fileChoice == 1){

            }
            else if(fileChoice == 0){}
            else{
                printf("***PLEASE choose 1 of options in menu, try again!\n");
            }
        }
    }while(choice != 0);
    






    free(members);
    members = NULL;

    return 0;
}
int inputFileChoice(){
    int fileChoice;
    printf("Enter file choice: ");
    scanf("%d", &fileChoice);
    getchar();
    return fileChoice;
}
int inputMemberChoice(){
    int memberChoice;
    printf("Enter your choice: ");
    scanf("%d", &memberChoice);
    getchar();
    return memberChoice;
}
int inputChoice(){
    int choice;
    printf("Enter your choice: ");
    scanf("%d",&choice);
    getchar();
    return choice;
}
int inputTrainerChoice(){
    int trainerChoice;
    printf("Enter your choice: ");
    scanf("%d", &trainerChoice);
    getchar();
    return trainerChoice;
}
int inputSortChoice(){
    int sortChoice;
    printf("Enter your choice: ");
    scanf("%d", &sortChoice);
    getchar();
    return sortChoice;
}
int inputSearchChoice(){
    int searchChoice;
    printf("Enter your choice: ");
    scanf("%d", &searchChoice);
    getchar();
    return searchChoice;
}
int isValidId(char id[]) {
    char preFix[4] = "GYM";
    if(strlen(id) >= 10 || strlen(id) == 0){
        return 0;
    }
    //hàm strncmp sẽ so sánh 2 string như 2 số theo bảng mã ascii
    else if(strlen(id) >=3 && strncmp(id, preFix, 3) == 0) {
        return 1; 
    } 
    else {
        return 0;
    }
}
int isValidName(char *name) {
    int hasLetter = 0;
    int len = strlen(name);

    if(len == 0) return 0;
    if(name[0] == ' ' || name[len - 1] == ' ') {
        return 0;
    }
    int i = 0;
    for(; i < len; i++){
        char c = name[i];
        // Không cho 2 space liên tiếp
        //đồng thời check ko cho đầu và kết thúc chuỗi là 1 space
        if(i < len -1 && name[i] == ' ' && name[i + 1] == ' '){
            return 0;
        }
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            hasLetter = 1;
        }
        else if(c == ' ') {
            continue;
        }
        else {
            return 0;
        }
    }
    return hasLetter;
}
int isValidBirthYear(int year) {
    int ok = 0;
    if (year >= 1900 && year <= 2020) {
        ok = 1;
    }
    return ok;
}
int isValidMemberShipType(int choice){
	int ok = 0;
    if (choice == 1 || choice == 2){
    	ok = 1;
    	return ok;
	}
  	return ok;
}
int searchMemberById(char findId[10], int total, struct memberProfile * members){
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
int searchTrainerById(char findId[10], int size, struct trainerProfile trainerList[]){
    int i = 0;
    for(; i < size; i++){
        if(strcmp(findId, trainerList[i].trainerID) == 0){
            return i;
        }
    }
    return -1;
}
//Hàm này chỉ display 1 member khi dùng search
void displayMember(int i, struct memberProfile * members){
    printf("%s\t|\t%s\t|\t%d\t|\t%s\n", 
            members[i].memberId,
            members[i].fullName,
            members[i].birthYear,
            members[i].memberType);
    
}
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
        char inputID[10];
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
        }
        while(!isValidName(inputName));
        strcpy((*members)[idx].fullName, inputName);
        int inputYear;
        //Kiểm tra năm sinh 
        do{
            printf("Enter the birthYear of #%d member: ", idx+1);
            scanf("%d", &inputYear);
        }
        while(!isValidBirthYear(inputYear));
        (*members)[idx].birthYear = inputYear;

        int type;
        do{
            printf("Enter the type membership (1. Standard / 2. VIP): ");
            scanf("%d", &type);
            getchar();
        }
        while(isValidMemberShipType(type) != 1);
        if(type == 1) strcpy((*members)[idx].memberType, "Standard");
        else if(type == 2) strcpy((*members)[idx].memberType, "VIP");
        (*members)[idx].registerTime = time(NULL);
        }
    (*total) += size;
    }
void sortMemberByBirthYearYoung_to_old(struct memberProfile * members, int total){
    if(total == 0 || members == NULL){
        printf("It is a empty list\n");
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
void displaySortMenu(){
    printf("\n=====SORT MENU=====\n");
    printf("1. Youngest to oldest\n");
    printf("2. Oldest to youngest\n");
    printf("0. Back to main menu\n");
}
void displayAllMember(int total, struct memberProfile*members){
    if(total == 0 || members == NULL){
        printf("This list is empty");
    }
    else{
        printf("\n===== MEMBER LIST =====\n");
        for(int i = 0; i < total; i++){
            struct tm *t = localtime(&members[i].registerTime);
            printf("%s\t|\t%s\t|\t%d\t|\t%s\t|\t%02d/%02d/%04d %02d:%02d:%02d\n", 
                members[i].memberId,
                members[i].fullName,
                members[i].birthYear,
                members[i].memberType,
                t->tm_mday,
                t->tm_mon + 1,
                t->tm_year + 1900,
                t->tm_hour,
                t->tm_min,
                t->tm_sec);
        }
    }
}
void displayFileMenu(){
    printf("\n===== FILE MENU =====\n");
    printf("1. Save data to file\n");
    printf("2. Load data from file\n");
    printf("0. Back to main menu\n");
}
void displayTrainerMenu(){
    printf("\n=====TRAINER MENU=====\n");
    printf("1. Assign trainer\n");
    printf("2. Revenue\n");
    printf("3. Group members\n");
    printf("4. Search\n");
}
void displaySearchmenu(){
    printf("\n=====SEARCH MENU=====\n");
    printf("1. Search by id\n");
    printf("2. Search by name\n");
}
void displayTrainer(int idx, struct trainerProfile trainerList[]){
    printf("%s\t%s\n",
        trainerList[idx].trainerID,
        trainerList[idx].trainerName);
}














