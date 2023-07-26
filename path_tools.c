/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:50:09 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/10 08:50:10 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_path(char **env)
{
	while (env)
	{
		if (ft_strncmp("PATH=", *env, 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

char	*ft_access(char **paths, char *cmd)
{
	char	*str;
	char	*str1;
	int		i;

	i = 0;
	while (paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		str1 = ft_strjoin(str, cmd);
		free(str);
		if (access(str1, F_OK) == 0)
			return (str1);
		free(str1);
		i++;
	}
	return (NULL);
}
