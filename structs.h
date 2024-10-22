/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:49:09 by fbelkaid          #+#    #+#             */
/*   Updated: 2024/10/21 23:33:15 by fbelkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
#include <stdlib.h>

typedef struct s_env
{
	char			*full_form;
	char			*env_var;
	char			*env_value;
	struct s_env	*next;
}					t_env;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN, 
	TOKEN_REDIR_OUT,	
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,  
	TOKEN_ENV_VAR, 
	TOKEND_S_QUOTE,
	TOKEND_D_QUOTE, 
}	t_token_type;

typedef struct s_token 
{
	t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

typedef struct s_redir
{
	char			*redirection;
	char			*direction;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmdl
{
	int				exit;
	char			**args;
	char			*cmd;
	char			*ldlm;
	t_redir			*redir;
	struct s_cmdl	*next;
}					t_cmdl;

typedef struct s_data
{
	t_env	*envl;
	t_cmdl	*cmds;
	int *pipes ;
	int		last_exit;
}					t_data;


#endif
