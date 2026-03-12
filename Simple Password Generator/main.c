#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define PASSWORD_LENGTH 20
char possible_chars[] = "QWERTYUIOPASDFGHJKLÇZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890";
int main(){
    srand(time(NULL));
    char password[PASSWORD_LENGTH+1];
    for (int i= 0; i<PASSWORD_LENGTH;i++){
        int random = rand()%(sizeof(possible_chars))-1;
        password[i] = possible_chars[random];
    }
    password[PASSWORD_LENGTH] = 0;
    printf("Your password is: %s\n", password);
}