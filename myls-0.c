#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "myls-0.h"
#include "list.h"
void print_noArguments(){
	char* name = ".";
	struct Node* tempList = NULL;
	if (strcmp("a","Makefile")>0) {
		printf("a > makefile\n");
	}
	//tempList->headList =NULL;
	DIR * buffer = opendir(name);
	if( buffer == NULL ){
		printf(" fail to open dir !\n");
	}
	struct dirent *buffer2;;
	while ((buffer2 = readdir(buffer)) != NULL) {
			if (buffer2->d_name[0] == '.'){
                continue;
            }
            printf ("[%s]\n", buffer2->d_name);
            insert(&tempList,buffer2->d_name);
    }
    printf("_________\n");
    bubbleSort(tempList);
    print(tempList);
}