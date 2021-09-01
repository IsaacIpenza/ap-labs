#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values) {

    long result = 0;

    if(operator == 3){ //Multiplication start value is 1
         result = 1;
    }

    for(int i = 0; i < nValues; i++){    
        if(operator == 1){      //addition
            result += values[i];
            (i < nValues - 1) ? printf("%i + ", values[i]) : printf("%d ", values[i]);
        }
        else if(operator == 2){ //substraction
            if( i == 0 ){
                result = values[i];
            }else{
                result -= values[i];
            }
            (i < nValues - 1) ? printf("%d - ", values[i]) : printf("%d ", values[i]);
        }
        else {                  //multiplication
            result *= values[i];
            (i < nValues - 1) ? printf("%d * ", values[i]) : printf("%d ", values[i]);
        }
    }

    printf(" = %li\n", result);
    return result;
}

int main(int argc, char *argv[]) {

    if(argc < 4){
        printf("Invalid number of arguments\n");
        return -1;
    }

    int operator;

    if(strcmp(argv[1], "add") == 0){
        operator = 1;
    }
    else if(strcmp(argv[1], "sub") == 0){
        operator = 2;
    }
    else if(strcmp(argv[1], "mult") == 0){
        operator = 3;
    }
    else{
        printf("Invalid operator\n");
        return -1;
    }

    int size = argc - 2;
    int numbers[size];

    for(int i = 2, j = 0; i < argc; i++, j++){
       if(!isdigit(*argv[i])){
           printf("Invalid argument as number -> %s \n", argv[i]);    
           return -1;        
        }
        else{
            numbers[j] = atoi(argv[i]);

        }
    }


    return calc(operator, size, numbers);
}
