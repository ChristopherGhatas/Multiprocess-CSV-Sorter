#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <malloc.h>

#include "scannerCSVsorter.h"

char* removeSpace(char* string) {
	
	int length = strlen(string);
	char ans[length-1];
	int i;

	
	//Special Case: if the string is empty
	if (length == 0) {
		//printf("hit special case:\n");
		return string;
	}
	 if (string[0] != ' ' && string[length-1] != ' ') {//Check if there are any spaces at all.
		return string;
	} 

	
	else if(string[0] == ' ' && string[length-1] != ' ') {// if there is one one space in the front

		for (i = 1; i < length; i++) {
			ans[i-1] = string[i];
		}

		ans[i-1] = '\0';		
	}
 
	else if(string[0] != ' ' && string[length-1] == ' ') { //if there is only have one space in the end

		for (i = 0; i < length-1; i++) {
			ans[i] = string[i];
		}
		
		ans[i] = '\0';
	}

	else { //if there are spaces on both ends

		for (i = 1; i < length-1; i++) {
			ans[i-1] = string[i];
		}
		
		ans[i-1] = '\0';
	}
	
	return strdup(ans);
}

char* removeNewLine(char* string) {
	char *ans = strdup(string);
	char *ptr;
	for (ptr = ans; *ptr != '\0'; ptr++){
	if(*ptr == '\r' || *ptr == '\n'){
	*ptr = '\0';
	ptr++;
	}
	}
	return strdup(ans);
}

boolean sortKeyInitializer(sortIndex* globalSKey, char* argKey, char* headerLine){
	boolean condition = FALSE;
	
	if(globalSKey == NULL || argKey == NULL || headerLine == NULL){
		printf("\nCritical Error: invalid parameters for sortKey\n");
	return condition;
	
	}
	
	globalSKey->index = -1; // set value below zero since zero is technically a valid value.
	
	char* header = strdup(headerLine);
	char* header2 = strdup(headerLine);
	char* token;
	
	if(strcmp("color", argKey) == 0){
		globalSKey->type = STR;
	}
	else if(strcmp("director_name", argKey) == 0){
		globalSKey->type = STR;
	}
	else if(strcmp("num_critic_for_reviews", argKey) == 0){
		globalSKey->type = INT;
	}
	else if(strcmp("duration", argKey) == 0){
		globalSKey->type = INT;
	}
	else if(strcmp("director_facebook_likes", argKey) == 0){
		globalSKey->type = INT;
	}
	else if(strcmp("actor_3_facebook_likes", argKey) == 0){
		globalSKey->type = INT;
	}
	else if(strcmp("actor_2_name", argKey) == 0){
		globalSKey->type = STR;
	} 
	else if(strcmp("actor_1_facebook_likes", argKey) == 0){
		globalSKey->type = INT;
	} 
	else if(strcmp("gross", argKey) == 0){
		globalSKey->type = INT;
	} 
	else if(strcmp("genres", argKey) == 0){
		globalSKey->type = STR;
	} 
	else if(strcmp("actor_1_name", argKey) == 0){
		globalSKey->type = STR;
	} 
	else if(strcmp("movie_title", argKey) == 0){
		globalSKey->type = STR;
	}  	
	else if(strcmp("num_voted_users", argKey) == 0){
		globalSKey->type = INT;
	}  
	else if(strcmp("cast_total_facebook_likes", argKey) == 0){
		globalSKey->type = INT;
	}  
	else if(strcmp("actor_3_name", argKey) == 0){
		globalSKey->type = STR;
	}  
	else if(strcmp("facenumber_in_poster", argKey) == 0){
		globalSKey->type = INT;
	}  
	else if(strcmp("plot_keywords", argKey) == 0){
		globalSKey->type = STR;
	}  
	else if(strcmp("movie_imdb_link", argKey) == 0){
		globalSKey->type = STR;
	}  
	else if(strcmp("num_user_for_reviews", argKey) == 0){
		globalSKey->type = INT;
	}  
	else if(strcmp("language", argKey) == 0){
		globalSKey->type = STR;
	}  
	else if(strcmp("country", argKey) == 0){
		globalSKey->type = STR;
	}  
	else if(strcmp("content_rating", argKey) == 0){
		globalSKey->type = STR;
	}  
	else if(strcmp("budget", argKey) == 0){
		globalSKey->type = INT;
	}  
	else if(strcmp("title_year", argKey) == 0){
		globalSKey->type = INT;
	}  
	else if(strcmp("actor_2_facebook_likes", argKey) == 0){
		globalSKey->type = INT;
	}  
	else if(strcmp("imdb_score", argKey) == 0){
		globalSKey->type = FLT;
	}
	else if(strcmp("aspect_ratio", argKey) == 0){
		globalSKey->type = FLT;
	}  
	else if(strcmp("movie_facebook_likes", argKey) == 0){
		globalSKey->type = INT;
	}  
	else{
		printf("ERROR: Invalid Sort Key");
		return condition;
	}
	
	int i;

	for ( i = 0; header[i] != '\0'; i++ ) {
		globalSKey->total_columns+= (header[i] == ',');
	} globalSKey->total_columns++; 
	
	i = 0;
	while( (token = strsep(&header, ",")) != NULL) {
		if(i == (globalSKey->total_columns-1)){
			token = removeNewLine(token);
		}
		token = removeSpace(token);
		if(strcmp(token, argKey) == 0){
			globalSKey->index = i;
			condition = TRUE;
			break;
		}
		i++;
	}
	

	
	return condition;
}

int commaCheck(char* line){
	char* tempStr2 = line;
	int commas2 = 0;
	printf("LINE COMMA %s", line);
	while(*tempStr2 !='\0'){
	
 	if(*tempStr2 == '\"'){
		printf("tempStr2 %c", *tempStr2);
		while(*tempStr2 !='\0'){
			tempStr2++;
			if(*tempStr2 == '\"'){ break;}
			else{
			tempStr2++;
			}
		}
		} 
		
	else if(*tempStr2 == ','){
		commas2++;
	}
	
	tempStr2++;
	}
	++commas2;
	
	printf("commaCheck comma %d\n", commas2);
	return commas2;
}