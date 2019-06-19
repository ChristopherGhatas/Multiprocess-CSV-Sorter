#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <malloc.h>
#include <dirent.h>


#include "scannerCSVsorter.h"

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

char* extension_removal(char* fileName) {
    char *retstr;
    char *lastdot;
    if (fileName == NULL)
         return NULL;
    if ((retstr = malloc (strlen (fileName) + 1)) == NULL)
        return NULL;
    strcpy (retstr, fileName);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}


FILE *openfile( char *dirname, char* out_dir, char* fileName, char* sortKey, const char *mode )
 {
       char pathname[1024];   /* should alwys be big enough */
       FILE *fp;

       sprintf( pathname, "%s/%s", dirname, fileName );
	   printf("dirname = %s, dir->d_name = %s \n", dirname, fileName);
       fp = fopen( pathname, mode );
	if(fp==NULL)
	{
		printf("\nCAN NOT OPEN FILE");
		exit(1);
	}
	char* fileName_nameonly = extension_removal(fileName);
	sortAlg(sortKey,fp,out_dir,fileName_nameonly);
	/* size_t len1 = strlen(dirname), len2 = strlen(fileName), len3 = strlen(sortKey);
	char *concat = (char*) malloc(len1 + len2 + len3 + 16);
	snprintf (concat, len1 + len2 + len3 + 16, "%s/%s-sorted-%s.csv", dirname, fileName,sortKey);
	printf("out_dir_final = %s",concat);
	FILE *output = fopen(concat, "wb");
	fclose(output); 
	fclose(fp); */
       return fp;
 }
 
int processCounterFunc(char* directory) {
	 int processCounter = 1;
	 DIR *tempdir;
	tempdir = opendir(directory);
	
	struct dirent *curr;
	
	if(tempdir == NULL) { 
		return; 
	}
	
	while ((curr = readdir(tempdir)) != NULL) {
		char dir_path[1024];
		snprintf(dir_path, sizeof(dir_path), "%s/%s", directory, curr->d_name);
		
		if(strcmp(curr->d_name, ".") == 0 || strcmp(curr->d_name, "..") == 0) {
            continue;
        }

		if(curr->d_type == 4) {
            processCounter++;
            processCounterFunc(dir_path);

        }
		
		else {
			int length = strlen(curr->d_name);
			if(strcmp(get_filename_ext(curr->d_name),"csv") == 0 && !(strstr(curr->d_name, "sorted"))) {
				processCounter++;
			}
		}
	}
	return processCounter;
	 
 }

void dirFunc(char *dirName, char *out_dir, char *sortKey, boolean dArg, boolean oArg) {
	
	DIR *curr_dir;
	struct dirent *pointer = NULL;
	int childCounter = 0;
	
	if(dArg == TRUE){
	DIR* cDir = opendir(dirName);
	if (cDir)
{
    /* Directory exists. */
    closedir(cDir);
}
else if (ENOENT == errno)
	{
	fprintf(stderr, "ERROR: Input directory does not exist\n");
	exit(1);
    /* Directory does not exist. */
	}
	
	}
	
	curr_dir = opendir(dirName);

	
	int dirPid = 0; int filePid = 0;
	
	if(curr_dir == NULL) { 
		return; 
	}
	
	if(oArg == TRUE){
	
	DIR* oDir = opendir(out_dir);
	if (oDir)
{
    /* Directory exists. */
    closedir(oDir);
}
else if (ENOENT == errno)
	{
	fprintf(stderr, "ERROR: Output directory does not exist\n");
	exit(1);
    /* Directory does not exist. */
	}
	}
	
	while((pointer = readdir (curr_dir)) != NULL) {
		if (strcmp(pointer->d_name, ".") == 0 || strcmp(pointer->d_name, "..") == 0) {
			continue;
		}
		
		if(pointer->d_type == 4) {
			dirPid = fork();
			if(dirPid == 0) {
				printf("%d, ", getpid()); fflush(stdout);
				char path[1024];
				snprintf(path, sizeof(path), "%s/%s", dirName, pointer->d_name);
				dirFunc(path, out_dir, sortKey, dArg, oArg);				
				exit(0);
			}
		} else {
			int length = strlen(pointer->d_name);
			if(strcmp(get_filename_ext(pointer->d_name),"csv") == 0 && !(strstr(pointer->d_name, "sorted"))) {
				childCounter++;
				filePid = fork();
				if(filePid == 0) {
					printf("%d, ", getpid());
					fflush(stdout);
					char path[1024];
					snprintf(path, sizeof(path), "%s/%s", dirName, pointer->d_name);
					FILE *file = fopen(path, "r");
					char* fileName_nameonly = extension_removal(pointer->d_name);
					sortAlg(sortKey,file,out_dir,fileName_nameonly);
					//sort(file, sortKey, path, output);
					exit(0);
				}				
			}
		}
	}
	
	if (dirPid != 0) {	
		wait(0); 
	}
	
	if (filePid != 0) {
		while(childCounter > 0) { 
			wait(0); 
			childCounter--;
		}
	}
	return;
}


