/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:14:26 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 08:48:37 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	calc_word(char *str)
{
	int		count_word;
	int		i;
	char	c;

	i = 0;
	count_word = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			c = str[i++];
			while (str[i] != '\0' && str[i] != c)
				i++;
			if (str[i] == c)
				i++;
			count_word++;
		}
		else
		{
			while (str[i] != '\0' && !is_quote(str[i]))
				i++;
			count_word++;
		}
	}
	return (count_word);
}

char	*ret_arg(char *str, int *i)
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
	return (ft_substr(&str[y], 0, len));
}

char	*ret_quote(char *str, int *i)
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
	{
		len++;
		(*i)++;
	}
	return (ft_substr(&str[y], 0, len));
}

char	**get_dst_quotes(char *str)
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
			dst[j] = ret_quote(str, &i);
		else
			dst[j] = ret_arg(str, &i);
		j++;
	}
	dst[j] = NULL;
	return (dst);
}

char	*handle_quotes(char *str)
{
	int		j;
	char	**dst;
	char	*tmp;
	char	*s;

	j = 0;
	s = NULL;
	tmp = NULL;
	dst = get_dst_quotes(str);
	while (dst[j])
	{
		if (is_quote(dst[j][0]))
		{
			tmp = ft_substr(dst[j], 1, ft_strlen(dst[j]) - 1);
			s = ft_strjoin_get(s, tmp);
			free(tmp);
		}
		else
			s = ft_strjoin_get(s, dst[j]);
		j++;
	}
	free(str);
	ft_free_str(dst);
	return (s);
}
