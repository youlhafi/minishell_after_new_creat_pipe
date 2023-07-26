/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:28:41 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:42:26 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_exist(t_pip *p, char *name)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (name[j] && name[j] != '=' && name[j] != '+')
		j++;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], name, j) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	return_valid(char *name, int i)
{
	if (name[i] == '+')
	{
		if (name[i + 1] == '=')
			return (1);
		else
			return (0);
	}
	return (1);
}

int	if_valid_name(char *name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) == 0)
		return (0);
	if (name[0] == '=')
		return (0);
	if (name[0] >= '0' & name[0] <= '9')
		return (0);
	while (name[i] != '=' && name[i] != '+')
	{
		if ((name[i] >= 0 && name[i] <= 47)
			|| (name[i] >= 58 && name [i] < 61)
			|| (name[i] > 61 && name [i] < 65)
			|| (name[i] > 90 && name [i] < 95)
			|| (name[i] > 122 && name [i] <= 127)
			|| name[i] == 96)
			return (0);
		i++;
	}
	return (return_valid(name, i));
}

int	if_valid_name_export(char *name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) == 0)
		return (0);
	if (name[0] >= '0' & name[0] <= '9')
		return (0);
	while (name[i])
	{
		if (name[i] == '+' || name[i] == '=')
			return (0);
		if ((name[i] >= 0 && name[i] <= 47)
			|| (name[i] >= 58 && name [i] < 61)
			|| (name[i] > 61 && name [i] < 65)
			|| (name[i] > 90 && name [i] < 95)
			|| (name[i] > 122 && name [i] <= 127)
			|| name[i] == 96)
			return (0);
		i++;
	}
	return (1);
}

void	print_export(t_pip *p)
{
	int	i;

	i = 0;
	if (p->envp)
	{
		while (p->envp[i])
		{
			write (1, "declare -x ", 11);
			write (1, p->envp[i], ft_strlen(p->envp[i]));
			write (1, "\n", 1);
			i++;
		}
	}
	i = 0;
	if (p->export)
	{
		while (p->export[i])
		{
			write (1, "declare -x ", 11);
			write (1, p->export[i], ft_strlen(p->export[i]));
			write (1, "\n", 1);
			i++;
		}
	}
}
