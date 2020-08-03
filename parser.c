#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "parser.h"
#include "list.h"


/*
    This function is to parse the input args, returning a pointer to 'parser' struct including:
    1. three boolean values to reflect the options 
    2. a pointer to an array of 'stat' struct with each element belonging to a path(file or directory)
    3. an int indicating the number of paths
*/

struct parser * parse(int arg_num, char ** args, int * path_num)
{
    struct parser * res = malloc(sizeof(struct parser));// WARNING: do not forget to free it!!!
    bool index_number = false;
    bool long_listing = false;
    bool recursively_listing = false;
    struct stat * ret;
    int index = 0;


    *path_num = 0;
    if(arg_num == 1){
        return NULL;
    }
    for(int i = 1; i < arg_num; i++){
        if(args[i][0] == '-'){
            for(int j = 1; j < strlen(args[i]); j++){
                if(args[i][j] == 'i'){
                    index_number = true;
                }else if(args[i][j] == 'l'){
                    long_listing = true;
                }else if(args[i][j] == 'R'){
                    recursively_listing = true;
                }else{
                    // options input is errous
                    *path_num = -1;
                    printf("Options Input Error!\n");
                    return NULL;
                }
            }
        }else{
            if(*path_num == 0){
                *path_num = arg_num - i;
                ret = malloc(sizeof(struct stat) * (*path_num)); // WARNING: do not forget to free it!!!
            }         
            if(stat(args[i], &ret[index++]) < 0){
                printf("For %s, fail to stat()\n", args[i]);
            }            
        }
    }

    res->index_number = index_number;
    res->long_listing = long_listing;
    res->recursive = recursively_listing;
    res->paths = ret;

    return res;
}

