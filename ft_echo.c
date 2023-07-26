/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:48:24 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/14 13:05:25 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_n(char *str)
{
	int	i;
	int	count;

	i = 1;
	count = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			count ++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}

void	ft_echo(t_cmd *cmds, t_pip *p)
{
	int	i;
	int	index;

	i = 0;
	p->if_n = 1;
	index = 0;
	while (cmds->args[++i])
	{
		if ((ft_strncmp(cmds->args[i], "-n", 2) == 0)
			&& all_n(cmds->args[i]) && index == 0)
			p->if_n = 0;
		else if (ft_strlen(cmds->args[i]) != 0)
		{
			index = 1;
			if (ft_strlen(cmds->args[i]) != 0 && ft_strncmp(cmds->args[i], "~",
					ft_strlen(cmds->args[i])) == 0)
				write(1, get_env("HOME", p), ft_strlen(get_env("HOME", p)));
			else
				write(1, cmds->args[i], ft_strlen(cmds->args[i]));
			if (cmds->args[i + 1])
				write(1, " ", 1);
		}
	}
	if (p->if_n)
		write(1, "\n", 1);
}
