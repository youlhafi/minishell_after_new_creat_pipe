/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:50:02 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 15:25:32 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	creat_pipe(t_cmd *cmds)
{
	t_cmd *tmp;
	int	fd[2];

	tmp = cmds;
	while (tmp->next)
	{
		pipe(fd);
		tmp->pipe_out = fd[1];
		tmp->next->pipe_in = fd[0];
		tmp = tmp->next;
	}
}

void	ft_closefd(t_cmd *cmds, int i)
{
	t_cmd *tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->i != i)
		{
			if (tmp->pipe_in != 0)
				close(tmp->pipe_in);
			if (tmp->pipe_out != 0)
				close(tmp->pipe_out);
		}
		tmp = tmp->next;
	}
}

void	parent_wait(t_cmd *cmds, t_pip *p)
{
	// int	j;
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->pipe_in != 0)
			close(tmp->pipe_in);
		if (tmp->pipe_out != 0)
			close(tmp->pipe_out);
		tmp = tmp->next;
	}
	close_fd(p);
	// if (p->if_here_doc)
	// 	unlink(".tmp_file");
	while (waitpid(-1, &g_global.status, 0) != -1)
	{
	// j = 0;
	// while (j <= i)
	// {
	// 	waitpid(p->child[j], &g_global.status, 0);
	// 	j++;
	// }
		if (WIFEXITED(g_global.status))
		{
			g_global.status = WEXITSTATUS(g_global.status);
		}
	}
}

void	ft_child(t_pip *p, char *cmd, t_cmd *cmds, t_cmd *tmp)
{
	pid_t child;

	child = fork();
	if (child == 0)
	{
		if (g_global.status != 0)
			exit(g_global.status);
		 ft_closefd(tmp, p->i);
		if (p->i == 0)
			first_dup(p, cmds);
		else if (p->i == p->nb_cmd - 1)
			last_dup(p, cmds);
		else
			midle_dup(p, cmds);
		exec_cmd(p, cmd, cmds);

		//close_fd(p);
		if (if_builtins(cmd))
			exit(g_global.status);
	}

		
}


void	multiple_pipe(t_pip *p, t_cmd *cmds, int i)
{
	int	count;
	t_cmd *tmp;

	tmp = cmds;
	count = i;
	creat_pipe(cmds);
	p->i = -1;
	p->if_here_doc = 0;
	//p->child = malloc(sizeof(pid_t) * p->nb_cmd);
	while (count > 0 && cmds)
	{
		init_p(p, cmds);
		p->i++;
		if (cmds->cmd && g_global.status == 0)
		{
			g_global.status = check_cmd(p, cmds->cmd, p->envp, cmds);
			// p->child[p->i] = fork();
			ft_child(p, cmds->cmd, cmds, tmp);
			if (!if_builtins(cmds->cmd) && p->cmd)
				free(p->cmd);
		}
		count--;
		cmds = cmds->next;
	}
	parent_wait(tmp, p);

	// free(p->child);
	// free(p->fd_pipe);
}
