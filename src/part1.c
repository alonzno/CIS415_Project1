#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

#include "../include/ll.h"

#define BUFFER_SIZE 256
#define ERR_LOW_ARGS 1

int main(int argc, char **argv) {
    int errrv;

    //Step 1: Read Input
    if (argc == 1) {
        fprintf(stderr, "Not enough arguements provided\n");
        exit(ERR_LOW_ARGS);
    }

    char *filename = argv[1];
    FILE *commands_file = fopen(filename, "r");

    if (commands_file == NULL) {
        errrv = errno;
        fprintf(stderr, "File could not be opened\n");
        perror(filename);
        exit(errrv);
    }

    char buffer[BUFFER_SIZE];
    struct dub_ll **head = (struct dub_ll **)malloc(sizeof(struct dub_ll *));
    
    if (head == NULL) {
        errrv = errno;
        fprintf(stderr, "Unable to allocate linked list head\n");
        perror("LL_Head");
        exit(errrv);
    }

    while (fgets(buffer, BUFFER_SIZE, commands_file)) {
        dub_ll_push(head, buffer);
        //fprintf(stderr, "%s", buffer);
    }
    
    dub_ll_print(head);

    return 0;
}
