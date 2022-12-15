#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LINE 4096

void readFile(char *fileName, char *searchTerm);
void readInput(char *searchTerm);
int readTermsFromIntput(char *line,char *searchTerm);

/* Funtion to handle user inputs */
int main (int argc,char *argv[]) {

    /* If no command-line arguments */
    if (argc == 1) {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }

    /* If one argument given check if it is a file or search term */
    else if (argc == 2) {
        /* It is a file */
        if ((fopen(argv[1],"r"))!=NULL) {
            printf("While no search term, there wont be any matches.\n");
            return 0;
        }
        /* It is a search term */
        else {
            readInput(argv[1]);
            return 0;
        }
    }
    
    else {
    /* Read all files, starting from the last input */
    while (argc > 2){
        readFile(argv[--argc],argv[1]);
        }
    }

}
 /* Function to read the user input */
void readInput(char *searchTerm) {
    char buf[MAX_LINE];

    printf("You have given a search term: %s.\n", searchTerm);
    printf("This program will print each line you give as an input that has the search term in them.\nWhen you are done press CTRL+D.\n");
    printf("Please input new line:\n");

    /* Read lines user gives as input and print all that have the search term in them */
    while ((fgets(buf,sizeof(buf),stdin))!=NULL) {
        if ((readTermsFromIntput(buf,searchTerm)) == 1) {
            printf("A search term found in the line: %s",buf);
        }
    }
    return;
}
/* Function to read file content */
void readFile(char *fileName, char *searchTerm) {
    FILE *file;
    size_t n = 0;
    char *buf;

    /* Print filename and open the file */
    printf("File: %s\n",fileName);
    if ((file = fopen(fileName,"r"))==NULL) {
        printf("my-grep: cannot open file\n");
        exit(1);
    }

    /* Read the file */
    while ((getline(&buf,&n,file))!= EOF) {
        /* If the search term found from the line print it */
        if (readTermsFromIntput(buf,searchTerm) == 1) {
            printf("%s",buf);
        }
    }
    printf("\n");

    /* Close the file */
    fclose(file);
    /* Free the memory allocated to buffer by getline function */
    free(buf);
    return;
}
/* Function to read terms from user input */
int readTermsFromIntput(char *line,char *searchTerm) {
    int termStart=0, termEnd=strlen(searchTerm), i, newTermIdx;
    char tempTerm[termEnd+2];

    /* Traversing through the input line */
    while(line[termEnd] != '\0') {
        /* Form temporary term of from the line */
        newTermIdx = 0;
        for (i=termStart;i<termEnd;i++) {
            tempTerm[newTermIdx++] = line[i];
        }
        tempTerm[newTermIdx++] = '\0';
        /* If searched term found in the line, then return 1 */
        if (strcmp(tempTerm,searchTerm)==0) {
            return 1;
        }
        /* Move to the next part on the line */
        termStart++;
        termEnd++;
    }
    /* No searched term in the line return 0 */
    return 0;
}
