/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:48:46 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:15:38 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		write (1, envp[i], ft_strlen(envp[i]));
		write (1, "\n", 1);
		i++;
	}
}

long long	ft_atoi_exit(const char *str)
{
	long long	i;
	long long	sign;
	long long	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	return (ret * sign);
}

int	check_exit(char *nb)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!nb)
		return (0);
	if (ft_atoi_exit(nb) > 9223372036854775807
		|| ft_atoi_exit(nb) < -9223372036854775807)
		return (1);
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	if (nb[i] == '\0')
		return (1);
	while (nb[i])
	{
		if (ft_isdigit(nb[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit2(t_pip *p, t_cmd *cmds, int i)
{
	if (i == 2)
	{
		p->if_exit = 1;
		g_global.status = ft_atoi(cmds->args[1]);
		write(2, "exit\n", 6);
	}
	else
	{
		p->if_exit = 1;
		g_global.status = 0;
		write(2, "exit\n", 6);
	}	
}

void	ft_exit(t_pip *p, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds->args[i])
		i++;
	if (check_exit(cmds->args[1]))
	{
		p->if_exit = 1;
		write(2, "exit\n", 6);
		ft_error("numeric argument required", 255, cmds->args[1], "exit");
		return ;
	}
	if (i > 2)
	{
		write(2, "exit\n", 6);
		ft_error("too many arguments", 1, NULL, "exit");
		return ;
	}
	ft_exit2(p, cmds, i);
}
