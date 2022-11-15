/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:57:18 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/14 20:40:01 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errmsg_cmd(char *cmd, char *detail, char *err_msg, int nb_err)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = false;
	if (cmd != NULL && cmd[0] != '\0')
		msg = ft_strjoin("minishell: ", cmd);
	else
		msg = ft_strdup("minishell");
	msg = ft_strjoin(msg, ": ");
	if (detail != NULL)
	{
		if (ft_strncmp(cmd, "export", 7) == 0
			|| ft_strncmp(cmd, "unset", 6) == 0)
			detail_quotes = true;
		if (detail_quotes)
			msg = ft_strjoin(msg, "`");
		msg = ft_strjoin(msg, detail);
		if (detail_quotes)
			msg = ft_strjoin(msg, "`");
		msg = ft_strjoin(msg, ": ");
	}
	msg = ft_strjoin(msg, err_msg);
	ft_putendl_fd(msg, STDERR);
	free(msg);
	return (nb_err);
}

int	my_pwd(t_data *sys_data, char **args)
{
	char	buff[PATH_MAX];
	char	*cwd;

	(void)args;
	if (sys_data->working_dir)
	{
		ft_putendl_fd(sys_data->working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buff, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	errmsg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
