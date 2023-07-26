/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:18:04 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 08:48:30 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_quotes(char *str)
{
	int		i;
	int		count;
	char	c;

	count = 0;
	i = 0;
	while (!is_quote(str[i]) && str[i])
		i++;
	c = str[i];
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count % 2 != 0)
		return (1);
	return (0);
}

int	check_inside(char *input)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (input[i])
	{
		if (input[i] == SINGLE_QHOT || input[i] == DOUBLE_QUOT)
			flag = !flag;
		i++;
	}
	if (!flag)
		return (1);
	return (0);
}

int	parse_quotes(t_list **lst)
{
	t_list	*tmp;
	char	**dst;
	int		i;

	tmp = (*lst);
	while (tmp)
	{
		if (ft_strchr(tmp->content, SINGLE_QHOT)
			|| ft_strchr(tmp->content, DOUBLE_QUOT))
		{
			dst = get_dst(tmp->content);
			i = parse_tool(dst);
			ft_free_str(dst);
			if (i)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parsing1(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (ft_strchr(tmp->content, ';'))
		{
			if (!into_quotes(tmp->content, ';'))
				return (1);
		}
		if (!ft_strcmp(tmp->content, "|"))
		{
			if (!tmp->back || !tmp->next
				|| !ft_strcmp(tmp->back->content, "<<")
				|| !ft_strcmp(tmp->back->content, ">")
				|| !ft_strcmp(tmp->back->content, "<")
				|| !ft_strcmp(tmp->back->content, ">>"))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parsing(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	if (parsing1(lst))
		return (1);
	while (tmp)
	{
		if (!ft_strcmp(tmp->content, ">") || !ft_strcmp(tmp->content, "<")
			|| !ft_strcmp(tmp->content, ">>")
			|| (!ft_strcmp(tmp->content, "<<") && !is_quote(tmp->content[0])))
		{
			if (!tmp->next || !ft_strcmp(tmp->next->content, ">>")
				|| !ft_strcmp(tmp->next->content, ">")
				|| !ft_strcmp(tmp->next->content, "<")
				|| !ft_strcmp(tmp->next->content, "<<"))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
