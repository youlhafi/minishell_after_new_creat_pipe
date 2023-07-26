/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:06:41 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 14:12:45 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_quoted_word(char *s, char c, size_t *i)
{
	int		len;

	len = 0;
	while (s[len])
	{
		len++;
		if (s[len] == c && s[len + 1] == SPACE)
			break ;
	}
	(*i) += len;
	if (is_quote(s[*i]))
		(*i)++;
	return (ft_substr(s, 0, len + 1));
}

static char	*copy_word(char *s, char c, size_t *i, int n)
{
	int		len;
	char	quote;

	len = 0;
	while (s[n] != c && s[n])
	{
		if (is_quote(s[n]))
		{
			quote = s[n];
			n++;
			len++;
			while (s[n] && s[n] != quote)
			{
				len++;
				n++;
			}
		}
		len++;
		n++;
	}
	*i += n;
	return (ft_substr(s, 0, len));
}

char	**split_string(char *s, char c)
{
	char	**words;
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	words = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	while (s[i] != '\0')
	{
		if (is_quote(s[i]) && s[i])
			words[j++] = copy_quoted_word(&s[i], s[i], &i);
		else
		{
			if (s[i] && s[i] != c && s[i] != '\t')
				words[j++] = copy_word(&s[i], c, &i, 0);
		}
		if (i >= ft_strlen(s))
			break ;
		else
			i++;
	}
	if (!j)
		return (NULL);
	words[j] = NULL;
	return (words);
}
