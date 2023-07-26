/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:19:45 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 13:20:25 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_status(char *str)
{
	char	*dst;
	char	*tmp;
	int		i;

	dst = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "$?", 2))
		{
			tmp = ft_itoa(g_global.status);
			dst = ft_strjoin_get(dst, tmp);
			free(tmp);
			i += 2;
		}
		else
		{
			dst = ft_strjoinch(dst, str[i]);
			i++;
		}
	}
	return (dst);
}

t_cmd	*cmd(int len_arg)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->cmd = NULL;
	new->args = malloc(sizeof(char *) * (len_arg + 1));
	new->files = malloc(sizeof(char *) * (len_arg + 1));
	new->type_file = malloc(sizeof(char *) * (len_arg + 1));
	new->type = malloc(sizeof(char *) * (len_arg + 1));
	new->pipe_in = 0;
	new->pipe_out = 0;
	new->herdoc_lim = NULL;
	new->next = NULL;
	return (new);
}

void	null_it(t_cmd *cmd, int i, int out)
{
	cmd->files[out] = NULL;
	cmd->type_file[out] = NULL;
	cmd->type[out] = NULL;
	cmd->args[i] = NULL;
}

void	parse_input(t_cmd *cmdList, t_list **new, int i, int out)
{
	t_cmd	*current_cmd;
	t_list	*tmp;

	tmp = *new;
	current_cmd = cmdList;
	while (tmp && tmp->content)
	{
		if (!current_cmd->cmd)
			command(current_cmd, tmp);
		if (tmp && tmp->content)
			arguments(current_cmd, &tmp, &i);
		redirection(current_cmd, &tmp, &out);
		if (tmp && (ft_strcmp(tmp->content, "|") == 0))
		{
			null_it(current_cmd, i, out);
			current_cmd->next = cmd(ft_lstsize(*new));
			current_cmd = current_cmd->next;
			tmp = tmp->next;
			out = 0;
			i = 0;
		}
		if (!tmp)
			null_it(current_cmd, i, out);
	}
}
