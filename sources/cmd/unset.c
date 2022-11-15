/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:53:52 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/14 20:39:48 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(char *arg, t_data *sys_data)
{
	char	*err_msg;
	char	*aux;

	(void)sys_data;
	aux = ft_strjoin("`", arg);
	err_msg = ft_strjoin(aux, "'");
	ft_free(aux);
	ft_putstr_fd("unset: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	ft_free(err_msg);
	return (1);
}

static int	len(char *content)
{
	int	i;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	return (i);
}

static void	free_env_node(char *arg, t_env_list *env)
{
	t_env_list	*aux;
	t_data		*sys_data;

	sys_data = NULL;
	if (ft_strncmp(arg, env->content, len(env->content)) == 0)
	{
		sys_data->env = sys_data->env->next;
		ft_free(env->content);
		ft_free(env);
		env = sys_data->env;
		return ;
	}
	while (env && env->next)
	{
		if (ft_strncmp(arg, env->next->content, len(env->next->content)) == 0)
		{
			aux = env->next->next;
			ft_free(env->next->content);
			ft_free(env->next);
			env->next = aux;
		}
		env = env->next;
	}
}

static void	free_secret_node(char *arg, t_env_list *env)
{
	t_env_list	*aux;
	t_data		*sys_data;

	sys_data = NULL;
	if (ft_strncmp(arg, env->content, len(env->content)) == 0)
	{
		sys_data->secret = sys_data->secret->next;
		ft_free(env->content);
		ft_free(env);
		env = sys_data->secret;
		return ;
	}
	while (env && env->next)
	{
		if (ft_strncmp(arg, env->next->content, len(env->next->content)) == 0)
		{
			aux = env->next->next;
			ft_free(env->next->content);
			ft_free(env->next);
			env->next = aux;
		}
		env = env->next;
	}
}

int	my_unset(t_data *sys_data, char **args)
{
	t_env_list	*env;
	t_env_list	*secret;
	int			i;
	int			flag;

	env = sys_data->env;
	secret = sys_data->secret;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		flag = 0;
		if (is_valid_val(args[i]) == -1)
			flag = print_error(args[i], sys_data);
		if (flag == 0)
		{
			free_env_node(args[i], env);
			free_secret_node(args[i], secret);
		}
		i++;
	}
	return (0);
}
