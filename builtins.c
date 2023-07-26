/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 07:52:56 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/15 13:22:20 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *get, t_pip *p)
{
	int	i;

	i = 0;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], get, ft_strlen(get)) == 0)
			return (p->envp[i] + (ft_strlen(get) + 1));
		i++;
	}
	return (NULL);
}

void	set_env(char *name, char *value, t_pip *p)
{
	char	*all;

	if (!value)
		return ;
	all = ft_strjoin(name, value);
	ft_export_help(p, all);
	free(all);
}

void	ft_pwd(t_pip *p)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		if (get_env("PWD", p) == NULL)
			return ;
		write (1, get_env("PWD", p), ft_strlen(get_env("PWD", p)));
		write (1, "\n", 1);
		return ;
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
}
