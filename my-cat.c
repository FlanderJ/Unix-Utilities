#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE 255

void readFile(char *fileName);

/* Function to process user input */
int main (int argc, char *argv[]) {

    /* If no files given, exit */
    if (argc == 1) {
        return 0;
    }

    /* Read all files, starting from the last input */
    while (argc > 1){
        readFile(argv[--argc]);
    }
}

/* Funtion to read the content of the file */
void readFile(char *fileName) {
    FILE *file;
    char buf[MAX_LINE];

    /* Print filename and open the file */
    printf("File: %s\n",fileName);
    if ((file = fopen(fileName,"r"))==NULL) {
        printf("my-cat: cannot open file\n");
        exit(1);
    }

    /* Read the file */
    while ((fgets(buf,MAX_LINE,file))!= NULL) {
        printf("%s",buf);
    }
    printf("\n");
    /* Close the file */
    fclose(file);
    return;
}
