/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:44 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 11:55:16 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_fd(t_pip *p, char *save, char *line)
{
	int	fd_tmp;

	fd_tmp = open(".tmp_file", O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(fd_tmp, save, ft_strlen(save));
	close(fd_tmp);
	free(save);
	p->fd_in = open(".tmp_file", O_RDONLY);
	if (p->fd_in < 0)
		unlink(".tmp_file");
	if (line)
		free(line);
}

void	handle_her_doc(int sign)
{
	if (sign == SIGINT)
	{
		g_global.herdoc = 1;
		g_global.var = dup(0);
		close(0);
	}
}

void	ft_read_here_doc(t_pip *p, char *limter)
{
	char	*line;
	char	*save;

	line = NULL;
	save = NULL;
	signal(SIGINT, handle_her_doc);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
		{
			if (g_global.herdoc == 1)
			{
				p->sign_in = 1;
				dup2(g_global.var, 0);
				if (save)
					free(save);
				return ;	
			}
			break ;
		}
		if (!ft_strcmp(limter, line))
			break ;
		save = ft_strjoin_get(save, line);
		save = ft_strjoin_get(save, "\n");
		free(line);
	}
	write_fd(p, save, line);
}
