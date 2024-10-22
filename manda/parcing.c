/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 06:13:12 by fbelkaid          #+#    #+#             */
/*   Updated: 2024/10/22 11:42:40 by fbelkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_get_file(char *line)
{
    int i =0 ;
    char *res;
    int j=0;

    while (line[i] && line[i] != '>' && line[i] != '<')
            i++;
        res = malloc(i + 1);
    if(!res)
        return NULL;
    if(line[i] == '>'|| line[i] == '<')
    {
        while(line[i]=='>' || line[i] == ' ')
            i++;
    }
    while(line[i] && (line[i] != ' '|| (line[i]>= 9 && line[i] <= 13)))
        {
            res[j] = line[i];
            j++;
            i++;
        }
        res[j]='\0';
    return (res);
}

void check_word(char *word, t_cmdl **cmnd)
{
    int i ;

    if(!cmnd)
        return ;
    i= -1;
    static int flg = 0;
    while (word[++i])
    {
        if(word[i]=='|' && word[i+1] != '|' && word[i-1] != '|')
            parce_pipe_word(word,cmnd,flg);
       if (word[i]=='<' && word[i+1]!= '<' && word[i-1] != '<') 
           parce_redir_in_word(word,cmnd, flg);
        if(word[i]=='>' && word[i+1] != '>' && word[i-1] != '>')
            parce_redir_out_word(word,cmnd,flg);    
        if(word[i]=='>' && word[i+1] == '>')
            parce_redir_append_word(word,cmnd,flg);
    }
    return ;
}

t_cmdl **parce_line(t_token **lst,t_cmdl **cmnd)
{
    t_token *tmp ;
    
    tmp = *lst;
    while(tmp)
    {
        if(tmp->type == TOKEN_WORD)
            check_word(tmp->value,cmnd);
       tmp = tmp->next;
    }
    
    return cmnd;
}
