#ifndef _MYLSPARSER_H_
#define _MYLSPARSER_H_

#include <stdbool.h>

struct parser {
    bool long_listing;
    bool index_number;
    bool recursive;
    struct inode * path;
};

struct parser * parse(int argnum, char * args[], int * path_num);


#endif