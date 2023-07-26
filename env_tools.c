/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:52:10 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 08:40:59 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_env2(t_list **lst, char **env)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->content, '$')
			&& (!ft_strnstr(tmp->content, "$?", ft_strlen(tmp->content))))
		{
			tmp->content = split_str(tmp->content, env);
			tmp->trimmed = 1;
		}
		tmp = tmp->next;
	}
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoinch(const char *s, char c)
{
	int		len;
	char	*result;

	len = ft_strlen(s);
	result = malloc(sizeof(char) * len + 2);
	if (result == NULL)
		return (NULL);
	ft_strcpy(result, s);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char	*single_dollar(const char *input, char *res, size_t *i)
{
	char	*temp;

	temp = ft_strjoinch(res, input[*i]);
	free(res);
	res = temp;
	(*i)++;
	return (res);
}
