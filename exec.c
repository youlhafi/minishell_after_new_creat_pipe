/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:48:12 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:31:58 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_builtins(char *trim)
{		
	if (ft_strcmp(trim, "export") == 0)
		return (1);
	else if (ft_strcmp(trim, "cd") == 0)
		return (1);
	else if (ft_strcmp(trim, "echo") == 0)
		return (1);
	else if (ft_strcmp(trim, "pwd") == 0)
		return (1);
	else if (ft_strcmp(trim, "unset") == 0)
		return (1);
	else if (ft_strcmp(trim, "env") == 0)
		return (1);
	else if (ft_strcmp(trim, "exit") == 0)
		return (1);
	return (0);
}

void	exec_builtins(t_pip *p, char *trim, t_cmd *cmds)
{
	if (ft_strcmp(trim, "export") == 0)
		ft_export(p, cmds);
	else if (ft_strcmp(trim, "cd") == 0)
		g_global.status = ft_cd(p, cmds);
	else if (ft_strcmp(trim, "echo") == 0)
		ft_echo(cmds, p);
	else if (ft_strcmp(trim, "pwd") == 0)
		ft_pwd(p);
	else if (ft_strcmp(trim, "unset") == 0)
		ft_unset(p, cmds);
	else if (ft_strcmp(trim, "env") == 0)
		ft_env(p->envp);
	else if (ft_strcmp(trim, "exit") == 0)
		ft_exit(p, cmds);
}

void	exec_cmd(t_pip *p, char *cmd, t_cmd *cmds)
{
	if (if_builtins(cmd))
		exec_builtins(p, cmd, cmds);
	else
		ft_exec(p, p->envp, cmds);
}
