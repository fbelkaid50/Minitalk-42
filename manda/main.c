/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:21:26 by fbelkaid          #+#    #+#             */
/*   Updated: 2024/10/22 11:42:22 by fbelkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_line(void)
{
	char *line;
	int i ;

	i = 0;
	line = readline("\033[1;35mminishell ~ \033[0;37m");
	while(line && line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if(line == NULL)
		exit (0);
	if(line[i] == '\0' || line[i]=='\n')
	{
		free(line);
		return (NULL);
	}
	else
	{
		add_history(line);
		i=0;
		while(line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
			i++;
	}
	return(line);
}

void show_prompt(int quote )
{
    char *line;
    int len;

    while(1)
    {
        line = readline(quote == 39 ? "\033[1;35m quote> \033[0;37m" : "\033[1;35m dquote> \033[0;37m");
        if (line == NULL)
        {
            exit(0);
        }
        len = ft_strlen(line);
        if (len == 0)
            continue; 
        if ((quote == 39 && line[len-1] == 39) || (quote == 34 && line[len-1] == 34))
            break;
    }
    free(line); 
}

int	check_the_validity(char *input)
{
	if (has_unclosed_quotes(input))
	{
		show_prompt(has_unclosed_quotes(input));
		return (1);
	}
	if (has_invalid_redirections(input))
	{
		printf("invalid redirection \n");
		return (1);
	}
	return (0);
}

void parc_cmnds(char *line,t_token **lst,t_cmdl **line_list) 
{
	char *trimd_line;
	
	trimd_line = ft_strtrim(line ," \t\n\v\f\r");
	if (!trimd_line)
		return  ;
	if (check_the_validity(line)) 
	{
		free(trimd_line);
		return  ;
	}
	tokenizing_inputs(trimd_line,lst);
	if (!*lst)
	{
		free(trimd_line);
		return ;
	}
	parce_line(lst,line_list);
	return ; 
}

const char* tokenTypeToString(t_token_type type) 
{
    switch(type) 
	{
        case TOKEN_ENV_VAR: return "TOKEN_ENV_VAR";
        case TOKEN_PIPE : return " TOKEN_PIPE";
		case TOKEN_REDIR_APPEND: return "TOKEN_REdir_append";
		case TOKEN_REDIR_HEREDOC: return "TOKEN_REDIR_HEREDOC";
		case TOKEND_S_QUOTE 	: return "TOKEND_S_QUOTE";
		case TOKEND_D_QUOTE : return "TOKEND_D_QUOTE";
		case TOKEN_REDIR_IN : return "TOKEN_REDIR_IN";
		case TOKEN_REDIR_OUT : return "TOKEN_REDIR_OUT";
        default: return "TOKEN_WORD";
    }
}

int main (int ac , char **av, char **env_origin)
{
	(void)ac;
	(void)av;
	char *line;
	(void)env_origin;
	t_token **lst;
	t_cmdl **line_list;

	lst = (t_token **)malloc(sizeof(t_token *));
	line_list = (t_cmdl **)malloc(sizeof(t_cmdl *));
	// (*line_list)->redir= (t_redir*)(malloc(sizeof(t_redir)));


	while(1)
	{
		handell_sig();
		line = get_line();
		if(line != NULL)
		{
			 parc_cmnds(line,lst,line_list) ;
			free(line);
		}
		while (*lst)
		{
			printf("value : %s\n",(*lst)->value);
			printf("type : %s\n",tokenTypeToString((*lst)->type));
			*lst = (*lst)->next;
		}
		while(*line_list)
		{
			printf("cmd : %s\n",(*line_list)->cmd);
			printf("args : %s\n",(*line_list)->ldlm) ;
			// printf("direction :%s\n",(*line_list)->redir->direction);
			// printf("redirection  :%s\n",(*line_list)->redir->redirection);
			*line_list = (*line_list)->next;
		}
	}
	
	return(0);
}
