/*
    This module is mainly for coding and debugging by printing out and checking the informtion
    MAY NOT SUBMIT ALL FUNCTIONS
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#include "printer.h"

static void print_stat(struct stat * input_stat);


// print according to the input path
void print_path(char * path)
{
	char* name = path;
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
    print_stat(&buffer3);

    closedir(buffer);
    return;
}


//print according to the input 'struct stat'
static void print_stat(struct stat * input_stat)
{

	// File Permission
    printf("File Permissions: \t");
    printf( (S_ISDIR(input_stat->st_mode)) ? "d" : "-");
    printf( (input_stat->st_mode & S_IRUSR) ? "r" : "-");
    printf( (input_stat->st_mode & S_IWUSR) ? "w" : "-");
    printf( (input_stat->st_mode & S_IXUSR) ? "x" : "-");
    printf( (input_stat->st_mode & S_IRGRP) ? "r" : "-");
    printf( (input_stat->st_mode & S_IWGRP) ? "w" : "-");
    printf( (input_stat->st_mode & S_IXGRP) ? "x" : "-");
    printf( (input_stat->st_mode & S_IROTH) ? "r" : "-");
    printf( (input_stat->st_mode & S_IWOTH) ? "w" : "-");
    printf( (input_stat->st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    // The # of HardLinks
    printf("Number of Links: \t%ld\n",(long)input_stat->st_nlink);
    // The User Name
    struct passwd * temp_passwd_uid = getpwuid(input_stat->st_uid);
    printf("UserID: \t\t%s\n", temp_passwd_uid->pw_name);
    // The Group Name
    struct group * temp_passwd_gid = getgrgid(input_stat->st_gid);
    printf("GroupID: \t\t%s\n", temp_passwd_gid->gr_name);
    // The Size of Files
    printf("File Size: \t\t%ld bytes\n", input_stat->st_size);
    // The Date and Time of Files
    char * time = asctime(gmtime(&(input_stat->st_mtime)));
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


    printf("File inode: \t\t%ld\n",(long)input_stat->st_ino);
 

    printf("\n\n");  

    return;
}

void ls_print(struct parser * input_parser, int path_num)
{
    for(int i = 0; i < path_num; i++){
        char* name = input_parser->paths[i];
        int len_name = strlen(name);
        DIR * buffer = opendir(name);
        if( buffer == NULL ){
            printf(" fail to open dir: '%s'!\n", name);
        }
        struct dirent *buffer2;;
        while ((buffer2 = readdir(buffer)) != NULL) {
            if(strcmp(buffer2->d_name, ".") != 0  && strcmp(buffer2->d_name, "..") != 0){
                char sub_name[len_name];
                strcpy(sub_name, name);
                strcat(sub_name, "/");
                strcat(sub_name, buffer2->d_name);
                //for(int c = 0; buffer2->d_name[c] != 0; c++){
                //    sub_name += buffer2->d_name[c];
                //}
                printf ("[%s]---[%s]---[%s]\n",name, sub_name, buffer2->d_name);

                struct stat buffer3;          
                if(stat(sub_name, &buffer3) < 0){
                    printf(" fail to stat()\n");
                }else{
                    print_stat(&buffer3); 
                }
            }
        }

        closedir(buffer);
    }
    
    // for the cases of no options

    // for the cases of -i

    return;
}
