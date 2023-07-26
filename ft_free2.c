/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:13:57 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:04:48 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i++]);
	}
	free(str);
}

void	free_strings(char *pwd1, char *pwd, char *shlvl, char *envp)
{
	free(pwd1);
	free(pwd);
	free(shlvl);
	free(envp);
}
