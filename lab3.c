#include <stdio.h>
#include <string.h>

void printTokens(char *inputString) {
    char *token;

    token = strtok(inputString, " ");

    while (token != NULL ) {
        printf( "%s\n", token );
        token = strtok(NULL, " ");
    }
}

int main () {
//    char string[27] = "Hi there! How is it going?";
//    printTokens(string);
    return 0;
}