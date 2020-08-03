
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "myls-0.h"
#include "list.h"
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
	if( argC == 1 ){
		print_noArguments();

		return 0;
	}
        
	for (int i = 1; i < argC; i++) {

        int argLength = strlen(args[i]);
		char* name = args[i];
		printf("%03d = '%-15s', %2d\n", i, args[i], argLength);
		DIR * buffer = opendir(name);
		if( buffer == NULL ){
			printf(" fail to open dir !\n");
		}
		struct dirent *buffer2;;
		while ((buffer2 = readdir(buffer)) != NULL) {
	            printf ("[%s]\n", buffer2->d_name);
	    }
		struct stat buffer3;          

		if(stat(name, &buffer3) < 0){
			printf(" fail to stat()\n");
		}
	
	    printf("Information for %s\n",name);
	    printf("---------------------------\n");
	    printf("File Size: \t\t%ld bytes\n",buffer3.st_size);
	    printf("Number of Links: \t%ld\n",buffer3.st_nlink);
	    printf("File inode: \t\t%ld\n",buffer3.st_ino);
	 
	    printf("File Permissions: \t");
	    printf( (S_ISDIR(buffer3.st_mode)) ? "d" : "-");
	    printf( (buffer3.st_mode & S_IRUSR) ? "r" : "-");
	    printf( (buffer3.st_mode & S_IWUSR) ? "w" : "-");
	    printf( (buffer3.st_mode & S_IXUSR) ? "x" : "-");
	    printf( (buffer3.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (buffer3.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (buffer3.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (buffer3.st_mode & S_IROTH) ? "r" : "-");
	    printf( (buffer3.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (buffer3.st_mode & S_IXOTH) ? "x" : "-");
	    printf("\n\n");

	 
	    printf("The file %s a symbolic link\n", (S_ISLNK(buffer3.st_mode)) ? "is" : "is not");
	    closedir(buffer);
	}

	
}