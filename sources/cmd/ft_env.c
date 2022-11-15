/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:29:58 by cmilagro          #+#    #+#             */
/*   Updated: 2022/09/24 17:25:58 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(t_env_list *env, char **args)
{
	(void)args;
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->content, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->content, 1);
	return (0);
}
