/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:54 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:27:23 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	upgrad_shlvl(t_pip *p)
{
	int		i;
	char	**split;
	int		lvl;
	char	*join;
	char	*it;

	i = 0;
	join = NULL;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], "SHLVL", 5) == 0)
			break ;
		i++;
	}
	split = ft_split(p->envp[i], '=');
	lvl = ft_atoi(split[1]);
	lvl++;
	it = ft_itoa(lvl);
	join = ft_strjoin("SHLVL=", it);
	ft_export_help(p, join);
	free(join);
	free(it);
	free_double(split);
}

void	ft_exec(t_pip *p, char **envp, t_cmd *cmds)
{
	if (ft_strcmp(p->cmd, "./minishell") == 0)
	{
		upgrad_shlvl(p);
	}
	else
	{
		execve(p->cmd, cmds->args, envp);
	}
}
