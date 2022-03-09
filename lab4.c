#include <stdio.h>


void findMinDistance(char *inputString){

    char repeat_char;
    int i = 0;
    int j;
    int length = 0; //counts the distance
    char *ptr1 = inputString;
    char *ptr2 = inputString;
    int match = 0;

    if (inputString == NULL) {
        printf("\nNo repeats found!");
        return;
    }

    while (ptr1[length] != '\0') { // find the len of the array
        length++;
    }

    int min_distance = length;
    while (ptr1[i] != '\0') {  // loops until ptr is at the end (increment by i)
        for (j = i + 1; j < length; j++) {  // j loop to compare with i
            if (ptr1[i] == ptr2[j]) {  // match the letter
                match = 1;
//                printf("\n%c", ptr2[i]);
                int counter = j - i;  // find min_distance
//                printf("%d",counter);
                if (counter < min_distance) {
                    min_distance = counter - 1;
                    repeat_char = ptr1[i];
                }
            }
        }
        i++;
    }

    if (match == 0) {
        printf("\nNo repeats found!");
    }
    else {
        printf("\nRepeated char = %c min distance = %d", repeat_char, min_distance);
    }


}

int main( int argc, char *argv[]) {
    findMinDistance(argv[1]);

    return 0;
}