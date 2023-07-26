/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:12:54 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/21 21:01:21 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_quote(char c)
{
	if (c == DOUBLE_QUOT || c == SINGLE_QHOT)
		return (1);
	return (0);
}

int	skip_quote(const char *s, int i)
{
	char	quote;

	quote = s[i];
	i++;
	if (s[i] != quote)
	{
		while (s[i])
		{
			if (s[i] == quote && s[i + 1] == SPACE)
				break ;
			i++;
		}
	}
	if (s[i] == quote)
		i++;
	return (i);
}

int	skip(const char *s, int i)
{
	char	quote;

	while (s[i] && s[i] != SPACE)
	{
		if (is_quote(s[i]))
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

int	count_words(const char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			i = skip_quote(s, i);
			count++;
		}
		else if (s[i] != c && s[i] != '\t')
		{
			i = skip(s, i);
			count++;
		}
		else
			i++;
	}
	return (count);
}

int	into(char *str, int n)
{
	int		first;
	int		second;
	char	c;

	first = 0;
	second = 0;
	if (str[n] == DOUBLE_QUOT)
		c = SINGLE_QHOT;
	else if (str[n] == SINGLE_QHOT)
		c = DOUBLE_QUOT;
	while (str[first] && str[first] != c)
		first++;
	second = first + 1;
	while (str[second] && str[second] != c)
		second++;
	if (n > first && n + 1 > first)
	{
		if (n < second && n + 1 < second)
			return (0);
	}
	return (1);
}
