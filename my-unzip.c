#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define BUF_SIZE 256

void readFile(char *fileName);
void uncompress(char *compressedLine, int charAmount);

/* Main function that checks the input arguments */
int main (int argc,char *argv[]) {

    /* If no input arguments */
    if (argc == 1) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }
    
    /* Read the files */
    while (argc > 1){
        readFile(argv[--argc]);
    }
}

/* Function to read the content in the file and pass it to anohter function process it */
void readFile(char *fileName) {
    FILE *file;
    char buf[BUF_SIZE];
    int charAmount;
    /* Open the file */
    if ((file = fopen(fileName,"r"))==NULL) {
        printf("my-unzip: cannot open file\n");
        exit(1);
    }
    /* Read content of the file 10 bytes at a time */
    while ((charAmount = fread(&buf, sizeof(char),BUF_SIZE,file))==BUF_SIZE) {
        /* Perform uncompress */
        uncompress(buf,charAmount);
    }
    /* Uncompress bytes that didnt fit into the last full buffer */
    uncompress(buf,charAmount); 

    /* Close the file */
    fclose(file);
    return;
}

/* Funtion to perform uncompressing */
void uncompress(char *compressedLine, int charAmount) {
    int i,j, numCount=0, amount;
    char curChar, nextChar, wholeNum[10];
    /* Traverse through the dada */
    for (i=0;i<=charAmount-1;i++) {
        curChar = compressedLine[i];
        nextChar = compressedLine[i+1];
        /* Print uncompressed data */
        if ((isdigit(curChar)) && (!isdigit(nextChar))) {
            wholeNum[numCount] = curChar;
            amount = atoi(wholeNum); /* Set the number in string to int variable */
            /* Print amount of chars equal to the amount of preceding number */
            while (amount != 0) {
                printf("%c", compressedLine[i+1]);
                amount--;
            }
            numCount=0;
            /* Fill the buffer with non-number values */
            for (j=0;j<strlen(wholeNum);j++){
                wholeNum[j]='n';
            }
            i++;
            continue;
        }
        /* If there are more then one int, concatenate them into string */
        else if ((isdigit(curChar)) && (isdigit(nextChar))) {
            wholeNum[numCount++] = curChar;
        }
        /* Print single characters */
        else {
            printf("%c",compressedLine[i]);
        }
    }
    return;
}