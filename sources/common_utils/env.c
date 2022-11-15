/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:38:52 by ldione            #+#    #+#             */
/*   Updated: 2022/10/11 19:28:06 by otttisss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (ft_substr(str, 0, i));
}

static char	*get_value(char	*str)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	i += 1;
	ret = ft_allocate(ft_strlen(str) - i + 1, sizeof(char));
	while (str[i] != '\0')
		ret[j++] = str[i++];
	ret[j] = '\0';
	return (ret);
}

char	*get_env_value(char *name, t_env_list *env)
{
	char		*sub_name;
	t_env_list	*env_copy;

	env_copy = env;
	while (env_copy)
	{
		sub_name = get_env_name(env_copy->content);
		if (ft_strncmp(sub_name, name, BUFF_SIZE) == 0)
			return (get_value(env_copy->content));
		free(sub_name);
		env_copy = env_copy->next;
	}
	return (NULL);
}

size_t	env_size(t_env_list *list)
{
	size_t	len;

	len = 0;
	while (list && list->next != NULL)
	{
		if (list->content != NULL)
		{
			len += ft_strlen(list->content);
			len++;
		}
		list = list->next;
	}
	return (len);
}

char	*env_to_string(t_env_list *list)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(sizeof(char) * env_size(list) + 1);
	i = 0;
	while (list && list->next != NULL)
	{
		if (list->content != NULL)
		{
			j = 0;
			while (list->content[j])
			{
				env[i] = list->content[j];
				i++;
				j++;
			}
		}
		if (list->next->next != NULL)
			env[i++] = '\n';
		list = list->next;
	}
	env[i] = '\0';
	return (env);
}
