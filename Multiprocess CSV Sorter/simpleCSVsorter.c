#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <malloc.h>

#include "scannerCSVsorter.h"


boolean sortAlg(char* sortPara, FILE *csv, char directory[], char fileName[]){
	char line[10000];
	size_t n = 0;
	ssize_t read;
	sortIndex globalSKey;
	boolean condition = FALSE;
	boolean first = TRUE;
	boolean quote = FALSE;
	char *tempStr;
	char* token;
	char *headerline;
	char *commaLine;
	int i,commas,line_counter, array_size, a, total_commas, curr_commas;;
	float f;
	array_size = 1;
	entry *entryArray = malloc(sizeof(entry));
	//entry entryArray[100];
	entry *temp;
	//entry clean[100];
	
	while ( fgets(line, 10000, csv) != NULL) { //starting the file reading
	
	   if( line_counter == array_size){
		
		entryArray = realloc(entryArray, (line_counter*2) * sizeof(entry));
		array_size = array_size*2;
		
	}    

	commas = 0;

	if(first == TRUE){ // handles headerline and the sort key intiialization.
	headerline = strdup(line);
	condition = sortKeyInitializer(&globalSKey, sortPara, line);
	if(condition == FALSE){
		fprintf(stderr, "ERROR: Failed to find sorting key in header %s\n", fileName);

		exit(1);

	}
	for ( i = 0; line[i] != '\0'; i++ ) {
		total_commas += (line[i] == ',');
		} total_commas++;
		
	first = FALSE;
	}
	else{
	entryArray[line_counter].line = strdup(line);
	tempStr = strdup(line);
	
	commaLine = strdup(line);

/* 	curr_commas = commaCheck(commaLine);
	printf("Total Commas = %d, Curr Commas = %d", total_commas, curr_commas);
	if(curr_commas != total_commas){
		fprintf(stderr, "ERROR: Wrong number of commas in lines\n");
		exit(1);
	}
	
		 */
		
	
	while(*tempStr!='\0'){
	quote == FALSE;
	
	if(commas == globalSKey.index){ // takes the value of the column being sorted for that entry and puts it into a struct.
		entryArray[line_counter].column	= malloc(sizeof(char) * strlen(line)); 
		int j = 0;
	while(*tempStr !='\0' && *tempStr !=',' && *tempStr !='\"' && *tempStr !='\r' && *tempStr!='\n'){ //goes forward until it hits a stopping point of a comma or various delimiters.
		entryArray[line_counter].column[j] = *tempStr;
		j++;
		tempStr++;		
	}
	
	if(*tempStr == '\"'){ // handles quotations that are also at the column being sorted. hits this if the quote comes after the last comma needed to the comma limit.
		tempStr++;
		while(*tempStr !='\0' && *tempStr !='\"' && *tempStr !='\r' && *tempStr!='\n'){
		entryArray[line_counter].column[j] = *tempStr;
		j++;
		tempStr++;		
		}
	}
		entryArray[line_counter].column[j] = '\0';
		entryArray[line_counter].column = removeSpace(entryArray[line_counter].column);
		
		if(globalSKey.type == INT){
		entryArray[line_counter].integer = atoi(entryArray[line_counter].column);
		}
		
		if(globalSKey.type == FLT){
		entryArray[line_counter].flt = atof(entryArray[line_counter].column);
		}
		
		break;
		}
	else if(*tempStr == '\"'){
		quote == TRUE;
		while(*tempStr!='\0'){
			tempStr++;
			if(*tempStr == '\"'){ break;}
			else{
			tempStr++;
			}
		}
		}
	else if(*tempStr == ','){
		commas++;
	}
	if(quote == FALSE){
	//printf("HERE AGAIN R: %c\n", *tempStr);
	tempStr++;
	}
	}
	line_counter++;
	}
	
	}
	
	//printf("\n\nFileNAME = %s\n\n", fileName);
	/* for(i=0;i<line_counter;i++){
	printf("%s", entryArray[i].line);
	} */
	mergeSort(entryArray, 0,  line_counter - 1, globalSKey);
	size_t len1 = strlen(directory), len2 = strlen(fileName), len3 = strlen(sortPara);
	char *concat = (char*) malloc(len1 + len2 + len3 + 16);
	snprintf (concat, len1 + len2 + len3 + 16, "%s/%s-sorted-%s.csv", directory, fileName,sortPara);
	//printf("out_dir_final = %s",concat);
	FILE *output = fopen(concat, "w");
	 	for(i=0;i<line_counter;i++){
	if(i == 0){
	fprintf(output,"%s", headerline);
	}
	fprintf(output,"%s", entryArray[i].line);
	}
	fclose(output); 
	
		
		//printf ("\nSuccessfully read\n");
		//free(entryArray);
		return TRUE;

}

/* int main(int argc, char* argv[]) {

		if (argc == 3) { //correct number of arguments
	
		}
	else {

		fprintf(stderr, "ERROR: Invalid number of parameters, Usage: -c sort_parameter\n");

		exit(1);
	}

	 if(strcmp(argv[1], "-c")==0){
		char* sortPara = argv[2];
		return sortAlg(sortPara );

}
	else{

		fprintf(stderr, "ERROR: Invalid parameters, Usage: -c sort_parameter\n");

		exit(1);

}



	return 0;
 */

/* char line[1024];
    while (fgets(line, 1024, stdin))
	{
		char* tmp = strdup(line);
		printf(" %s", tmp);
		free(tmp);
	} 


}*/


