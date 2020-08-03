#ifndef _MYLSPARSER_H_
#define _MYLSPARSER_H_

#include <stdbool.h>

struct parser {
    bool long_listing;
    bool index_number;
    bool recursive;
    struct stat * paths;
};

struct parser * parse(int argnum, char * args[], int * path_num);


#endif