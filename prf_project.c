#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct memberProfile{
    char memberId[10];
    char trainerId[32];
    char fullName[30];
    int birthYear;
    char memberType[30];
    time_t registerTime;
    
};
struct trainerProfile{
    char trainerId[10];
    char trainerName[32];
    char specialty[20];
    char assignedMemberId[10];
    int monthlyFee;
    int memberCnt;
    long long total;
};
struct trainerProfile trainers[] = {
    {"T001", "An","Strength", "", 10000000, 0, 0},
    {"T002", "Binh", "Hypertrophy", "", 7000000, 0, 0},
    {"T003", "Lan", "Endurance", "", 5000000, 0, 0}
};
int numberOfTrainer = sizeof(trainers)/sizeof(trainers[0]);
//Function
void removeMember(struct memberProfile ** members, int * total);
void loadBinaryFile();
int inputLoadFile();
void loadTextFile();
void displaySaveMenu();
void buildBinaryFileName(char inputName[], char finalName[], int size);
void buildFileName(char inputName[], char finalName[], int size);
void inputString(char str[], int size);
void clearBuffer();
int inputSaveChoice();
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
void sortByDateLastest(struct memberProfile * members, int total);
void sortByDateOldest(struct memberProfile * members, int total);
void displayFileMenu();
int inputFileChoice();
void displayTrainerMenu();
int inputTrainerChoice();
void displaySearchmenu();
int inputSearchChoice();
void saveDataBinary(struct memberProfile * members, int total);
void displayTrainer(int idx, struct trainerProfile trainerList[]);
void saveDataToFile( struct memberProfile * members, int total);
void displayMenuLoadFile();
void autoLoadFile(struct memberProfile **members, int *total);
void autoSaveFile(struct memberProfile * members, int total);
void displayAllTrainer(struct trainerProfile *trainerList, int numberOfTrainer);
void assignTrainer(int trainerIndex,int memberIndex, struct memberProfile **members, struct trainerProfile *trainers);
void caculateTotalRevenue(struct trainerProfile *trainers, int numberOfTrainer);
void displayRevenue(struct trainerProfile *trainer, int numberOfTrainer);
void groupMemberByTrainerId(struct memberProfile *members, int total);
int main(){
    int choice;
    int total = 0;
    struct memberProfile * members = NULL;
    autoLoadFile(&members, &total);
    do{
        displayMenu();
        choice = inputChoice();
        //member
        if(choice == 1){
            int memberChoice;
            displayMemberMenu();
            memberChoice = inputMemberChoice();
            if(memberChoice == 1){
                int n;
                printf("How many members: ");
                scanf("%d",&n);
                clearBuffer();
                addMember(n, &total, &members);
            }
            else if(memberChoice == 2){
                removeMember(&members, &total);

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
                else if(sortChoice == 3){
                    sortByDateLastest(members, total);
                }
                else if(sortChoice == 4){
                    sortByDateOldest(members, total);

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
        //trainer
        else if(choice == 2){
            int trainerChoice;
            displayTrainerMenu();
            trainerChoice = inputTrainerChoice();
            if(trainerChoice == 1){
                char idMember[10];
                printf("Enter id member need to assign: ");
                inputString(idMember, sizeof(idMember));
                int memberIndex = searchMemberById(idMember, total, members);
                if(memberIndex != -1){
                    displayAllTrainer(trainers, numberOfTrainer);
                    char assignedTrainer[10];
                    printf("Enter your id trainer: ");
                    inputString(assignedTrainer, sizeof(assignedTrainer));
                    int trainerIndex = searchTrainerById(assignedTrainer, numberOfTrainer, trainers);
                    if(trainerIndex != -1){
                        assignTrainer(trainerIndex, memberIndex,  &members, trainers);
                    }

                }
                else{
                    printf("Cannot find this id\n");
                }
            }
            else if(trainerChoice == 2){
                caculateTotalRevenue(trainers, numberOfTrainer);
                displayRevenue(trainers, numberOfTrainer);
            }
            else if(trainerChoice == 3){
                groupMemberByTrainerId(members, total);
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
                    int index = searchTrainerById(findId, numberOfTrainer, trainers);
                    if(index!= -1){
                        displayTrainer(index, trainers);
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
				int saveChoice;
				displaySaveMenu();
				saveChoice = inputSaveChoice();
				if(saveChoice == 1){
					saveDataBinary(members, total);
				}
				else if(saveChoice == 2){
					saveDataToFile(members, total);
				}
                
            }
			else if(fileChoice == 2){
				int loadChoice;
				displayMenuLoadFile();
				loadChoice = inputLoadFile();
				if(loadChoice == 1){
					loadBinaryFile();

				}
				else if(loadChoice == 2){
					loadTextFile();
				}
			}
            else if(fileChoice == 0){}
            else{
                printf("***PLEASE choose 1 of options in menu, try again!\n");
            }
        }
    }while(choice != 0);
    





    autoSaveFile(members, total);
    free(members);
    members = NULL;

    return 0;
}



//Prototype
int inputFileChoice(){
    int fileChoice;
    printf("Enter file choice: ");
    scanf("%d", &fileChoice);
    clearBuffer();
    return fileChoice;
}
int inputMemberChoice(){
    int memberChoice;
    printf("Enter your choice: ");
    scanf("%d", &memberChoice);
    clearBuffer();
    return memberChoice;
}
int inputChoice(){
    int choice;
    printf("Enter your choice: ");
    scanf("%d",&choice);
    clearBuffer();
    return choice;
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
int inputLoadFile(){
	int loadChoice;
	printf("Enter your choice: ");
	scanf("%d", &loadChoice);
	clearBuffer();
	return loadChoice;
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
int searchTrainerById(char findId[10], int size, struct trainerProfile trainerList[]){
    int i = 0;
    for(; i < size; i++){
        if(strcmp(findId, trainerList[i].trainerId) == 0){
            return i;
        }
    }
    return -1;
}
//Hàm này chỉ display 1 member khi dùng search
void displayMember(int i, struct memberProfile * members){
    struct tm *t = localtime(&members[i].registerTime);
    printf("%s\t|\t%s\t|\t%s\t|\t%d\t|\t%s\t|\t%02d/%02d/%04d\n", 
                members[i].memberId,
                members[i].trainerId,
                members[i].fullName,
                members[i].birthYear,
                members[i].memberType,
                t->tm_mday,
                t->tm_mon + 1,
                t->tm_year + 1900);
    
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
            if(!isValidName(inputName)){
                printf("This name is not valid\n");
            }
            if(searchMemberByName(inputName, *total, *members) != -1){
                printf("This name already exists.\n");
            }
            
        }
        while(!isValidName(inputName) || searchMemberByName(inputName, *total, *members) != -1);
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
void sortByDateLastest(struct memberProfile * members, int total){
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
void sortByDateOldest(struct memberProfile * members, int total){
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
void removeMember(struct memberProfile ** members, int * total){
    int i;
    char removeId[16];
    printf("Enter the id: ");
    inputString(removeId, sizeof(removeId));
    int index = searchMemberById(removeId, *total, *members);
    //tìm thấy nên index ko âm
    if(index != -1){
        for(i = index; i < (*total)-1; i++){
            (*members)[i] = (*members)[i+1];
        }
        struct memberProfile *tmp = 
            realloc(*members, (*total -1) * sizeof(struct memberProfile));
        (*total)--;
        *members = tmp;
        printf("Remove successfully\n");
    }
    else{
        printf("Cannot find this name\n");
    }

}
void displaySortMenu(){
    printf("\n=====SORT MENU=====\n");
    printf("1. Youngest to oldest\n");
    printf("2. Oldest to youngest\n");
    printf("3. Lastest to oldest\n");
    printf("4. Oldest to lastest\n");
    printf("0. Back to main menu\n");
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
            printf("%s\t|\t%s\t|\t%s\t|\t%d\t|\t%s\t|\t%02d/%02d/%04d\n", 
                members[i].memberId,
                members[i].trainerId,
                members[i].fullName,
                members[i].birthYear,
                members[i].memberType,
                t->tm_mday,
                t->tm_mon + 1,
                t->tm_year + 1900);
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
    printf("%s\t%s\t%s\t%d\t\t%d\n",
        trainers[idx].trainerId,
        trainers[idx].trainerName,
        trainers[idx].specialty,
        trainers[idx].monthlyFee,
        trainers[idx].memberCnt);
}
void saveDataToFile( struct memberProfile * members, int total){
    char input[30];
    char fName[40];
    printf("Enter your name file : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    snprintf(fName, sizeof(fName), "%s.txt", input);
    FILE * fptr;
    fptr = fopen(fName, "w");
    if(!fptr){
        printf("Cannot create file\n");
        return;
    }
    else{
        for(int i = 0; i < total; i++){
            struct tm *t = localtime(&members[i].registerTime);
            if (t == NULL) continue;
            fprintf(fptr,
                "ID: %s\n"
                "Name: %s\n"
                "Birth Year: %d\n"
                "Type: %s\n"
                "Register Date: %02d/%02d/%04d\n"
                "-----------------------\n",
                members[i].memberId,
                members[i].fullName,
                members[i].birthYear,
                members[i].memberType,
                t->tm_mday,
                t->tm_mon + 1,
                t->tm_year + 1900);
        }
        printf("Export successfully\n");
        fclose(fptr);
    }
}
void clearBuffer(){
    while (getchar() != '\n');
}
void autoSaveFile(struct memberProfile * members, int total){
    FILE* fptr = fopen("Gym_Membership_&_Trainer_Management.txt", "w");
    if(!fptr){
        printf("Cannot create file\n");
        return;
    }
    else{
        for(int i = 0; i < total; i++){
            struct tm *t = localtime(&members[i].registerTime);
            if (t == NULL) continue;
            fprintf(fptr,
                "ID: %s\n"
                "Trainer: %s\n"
                "Name: %s\n"
                "Birth Year: %d\n"
                "Type: %s\n"
                "Register Date: %02d/%02d/%04d\n"
                "-----------------------\n",
                members[i].memberId,
                members[i].trainerId,
                members[i].fullName,
                members[i].birthYear,
                members[i].memberType,
                t->tm_mday,
                t->tm_mon + 1,
                t->tm_year + 1900);
        }
        printf("Export successfully\n");
        fclose(fptr);
    }
}
void autoLoadFile(struct memberProfile **members, int *total){
    FILE * fptr = fopen("Gym_Membership_&_Trainer_Management.txt", "r");
    if (!fptr){
		printf("File is not created\n");
		return;
	}
	else{
		printf("\n");
		char line[256];
        struct memberProfile temp;
		while(fgets(line, sizeof(line), fptr)){
            line[strcspn(line, "\n")] = '\0';
            if(strncmp(line, "ID: ", 4) == 0){
                strcpy(temp.memberId, line + 4);
            }
            else if(strncmp(line, "Name: ", 6) == 0){
                strcpy(temp.fullName, line + 6);
            }
            else if(strncmp(line, "Birth Year: ", 12) == 0){
                //đọc năm dạng chuỗi và đổi về giá int
                temp.birthYear = atoi(line + 12);
            }
            else if(strncmp(line, "Type: ", 6) == 0){
                strcpy(temp.memberType, line + 6);
            }
            else if(strncmp(line, "Register Date: ", 15) == 0){
                int day, month, year;
                //đọc string theo format
                sscanf(line + 15, "%d/%d/%d", &day, &month, &year);
                struct tm tm_info = {0};
                tm_info.tm_mday = day;
                tm_info.tm_mon = month - 1;
                tm_info.tm_year = year - 1900;
                //chuyển từ struct tm về time_t dùng mktime
                temp.registerTime = mktime(&tm_info);
            }
            else if(strncmp(line, "-----------------------", 23) == 0){
                // gặp dấu phân cách , lưu member vào mảng
                struct memberProfile *tmpPtr =
                    realloc(*members, (*total + 1) * sizeof(struct memberProfile));
                if(tmpPtr == NULL){
                    printf("Memory allocation failed\n");
                    fclose(fptr);
                    return;
                }
                *members = tmpPtr;
                (*members)[*total] = temp;
                (*total)++;
            }
    }
    fclose(fptr);
}
}
void inputString(char str[], int size){
	fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}

void buildFileName(char inputName[], char finalName[], int size){
	snprintf(finalName, size, "%s.txt", inputName);
}
void buildBinaryFileName(char inputName[], char finalName[], int size){
	snprintf(finalName, size, "%s.bin", inputName);
}
void saveDataBinary(struct memberProfile * members, int total){
	char input[30];
    char fName[40];
    printf("Enter your name file : ");
    inputString(input, sizeof(input));
	buildBinaryFileName(input, fName, sizeof(fName));
    FILE * fptr;
    fptr = fopen(fName, "wb");
	if(!fptr){
        printf("Cannot create file\n");
        return;
    }
	else{
		fwrite(members, sizeof(struct memberProfile), total, fptr);
		printf("Export successfully\n");
        fclose(fptr);
	}
}
int inputSaveChoice(){
	int saveChoice;
	printf("Enter your save choice: ");
	scanf("%d", &saveChoice);
	clearBuffer();
	return saveChoice;
}

void displayMenuLoadFile(){
	printf("\n====MENU LOAD FILE=====\n");
	printf("1. Binary file\n");
	printf("2. Text file\n");
}
void loadBinaryFile(){
	char inputName[32];
	char fName[40];
	printf("Enter your name file : ");
    inputString(inputName, sizeof(inputName));
	buildBinaryFileName(inputName, fName, sizeof(fName));
	FILE * fptr = fopen(fName, "rb");
	if(!fptr){
		printf("Cannot open this file\n");
		return;
	}
	else{
		printf("\n");
		struct memberProfile tmp;
		
		while(fread(&tmp, sizeof(struct memberProfile), 1, fptr)){
			time_t rawTime = tmp.registerTime;
			struct tm * timeInfo = localtime(&rawTime);
			char date[32];
			strftime(date, sizeof(date), "%d/%m/%Y", timeInfo);
			printf("ID: %s\n", tmp.memberId);
			printf("Name: %s\n", tmp.fullName);
			printf("Birth Year: %d\n", tmp.birthYear);
			printf("Type: %s\n", tmp.memberType);
			printf("Register Date: %s\n", date);
			printf("-----------------------\n");
		}
		printf("Load successfully\n");
    	fclose(fptr);

	}

}
void displaySaveMenu(){
	printf("\n=====SAVE MENU=====\n");
	printf("1. Binary\n");
	printf("2.Text\n");
}
void loadTextFile(){
	char inputName[32];
	char fName[40];
	printf("Enter your name file : ");
    inputString(inputName, sizeof(inputName));
	buildFileName(inputName, fName, sizeof(fName));
	FILE * fptr;
	fptr = fopen(fName, "r");
	if (!fptr){
		printf("Cannot open file\n");
		return;
	}
	else{
		printf("\n");
		char line[256];
		while(fgets(line, sizeof(line), fptr)){
			printf("%s", line);
		}
		printf("Sucessfully\n");
		fclose(fptr);
	}
}
void displayAllTrainer(struct trainerProfile *trainers, int numberOfTrainer){
    for(int i = 0; i < numberOfTrainer; i++){
        displayTrainer(i,trainers);
    }
}
void assignTrainer(int trainerIndex,int memberIndex, struct memberProfile **members, struct trainerProfile *trainers){
    strcpy((*members)[memberIndex].trainerId, 
    trainers[trainerIndex].trainerId);
    trainers[trainerIndex].memberCnt ++;
    printf("Assign succesfully\n");
}
void caculateTotalRevenue(struct trainerProfile *trainers, int numberOfTrainer){
    for(int i = 0; i < numberOfTrainer; i++){
        trainers[i].total += (trainers[i].monthlyFee) * (trainers[i].memberCnt);
    }
    printf("Calculate successfully\n");
}
void displayRevenue(struct trainerProfile *trainer, int numberOfTrainer){
    for(int i =0; i < numberOfTrainer; i++){
        printf("%s\t\t%s\t\t%d\t\t%d\t\t%lld\n",
            trainers[i].trainerId,
            trainers[i].trainerName,
            trainers[i].memberCnt,
            trainers[i].monthlyFee,
            trainers[i].total);
    }
}
void groupMemberByTrainerId(struct memberProfile *members, int total){
    for(int i = 0; i < total-1; i++){
        for(int j = 0; j < total - 1 - i; j ++){
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
