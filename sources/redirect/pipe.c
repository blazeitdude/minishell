/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:39:08 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/14 20:32:34 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_data *sys_data, t_token *token, int type)
{
	closefd(sys_data->fdout);
	if (type == TRUNC)
		sys_data->fdout = open(token->content,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		sys_data->fdout = open(token->content,
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (sys_data->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->content, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		sys_data->ret = 1;
		sys_data->no_exec = 1;
		return ;
	}
	dup2(sys_data->fdout, STDOUT);
}

void	input(t_data *sys_data, t_token *token)
{
	closefd(sys_data->fdin);
	sys_data->fdin = open(token->content, O_RDONLY, S_IRWXU);
	if (sys_data->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->content, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		sys_data->ret = 1;
		sys_data->no_exec = 1;
		return ;
	}
	dup2(sys_data->fdin, STDIN);
}

int	create_pipes(t_data *sys_data)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		closefd(fd[1]);
		dup2(fd[0], STDIN);
		sys_data->pipin = fd[0];
		sys_data->pid = -1;
		sys_data->parent = 0;
		sys_data->no_exec = 0;
		return (2);
	}
	else
	{
		closefd(fd[0]);
		dup2(fd[1], STDOUT);
		sys_data->pipout = fd[1];
		sys_data->pid = pid;
		sys_data->last = 0;
		return (1);
	}
}
