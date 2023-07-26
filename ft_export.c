/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:48:53 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/15 08:29:09 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_without_plus(t_pip *p, char *new)
{
	char	**split;
	char	*join;
	int		i;

	join = NULL;
	i = 0;
	split = ft_split(new, '+');
	while (split[i])
	{
		join = ft_strjoin_get(join, split[i]);
		i++;
	}
	free_double(split);
	ft_export_help(p, join);
	free(join);
}

void	ft_unset_env(t_pip *p, char *cmd)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	j = 0;
	i = 0;
	if (!p->envp)
		return ;
	while (cmd[j] && cmd[j] != '=')
		j++;
	while (p->envp[i])
		i++;
	res = malloc(sizeof (char *) * i);
	i = 0;
	k = 0;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], cmd, j) != 0)
			res[k++] = ft_strdup(p->envp[i]);
		i++;
	}
	res[k] = NULL;
	free_double(p->envp);
	p->envp = res;
}

void	replace_new_value(t_pip *p, char *new)
{
	int		i;
	int		j;
	char	*unset;

	i = 0;
	j = 0;
	unset = NULL;
	while (new[i] != '+')
		i++;
	while (p->envp[j])
	{
		if (ft_strncmp(p->envp[j], new, i) == 0)
		{
			unset = ft_strdup(p->envp[j]);
			ft_unset_env(p, unset);
			unset = ft_strjoin_get(unset, &new[i + 2]);
			ft_export_help(p, unset);
			free(unset);
		}
		j++;
	}
}

void	add_to_env(t_pip *p, char *new)
{
	int		i;
	char	**ret;

	i = 0;
	if (if_exist(p, new))
		ft_unset_env(p, new);
	while (p->envp[i])
		i++;
	ret = malloc(sizeof (char *) * (i + 2));
	i = 0;
	while (p->envp[i])
	{
		ret[i] = ft_strdup(p->envp[i]);
		i++;
	}
	ret[i++] = ft_strdup(new);
	ret[i] = NULL;
	free_double(p->envp);
	p->envp = ret;
}

int	ft_export_help(t_pip *p, char *new)
{
	char	*plus;
	char	**split;

	split = ft_split(new, '=');
	if (!split[0])
		return (ft_error("not a valid identifier", 1, new, "export"));
	plus = ft_strchr(split[0], '+');
	free_double(split);
	if (if_valid_name(new))
	{
		if (plus)
		{
			if (if_exist(p, new))
				replace_new_value(p, new);
			else
				add_new_without_plus(p, new);
		}
		else
			add_to_env(p, new);
	}
	else
		return (ft_error("not a valid identifier", 1, new, "export"));
	return (0);
}
