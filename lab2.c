#include <stdio.h>
#include <stdbool.h>

void printMultiplicationTable() {
    int i;
    int j;
    int limit = 11;

    for ( i = 1; i < limit; i++) {
        for (j = 1; j < limit; j++) {
            printf("%d\t", i * j);
        }
            printf("\n");
    }
}

int isPalindrome(int elements[], int size) {

    int marker = 1;

    for (int i = 0; i <= size / 2 && size != 0; i++) {
        if (elements[i] != elements[size - i - 1]) {
            marker = 0;
            break;
        }
    }

    if (marker == 0) {
        return 0;
    }
    else {
        return 1;
        }
}


int main() {

//    printMultiplicationTable();
//    int element[] = {};
//    int element[] = {1, 2, 1};
//    int size = sizeof(element) / sizeof(element[0]);
//    isPalindrome(element, size);

    return 0;
}