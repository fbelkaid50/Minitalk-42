/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 07:37:40 by fbelkaid          #+#    #+#             */
/*   Updated: 2024/10/22 00:43:58 by fbelkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_token_len (char *line)
{
    int i = 0;
    while(line[i] && (line[i] != ' ' || (line[i] >= 9 && line[i] <= 13)))
        i++;
    return i;
}

char *ft_token(char *line , int token_len)
{
    int i = 0;
    char *token;

    token = malloc(sizeof(char) * token_len + 1);
    if (token == NULL)
        return NULL;
    while (i<token_len)
    {
        token [i]=line[i];
        i++;
    }
    token[i] = '\0';
    return token;
}

char *skip_space(char *line)
{
   int i = -1;
   int flag = 0;
   int j = 0;
   int len = ft_strlen(line);
   char *res = malloc((len + 1) * sizeof(char));
   if (res == NULL)
       return NULL;
   while(line[++i])
   {
         while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
         {
                flag = 1;
                i++;
         }
         if (flag)
            {
                res[j]=' ';
                j++;
                flag =0;
            }
        res[j]=line[i]; 
        j++;
   }
   res[j] = '\0'; 
   return res;
}

int ft_token_count(char *line) 
{
    int count = 0;
    int in_quotes = 0;
    char quote;
   
    while (*line)
    {
        if (*line == 34 || *line == 39) 
        {
            if (in_quotes && quote == *line) 
            {
                in_quotes = 0; 
                count++; 
            }
            else if (!in_quotes) 
            {
                in_quotes = 1; 
                quote = *line; 
            }
        }
        else if (!in_quotes && (*line == ' ' || (*line >= 9 && *line <= 13))) 
        {
            count++; 
            while (*line && (*line == ' ' || (*line >= 9 && *line <= 13))) 
                line++;
            continue; 
        }
        line++; 
    }
    if (*(line - 1) != ' ' && *(line - 1) != 34 && *(line - 1) != 39) 
        count++; 
    return count;
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void define_type(t_token *lst, char *value)
{
    if (ft_strcmp(value, "|") == 0)
        lst->type = TOKEN_PIPE;
    else if (ft_strcmp(value, ">") == 0)
        lst->type = TOKEN_REDIR_OUT;
    else if (ft_strcmp(value, ">>") == 0)
        lst->type = TOKEN_REDIR_APPEND;
    else if (ft_strcmp(value, "<") == 0)
        lst->type = TOKEN_REDIR_IN;
    else if (ft_strcmp(value, "<<") == 0)
        lst->type = TOKEN_REDIR_HEREDOC;
    else if (ft_strcmp(value, "$") == 0)
        lst->type = TOKEN_ENV_VAR;
    else
        lst->type = TOKEN_WORD;       
}

t_token *new_token(char *org,int qute_flg)
{
    t_token *token;
    token = NULL;
    
    token = (t_token *)malloc(sizeof(t_token));
    if (token == NULL)
        return NULL;
    token->value = ft_strdup(org);
    if (token->value == NULL)
    {
        free(token);
        return NULL;
    }
    if (qute_flg)
    {
        if (qute_flg == 39)
            token->type = TOKEND_S_QUOTE;
        else
        token->type = TOKEND_D_QUOTE;
    }
    else
        define_type(token, token->value);
    token->next = NULL;
        return (token);
}

void add_back1(t_token **lst, t_token *new)
{
    t_token *tmp;

    if (!*lst)
    {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

char *get_quote(char *line, char c)
{
    char *res;
    int len = 0;
    char *start = line;
    int i =0;

    while (*line && *line != c)
    {
        len++;
        line++;
    }
    res = malloc(sizeof(char) * (len + 1));
    if (res == NULL)
        return NULL;
    line = start;
    while(i<len)
    {
        res[i++] = *line;
        line++;
    }
    res[len] = '\0';
    return res;
}

void tokenizing_inputs(char *line ,t_token **lst)
{
    int token_len;
    int token_count;
    char c;

    token_count = ft_token_count(line);
    while(*line)
    {
        if (*line == 34 || *line == 39)
        {
            c = *line;
            line++;
            add_back1(lst, new_token(get_quote(line,c), c ));
            while(*line && *line != c)
                line++;
            line++;
        }
        else if (*line != ' ' && (*line < 9 || *line > 13))
        {
            token_len = ft_token_len(line);
            add_back1(lst, new_token(ft_token(line, token_len), 0));
            line += token_len;
        }
        else
            line++;
    }
}
