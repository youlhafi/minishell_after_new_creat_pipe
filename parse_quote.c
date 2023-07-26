/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:25:56 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 09:21:53 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*re_arg(char *str, int *i)
{
	int		len;
	int		y;

	y = (*i);
	len = 0;
	while (!is_quote(str[*i]) && str[*i])
	{
		(*i)++;
		len++;
	}
	return (ft_substr(str, y, len));
}

char	*re_quote(char *str, int *i)
{
	int		y;
	int		len;
	char	c;

	y = (*i);
	len = 0;
	c = str[*i];
	(*i)++;
	while (str[*i] != c && str[*i])
	{
		(*i)++;
		len++;
	}
	if (str[*i] == c)
		(*i)++;
	return (ft_substr(str, y, len + 2));
}

char	**get_dst(char *str)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char *) * (calc_word(str) + 1));
	while (str[i])
	{
		if (is_quote(str[i]))
			dst[j++] = re_quote(str, &i);
		else if (!is_quote(str[i]))
			dst[j++] = re_arg(str, &i);
	}
	dst[j] = (NULL);
	return (dst);
}

int	parse_tool(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		if (check_quotes(dst[i]))
			return (1);
		i++;
	}
	return (0);
}
