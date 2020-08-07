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
#include <ctype.h>
#include <math.h>

#include "parser.h"

//static void print_path(char * path);
static void print_stat(struct parser * input_parser, struct stat * input_stat, char * name, unsigned long long max_values[]);
static int strcicmp(char const * a, char const * b);
static void bubblesort(char * arr_str[], int size);

/*
// print according to the input path
static void print_path(char * path)
{
	DIR * buffer = opendir(path);
	if( buffer == NULL ){
		printf(" fail to open dir: %s !\n", path);
	}
	struct dirent *buffer2;;
	while ((buffer2 = readdir(buffer)) != NULL) {
            printf ("[%s]\n", buffer2->d_name);
    }
	struct stat buffer3;          

	if(stat(path, &buffer3) < 0){
		printf(" fail to stat()\n");
	}
    print_stat(&buffer3);

    closedir(buffer);
    return;
}
*/



//print according to the input 'struct stat'
static void print_stat(struct parser * input_parser, struct stat * input_stat, char * name, unsigned long long max_values[])
{
    // for option -i

    if(input_parser->index_number && max_values[0] > 1){
        unsigned long long ino = ((struct stat *)input_stat)->st_ino;
        int count = (ino == 0) ? 1  : ((int)(log10(ino)) + 1);
        int count_max = (max_values[0] == 0) ? 1  : ((int)(log10(max_values[0])) + 1);
        for(int i = 0; i < count_max  - count; i++){
            printf(" ");
        }
        printf("%lld ", ino);
    }
    // for option -l
    if(input_parser->long_listing && max_values[1] && max_values[2]){
        // File Permission
        //printf("File Permissions: \t");
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
        printf(" ");
        // The # of HardLinks
        unsigned long long n = ((struct stat *)input_stat)->st_nlink;
        int count = (n == 0) ? 1  : ((int)(log10(n)) + 1);
        int count_max = (max_values[2] == 0) ? 1  : ((int)(log10(max_values[2])) + 1);
        for(int i = 0; i <count_max  - count; i++){
            printf(" ");
        }
        printf("%ld ",(long)input_stat->st_nlink);
        // The User Name
        struct passwd * temp_passwd_uid = getpwuid(input_stat->st_uid);
        printf("%s ", temp_passwd_uid->pw_name);
        // The Group Name
        struct group * temp_passwd_gid = getgrgid(input_stat->st_gid);
        printf("%s ", temp_passwd_gid->gr_name);
        // The Size of Files
        unsigned long long s = ((struct stat *)input_stat)->st_size;
        count = (s == 0) ? 1  : ((int)(log10(s)) + 1);
        count_max = (max_values[1] == 0) ? 1  : ((int)(log10(max_values[1])) + 1);
        //printf("max_size = %lld, max_count = %d, this_size = %lld, count = %d\n", max_values[1], count_max, s, count);
        for(int i = 0; i <count_max  - count; i++){
            printf(" ");
        }
        printf("%ld ", input_stat->st_size);
        // The Date and Time of Files
        struct tm * local_time = localtime(&(input_stat->st_mtime));
        int year = 1900 + local_time->tm_year;
        int month = local_time->tm_mon;
        int day = local_time->tm_mday;
        int hour = local_time->tm_hour;
        int min = local_time->tm_min;
        const char * months[] = {
            "Jan",
            "Feb",
            "Mar",
            "Apr",
            "May",
            "Jun",
            "Jul",
            "Aug",
            "Sep",
            "Oct",
            "Nov",
            "Dec"
        };
        printf("%s %2d %d %02d:%02d ", months[month], day, year, hour, min);
    }

    // The File name
    printf("%s\n", name);
    return;
}

