/* xor.c */

#define KEY 'X';
#define CLEARTEXT 'A';

#include <stdio.h>

void printchr(char c, char *text){
    printf("%s = '%c' (0x%x)\n",text, c, c);
    return;
}

int main(){

char cleartext,key, ciphertext, newcleartext;
cleartext = CLEARTEXT;
printchr(cleartext, "cleartext");
key = KEY;

printchr(key,"key");
ciphertext = cleartext ^key; //XOR

printchr(ciphertext, "ciphertext");

newcleartext = ciphertext ^ key;
printchr(newcleartext, "newcleartext");

return 0;


}
