#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "member.h"
#include "trainer.h"
#include "search_sort.h"
#include "UI.h"
#include "utils.h"
#include "file_io.h"

int main(){
    int choice;
    int total = 0;
    struct memberProfile * members = NULL;
    autoLoadFile(&members, &total, trainers, numberOfTrainer);
    autoUpdateActive(members,total);

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
                    char findId[16];
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
                printf("***PLEASE choose in 0-2 of options in menu, try again!\n");
            }
        
        }
        //trainer
        else if(choice == 2){
            int trainerChoice;
            displayTrainerMenu();
            trainerChoice = inputTrainerChoice();
            if(trainerChoice == 1){
                char idMember[16];
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
                else if(searchChoice == 2){
                    char findName[30];
                    printf("Enter ID you want to find: ");
                    fgets(findName, sizeof(findName), stdin);
                    findName[strcspn(findName, "\n")] = '\0';
                    int index = searchTrainerByName(findName, trainers, numberOfTrainer);
                    if(index != -1){
                        displayTrainer(index, trainers);
                    }
                    else{
                        printf("This name is not exist\n");
                    }
                }
                else if(searchChoice == 0) {}
		    }
            else if(trainerChoice == 0){}
            else{
                printf("***Try again, please enter in the (0-2)\n");
			}
    }  
        //Display all list
        else if(choice == 3){
            displayAllMember(total, members);
        }
        //FILE processing
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
	system("\nPause");
    return 0;
}


