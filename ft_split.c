/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:04 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:14:24 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
	}
	return (count);
}

static char	*ft_putword(int len, const char *s, int i, char *str)
{
	int	j;

	j = 0;
	while (len > 0)
	{
				str[j] = s[i - len];
				len--;
				j++;
	}
	str[j] = '\0';
	return (str);
}

static char	**ft_free_strs(char **str, int j)
{
	j -= 1;
	while (j >= 0)
		free(str[j]);
	return (NULL);
}

static char	**ft_splitwords(const char *s, char c, char **str, int words)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	len = 0;
	while (j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		str[j] = malloc(sizeof(char) * len + 1);
		if (!str)
			return (ft_free_strs(str, j));
		ft_putword(len, s, i, str[j]);
		len = 0;
		j++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char	const *s, char c)
{
	int		words;
	char	**str;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	str = malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	if (!(ft_splitwords(s, c, str, words)))
	{
		free(str);
		return (NULL);
	}
	return (str);
}
