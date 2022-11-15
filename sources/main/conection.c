/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:12:19 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/15 14:57:27 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_and_exec(t_data *sys_data, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = find_prev_sep(token, NOSKIP);
	next = find_next_sep(token, NOSKIP);
	pipe = 0;
	if (find_type(prev, TRUNC))
		redirect(sys_data, token, TRUNC);
	else if (find_type(prev, APPEND))
		redirect(sys_data, token, APPEND);
	else if (find_type(prev, INPUT))
		input(sys_data, token);
	else if (find_type(prev, PIPE))
		pipe = create_pipes(sys_data);
	if (next && find_type(next, END) == 0 && pipe != 1)
		redir_and_exec(sys_data, next->next);
	if ((find_type(prev, END) || find_type(prev, PIPE) || !prev)
		&& pipe != 1 && sys_data->no_exec == 0)
		executor(sys_data, token);
}

static void	free_and_exit(t_data *sys_data)
{
	free_tokens(sys_data->tokens, sys_data);
	exit(sys_data->ret);
}

void	shell_include(t_data *sys_data)
{
	t_token	*token;
	int		stat;

	token = next_run(sys_data->tokens, NOSKIP);
	if (find_types(sys_data->tokens, "TAI"))
		token = sys_data->tokens->next;
	while (sys_data->exit == 0 && token)
	{
		sys_data->charge = 1;
		sys_data->parent = 1;
		sys_data->last = 1;
		redir_and_exec(sys_data, token);
		reset_std(sys_data);
		close_inout(sys_data);
		init_fd(sys_data);
		waitpid(-1, &stat, 0);
		stat = WEXITSTATUS(stat);
		if (sys_data->last == 0)
			sys_data->ret = stat;
		if (sys_data->parent == 0)
			free_and_exit(sys_data);
		sys_data->no_exec = 0;
		token = next_run(token, SKIP);
	}
}