int main(int argc, char* argv[]) {
	
	if (argc == 3 || argc == 5 || argc == 7) { //correct number of arguments
	
		}
	else {

		fprintf(stderr, "ERROR: Invalid number of parameters, Usage: -c sort_parameter\n");

		exit(1);
	}

	int i;
	int processCounter;
	cmdArg cArg;
	cArg.active = FALSE;
	cmdArg dArg;
	dArg.active = FALSE;
	cmdArg oArg;
	oArg.active = FALSE;
	//printf("argc = %d", argc);
	for(i = 1; (i+1)<argc; i = i+2){
		//printf("i = %d", i);
	 if(strcmp(argv[i], "-c")==0){
		 cArg.active = TRUE;
		 cArg.parameter = argv[i+1];
		// printf("cArg.parameter %s\n", cArg.parameter);
		/* char* sortPara = argv[2];
		return sortAlg(sortPara); */

}
	else if(strcmp(argv[i], "-d")==0){
		dArg.active = TRUE;
		dArg.parameter = argv[i+1];

	}
	else if(strcmp(argv[i], "-o")==0){
		oArg.active = TRUE;
		oArg.parameter = argv[i+1];
		 
	}
	 else{
		 printf("\ni = %d\n",i);
		 printf("\nargv = %s\n",argv[i]);

		fprintf(stderr, "ERROR: Invalid parameters, Usage: -c/-d/-o sort_parameter\n");

		exit(1);

	} 
	
	}
	
	if(cArg.active != TRUE){
		fprintf(stderr, "Critical ERROR: no sorting parameter listed, -c not used , Usage: -c/-d/-o sort_parameter\n");
		exit(1);
	}
	
	char* curr_dir = "./";
	if(dArg.active == TRUE){
		
		curr_dir = dArg.parameter;
		
	}
	
	char* out_dir = "./";
	if(dArg.active == TRUE){
		
		out_dir = oArg.parameter;
		
	}

	
	int j = getpid();
	printf("\n\nInitial PID: %d\n", j); 
	printf("PIDS of all child processes: "); fflush(stdout);
	dirFunc(curr_dir, out_dir, cArg.parameter, dArg.active, oArg.active);
	processCounter = processCounterFunc(curr_dir);
	printf("\nNumber of Processes: %d \n", processCounter); fflush(stdout);
	
	
/* 	
	DIR* pointer = NULL;
	struct dirent*curr;
	
	pointer = opendir(curr_dir);
	if(pointer == NULL){
	exit(1);
	}

	curr = readdir(pointer);
	int pid;
	int ids[300];
	int childCounter = 0;
	ids[0] = getpid();
	while(curr!=NULL){
		printf("NAME IS %s\n",curr->d_name);
		printf("%s\n", get_filename_ext(curr->d_name));
		if(strcmp(get_filename_ext(curr->d_name),"txt") == 0){
			char fileName[255];
			fileName[254] = '\0';
			strncpy(fileName, curr->d_name, 254);
		pid = fork();	
		if(pid == 0){
			printf("\n\nchild works \n\n");
			printf("child %s",fileName);
		FILE *fp = openfile(curr_dir,out_dir, fileName, cArg.parameter, "r");
		}
		else{
		childCounter++;
		ids[childCounter] = pid;
		curr = readdir(pointer);
		}
		}
		curr = readdir(pointer);
	}
	if(getpid() == ids[0]){
	int w;
	int status;
	printf("Childcounter = %d", childCounter);
	childCounter++;
	for(w = 0; w<childCounter; w++){
		printf("PID %d : %d", w, ids[w]);
		wait(&status);
	}
	} */

	return 0;
	
}
