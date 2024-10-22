/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:39:43 by fbelkaid          #+#    #+#             */
/*   Updated: 2024/10/22 10:38:45 by fbelkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"
#include<string.h>

t_cmdl *get_cmd() 
{
    t_cmdl *cmd = malloc(sizeof(t_cmdl));
    if (!cmd) return NULL;

    cmd->cmd = NULL; 
    cmd->args = NULL;
    cmd->ldlm = NULL; 
    cmd->next = NULL;

    return cmd;
}

t_cmdl *ft_cmd(char *word, int length) 
{
    t_cmdl *cmd = get_cmd();
    if (!cmd) 
        return NULL;

    cmd->cmd = malloc(length + 1);
    if (!cmd->cmd) {
        free(cmd);
        return NULL;
    }
    strncpy(cmd->cmd, word, length);
    cmd->cmd[length] = '\0'; 
    cmd->next=NULL;

    return cmd;
}
