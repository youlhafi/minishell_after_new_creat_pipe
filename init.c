/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:33:03 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/22 09:09:45 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_p(t_pip *p, t_cmd *cmds)
{
		g_global.status = 0;
		p->sign_in = 0;
		p->sign_out = 0;
		p->fd_in = 0;
		p->fd_out = 1;
		g_global.status = open_files(p, cmds);
		// p->std_in = dup(0);
		// p->std_out = dup(1);
}
