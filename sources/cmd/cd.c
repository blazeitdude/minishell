/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:14:39 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/07 01:36:54 by otttisss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_env_list *env, const char *var, size_t len)
{
	char	*pwd;
	int		i;
	int		j;
	int		str;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->content, var, len) == 0)
		{
			str = ft_strlen(env->content) - len;
			pwd = malloc(sizeof(char) * str + 1);
			i = 0;
			j = 0;
			while (env->content[i++])
			{
				if (i > (int)len)
					pwd[j++] = env->content[i];
			}
			pwd[j] = '\0';
			return (pwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_pwd(t_env_list *env)
{
	char	path[PATH_MAX];
	char	*pwd;

	if (getcwd(path, PATH_MAX) == NULL)
		return (ERROR);
	pwd = ft_strjoin("OLDPWD=", path);
	if (!pwd)
		return (ERROR);
	if (is_located_env(env, pwd) == 0)
		add_environment(pwd, env);
	ft_free(pwd);
	return (0);
}

static int	change_dir(int opt, t_env_list *env)
{
	int		ret;
	char	*path;

	path = NULL;
	if (opt == 0)
	{
		update_pwd(env);
		path = get_path(env, "HOME", 4);
		if (!path)
			ft_putendl_fd("cd: OLDPWD not set", STDERR);
	}
	else if (opt == 1)
	{
		path = get_path(env, "OLDPWD", 6);
		if (!path)
		{
			ft_putendl_fd("cd: OLDPWD not set", STDERR);
			return (ERROR);
		}
		update_pwd(env);
	}
	ret = chdir(path);
	ft_free(path);
	return (ret);
}

static void	cd_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

int	my_cd(char **args, t_env_list *env)
{
	int	cd;

	if (!args[1])
		return (change_dir(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		cd = change_dir(1, env);
	else
	{
		update_pwd(env);
		cd = chdir(args[1]);
		if (cd < 0)
			cd *= -1;
		if (cd != 0)
			cd_error(args);
	}
	return (cd);
}
