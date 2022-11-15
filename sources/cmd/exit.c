/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:35 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/14 20:40:40 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exit(t_data *sys_data, char **command)
{
	sys_data->exit = 1;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (command[1] && !strisnum(command[1]))
	{
		sys_data->ret = 2;
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(command[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	else if (command[1] && command[2])
	{
		sys_data->ret = 1;
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
	}
	else if (command[1])
		sys_data->ret = ft_atoi(command[1]) % 256;
	else
		sys_data->ret = 0;
}
