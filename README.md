# Multiprocess-CSV-Sorter
#Scanner CSV Sorter Documentation:

Usage:

The program reads from a directory either specified by user or from current directory where the program is run from. 
Then it sorts all csv files within it and outputs it to a specified directory or the current directory.
The proper parameters required for the program are -c, and a column to sort in the csv file, -d, a directory with csv files, -o, a directory to output to. 
It can run without -o and -d but needs -c to be function.

Example of usage:

./scannerCSVsorter -c sortKey -d thisdir -o outdir

Design:

It uses the files scannerCSVsorter.c simpleCSVsorter.c, scannerCSVsorter.h, sortKeyFunctions.c, and mergesort.c
Checks for inputs and returns error if incorrect usage. It must be 3, 5, or 7 inputs. Else it is an error.

It places the parameters in a struct for each input parameter and sets a boolean to check if it is active in the code or not.
If -c is active it continues, if it is not, it gives a critical error and ends the program. 
if -d is active it inputs the directory into a variable for use, if not, it sets variable to current directory.
if -o is active it inputs the directory into a variable for use, if not, it sets variable to current directory.

It then gets the pid and prints the pid.
It goes into a function called dirFunc which handles directory parsing.
It first checks if both input and output directories exist, if they dont, it returns a critical error and exits the program.

Then it uses a pointer to parse through the input directory. If there is a subdirectory, it recursively calls itself with a fork to do the process.
If it is a file that has a csv extension and does not have sorted as part of its name, then it increments childprocess. Then forks to do the process.
When it forks, it creates a new pathname from the directory and filename. It also prints the pid. Then it sends pathname into sortAlg function to continue.

It goes to sortAlg. sets up many different variables for the next processes. It uses
while(fgets) for the csv file passed into it to go through it. It checks if the boolean variable First is true which it is
in the first line then, it finds the header line in the sortKeyInitializer. The function
uses strsep function to go through the headerline and finds the index of the commas and it also
sets the type of the column and places both in the struct globalSKey. First is then set to FALSE.

then there is an else statement, that continues for the later lines. It duplicates the line into a struct for the line called entry in an array of entries.
 It goes through each line character by character and it counts the commas until it hits the index from globalSKey. When it hits a double quote,
it then skips to the next double quotes, and continues as normal. When it hits the index number, it then puts the
characters in an array and puts the array in the entry struct. It also converts it to float or int if either are the current type in globalSKey.

It performs mergesort on the entry array. it creates a left and right array and begins to compare the two recursively through
the general mergesort algorithm and it uses the type in the globalSKey to determine which type of mergesort to use(INT, FLOAT, STRING).
Then it creates a new file in the output directory with the name of the file and -sorted and the parameter it sorted by.
It then prints into the file the the lines in order from 0 - end of array.

I used fgets instead of others because it reads each line well with a buffer. The program are divided into several files. simpleCSVsorter.c holds the sortAlg function.
mergesort.c holds the mergesort functions. sortKeyFunctions.c holds the sortKeyInitializer, which initializes the global sort key, removeNewLine and removeSpace, which fixes the token.
scannerCSVsorter.h holds the sortKey struct and the entry struct. It also holds the typedef for boolean and sortKey types, and the function declarations.

I then have a wait call if subdirectory was found. I have a wait call in a while loop based on the childCounter and it decriments until its done.
Then there is a function called processCounterFunc which counts the processes done so it can print that number to stdout. 
It goes through the directories the same way as dirFunc but it only counts the times it could have forked and instead increments a processCounter. It then returns it to the main and is printed out.
