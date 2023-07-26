/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:48:01 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:09:45 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_permission(char *file, char type)
{
	if (type == 'r' && access(file, F_OK) == 0)
	{
		if (access(file, R_OK) != 0)
			return (ft_error("Permission denied", 1, file, NULL));
	}
	else if (type == 'w' && access(file, F_OK) == 0)
	{
		if (access(file, W_OK) != 0)
			return (ft_error("Permission denied", 1, file, NULL));
	}
	return (ft_error("No such file or directory", 1, file, NULL));
}

int	ft_error(char *msg, int ex, char *dir, char *cmd)
{
	write (2, "minishell: ", 12);
	if (cmd)
	{
		write (2, cmd, ft_strlen(cmd));
		write (2, ": ", 2);
	}
	if (dir)
	{
		write (2, dir, ft_strlen(dir));
		write (2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	g_global.status = ex;
	return (ex);
}
