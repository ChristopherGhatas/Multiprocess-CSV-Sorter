#ifndef SIMPLECSVSORTER_H
#define SIMPLECSVSORTER_H

typedef enum _sortType {INT,FLT,STR} sortType;

typedef enum _boolean {FALSE,TRUE} boolean;


typedef struct sortIndex { //sort index struct to hold sort index values
	int index;
	sortType type;
	int total_columns;
}sortIndex;

typedef struct entry { // entry struct to hold all entry values like index value and whole line.
	char* column;
	char* line;
	int integer;
	float flt;
	
}entry;

typedef struct cmdArg { //Command Line Argument Structs
	boolean active;
	char* parameter;
	
}cmdArg;

boolean sortAlg(char* sortPara, FILE *csv, char directory[], char fileName[]);

boolean sortKeyInitializer(sortIndex* globalSKey, char* argKey, char* headerLine);

char* removeSpace(char* string);

char* removeNewLine(char* string) ;

int commaCheck(char* line);

void mergeSort(entry arr[], int l, int r, sortIndex globalSKey);

void merge(entry arr[], int l, int m, int r, sortIndex globalSKey);
#endif