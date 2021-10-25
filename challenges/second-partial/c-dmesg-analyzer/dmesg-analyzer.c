#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define REPORT_FILE "report.txt"
#define HASHSIZE 10000
#define LOGS 5000

#define LOGSIZE 1000
#define DATASIZE 1000

void analizeLog(char *logFile, char *report);

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage:./dmesg-analizer logfile.txt\n");
        return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

struct nlist {
    struct nlist *next;
    char *name;
    char defn[LOGS][LOGSIZE];
    int li;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
	unsigned hashval;
	
	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;
    for(np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if(strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;
    
	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL) {
			return NULL;
		}
        hashval = hash(name);
        np->next = hashtab[hashval];
        np->li = 0;
        strcpy(np->defn[np->li], defn);
        hashtab[hashval] = np;
    } else {
        np->li++;
        strcpy(np->defn[np->li], defn);
    }
    return np;
}

void generateReport(char *report){
    FILE* outFp;
    outFp = fopen(report, "w+");
    
    if(outFp == NULL) {
        printf("Error opening/creating file ->  %s\n", report);
		return;
	}

    struct nlist *lines;

    for (int i = 0; i <= HASHSIZE; i++) {
        lines = hashtab[i];

        if (lines != NULL) {
            fputs("", outFp);
            fputs(lines->name, outFp);
            fputs("\n", outFp);

            for(int j = 0; j < LOGS; j++) {

                if(strcmp(lines->defn[j], "") != 0) {
                    fputs("  ", outFp);
                    fputs(lines->defn[j], outFp);
                    fputs("\n", outFp);
                } else {
                    break;
                }
            }
        }
    }

    fclose(outFp);
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.
    FILE* fp;
	char *logLine = NULL;
	size_t len = 0;

    fp = fopen(logFile, "r");
    if (fp == NULL) {
        printf("Error opening file ->  %s\n", logFile);
		return;
	}

	while (getline(&logLine, &len, fp) > 0) {
        char *currentChar;
        char arrLog[LOGSIZE] = "";
        char arrLogType[DATASIZE] = "";
        int addLog = 1, addType = 0, typeFound = 0;

		for (currentChar = logLine; *currentChar != '\n'; currentChar++) {

            if(addLog == 0 && addType == 0 && typeFound == 1){
                
                if (*currentChar != ' '){
                    typeFound = 0;
                    addType = 1;
                } else {
                    addLog = 1;
                }
            }

            if (addLog == 1 && *currentChar == ']' && typeFound == 0) {
				strncat(arrLog, &(*currentChar), 1);
				
				addType = 1;
				addLog = 0;

			} else if(addType == 1 && *currentChar == ':') {
				strncat(arrLogType, &(*currentChar), 1);
				
				typeFound = 1;
				addType = 0;
				addLog = 0;

			} else if (addLog == 1) {
				strncat(arrLog, &(*currentChar), 1);
            } else if (addType == 1) {
				strncat(arrLogType, &(*currentChar), 1);
			}
        }
        if (typeFound == 0) {
            strcat(arrLog, " ");
            strcat(arrLog, arrLogType);
            strcpy(arrLogType, "General:");
        }

        if (strcmp(arrLog, " ") != 0) {
            install(arrLogType, arrLog);
        }
	}

    fclose(fp);

    generateReport(report);

    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[HASHSIZE];

    inputFd = open(report, O_RDONLY);
    if(inputFd == -1){
        printf("Error opening file ->  %s\n", report);
        return;
    }

    openFlags = O_WRONLY | O_CREAT | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                 S_IROTH | S_IWOTH;  

    outputFd = open("report_dmesg.txt", openFlags, filePerms);
    if (outputFd == -1){
        printf("Error opening/creating file ->  %s\n", report);
		return;
    }

    while ((numRead = read(inputFd, buf, 1)) > 0) {
        if (write(outputFd, buf, numRead) != numRead) {
            printf("Error writing");
            return;
        }
    }

    if (numRead == -1) {
        printf("Error reading");
        return;
    }

    if(close(inputFd) == -1) {
        printf("Error closing input");
    }

    if(close(outputFd) == -1) {
        printf("Error closing output");
    }

    printf("Report is generated at: [%s]\n", report);
}