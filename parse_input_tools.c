/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:18:50 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 09:19:50 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	command(t_cmd *currentCmd, t_list *tmp)
{
	if (tmp != NULL && tmp->content && tmp->is_quote == 0)
	{
		if (ft_strnstr(tmp->content, "$?", ft_strlen(tmp->content)))
		{
			currentCmd->trimmed = tmp->trimmed;
			currentCmd->cmd = ft_status(tmp->content);
		}
		else if (ft_strncmp(tmp->content, "quotes",
				ft_strlen(tmp->content)) == 0)
			ft_error("command not found", 127, " ", NULL);
		else
		{
			currentCmd->trimmed = tmp->trimmed;
			currentCmd->cmd = ft_strdup(tmp->content);
		}
	}
}

void	arguments(t_cmd *currentCmd, t_list **tmp, int *i)
{
	while (*tmp != NULL && (*tmp)->content != NULL
		&& (*tmp)->is_quote == 0)
	{
		if (ft_strnstr((*tmp)->content, "$?",
				ft_strlen((*tmp)->content)) != NULL)
		{
			currentCmd->trimmed = (*tmp)->trimmed;
			currentCmd->args[*i] = ft_status((*tmp)->content);
		}
		else
		{
			currentCmd->trimmed = (*tmp)->trimmed;
			currentCmd->args[*i] = ft_strdup((*tmp)->content);
		}
		*tmp = (*tmp)->next;
		(*i)++;
	}
}

void	red_tool(t_cmd *currentCmd, t_list **tmp, int *out)
{
	if ((ft_strcmp((*tmp)->content, ">>") == 0) && (*tmp)->next->content)
	{
		*tmp = (*tmp)->next;
		currentCmd->trimmed = (*tmp)->trimmed;
		currentCmd->files[*out] = ft_strdup((*tmp)->content);
		currentCmd->type_file[*out] = ft_strdup("out");
		currentCmd->type[*out] = ft_strdup("H");
		(*out)++;
		*tmp = (*tmp)->next;
	}
	else if ((ft_strcmp((*tmp)->content, "<<") == 0) && (*tmp)->next->content)
	{
		*tmp = (*tmp)->next;
		currentCmd->trimmed = (*tmp)->trimmed;
		currentCmd->files[*out] = ft_strdup((*tmp)->content);
		currentCmd->type_file[*out] = ft_strdup("in");
		currentCmd->type[*out] = ft_strdup("H");
		currentCmd->herdoc_lim = ft_strdup((*tmp)->content);
		(*out)++;
		*tmp = (*tmp)->next;
	}
}

void	sing_red(t_cmd *currentCmd, t_list **tmp, int *out)
{
	if (*tmp != NULL && (ft_strcmp((*tmp)->content, ">") == 0)
		&& (*tmp)->next->content)
	{
		*tmp = (*tmp)->next;
		currentCmd->trimmed = (*tmp)->trimmed;
		currentCmd->files[*out] = ft_strdup((*tmp)->content);
		currentCmd->type_file[*out] = ft_strdup("out");
		currentCmd->type[*out] = ft_strdup("R");
		(*out)++;
		*tmp = (*tmp)->next;
	}
	else if (*tmp != NULL && (ft_strcmp((*tmp)->content, "<") == 0)
		&& (*tmp)->next->content)
	{
		*tmp = (*tmp)->next;
		currentCmd->trimmed = (*tmp)->trimmed;
		currentCmd->files[*out] = ft_strdup((*tmp)->content);
		currentCmd->type_file[*out] = ft_strdup("in");
		currentCmd->type[*out] = ft_strdup("R");
		(*out)++;
		*tmp = (*tmp)->next;
	}
}

void	redirection(t_cmd *currentCmd, t_list **tmp, int *out)
{
	if (*tmp != NULL && (ft_strcmp((*tmp)->content, ">>") == 0)
		&& (*tmp)->next->content)
		red_tool(currentCmd, tmp, out);
	else if (*tmp != NULL && (ft_strcmp((*tmp)->content, "<<") == 0)
		&& (*tmp)->next->content)
		red_tool(currentCmd, tmp, out);
	else if (*tmp != NULL && (ft_strcmp((*tmp)->content, ">") == 0)
		&& (*tmp)->next->content)
		sing_red(currentCmd, tmp, out);
	else if (*tmp != NULL && (ft_strcmp((*tmp)->content, "<") == 0)
		&& (*tmp)->next->content)
		sing_red(currentCmd, tmp, out);
}
