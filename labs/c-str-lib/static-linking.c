#include <stdio.h>
#include <string.h>

int mystrlen(char *str);
char *mystradd(char *origin, char *addition);
int mystrfind(char *origin, char *substr);

int main(int argc, char* argv[]) {
    if(argc<4){
        printf("Invalid number of arguments\n");
        return 0;
    }

    if(strcmp(argv[1], "-add") == 0){
        printf("Initial Length: %d\n",mystrlen(argv[2]));

        char* result = mystradd(argv[2], argv[3]);

        printf("New String: %s\n",result);
        printf("New Length: %d\n",mystrlen(result));

    }else if(strcmp(argv[1], "-find") == 0){
        int position = mystrfind(argv[2], argv[3]);

        if(position >= 0){
            printf("['%s'] string was found at [%d] position\n", argv[3], position);
        }else{
            printf("['%s'] string was not found... Error 404 XD\n", argv[3]);
        }

    }else{
        printf("Invalid operation \n");
        printf(" -> Operation: -add <String 1> <String 2>");
        printf(" -> Operation: -find <String 1> <String 2>");
        
    }

    return 0;
}
