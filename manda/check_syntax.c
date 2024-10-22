/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 03:12:25 by fbelkaid          #+#    #+#             */
/*   Updated: 2024/10/18 16:24:15 by fbelkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int has_unclosed_quotes( char *input)
{
    int i;
    int quote;

    i = 0;
    quote = 0;
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
            if (quote == 0)
                quote = input[i];
            else if (quote == input[i])
                quote = 0;
        }
        i++;
    }
    return (quote);
}

void skip_spaces(char *line, int *i)
{
    while (line[*i] && (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13)))
        (*i)++;
}

void skip_quotes(char *line, int *i)
{
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'' && line[*i] != '\"')
			(*i)++;
	}
}

int check_lg_AND(char *input)
{
    int i;

    i = 0;
	if(input[0] == '&' || input[0] == '|')
		return (1);
    while (input[i++])
    {
		if(input[i]=='\'' || input[i]=='\"')
		skip_quotes(input, &i);
        if (input[i] == '&' && input[i + 1] == '&')
        {
			i++;
            if (input[i + 2] == '\0' || input[i + 2] == '&' || input[i + 2] == '|' || input[i + 2] == '<' || input[i + 2] == '>')
                return (1);
            if (input[i + 2] == ' ' || (input[i + 2] >= 9 && input[i + 2] <= 13))
            {
               skip_spaces(input, &i);
                if (input[i] == '\0' || input[i] == '&' || input[i] == '|' || input[i] == '<' || input[i] == '>')
                    return (1);
            }
        }
		if (input[i]=='&'  && input[i+1]==' ' && input[i+2]=='&')
			return (1);
            //////skip_space problem    
    }
    return (0);
}

int check_lg_OR(char *input)
{
    int i;

    i = 0;
    while (input[i++])
    {
		if(input[i]=='\'' || input[i]=='\"')
		skip_quotes(input, &i);
        if (input[i] == '|' && input[i + 1] == '|')
        {
			i++;
            if (input[i + 2] == '\0' || input[i + 2] == '&' || input[i + 2] == '|' || input[i + 2] == '<' || input[i + 2] == '>')
                return (1);
            if (input[i + 2] == ' ' || (input[i + 2] >= 9 && input[i + 2] <= 13))
            {
                skip_spaces(input, &i);
                if (input[i] == '\0' || input[i] == '&' || input[i] == '|' || input[i] == '<' || input[i] == '>')
                    return (1);
            }
        }
		if (input[i]=='|' && input[i+1]==' ' && input[i+2]=='|')
            return (1); 
            //////skip_space problem
    }
    return (0);
} 

int check_redir_ar(const char *line,int i)
{	
    if (line[i+1]==' ' || (line[i+1]>= 9 && line [i+1]<= 13))
        {
            while (line[i+1] == ' ' || (line[i+1]>= 9 && line [i+1]<= 13))
                i++;
        }
    if (line[i+1] == '\0')
        return (1);
    if (line[i] == '>' && line[i + 1] == '<')
        return (1);
    if (line[i] == '<' && line[i + 1] == '>')
        return (1);
    if (line[i]=='>' || line [i]=='<')
        i++;
    return (0);
}

int has_invalid_redirections(char *input)
{
    int i=0;
    char c;

    if (input[0]== '>'|| input [0] == '<')
        return (1);
    while (input[i++])
    {
        if (input[i]=='\'' || input[i]=='\"')
            skip_quotes(input, &i);
        if (input[i] == '>' || input[i] == '<')
        {
            if(input[i+1] == '\0')
                return (1);
            c = input[i];
            if(input[i+2] =='<'||input[i+2] == '>')
                return(1);
            if(input[i+1] == ' ' || (input[i+1]>= 9 && input[i+1]<= 13))
            {
                skip_spaces(input, &i);
                if (input[i+1] == '\0' || input[i+1] == c)
                    return (1);
            }
            if(input[i+1] == c)
            {
                i = i+2;
                if(check_redir_ar(input,i))
                    return(1);
            }
            else if(input[i+1] != '\0' && input [i+1]!= c)
            {
               if(check_redir_ar(input,i))
                    return(1);
            }
        }
    }
    //////spces problem
    return (0);
}
