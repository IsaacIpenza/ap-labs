#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

int numcmp(char *s1, char *s2) {
	int n1 = atoi(s1);
	int n2 = atoi(s2);
	if(n1 > n2) {
		return 1;
	} else {
		return -1;
	}
}

int main(int argc, char **argv)
{
	char* dataType;
	char* sortType;
	FILE* inputFile;
	char* inputFileName;
	FILE* outputFile;
	char* outputFileName;
	int fileLength = 0;
	char *line;
	char **lines;
	size_t len = 0;

	if(argc < 5 || argc > 6){
        printf("Invalid number of arguments\n");
        return 0;
    }

	if(argc == 5){
		dataType = "strings";
		inputFileName = argv[1];
		inputFile = fopen(inputFileName, "r");

		if(inputFile == NULL){
			printf("Invalid input file name\n");
        	return 0;
		}

		if(strcmp(argv[2], "-quicksort") == 0){
			sortType = "quicksort";
		}else if (strcmp(argv[2], "-mergesort") == 0){
			sortType = "mergesort";
		}else{
			printf("Invalid sort algorithm\n");
			return 0;
		} 

		if(strcmp(argv[3], "-o") != 0){
			printf("Invalid argument to provide the output file\n");
        	return 0;
		}

		outputFileName = argv[4];
	}

	if(argc == 6){
		dataType = "numbers";

		if(strcmp(argv[1], "-n") != 0){
			printf("Invalid argument for sorting numbers\n");
        	return 0;
		}

		inputFileName = argv[2];
		inputFile = fopen(inputFileName, "r");

		if(inputFile == NULL){
			printf("Invalid input file name\n");
        	return 0;
		}

		if(strcmp(argv[3], "-quicksort") == 0){
			sortType = "quicksort";
		}else if (strcmp(argv[3], "-mergesort") == 0){
			sortType = "mergesort";
		}else{
			printf("Invalid sort algorithm\n");
			return 0;
		} 

		if(strcmp(argv[4], "-o") != 0){
			printf("Invalid argument to provide the output file\n");
        	return 0;
		}

		outputFileName = argv[5];
	}

	while(getline(&line, &len, inputFile) != -1){
		fileLength++;
	}

	fseek(inputFile, 0, SEEK_SET);

	lines = (char **)malloc(fileLength * sizeof(char*));

	int i = 0;
	while(getline(&lines[i], &len, inputFile) != -1) {
		i++;
	}

	if(strcmp(sortType, "quicksort") == 0){
		printf("... sorting %s file with quicksort \n", inputFileName);

		if(strcmp(dataType, "strings") == 0){
			quicksort((void **) lines, 0, fileLength-1, (int (*)(void *, void *))strcmp);
		}

		if(strcmp(dataType, "numbers") == 0){
			quicksort((void **) lines, 0, fileLength-1, (int (*)(void *, void *))numcmp);
		}
	}
	
	if(strcmp(sortType, "mergesort") == 0){
		printf("... sorting %s file with mergesort \n", inputFileName);

		if(strcmp(dataType, "strings") == 0){
			mergesort((void **) lines, 0, fileLength-1, (int (*)(void *, void *))strcmp) ;
		}

		if(strcmp(dataType, "numbers") == 0){
			mergesort((void **) lines, 0, fileLength-1, (int (*)(void *, void *))numcmp);
		}
	}

	outputFile = fopen(outputFileName, "wb");

	for(int j = 0; j < fileLength; j++){
		fputs(lines[j], outputFile);
	}

	fclose(inputFile);
	fclose(outputFile);

	printf("... Results file can be found at %s\n", outputFileName);
	return 1;
}