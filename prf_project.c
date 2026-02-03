#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct memberProfile{
    char memberId[10];
    char fullName[30];
    int birthYear;
    char memberType[30];
};
void displayMenu();
int inputChoice();
void displayMemberMenu();
void addMember(int size, int*total, struct memberProfile **members);
void displayAllMember(int total, struct memberProfile*members);
int searchMemberById(char findId[10], int total, struct memberProfile* members);
void displayMember(int i, struct memberProfile * members);
void displaySortMenu();
int inputMemberChoice();
int inputSortChoice();
void sortMemberByBirthYearYoung_to_old(struct memberProfile ** members, int total);
void sortMemberByBirthYearOlder_to_young(struct memberProfile ** members, int total);




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
                    sortMemberByBirthYearYoung_to_old(&members, total);
                }
                else if(sortChoice == 2){
                    sortMemberByBirthYearOlder_to_young(&members, total);
                }
                else{
                    printf("***PLEASE select 1 or 2, try again!\n");
                }

            }
            else if(memberChoice == 4){
                //Nhập id muốn tìm
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
            else{
                printf("***PLEASE choose 1 of options in menu, try again!\n");
            }
        
        }
        
        else if(choice == 3){
            displayAllMember(total, members);
        }
    }while(choice != 0);
    







    return 0;
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
int inputSortChoice(){
    int sortChoice;
    printf("Enter your choice: ");
    scanf("%d", &sortChoice);
    getchar();
    return sortChoice;
}
int isValidId(char id[]) {
    char preFix[4] = "GYM";
    if(strlen(id) > 10 || strlen(id) == 0){
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
    if(name[0] == ' ' || name[len - 1] == ' ') return 0;

    for(int i = 0; i < len; i++){
        char c = name[i];
        // Không cho 2 space liên tiếp
        //đồng thời check ko cho đầu và kết thúc chuỗi là 1 space
        if(name[i] == ' ' && name[i + 1] == ' '){
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
int searchMemberById(char findId[10], int total, struct memberProfile * members){
    int i = 0;
    for(; i < total;i++){
        if(strcmp(findId, members[i].memberId) == 0){
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
        printf("=====MENU====\n");
        printf("1. Member\n");
        printf("2. Trainer\n");
        printf("3. Display\n");
        printf("4. Export file\n");
        printf("0. Exit\n");
}
void displayMemberMenu(){
    printf("=====MENU====\n");
    printf("1. Add member\n");
    printf("2. Remove member\n");
    printf("3. Sort member\n");
    printf("4. Search member\n");
}
void addMember(int size, int*total, struct memberProfile **members){
    *members = realloc(*members, (*total +size) * sizeof(struct memberProfile));
    if(*members == NULL){
        printf("Memory allocation failed!\n");
        return;
    }
    for(int i = 0; i < size; i++){
        //tạo index mới trong mảng
        int idx = (*total) + i; 
        char inputID[10];
        //kiểm tra ID
        do{
            printf("Enter the #%d member ID: ", idx+1);
            fgets(inputID, sizeof(inputID), stdin);
            inputID[strcspn(inputID, "\n")] = '\0';
        }
        while(!isValidId(inputID));
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
        do{
            printf("Enter the birthYear of #%d member: ", idx+1);
            scanf("%d", &inputYear);
        }
        while(!isValidBirthYear(inputYear));
        (*members)[idx].birthYear = inputYear;

        int type;
        printf("Enter the type membership (1. Standard / 2. VIP): ");
        scanf("%d", &type);
        getchar();
        if(type == 1) strcpy((*members)[idx].memberType, "Standard");
        else if(type == 2) strcpy((*members)[idx].memberType, "VIP");
        }
    (*total) += size;
    }
void sortMemberByBirthYearYoung_to_old(struct memberProfile ** members, int total){
    int i =0;
    for(; i < total - 1; i++){
        int j = 0;
        for(; j < total - 1 - i; j++){
            if((*members)[j].birthYear < (*members)[j+1].birthYear){
                struct memberProfile temp = (*members)[j];
                (*members)[j] = (*members)[j+1];
                (*members)[j+1] = temp;
            }
        }
    }
    printf("Sort succesfully\n");

}
void sortMemberByBirthYearOlder_to_young(struct memberProfile ** members, int total){
    int i =0;
    for(; i < total - 1; i++){
        int j = 0;
        for(; j < total - 1 - i; j++){
            if((*members)[j+1].birthYear < (*members)[j].birthYear){
                struct memberProfile temp = (*members)[j];
                (*members)[j] = (*members)[j+1];
                (*members)[j+1] = temp;
            }
        }
    }
    printf("Sort succesfully\\n");
}
void displaySortMenu(){
    printf("=====SORT=====\n");
    printf("1. Youngest to oldest\n");
    printf("2. Oldest to youngest\n");
}
void displayAllMember(int total, struct memberProfile*members){
    if(total == 0){
        printf("This list is empty");
    }
    else{
        for(int i = 0; i < total; i++){
            printf("%s\t|\t%s\t|\t%d\t|\t%s\n", 
                members[i].memberId,
                members[i].fullName,
                members[i].birthYear,
                members[i].memberType);
        }
    }
}





















