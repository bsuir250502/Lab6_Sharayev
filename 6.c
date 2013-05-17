#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

char readArgument(int, char **);
int *fillArr(int);
int displayArr(int *, int);
int assumeElem(int *, int);
int displayBin(char *);

int main(int argc, char **argv)
{
    FILE *fp;
    char *filename, arg;
    arg = readArgument(argc, argv);
    int numOfElements, *arr, sum;
    if(arg == '0') {
        printf("You need to specify file name with key -n,  set key (-h) to display manual or -f to fill binary file with following name\n");
        return 0;
    }
    else if (arg == 'h') {
        printManual();
    }
    else {
        filename = (char *) malloc( (strlen(argv[2])) * sizeof(char));
	strcpy(filename, argv[2]);
	if(arg == 'f') {
	    printf("Enter number of elements of matrix\n");
	    numOfElements = input_number_in_range(0, 50);
	    fp = fopen(filename, "w+b");
	    fwrite(&numOfElements, sizeof(int), 1, fp);
	    fclose(fp);
	    return 0;
	}
    }
    //printf("%s\n", filename);
    fp = fopen(filename, "r+b");
    fread(&numOfElements, sizeof(int), 1, fp);
    fclose(fp);
    
    arr = fillArr(numOfElements); 
    displayArr(arr, numOfElements);
    sum = assumeElem(arr, numOfElements);
    
    fp = fopen(filename, "a+b");
    fseek(fp, 0, 2);
    fwrite(&sum, sizeof(int), 1, fp);
    fclose(fp);
    
    printf("numOfElements = %d, sum = %d\n", numOfElements, sum);
    
    free(arr);
    free(filename);
    fclose(fp);
    return 0;
}

int *fillArr(int numOfElements) 
{
    int *arr, i;
    
    arr = (int *)malloc(numOfElements * sizeof(int));
    printf("Specify elements of the array\n");
    for(i = 0; i < numOfElements; i++) {
        arr[i] = i;//input_number_in_range(0, 1024);
    }
    
    return arr;
}

int displayArr(int *arr, int numOfElem)
{
    int i;
    for(i = 0; i < numOfElem; i++) {
        printf("%d  ",arr[i]);
    }
    
    return 0;
}

int assumeElem(int *arr, int numOfElem)
{
    int i, sum = 0;
    for(i = 0; i < numOfElem; i++) {
        sum += arr[i];
    }
    
    return sum;
}

int displayBin(char *filename)
{
  FILE *fp;
    fp = fopen(filename, "r+b");
    fread(&, sizeof(int), 1, fp);
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
        if(!(strcmp(argv[1], "-n"))) {
            return 'n';
        }
        if(!(strcmp(argv[1], "-f"))) {
            return 'f';
        }
    }
    
    return '0';
}
