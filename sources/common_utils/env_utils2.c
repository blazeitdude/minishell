/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:30:38 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/14 20:32:03 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **env_arr, int env_len)
{
	char	*aux;
	int		sorted;
	int		i;

	sorted = 0;
	while (env_arr && sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(env_arr[i], env_arr[i + 1]) > 0)
			{
				aux = env_arr[i];
				env_arr[i] = env_arr[i + 1];
				env_arr[i + 1] = aux;
				sorted = 0;
			}
			i++;
		}
		env_len--;
	}
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static char	*ft_msg_aux(char *arg)
{
	char	*value;
	char	*aux;
	char	*msg;

	value = get_value_utils(arg);
	aux = ft_strjoin("", value);
	ft_free(value);
	value = ft_strjoin(aux, "");
	ft_free(aux);
	msg = get_env_name(arg);
	aux = ft_strjoin(msg, "=");
	ft_free(msg);
	msg = ft_strjoin(aux, value);
	ft_free(aux);
	ft_free(value);
	return (msg);
}

static char	*ft_msg(char *arg)
{
	char	*msg;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	while (arg[i++] && flag == 0)
		if (arg[i] == '=')
			flag = 1;
	if (flag == 1)
		msg = ft_msg_aux(arg);
	else
		msg = ft_strdup(arg);
	return (msg);
}

int	print_secret(t_data *data, int fd)
{
	int		i;
	char	**env_arr;
	char	*msg;

	env_arr = env_2_arr(data->secret);
	if (!env_arr)
		return (1);
	sort_env(env_arr, arr_len(env_arr));
	i = 0;
	while (env_arr[i])
	{
		ft_putstr_fd("declare -x ", fd);
		msg = ft_msg(env_arr[i]);
		ft_putendl_fd(msg, fd);
		ft_free(msg);
		i++;
	}
	free_str_array(env_arr);
	return (0);
}
