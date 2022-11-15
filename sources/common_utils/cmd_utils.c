/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:40:22 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/11 19:28:38 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_environment(const char *val, t_env_list *env)
{
	t_env_list	*new;
	t_env_list	*tmp;

	if (env && env->content == NULL)
	{
		env->content = ft_strdup(val);
		return (0);
	}
	new = malloc(sizeof(t_env_list));
	if (!new)
		return (-1);
	new->content = ft_strdup(val);
	while (env && env->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

char	*env_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_located_env(t_env_list *env, char *args)
{
	char	name[BUFF_SIZE];
	char	name_envi[BUFF_SIZE];

	env_name(name, args);
	while (env && env->next)
	{
		env_name(name_envi, env->content);
		if (ft_strncmp(name, name_envi, 10) == 0)
		{
			ft_free(env->content);
			env->content = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

bool	is_valid_env_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i] == 0 && var[i] != '_'))
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i] == 0 && var[i] != '_'))
			return (false);
		i++;
	}
	return (true);
}
