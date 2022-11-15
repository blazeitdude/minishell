/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:08:11 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/06 16:36:33 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_size(int ret)
{
	char	*tmp;
	int		ret_len;

	tmp = ft_itoa(ret);
	ret_len = ft_strlen(tmp);
	ft_free(tmp);
	return (ret_len);
}

int	get_var_len(const char *arg, int pos, t_env_list *env, int ret)
{
	char	var_name[BUFF_SIZE];
	char	*var_val;
	int		i;

	i = 0;
	if (arg[pos] == '?')
		return (ret_size(ret));
	if (ft_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_val = get_env_value(var_name, env);
	i = ft_strlen(var_val);
	ft_free(var_val);
	return (i);
}

int	arg_alloc_len(const char *arg, t_env_list *env, int ret)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == EXPANSION)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_var_len(arg, i, env, ret);
			if (ft_isdigit(arg[i]) == 0)
			{
				while (arg[i + 1] && is_env_char(arg[i]))
					i++;
			}
			else
				size--;
		}
		size++;
	}
	return (size);
}

char	*get_var_val(const char *arg, int pos, t_env_list *env, int ret)
{
	char	var_name[BUFF_SIZE];
	char	*var_val;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_val = ft_itoa(ret);
		return (var_val);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_val = get_env_value(var_name, env);
	return (var_val);
}
