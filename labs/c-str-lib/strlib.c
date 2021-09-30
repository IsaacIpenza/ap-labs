#include <stdlib.h>

int mystrlen(char *str){

    char* string= str;
    int lenght = 0;
    
    while(*string != '\0'){
        lenght++;
        string++;
    }

    return lenght;
}

char *mystradd(char *origin, char *addition){

    char* originTmp = origin;
    char* additionTmp = addition;
    int originLenght = mystrlen(origin);
    int additionLenght = mystrlen(addition);

    char* tmp = (char *) malloc(originLenght + additionLenght + 1);
    char* result = tmp;

    while(*origin != '\0'){
        *tmp = *origin;

        tmp++;
        origin++;
    }

    while(*addition != '\0'){
        *tmp = *addition;

        tmp++;
        addition++;
    }

    return result;
}

int mystrfind(char *origin, char *substr){
    
    int result = 0;
    int lenght = mystrlen(substr);
    int originPos = 0;
    int substrPos = 0;

    while(origin[originPos] != '\0') {
        result = originPos;

        while(origin[originPos]==substr[substrPos]){
            originPos++;
            substrPos++;  
        }

        if(substrPos == lenght){
            return result;
        }else{
            originPos++; 
            substrPos = 0;  
        } 
    }
    return -1;
}
