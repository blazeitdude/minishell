/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:41:58 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/14 20:40:27 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *arg, t_data *sys_data)
{
	char	*err_msg;
	char	*aux;

	(void)sys_data;
	aux = ft_strjoin("`", arg);
	err_msg = ft_strjoin(aux, "'");
	ft_free(aux);
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	ft_free(err_msg);
}

int	is_valid_val(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
		return (-1);
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (-1);
		i++;
	}
	if (arg[i] && arg[i] == '=')
		return (1);
	return (0);
}

int	add_2_env(char *arg, t_env_list *env)
{
	t_env_list	*new;
	t_env_list	*aux;

	if (env && env->content == NULL)
	{
		env->content = ft_strdup(arg);
		return (0);
	}
	new = malloc(sizeof(t_env_list));
	if (!new)
		return (-1);
	new->content = ft_strdup(arg);
	while (env && env->next && env->next->next)
		env = env->next;
	aux = env->next;
	env->next = new;
	new->next = aux;
	return (0);
}

int	my_export(t_data *sys_data, char **args)
{
	int	i;
	int	ret;
	int	n;

	i = 1;
	if (!args[i])
		return (print_secret(sys_data, 1));
	while (args[i])
	{
		ret = is_valid_val(args[i]);
		if (ret == -1)
			print_error(args[i], sys_data);
		n = is_in_env(args[i], ret, sys_data->env);
		n += is_in_env(args[i], ret, sys_data->secret);
		if (n <= 1)
			if (ret == 1)
				add_2_env(args[i], sys_data->env);
		if (n == 0)
			add_2_env(args[i], sys_data->secret);
		i++;
	}
	return (0);
}
