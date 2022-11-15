/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:39:53 by ldione            #+#    #+#             */
/*   Updated: 2022/10/15 16:19:23 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 1);
	else
		perror(s);
	exit(errno);
}

void	*ft_allocate(size_t num, size_t size)
{
	void	*out;

	out = malloc(size * num);
	if (!out)
		terminate(ERR_OF_ALLOC);
	ft_bzero(out, num * size);
	return (out);
}

int	get_lvl(char *str)
{
	int	sign;
	int	i;
	int	ret;

	(void)sign;
	ret = 0;
	i = 0;
	sign = 1;
	if (str == NULL)
		terminate(ERR_OF_ENV);
	if (str[0] == '-')
		sign = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (0);
		ret = ret * 10 + str[i] - 48;
		i++;
	}
	return (ret);
}

void	free_env(t_env_list *env)
{
	t_env_list	*tmp;

	while (env && env->next)
	{
		tmp = env;
		free(tmp->content);
		free(tmp);
		env = env->next;
	}
	free(env->content);
	free(env);
}

t_token	*free_tokens(t_token *tokens, t_data *sys_data)
{
	if (sys_data->exit != 1)
	{
		while (tokens && tokens->next)
		{
			ft_clean_str(&tokens->content);
			tokens = tokens->next;
			free(tokens->prev);
		}
		if (tokens && tokens->content != NULL)
		{
			ft_clean_str(&tokens->content);
			free(tokens);
			tokens = NULL;
		}
	}
	return (tokens);
}
