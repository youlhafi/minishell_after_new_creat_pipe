/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:16 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/10 08:49:18 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_checkset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		i;
	int		start;
	int		end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_checkset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while ((end > start) && ft_checkset(s1[end - 1], set))
		end--;
	new = malloc(sizeof(char) * ((end - start)) + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		new[i] = s1[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}