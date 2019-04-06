#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
//BEGIN helper functions
//END helper functions

//BEGIN dub_ll
struct dub_ll {
    char *command;
    char *prog_name;
    char *args;
    
    pid_t pid;

    struct dub_ll *next;
    struct dub_ll *prev;
};

void dub_ll_push(struct dub_ll **head, char *_command) {
    
    struct dub_ll *new_node = (struct dub_ll *)malloc(sizeof(struct dub_ll));
    
    new_node -> command = strdup(_command);
    new_node -> next = (*head);
    new_node -> prev = NULL;

    if ((*head) != NULL) {
        (*head) -> prev = new_node;
    }

    (*head) = new_node;
}

void dub_ll_push_new(struct dub_ll **head, char *_prog_name) {
    
    struct dub_ll *new_node = (struct dub_ll *)malloc(sizeof(struct dub_ll));
    
    new_node -> prog_name = strdup(_prog_name);
    new_node -> args = NULL;
    new_node -> pid = 0;
    new_node -> next = (*head);
    new_node -> prev = NULL;

    if ((*head) != NULL) {
        (*head) -> prev = new_node;
    }

    (*head) = new_node;
}

void dub_ll_set_args(struct dub_ll **node, char *_args) {
    (*node) -> args = strdup(_args);
}

void dub_ll_print(struct dub_ll **head) {
    struct dub_ll *tmp = (*head);
    while (tmp != NULL) {
        fprintf(stderr, "%s\n", tmp -> prog_name);
        if (tmp -> args != NULL) {
            fprintf(stderr, "\t%s\n", tmp -> args);
        }
        tmp = tmp -> next;
    }
}
/*
void dub_ll_split(struct dub_ll **head) {
    struct dub_ll *tmp = (*head);
    char *curr_command;
    int offset;
    bool no_args;
    while (tmp != NULL) {



        tmp = tmp -> next;   
    }
}
*/
//END dub_ll
#endif
