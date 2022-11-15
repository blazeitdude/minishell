/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:15:06 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/14 20:36:27 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

int	exec_cmd(char **cmd, t_data *sys_data)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		ret = my_echo(sys_data, cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ret = my_cd(cmd, sys_data->env);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ret = my_pwd(sys_data, cmd);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		my_exit(sys_data, cmd);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ret = my_env(sys_data->env, cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		my_export(sys_data, cmd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		my_unset(sys_data, cmd);
	return (ret);
}
