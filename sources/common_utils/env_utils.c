/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:45:11 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/14 20:30:49 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*until_name(char *name, t_env_list *env)
{
	t_env_list	*aux;
	char		*env_name;

	aux = env;
	while (aux && aux->next)
	{
		env_name = get_env_name(aux->content);
		if (ft_strcmp(name, env_name) == 0)
		{
			ft_free(env_name);
			return (aux);
		}
		ft_free(env_name);
		aux = aux->next;
	}
	return (NULL);
}

int	name_in_env(char *name, t_env_list *env)
{
	char		*env_name;
	t_env_list	*aux;

	aux = env;
	while (aux && aux->next)
	{
		env_name = get_env_name(aux->content);
		if (ft_strcmp(name, env_name) == 0)
		{
			ft_free(env_name);
			return (1);
		}
		ft_free(env_name);
		aux = aux->next;
	}
	return (0);
}

int	is_in_env(char *arg, int ret, t_env_list *env)
{
	char		*name;
	t_env_list	*first;

	if (ret == -1)
		return (-1);
	name = get_env_name(arg);
	first = env;
	if (ret == 1 && name_in_env(name, env))
	{
		env = until_name(name, env);
		ft_free(env->content);
		env->content = ft_strdup(arg);
		env = first;
		ft_free(name);
		return (1);
	}
	else if (ret == 0 && name_in_env(name, env))
	{
		ft_free(name);
		return (1);
	}
	ft_free(name);
	return (0);
}

char	**env_2_arr(t_env_list *env)
{
	t_env_list	*aux;
	int			i;
	char		**env_arr;

	aux = env;
	env_arr = malloc(sizeof(char *) * (my_lstsize(aux) + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (aux)
	{
		if (aux->content)
			env_arr[i] = ft_strdup(aux->content);
		i++;
		aux = aux->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

char	*get_value_utils(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i + 1])
		return (ft_strdup(&arg[i + 1]));
	else
		return (ft_strdup(""));
}
