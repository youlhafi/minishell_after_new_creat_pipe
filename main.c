/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:43:33 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 16:13:25 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*minishell(char *str)
{
	char	*dst;
	int		len;

	dst = NULL;
	len = (ft_strlen(str) - 2);
	if (!dst)
		return (NULL);
	dst = ft_substr(str, 2, len);
	return (dst);
}

void	ft_token(char *str, t_pip *p)
{
	t_cmd	*cmd_list;
	t_list	*new;
	t_list	*lst;
	char	**dst;
	int		i;

	i = 0;
	new = NULL;
	lst = NULL;
	cmd_list = NULL;
	dst = split_string(str, SPACE);
	if (!dst)
		return ;
	while (dst[i])
		ft_add_back_token(&lst, ft_new_token(dst[i++]));
	new = ft_lex(&lst);
	if (if_error(new, dst))
		return ;
	ft_env2(&new, p->envp);
	ft_quotes(&new);
	cmd_list = cmd(ft_lstsize(new));
	parse_input(cmd_list, &new, 0, 0);
	check_pipe(p, cmd_list);
	ft_free_token(lst);
	ft_free_token(new);
	ft_free_list(cmd_list);
	ft_free_str(dst);
}

char	**get_short_env(void)
{
	t_env	env;
	char	**ret;

	env.envp = NULL;
	env.pwd = ft_strdup("PWD=");
	env.pwd1 = getcwd(NULL, 0);
	env.pwd = ft_strjoin_get(env.pwd, env.pwd1);
	env.shlvl = ft_strdup("SHLVL=1");
	env._ = ft_strdup("_=/usr/bin/env");
	env.envp = ft_strjoinspace(env.envp, env.pwd);
	env.envp = ft_strjoinspace(env.envp, env.shlvl);
	env.envp = ft_strjoinspace(env.envp, env._);
	ret = ft_split(env.envp, ' ');
	free(env._);
	free_strings(env.pwd1, env.pwd, env.shlvl, env.envp);
	return (ret);
}

void	main_shell(t_pip p)
{
	char	*str;

	str = NULL;
	while (1)
	{
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, handle_ctrl_b);
		str = readline("minishell>");
		if (str != NULL)
		{
			if (str[0])
			{
				g_global.herdoc = 0;
				ft_token(str, &p);
				add_history(str);
			}
		}
		if (!str)
		{
			printf("exit\n");
			exit(0);
		}
		free(str);
		if (p.if_exit == 1)
			break ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pip	p;

	(void)ac;
	(void)av;
	// rl_catch_signals = 0;
	if (!getenv("PWD"))
		p.envp = get_short_env();
	else
		p.envp = get_env1(env);
	p.export = NULL;
	p.if_exit = 0;
	main_shell(p);
	return (g_global.status);
}
