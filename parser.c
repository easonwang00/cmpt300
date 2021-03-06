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
    2. a pointer to an array of strings with each element as a path(file or directory)
    3. an int indicating the number of paths
*/

struct parser * parse(int arg_num, char ** args, int * path_num)
{
    struct parser * res = malloc(sizeof(struct parser));// WARNING: do not forget to free it!!!
    bool index_number = false;
    bool long_listing = false;
    bool recursively_listing = false;
    char ** paths = NULL;
    int index = 0;
    *path_num = 0;

    if(arg_num == 1){
        *path_num = 1;
        paths = malloc(sizeof(char *));
        paths[0] = ".";
        res->paths = paths;
        return res;
    }

    int i = 1; 
    while(i < arg_num && args[i][0] == '-'){
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
        i++;
    }
    if(i == arg_num){
        *path_num = 1;
        paths = malloc(sizeof(char *));
        paths[0] = ".";        
    }else{
        while(i < arg_num){
            if(*path_num == 0){
                *path_num = arg_num - i;
                paths = malloc(sizeof(char *) * (*path_num));
            }         
            paths[index++] = args[i];
            i++; 
        }
    }
    res->index_number = index_number;
    res->long_listing = long_listing;
    res->recursive = recursively_listing;
    res->paths = paths;

    return res;
}

