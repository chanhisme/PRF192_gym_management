#include "file_io.h"
#include <stdio.h>
#include "member.h"
#include "trainer.h"
#include "UI.h"
#include <string.h>
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
int inputLoadFile(){
	int loadChoice;
	printf("Enter your choice: ");
	scanf("%d", &loadChoice);
	clearBuffer();
	return loadChoice;
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
void autoLoadFile(struct memberProfile **members, int *total,
    struct trainerProfile *trainers, int numberOfTrainer){
    FILE * fptr = fopen("Gym_Membership_&_Trainer_Management.txt", "r");
    if (!fptr){
		printf("File is not created\n");
		return;
	}
	else{
		printf("\n");
		char line[256];
        //set bằng 0 hết trc khi cộng
        for(int i = 0; i < numberOfTrainer; i++){
            trainers[i].memberCnt = 0;
        }
        struct memberProfile temp = {0};
		while(fgets(line, sizeof(line), fptr)){
            line[strcspn(line, "\n")] = '\0';
            if(strncmp(line, "ID: ", 4) == 0){
                strcpy(temp.memberId, line + 4);
            }
            else if(strncmp(line, "Trainer: ",9) == 0){
                strcpy(temp.trainerId,line+9);
            }
            else if(strncmp(line, "Name: ", 6) == 0){
                strcpy(temp.fullName, line + 6);
            }
            else if(strncmp(line, "Birth Year: ", 12) == 0){
                //atoi đọc năm dạng chuỗi và đổi về giá int
                temp.birthYear = atoi(line + 12);
            }
            else if(strncmp(line, "Active: ", 8)==0){
                temp.active = atoi(line + 8);
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
                //kiểm tra có tồn tại thì sẽ cộng
                // \0 là kí tự kết thúc chuỗi
                if(temp.trainerId[0] != '\0'){
                    int pos = searchTrainerById(temp.trainerId, numberOfTrainer, trainers);
                    if(pos != -1){
                        trainers[pos].memberCnt++;
                    }
                }
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
                memset(&temp, 0, sizeof(temp));
            }
        }
    fclose(fptr);
    }
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
                "Active: %d\n"
                "-----------------------\n",
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
        printf("Export successfully\n");
        fclose(fptr);
    }
}
void buildBinaryFileName(char inputName[], char finalName[], int size){
	snprintf(finalName, size, "%s.bin", inputName);
}
void buildFileName(char inputName[], char finalName[], int size){
	snprintf(finalName, size, "%s.txt", inputName);
}





































