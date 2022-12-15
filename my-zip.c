#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX_LINE 4096

void readFile(char *fileName);
void compress(char *lineToCompress, char *compressedLine);
void printCompressed(char *compressedLine);

/* Main funtion to handle input arguments */
int main (int argc,char *argv[]) {

    /* If no input arguments */
    if (argc == 1) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    /* Read files */
    while (argc > 1){
        readFile(argv[--argc]);
    }

}

/* Funtion to read files and send data to be processed */
void readFile(char *fileName) {
    FILE *file;
    size_t n = 0;
    char *buf=NULL,compressedLine[MAX_LINE];

    /* Print filename and open the file */
    printf("File: %s\n",fileName);
    if ((file = fopen(fileName,"r"))==NULL) {
        printf("my-zip: cannot open file\n");
        exit(1);
    }

    /* Read lines */
    while ((getline(&buf,&n,file))!= EOF) {
        compress(buf,compressedLine);
        printCompressed(compressedLine);
    }
    printf("\n");
    /* Close the file */
    fclose(file);
    /* Free the memory allocated to buffer by getline function */
    free(buf);
    return;
}

/* Function to compress lines given to it as input */
void compress(char *lineToCompress, char *compressedLine) {
    int count=1,i, compressedIdx=0;
    char curChar = lineToCompress[0],intBuf[4];
    /* Traverse through all characters of the line */
    for (i=1;i<strlen(lineToCompress);i++) {
        /* If current char equals the next one, then increase count */
        if (lineToCompress[i] == curChar) {
            count++;
            continue;
        }
        /* Else add new values to compressed line */
        else {
            /* In a case if there are more than one piece of the same char in a row */
            if (count != 1) {
                if (count > 9) { /* If the count of of chars is more then 9, use different adding method */
                    sprintf(intBuf,"%d",count);
                    strcat(compressedLine,intBuf);
                    compressedIdx = compressedIdx + strlen(intBuf);
                }
                else {
                    compressedLine[compressedIdx++] = count+'0'; /* add the count of the following char */
                }
                compressedLine[compressedIdx++] = curChar;
                curChar = lineToCompress[i]; /* Set current char to next char in line */
                count = 1; /* Count of the chars set to 0 again */
                continue;
            }
            compressedLine[compressedIdx++] = curChar;
            curChar = lineToCompress[i]; /* Set current char to next char in line */
        }
    }
    /* Check if there was more than one piece of the last char in the line*/
    if (count !=1) {
        if (count > 9) { /* If the count of of chars is more then 9, use different adding method */
            sprintf(intBuf,"%d",count);
            strcat(compressedLine,intBuf);
            compressedIdx = compressedIdx + strlen(intBuf);
        }
        else {
            compressedLine[compressedIdx++] = count+'0'; /* add the count of the following char */
        }
        compressedLine[compressedIdx++] = curChar;
        compressedLine[compressedIdx++] = '\0'; /* Null to the end of the line */
    }
    else {
        compressedLine[compressedIdx++] = curChar;
        compressedLine[compressedIdx++] = '\0'; /* Null to the end of the line */
    }
    return;
}

/* Function to print compressed lines using fwrite */
void printCompressed(char *compressedLine) {
    int i, ASCIInum;
    for (i=0;i<strlen(compressedLine);i++) {
        /* An integer */
        if (isdigit(compressedLine[i])) {
            ASCIInum = compressedLine[i];
            fwrite(&ASCIInum,sizeof(char),1,stdout);
        }
        /* A char */
        else {
            ASCIInum = (int)compressedLine[i];
            fwrite(&ASCIInum,sizeof(char),1,stdout);
        }
    }
    return;
}