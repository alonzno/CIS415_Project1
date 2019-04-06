#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
//BEGIN helper functions
//END helper functions

//BEGIN singly_ll
struct singly_ll {
    char *arg;
    struct singly_ll *next;
};

void singly_ll_push(struct singly_ll **head, char *_arg) {
    struct singly_ll *new_node = (struct singly_ll *)malloc(sizeof(struct singly_ll));
    new_node -> arg = strdup(_arg);
    new_node -> next = (*head);
    (*head) = new_node;
}

void singly_ll_print(struct singly_ll **head) {
    struct singly_ll *tmp = (*head);
    while (tmp != NULL) {
        fprintf(stderr, "\t%s\n", tmp -> arg);
        tmp = tmp -> next;
    }
}

int singly_ll_len(struct singly_ll **head) {
    struct singly_ll *tmp = (*head);
    int counter = 0;
    while (tmp != NULL) {
        counter++;
        tmp = tmp -> next;
    }
    return counter;
}
//END singly_ll

//BEGIN dub_ll
struct dub_ll {
    char *command;
    char *prog_name;
    char **args;
    struct singly_ll **arg_list;
    
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
    new_node -> arg_list = (struct singly_ll **)malloc(sizeof(struct singly_ll *));
    (*(new_node -> arg_list)) = NULL;
    new_node -> pid = 0;
    new_node -> next = (*head);
    new_node -> prev = NULL;

    if ((*head) != NULL) {
        (*head) -> prev = new_node;
    }

    (*head) = new_node;
}

void dub_ll_set_args(struct dub_ll **node, char *_args) {
    singly_ll_push((*node) -> arg_list, _args);
}

void dub_ll_print(struct dub_ll **head) {
    struct dub_ll *tmp = (*head);
    while (tmp != NULL) {
        fprintf(stderr, "%s\n", tmp -> prog_name);
        
        singly_ll_print(tmp -> arg_list);
        tmp = tmp -> next;
    }
}

void dub_ll_make_arg_dp(struct dub_ll **head) {
    struct dub_ll *tmp = (*head);
    struct singly_ll *curr_list;
    int list_len = 0;
    int counter = 0;
    while (tmp != NULL) {
        list_len = singly_ll_len(tmp -> arg_list);
        tmp -> args = (char **)malloc(sizeof(char *) * list_len + 2);
        curr_list = (*(tmp -> arg_list));
        while (curr_list != NULL) {
            
        }

    }
}

void dub_ll_start(struct dub_ll **head) {
    struct dub_ll *tmp = (*head);
    pid_t curr_pid;
    while (tmp != NULL) {
        curr_pid = fork();
        if (curr_pid < 0) {
            //Handle Error
            exit(1);
        }
        if (curr_pid == 0) {
            execlp(tmp -> prog_name, tmp -> args);
            exit(-1);
        }
        tmp -> pid = curr_pid;
        tmp = tmp -> next;
    }
    tmp = (*head);
    while (tmp != NULL) {
        wait(tmp -> pid);
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
