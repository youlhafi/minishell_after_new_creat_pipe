/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:38 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/10 08:49:40 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_free(char *s)
{
	free(s);
	return (NULL);
}

static char	*ft_read(int fd, char *s)
{
	char	*buff;
	ssize_t	r_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	r_bytes = 1;
	while (r_bytes != 0)
	{	
		r_bytes = read(fd, buff, BUFFER_SIZE);
		if (r_bytes == -1)
		{
			if (s)
				free(s);
			return (ft_free(buff));
		}
		buff[r_bytes] = 0;
		s = ft_strjoin_get(s, buff);
		if (ft_strchr(s, '\n'))
			break ;
	}
	free (buff);
	return (s);
}

static char	*ft_one_line(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (s[i] == '\0')
		return (NULL);
	while (s[i] != '\n' && s[i])
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (ft_free(s));
	i = 0;
	while (s[i] != '\n' && s[i])
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_left(char *rest)
{
	char	*left;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (rest[i] != '\n' && rest[i])
		i++;
	if (rest[i] == '\0')
		return (ft_free(rest));
	left = malloc(sizeof(char) * (ft_strlen(rest) - i) + 1);
	if (!left)
		return (ft_free(rest));
	i++;
	while (rest[i])
		left[j++] = rest[i++];
	left[j] = '\0';
	free(rest);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    
	rest = ft_read(fd, rest);
	if (!rest)
		return (NULL);
	line = ft_one_line(rest);
	rest = ft_left(rest);
	return (line);
}