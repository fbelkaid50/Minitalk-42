#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
// #include "./includes/execution.h"
#include"structs.h"

void	handler(int sig);
void	handell_sig(void);
char *ft_strchr(const char *s, int c);
char *ft_strdup( char *s1);
void add_back1(t_token **lst, t_token *new);
void tokenizing_inputs(char *line ,t_token **lst );
int ft_token_len(char *line);
int ft_token_count(char *line);
int ft_strlen(char *str);
char *ft_token (char *line , int token_len);
char *skip_space(char *line);
t_token *new_token(char  *org,int flg);
int has_invalid_redirections( char *input);
int has_unclosed_quotes( char *input);
char *ft_strtrim (char *s1, char *set);
void parce_pipe(t_cmdl *cmd);
void add_back(t_cmdl **lst, t_cmdl *cmnd);
t_cmdl *ft_cmd(char *word, int length);
t_cmdl *get_cmd();
void  parce_redir_in_word(char *word, t_cmdl **cmnds,int flag);
t_cmdl **parce_line(t_token **lst,t_cmdl **cmnd);
char *ft_get_file(char *line);
void  parce_redir_out_word(char *word, t_cmdl **cmnds,int flag);
void  parce_redir_append_word(char *word, t_cmdl **cmnds,int flag) ;
void  parce_pipe_word(char *word, t_cmdl **cmnds,int flag) ;

#endif
