#include <stdio.h>
#include <stdlib.h>

#define MAX_COLUMNS 10

// preq: need 1 blank space at the end of the file

int Powerof(int base, int exp) {
    if(exp < 0)
        return -1;

    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

void toBinary(char *inputString){

    FILE *fptr;
    fptr = fopen(inputString, "r");
    char line[256];
    if (fptr == NULL) {  // if file does not exist
        printf("Error! File not found.\n");
        exit(0);
    }

    int row;
    int column;

    if (fscanf( fptr, "%d %d", &row, &column) != 2) {
        printf("Error! Rows and Columns are not correct");
        exit(0);
    }

    if (column == 0 || row == 0) {
        printf("Error! Row and Column cannot be 0!");
        exit(0);
    }

//    printf("%d %d\n", row, column);

    if (column > MAX_COLUMNS) {
        printf("Error! Column greater than 10.");
        exit(0);
    }
    int size = column;
    char digit;
    int Currentcolumn = column;
    int total = 0;
    int counter = 0;
    int newLineCounter = 0;

    int columncounter = 0;

//     Extract characters from file and store in character c
//    for (c = getc(fptr); c != EOF; c = getc(fptr))
//        if (c == '\n') // Increment count if this character is newline
//            newLineCounter = newLineCounter + 1;
//
//    if (newLineCounter > row || newLineCounter < row) {
//        printf("Error! Rows does not match specified.");
//        exit(0);
//    }

    fgets(line, sizeof(line), fptr);

    while (!feof( fptr) ) {
        fscanf(fptr, "%c", &digit);
        if (digit != '1' && digit != '0' && digit != ' ' && digit != '\n') {  // if special characters in file
            printf("Error! Invalid character found.");
            exit(0);
        }
        if (digit == ' ') { // don't account for additional spaces
            continue;
        }
        if (digit != ' ') {
            if (digit == '1' || digit == '0') {
                Currentcolumn --;
                counter++;
                columncounter++;
                if (digit == '1') {
                    total += Powerof(2, Currentcolumn);
                    if (digit == '0') {
                        continue;
                    }
                }
            }

            if (digit == '\n') {
                newLineCounter++;
                if (counter == size){
                    printf("%d\n", total);
                }
//                printf("   tello   %d\n", counter);
                Currentcolumn = column;
                total = 0;
                counter = 0;

            }


        }


    }
    if (columncounter/column != row ) {  // wrong number of columns
        printf("Error! Wrong number of columns.");
        exit(0);
    }

    if (newLineCounter - 1 > row || newLineCounter - 1 < row) { // newLineCounter is for rows
        printf("Error! Rows does not match specified.");
        exit(0);
    }

    fclose(fptr);

}

int main( int argc, char *argv[]) {
    toBinary(argv[1]);
    return 0;
}