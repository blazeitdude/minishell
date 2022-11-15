/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:12:49 by ldione            #+#    #+#             */
/*   Updated: 2022/10/15 16:17:32 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "errors.h"
# include <signal.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <stdbool.h>

# define EMPTY				0
# define COMND				1
# define ARG				2
# define TRUNC				3
# define APPEND				4
# define INPUT				5
# define PIPE				6
# define END				7
# define BUFF_SIZE			4096
# define RED				"\033[0;31m"
# define START_C			"\033[47;31m"
# define END_C				"$:\033[0m "
# define RESET				"\033[0m"
# define STDIN 				0
# define STDOUT 			1
# define STDERR 			2
# define SKIP				1
# define NOSKIP 			0
# define ERROR				1
# define SUCCESS			0
# define EXPANSION			-36
# define CMD_NOT_FOUND  	127
# define CMD_NOT_EXECUTABLE 126

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
	pid_t	pid;
	char	*usrname;
	char	*usrend;
	int		exit_status;
}	t_sig;

typedef struct s_token
{
	char				*content;
	int					type;
	struct s_token		*next;
	struct s_token		*prev;	
}	t_token;

typedef struct s_env_list
{
	char				*content;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_data
{
	t_env_list			*env;
	t_env_list			*secret;
	t_token				*tokens;
	char				*working_dir;
	char				*old_dir;
	int					exit;
	int					ret;
	int					stdin;
	int					stdout;
	int					fdin;
	int					fdout;
	int					pid;
	int					parent;
	int					last;
	int					pipin;
	int					pipout;
	int					no_exec;
	int					charge;
}	t_data;

typedef struct s_expand
{
	char	*new_arg;
	int		i;
	int		j;
}	t_expand;

int			add_environment(const char *val, t_env_list *env);
int			arg_alloc_len(const char *arg, t_env_list *env, int ret);
void		classification(t_token *token, int sep);
int			check_eof(char *input_line);
void		closefd(int fd);
void		close_inout(t_data *data);
int			create_pipes(t_data *data);
char		*env_name(char *dest, const char *src);
char		*env_to_string(t_env_list *list);
int			exec_cmd(char **cmd, t_data *data);
int			exec_bin(char **args, t_env_list *env, t_data *data);
void		executor(t_data *data, t_token *token);
int			errmsg_cmd(char *cmd, char *detail, char *err_msg, int nb_err);
char		*expand(char *arg, t_env_list *env, int ret);
char		**env_2_arr(t_env_list *env);
void		*ft_allocate(size_t num, size_t size);
void		free_env(t_env_list *env);
void		free_str_array(char **strs);
void		free_tab(char **tab);
t_token		*find_next_sep(t_token *token, int flag);
t_token		*find_prev_sep(t_token *token, int flag);
int			find_type(t_token *token, int type);
t_token		*free_tokens(t_token *tokens, t_data *sys_data);
int			find_types(t_token *token, char *type);
char		*get_env_name(char *str);
char		*get_env_value(char *name, t_env_list *env);
int			get_env_var_index(char *env, char *var);
char		*get_var_val(const char *arg, int pos, t_env_list *env, int ret);
char		*get_value_utils(char *arg);
int			get_lvl(char *str);
int			has_type(t_token *token, int type);
int			has_pipe(t_token *token);
void		init_envi(t_data *sys_data, char **envi);
void		init_secret_envi(t_data *data, char **envi);
void		init_fd(t_data *sys_data);
void		init_shlvl(t_data *sys_data);
void		init_usrname(t_env_list *env);
void		init_signal(void);
void		input(t_data *data, t_token *token);
int			is_located_env(t_env_list *env, char *args);
int			is_valid(t_token *token);
int			is_valid_val(char *arg);
int			is_builtin(char *cmd);
int			is_env_char(int c);
int			is_in_env(char *arg, int ret, t_env_list *env);
int			my_echo(t_data *data, char **args);
int			my_pwd(t_data *data, char **args);
int			my_cd(char **args, t_env_list *env);
void		my_exit(t_data *data, char **command);
int			my_env(t_env_list *env, char **args);
int			my_export(t_data *data, char **args);
int			my_unset(t_data *data, char **args);
int			my_lstsize(t_env_list *lst);
void		multi_print(char *s, int fd, char *start, char *end);
t_token		*next_type(t_token *token, int type, int skip);
t_token		*next_run(t_token *token, int skip);
int			quotes(char *line, int len);
int			quotes_check(t_data *sys_data, char **line);
int			print_secret(t_data *data, int fd);
int			receiver(t_data *sys_data);
void		redirect(t_data *data, t_token *token, int type);
void		reset_std(t_data *data);
int			sep_check(char *line, int i);
int			sep_ignore(char *line, int i);
void		signal_sigint(int sig_code);
void		signal_sigquit(int sig_code);
void		signal_init(void);
void		shake_tokens(t_data *sys_data, t_token *prev, t_token *token);
void		shell_include(t_data *data);
int			strisnum(const char *str);
t_token		*tokenization(char *line, t_token *prev, t_token *next);
int			token_verify(t_data *sys_data, t_token *token);
char		*line_space(char *line);

extern t_sig	g_sig;
#endif