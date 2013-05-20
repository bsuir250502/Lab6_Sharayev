#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mylib.h"

char readArgument(int, char **);
int **fillArr(char *, int *);
int displayArr(int **, int);
int assumeElem(int **, int);
int displayBin(char *);
int createFile(char *);
int getArrSize(char *);
int freeMemory(int **, int);

int main(int argc, char **argv)
{
    FILE *fp;
    char *filename, arg;
    arg = readArgument(argc, argv);
    int arrSize, **arr, sum;
    if(arg == '0') {
        printf("Specify key -r or -c with file name to read or create binary file, or set -h to display manual\n");
        return 0;
    }
    else if (arg == 'h') {
            printManual();
        }
        else {
            filename = (char *) malloc( (strlen(argv[2])) * sizeof(char));
	        strcpy(filename, argv[2]);
	   if(arg == 'c') {
	       createFile(filename);
	       return 0;
	   }
    }
    //printf("%s\n", filename);
    
    
    arr = fillArr(filename, &arrSize); 
    displayArr(arr, arrSize);
    sum = assumeElem(arr, arrSize);
    
    fp = fopen(filename, "a+b");
    fseek(fp, 0, 2);
    fwrite(&sum, sizeof(int), 1, fp);
    fclose(fp);
    
    printf("numOfElements = %d, sum = %d\n", arrSize, sum);
    
    freeMemory(arr, arrSize);
    free(filename);
    fclose(fp);
    return 0;
}

int createFile(char *filename)
{
    int numOfElements;
    FILE *fp;
    
    if(!(fp = fopen(filename, "w+b")) ) {
        printf("There is no file with such name\n");
        return 0;
    }
    printf("Enter number of elements of matrix\n");
    numOfElements = input_number_in_range(0, 50);
    fwrite(&numOfElements, sizeof(int), 1, fp);

    fclose(fp);
    return 0;
}

int **fillArr(char *filename, int *arrSize) 
{
    int **arr, i, j;
    
    *arrSize = getArrSize(filename);
    printf("%d\n", *arrSize);
    arr = (int **)malloc(*arrSize * sizeof(int *));
    for(i = 0; i < *arrSize; i++) {
        arr[i] = (int *)malloc(*arrSize * sizeof(int));  
    }
    printf("Specify elements of the array\n");
    for(i = 0; i < *arrSize; i++) {
        for(j = 0; j < *arrSize; j++) {
            arr[i][j] = input_number_in_range(0, 1024);
        } 
    }
    
    return arr;
}

int displayArr(int **arr, int arrSize)
{
    int i, j;

    for(i = 0; i < arrSize; i++) {
        for(j = 0; j < arrSize; j++) {
            printf("%d  ",arr[i][j]);
        } 
        puts("");
    }
    
    return 0;
}

int assumeElem(int **arr, int numOfElem)
{
    int i, j, sum = 0;

    for(i = 1; i < numOfElem; i++) {
        for(j = 0; j < i; j++)
            sum += arr[i][j];
    }
    
    return sum;
}

int displayBin(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r+b");
    //fread(&, sizeof(int), 1, fp);
    fclose(fp);
    
    return 0;
}


char readArgument(int argc, char **argv)
{
    if (argc == 2) {
        if (!(strcmp(argv[1], "-h"))) {
            return 'h';
        }        
    }
    else if(argc == 3) {
        if(!(strcmp(argv[1], "-r"))) {
            return 'r';
        }
        if(!(strcmp(argv[1], "-c"))) {
            return 'c';
        }
    }
    
    return '0';
}

int getArrSize(char *filename)
{
    int numOfElements;
    FILE *fp;

    if(!(fp = fopen(filename, "r+b")) ) {
        printf("File is not opened\n");
        exit(1);
    }
    fread(&numOfElements, sizeof(int), 1, fp);
    if(!numOfElements) {
        printf("File %s is empty\n", filename);
        exit(1);
    }
    fclose(fp);

    return pow(numOfElements, 1/2);
}

int freeMemory(int **arr, int arrSize)
{
    int i, j;
    for(i = 0; i < arrSize; i++) {
        for(j = 0; j < arrSize; j++) {
            free(arr[i]);
        }
    }

    free(arr);
    return 0;
}