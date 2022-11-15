/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:52:37 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/15 15:18:04 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	cmderr(char	*path)
{
	DIR	*directory;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	directory = opendir(path);
	multi_print(g_sig.usrname, STDERR, "\033[47;31m🏔 \033[0m", NULL);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && directory == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && directory != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && directory == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && directory == NULL))
		ret = CMD_NOT_FOUND;
	else
		ret = CMD_NOT_EXECUTABLE;
	if (directory)
		closedir(directory);
	closefd(fd);
	return (ret);
}

int	sys_bin(char *path, char **args, t_env_list *env, t_data *sys_data)
{
	char	**env_array;
	char	*ptr;
	int		ret;

	ret = SUCCESS;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		ptr = env_to_string(env);
		env_array = ft_split(ptr, '\n');
		ft_free(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = cmderr(path);
		free_tab(env_array);
		free_tokens(sys_data->tokens, sys_data);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	if (ret == 32256 || ret == 32512)
		ret = ret / 256;
	return (ret);
}

char	*path_join(char *s1, char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_free(tmp);
	return (path);
}

char	*check_directory(char *bin, char *cmd)
{
	DIR				*dir;
	struct dirent	*item;
	char			*path;

	path = NULL;
	dir = opendir(bin);
	if (!dir)
		return (NULL);
	while (1)
	{
		item = readdir(dir);
		if (!item)
			break ;
		if (ft_strcmp(item->d_name, cmd) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(dir);
	return (path);
}

int	exec_bin(char **args, t_env_list *env, t_data *sys_data)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	i = 0;
	ret = CMD_NOT_FOUND;
	while (env && env->content && ft_strncmp(env->content, "PATH=", 5) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (sys_bin(args[0], args, env, sys_data));
	bin = ft_split(env->content, ':');
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = check_directory(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_directory(bin[i++], args[0]);
	if (path != NULL)
		ret = sys_bin(path, args, env, sys_data);
	else
		ret = sys_bin(args[0], args, env, sys_data);
	free_tab(bin);
	ft_free(path);
	return (ret);
}
