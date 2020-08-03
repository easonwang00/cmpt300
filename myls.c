
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

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
	char* name = "testDir";
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
	// File Permission
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
    printf("\n");
    // The # of HardLinks
    printf("Number of Links: \t%ld\n",(long)buffer3.st_nlink);
    // The User Name
    printf("UserID: \t\t%d\n", buffer3.st_uid);
    // The Group Name
    printf("GroupID: \t\t%d\n", buffer3.st_gid);
    // The Size of Files
    printf("File Size: \t\t%lld bytes\n", buffer3.st_size);
    // The Date and Time of Files
    char * time = asctime(gmtime(&(buffer3.st_mtime)));
    char month[] = {'J','a','n','\0'};
    char day[] = {'0','0','\0'};
    char hour[] = {'0','0','\0'};
    char min[] = {'0','0','\0'};
    char year[] = {'0','0','0','0','\0'};
    //printf("%ld\t%s\n",strlen(time),time);
    for(int i = 4; i < strlen(time)-1; i++){
        if(i <= 6){
            month[i-4] = time[i];
        }else if(i == 8 || i == 9){
            day[i-8] = time[i];
        }else if(i == 11 || i == 12){
            hour[i-11] = time[i];
        }else if(i == 14 || i == 15){
            min[i-14] = time[i];
        }else if(i >= strlen(time)-5){
            year[i-strlen(time)+5] = time[i];
        }
    }
    if(day[0] == '0'){
        day[0] = 31;
    }
    printf("The Time of the Latest Modification: \t%s %s %s %s:%s\n", month, day, year, hour, min);
    // The File name


    printf("File inode: \t\t%ld\n",(long)buffer3.st_ino);
 

    printf("\n\n");

 
    printf("The file %s a symbolic link\n", (S_ISLNK(buffer3.st_mode)) ? "is" : "is not");

	
}