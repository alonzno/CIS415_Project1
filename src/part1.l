%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ll_1.h"

struct dub_ll **head;
%}

%x  args
%x  quote

%%
[a-zA-Z0-9\-_\/.]+ {
                       dub_ll_push_new(head, yytext);
                       BEGIN args;
                   }
<args>[\"]          {
                       BEGIN quote;
                   }
<args>[a-zA-Z0-9\-_\/.]+ {
                                dub_ll_set_args(head, yytext);
                            }
<args>\n           {
                       BEGIN INITIAL;
                   }
<args><<EOF>>      {
                       BEGIN INITIAL;
                   }
<quote>[a-zA-Z0-9\-_\/. \']+ {
                                 dub_ll_set_args(head, yytext);
                             }
<quote>[\"]         {
                       BEGIN args;
                    }
\n {}
.  { 
       fprintf(stderr, "Lexically erroneous command\n");
       exit(3);
   }

%%

int yywrap(void) {}

int main(int argc, char **argv) {
    extern FILE *yyin;
    if (argc != 2) {
        fprintf(stderr, "Bad Arguments\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");

    if (yyin == NULL) {
        fprintf(stderr, "Error opening file\n");
        perror(argv[1]);
        exit(2);
    }

    head = (struct dub_ll **)malloc(sizeof(struct dub_ll *));
    (*head) = NULL;
    
    yylex();
    
    fprintf(stdout, "\n");


    dub_ll_make_arg_dp(head);
    
    //dub_ll_print(head);

    dub_ll_start(head);
    
    dub_ll_free(head);
    
    return 0;
}


