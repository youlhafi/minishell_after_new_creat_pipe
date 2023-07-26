/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:47:29 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:09:45 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_export(t_pip *p, char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (name[j] && name[j] != '=' && name[j] != '+')
		j++;
	if (p->export)
	{
		while (p->export[i])
		{
			if (ft_strncmp(p->export[i], name, j) == 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int	count_export(t_pip *p)
{
	int	i;

	i = 0;
	if (p->export)
		while (p->export[i])
			i++;
	return (i);
}

int	add_to_export(t_pip *p, char *exp)
{
	char	**new;
	int		i;

	i = count_export(p);
	if (if_valid_name_export(exp))
	{
		new = malloc(sizeof (char *) * (i + 2));
		i = 0;
		if (p->export)
		{
			while (p->export[i])
			{
				new[i] = ft_strdup(p->export[i]);
				i++;
			}
		}
		new[i++] = ft_strdup(exp);
		new[i] = NULL;
		if (p->export)
			free_double(p->export);
		p->export = new;
	}
	else
		return (ft_error("not a valid identifier", 1, exp, "export"));
	return (0);
}

void	ft_export_2(t_pip *p, t_cmd *cmds)
{
	int	index;
	int	i;

	i = 0;
	index = 0;
	while (cmds->args[++i])
	{
		if (!ft_strchr(cmds->args[i], '='))
		{
			if (!if_export(p, cmds->args[i]) && !if_exist(p, cmds->args[i]))
				g_global.status = add_to_export(p, cmds->args[i]);
			if (g_global.status == 1)
				index = 1;
		}
		else
		{
			g_global.status = ft_export_help(p, cmds->args[i]);
			if (g_global.status == 1)
				index = 1;
			if (if_export(p, cmds->args[i]))
				ft_unset_export(p, cmds->args[i]);
		}
	}
	if (index == 1)
		g_global.status = 1;
}

void	ft_export(t_pip *p, t_cmd *cmds)
{
	int	i;
	int	index;

	i = 1;
	index = 0;
	if (!cmds->args[i])
		print_export(p);
	else
		ft_export_2(p, cmds);
}
