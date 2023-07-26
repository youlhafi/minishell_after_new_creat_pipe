/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:45:36 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 15:25:49 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SPACE 32
# define DOUBLE_QUOT 34
# define SINGLE_QHOT 39
# define NEW_LINE 10
# define TAB 9
# define PIPE 124
# define GREAT_RED '>'
# define LESS_RED '<'
# define BACKSLACH 92
# define OPTION 45

# include<stdio.h>
# include<stdbool.h>
# include<stdlib.h>
# include<unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include<readline/history.h>
# include<readline/readline.h>
# include"libft/libft.h"
# define BUFFER_SIZE 1

typedef struct globa
{
	int	herdoc;
	int	status;
	int	var;
	int	read;
}	t_globa;

t_globa	g_global;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**files;
	char			**type_file;
	char			**type;
	char			**in_file;
	char			**out_file;
	char			**type_out;
	char			**type_in;
	char			*herdoc_lim;
	int				trimmed;
	int				pipe_in;
	int				pipe_out;
	int 			i;
	int				is_argument;
	int				in;
	int				out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_list
{
	char			*content;
	int				trimmed;
	int				is_quote;
	struct s_list	*next;
	struct s_list	*back;
}	t_list;

typedef struct s_pip
{
	char	**envp;
	char	**export;
	int		if_exit;
	int		fd_in;
	int		fd_out;
	int		std_in;
	int		std_out;
	int		nb_cmd;
	char	*path;
	char	**paths;
	char	*cmd;
	int		*fd_pipe;
	int		i;
	int		if_here_doc;
	int		sign_in;
	int		sign_out;
	int		if_n;
	pid_t	*child;
}	t_pip;

typedef struct s_env
{
	char	*pwd;
	char	*pwd1;
	char	*shlvl;
	char	*_;
	char	*envp;
}	t_env;

void		ft_add_back_token(t_list **lst, t_list *new);
t_list		*ft_new_token(void *content);
void		ft_add_front_token(t_list **lst, t_list *new);
char		**split_string(char *s, char c);
int			ft_lstsize(t_list *lst);
int			ft_strcmp(const char *s1, const char *s2);
int			is_quote(char c);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strjoinch(const char *s, char c);
char		*get_env_value(char *variable, char **env);
char		*replace_env_variables(const char *input, char **env);
char		*split_str(char *str, char **env);
int			into_quotes(char *input_string, char character);
t_list		*ft_lex(t_list **lst);
void		parse_input(t_cmd *cmdList, t_list **new, int i, int out);
void		redirection(t_cmd *currentCmd, t_list **tmp, int *out);
void		arguments(t_cmd *currentCmd, t_list **tmp, int *i);
void		command(t_cmd *currentCmd, t_list *tmp);
void		red_tool(t_cmd *currentCmd, t_list **tmp, int *out);
char		*ft_status(char *str);
char		*handle_quotes(char *str);
int			check_quotes(char *str);
int			parsing(t_list **lst);
void		ft_free_token(t_list *token);
void		ft_free_str(char **str);
void		ft_quotes(t_list **lst);
void		ft_env2(t_list **lst, char **env);
int			into(char *str, int n);
int			count_words(const char *s, char c);
t_cmd		*cmd(int len_arg);
int			calc_word(char *str);
char		*ret_quote(char *str, int *i);
char		*ret_arg(char *str, int *i);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strjoinch(const char *s, char c);
void		handle_ctrl_c(int i);
char		*single_dollar(const char *input, char *res, size_t *i);
void		ft_free_list(t_cmd *cmd_list);
char		**get_dst_quotes(char *str);
int			parse_quotes(t_list **lst);
char		*re_arg(char *str, int *i);
char		*re_quote(char *str, int *i);
char		**get_dst(char *str);
int			parse_tool(char **dst);
int			spe_case(char *str);
void		handle_ctrl_b(int i);
char		**get_env1(char **env);
int			if_error(t_list *new, char **dst);
int			is_arg(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoinspace(char *s1, char *s2);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		**ft_split(char	const *s, char c);
char		*get_next_line(int fd);
int			ft_cd(t_pip *p, t_cmd *cmds);
void		ft_echo(t_cmd *cmds, t_pip *p);
void		ft_env(char **envp);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_pwd(t_pip *p);
void		ft_export(t_pip *p, t_cmd *cmds);
int			ft_export_help(t_pip *p, char *new);
void		ft_unset(t_pip *p, t_cmd *cmds);
void		ft_unset_help(t_pip *p, char *cmd);
char		*ft_strdup(const char *s);
void		check_pipe(t_pip *p, t_cmd *cmds);
void		exec_cmd(t_pip *p, char *cmd, t_cmd *cmds);
void		ft_exec(t_pip *p, char **envp, t_cmd *cmds);
int			if_builtins(char *cmd);
void		exec_builtins(t_pip *p, char *trim, t_cmd *cmds);
char		*ft_strtrim(char const *s1, char const *set);
int			check_in(t_pip *p, t_cmd *cmds);
int			check_out(t_pip *p, t_cmd *cmds);
void		close_fd(t_pip *p);
void		multiple_pipe(t_pip *p, t_cmd *cmds, int i);
void		ft_exit(t_pip *p, t_cmd *cmds);
void		ft_read_here_doc(t_pip *p, char *limter);
char		*get_next_line(int fd);
char		*ft_strjoin_get(char *s1, char *s2);
int			ft_error(char *msg, int ex, char *dir, char *cmd);
int			check_cmd(t_pip *p, char *cmd, char **envp, t_cmd *cmds);
char		*get_env(char *get, t_pip *p);
int			check_permission(char *file, char type);
int			if_export(t_pip *p, char *name);
void		ft_unset_export(t_pip *p, char *cmd);
void		ft_unset_help(t_pip *p, char *cmd);
int			if_valid_name_export(char *name);
void		free_double(char **str);
int			if_exist(t_pip *p, char *name);
void		single_cmd(t_pip *p, t_cmd *cmds);
int			open_in_file(t_pip *p, char *file, char *type, char *lim);
int			open_out_file(t_pip *p, char *file, char *type);
void		first_dup(t_pip *p, t_cmd *cmds);
void		last_dup(t_pip *p, t_cmd *cmds);
void		midle_dup(t_pip *p, t_cmd *cmds);
int			open_files(t_pip *p, t_cmd *cmds);
void		set_env(char *name, char *value, t_pip *p);
char		*get_env(char *get, t_pip *p);
int			if_valid_name(char *name);
void		init_p(t_pip *p, t_cmd *cmds);
void		print_export(t_pip *p);
void		free_strings(char *pwd1, char *pwd, char *shlvl, char *envp);

#endif
