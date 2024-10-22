/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_Wredir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:19:23 by fbelkaid          #+#    #+#             */
/*   Updated: 2024/10/22 11:42:09 by fbelkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_back(t_cmdl **lst, t_cmdl *cmnd) 
{
    if (!*lst) 
    {
        *lst = cmnd;
        return;
    }
    t_cmdl *tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = cmnd; 
}

void initialize_redir(t_cmdl **redir, char *word, char *c) 
{
    (*redir)->redir = malloc(sizeof(t_redir));
    if (!redir)
        return ;

    (*redir)->redir->direction = ft_strdup(word); 
    (*redir)->redir->redirection = ft_strdup(c);
    (*redir)->next = NULL;
}

void  parce_redir_in_word(char *word, t_cmdl **cmnds,int flag) 
{ 
    int i;
    t_cmdl *tmp;

    i = -1;
    flag =1;
    while (word[++i])
     {
        if(word[i] == '<' || word[i+1]=='\0') 
        {
            i++;
            while(word[i] == '<')
                i++;
            tmp= ft_cmd(word, i -1);
            add_back(cmnds, tmp);
            initialize_redir(cmnds, word + i, "<");
            if(!tmp)
                printf("error\n");
            (*cmnds)->ldlm = ft_strdup("<");
            break;
        }
    }
    return ;
}
void  parce_redir_out_word(char *word, t_cmdl **cmnds,int flag) 
{ 
    int i;
    t_cmdl *tmp;

    i = -1;
    flag =1;
    while (word[++i])
     {
        if(word[i] == '>' || word[i+1]=='\0') 
        {
            i++;
            while(word[i] == '>')
                i++;
            tmp= ft_cmd(word, i -1);
            add_back(cmnds, tmp);
            initialize_redir(cmnds, word + i, ">");
            if(!tmp)
                printf("error\n");
            (*cmnds)->ldlm = ft_strdup(">");
            break;
        }
    }
    return ;
}
void  parce_redir_append_word(char *word, t_cmdl **cmnds,int flag) 
{ 
    int i;
    t_cmdl *tmp;

    i = -1;
    flag =1;
    while (word[++i])
     {
        if((word[i] == '>' && word[i+1] == '>' )|| word[i+1]=='\0') 
        {
            i=i+2;
            while(word[i] == '>')
                i++;
            tmp= ft_cmd(word, i -2);
            add_back(cmnds, tmp);
            initialize_redir(cmnds, word + i, ">>");
            if(!tmp)
                printf("error\n");
            (*cmnds)->ldlm = ft_strdup(">>");
            break;
        }
    }
    return ;
}

void  parce_pipe_word(char *word, t_cmdl **cmnds,int flag) 
{ 
    int i;
    t_cmdl *tmp;
    
    i = -1;
    flag =1;
    while (word[++i])
    {
        if(word[i] == '|'|| word[i+1]=='\0') 
        {
            tmp= ft_cmd(word,i);
            if(!tmp)
                printf("error\n");
            add_back(cmnds,tmp);
            (*cmnds)->ldlm=ft_strdup("|");
            free(tmp);
            break;
        }
    }
    tmp = ft_cmd(word+i+1,ft_strlen(word) -ft_strlen((*cmnds)->cmd));
    add_back(cmnds,tmp);
    free(tmp);
    return ;
}