void ls_print(struct parser * input_parser, int path_num)
{
    // THe three lines below are for recursively listing
    char ** sub_dir_paths[path_num];
    //int sub_dir_paths_nums[path_num];
    struct parser sub_paths_parsers[path_num]; 

    for(int i = 0; i < path_num; i++){
        char* name = input_parser->paths[i];
        printf("%s:\n", name);
        //nt len_name = strlen(name);
        int len_name = 1024; //IT IS CONFUSING HERE, FIGURE IT OUT!!! https://www.stev.org/post/csomesimpleexamplesofusingstrcat
        DIR * buffer = opendir(name);
        if( buffer == NULL ){
            printf(" fail to open dir: '%s'!\n", name);
        }
        struct dirent * buffer2;
        int sub_name_num = 0;
        while((buffer2 = readdir(buffer)) != NULL){ // count # of the sub_dirs or files to be listed
            if(buffer2->d_name[0] != '.'){
                sub_name_num++;
            }
        }
        char * sub_dir_names[sub_name_num];
        int idx = 0;
        rewinddir(buffer);
        while ((buffer2 = readdir(buffer)) != NULL) { // add the names of those sub_dirs or files waiting to be sorted
            if(buffer2->d_name[0] != '.'){
                sub_dir_names[idx++] = buffer2->d_name;
            }
        }
        bubblesort(sub_dir_names, sub_name_num);
        unsigned long long max_values[] = {0, 0, 0}; // store the largest sizes of st_ino, st_size, st_nlinks
        struct stat buffer3[sub_name_num];
        char real_sub_dir_names[sub_name_num][1024];
        int sub_dir_count = 0; // count the number of sub_directories
        for(int j = 0; j < sub_name_num; j++){
            char sub_name[len_name];
            strcpy(sub_name, name);
            strcat(sub_name, "/");
            strcat(sub_name, sub_dir_names[j]);
            strcpy((char *)(&real_sub_dir_names[j]), sub_name);
            if(stat((char *)(&real_sub_dir_names[j]), (struct stat *)(&buffer3[j])) < 0){
                printf(" fail to stat()\n");
            }else{
                if(max_values[0] < buffer3[j].st_ino){
                    max_values[0] = buffer3[j].st_ino;
                }
                if(max_values[1] < buffer3[j].st_size){
                    max_values[1] = buffer3[j].st_size;
                }
                if(max_values[2] < buffer3[j].st_nlink){
                    max_values[2] = buffer3[j].st_nlink;
                }
                if(buffer3[j].st_nlink > 1){
                    sub_dir_count++; //count how many sub_dir or there are
                }
            }                  
        }
        sub_dir_paths[i] = malloc(sizeof(char *) * sub_dir_count); //DO NOT FORGET TO FREE
        int idx_for_sub_dir_paths = 0;
        for(int k = 0; k < sub_name_num; k++){
            print_stat(input_parser, (struct stat *)(&buffer3[k]), sub_dir_names[k], max_values); 
            if(buffer3[k].st_nlink > 1){
                sub_dir_paths[i][idx_for_sub_dir_paths++] = (char *)&real_sub_dir_names[k];
            }
        }

        if(input_parser->recursive){
            sub_paths_parsers[i].index_number = input_parser->index_number;
            sub_paths_parsers[i].long_listing = input_parser->long_listing;
            sub_paths_parsers[i].recursive = input_parser->recursive;
            sub_paths_parsers[i].paths = sub_dir_paths[i];    
            //sub_dir_paths_nums[i] = sub_dir_count; 
            ls_print(&sub_paths_parsers[i], sub_dir_count);
            free(sub_paths_parsers[i].paths);
            sub_paths_parsers[i].paths = NULL;            
        }
        
        closedir(buffer);
        if(i < path_num - 1){
            printf("\n\n");
        }
    }

    return;
}



static int strcicmp(char const * a, char const * b) // compare two strings: return 1 when a > b, 0 when equal, -1 when a < b
{
    for(;; a++, b++){
        int d = tolower((unsigned char) * a) - tolower((unsigned char) * b);
        if(d != 0){
            return d;
        }else if(a == 0 && b != 0){
            return -1;
        }else if(a != 0 && b == 0){
            return 1;
        }else if(a == 0 && b == 0){
            return 0;
        }
    }
    return -2;
}
static void bubblesort(char * arr_str[], int size)
{
    for(int i = size - 1; i > 0; i--){
        int swapped = 0;
        for(int j = 0; j < i; j++){            
            if(strcicmp(arr_str[j], arr_str[j+1]) > 0){
                swapped = 1;
                char * temp = arr_str[j];
                arr_str[j] = arr_str[j+1];
                arr_str[j+1] = temp;
            }
        }
        if(swapped == 0){
            break;
        }
    }
    return;
}