#include "member.h"
#include "utils.h"
#include <string.h>
#include <ctype.h>
int canRemove(struct memberProfile *members, int index){
    int isRemove = 0;
    if( members[index].active == 0){
        isRemove = 1;
    }
return isRemove;
}
int isValidId(char id[]) {
    char preFix[] = "GYM";
    if(strlen(id) >= 12 || strlen(id) == 0){
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
int worldCouting(char *name){
    int isWorld = 0;
    int cnt = 0;
    //duyệt từng kí tự nếu vào dc từ thì cnt++ còn khi ở trong từ thì ko thực hiện gì hết
    //khi gặp space thì set lại isWorld = 0 và lặp lại 
    for(int i = 0; name[i] != '\0'; i ++){
        if( !(isspace(name[i])) && isWorld == 0 ){
            cnt++;
            isWorld = 1;
        }
        else{
            isWorld = 0;
        }
    }
    return cnt;
}
int isValidName(char *name) {
    int hasLetter = 0;
    int len = strlen(name);

    if(len == 0) return 0;
    if(name[0] == ' ' || name[len - 1] == ' ') {
        return 0;
    }
    for(int i = 0; i < len; i++){
        char c = name[i];
        // Không cho 2 space liên tiếp
        //đồng thời check ko cho đầu và kết thúc chuỗi là 1 space
        if(i < len -1 && name[i] == ' ' && name[i + 1] == ' '){
            return 0;
        }
        if(isalnum(c)) {
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




