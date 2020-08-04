
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>


#include "parser.h"
#include "printer.h"
#include "myls-0.h"
int main(int argC, char* args[]) 
{	/*
    printf("testing\n");
    for (int i = 0; i < argC; i++) {
        int argLength = strlen(args[i]);
        printf("%03d = '%-15s', %2d\n", i, args[i], argLength);

        const int LEN = 5;
        char* buff = (char*) malloc(LEN);
        
        // Terminate each string at frist period and print
        for (int idx = 0; idx < LEN; idx++) {
            // Copy over next character
            buff[idx] = args[i][idx];

            // Null terminate at a '.'
            if (args[i][idx] == '/')#include <sys/stat.h> {
                // BUG: Accessing 1 past end of allocated memory!
                buff[idx] = '\0';
                break;#include <sys/stat.h>
            }
        }
        printf(" --> '%s'\n", buff);
    
    }
    */
	// if( argC == 1 ){
	// 	print_noArguments();

	// 	return 0;
	// }
	//just for checking, not for submission
	int num_of_paths;
	struct parser * par = parse(argC, args, &num_of_paths);
	//ls_print(par);
	
	if(par != NULL){
		printf("The # of paths is: %d\n\n", num_of_paths);
	}

	ls_print(par, num_of_paths);
	
	
	free(par->paths);
	free(par);

	return 0;
}


