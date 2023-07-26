/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:48:19 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:29:27 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home(t_pip *p)
{
	char	*pwd;

	if (!get_env("HOME", p))
		return (ft_error("HOME not set", 1, NULL, "cd"));
	pwd = getcwd(NULL, 0);
	set_env("OLDPWD=", pwd, p);
	free(pwd);
	pwd = ft_strdup(get_env("HOME", p));
	chdir(pwd);
	set_env("PWD=", pwd, p);
	free(pwd);
	return (0);
}

int	cd_oldpwd(t_pip *p)
{
	char	*pwd;
	char	*pwd1;

	pwd = ft_strdup(get_env("OLDPWD", p));
	if (pwd == NULL)
		return (ft_error("OLDPWD not set", 1, NULL, "cd"));
	pwd1 = getcwd(NULL, 0);
	set_env("OLDPWD=", pwd1, p);
	free(pwd1);
	chdir(pwd);
	set_env("PWD=", pwd, p);
	ft_pwd(p);
	free(pwd);
	return (0);
}

int	change_env(t_pip *p, t_cmd *cmds)
{
	char	*pwd;
	char	*pwd1;

	if (access(cmds->args[1], X_OK) != 0)
		return (ft_error("Permission denied", 1, cmds->args[1], "cd"));
	pwd1 = get_env("PWD", p);
	set_env("OLDPWD=", pwd1, p);
	chdir(cmds->args[1]);
	pwd = getcwd(NULL, 0);
	set_env("PWD=", pwd, p);
	free(pwd);
	return (0);
}

int	cd_error(t_pip *p, t_cmd *cmds)
{
	char	*pwd;

	if (get_env("PWD", p) == NULL)
		return (1);
	if (ft_strrchr(get_env("PWD", p), '.'))
	{
		pwd = ft_strdup(get_env("OLDPWD", p));
		if (chdir(pwd) == -1)
			chdir(cmds->args[1]);
		set_env("PWD=", pwd, p);
		free(pwd);
		return (0);
	}
	write (2, "cd: error retrieving current directory: getcwd: cannot", 55);
	write(2, " access parent directories: No such file or directory\n", 55);
	pwd = ft_strdup(get_env("PWD", p));
	pwd = ft_strjoin_get(pwd, "/..");
	set_env("PWD=", pwd, p);
	free(pwd);
	return (1);
}

int	ft_cd(t_pip *p, t_cmd *cmds)
{
	int		acc;
	char	*pwd;

	if (!cmds->args[1])
		return (cd_home(p));
	else if (ft_strcmp(cmds->args[1], "-") == 0)
		return (cd_oldpwd(p));
	else if (ft_strcmp(cmds->args[1], "~") == 0)
		return (cd_home(p));
	else
	{
		acc = access(cmds->args[1], F_OK);
		pwd = getcwd(NULL, 0);
		if (pwd == NULL && g_global.status == 1
			&& (ft_strcmp(cmds->args[1], "..") == 0))
			return (cd_error(p, cmds));
		else
			if (acc != 0)
				return (ft_error("no such file or directory", 1,
						cmds->args[1], "cd"));
		return (free(pwd), change_env(p, cmds));
	}
	return (0);
}
