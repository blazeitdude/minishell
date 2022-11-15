/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:21:44 by ldione            #+#    #+#             */
/*   Updated: 2022/10/15 16:26:06 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	token_verify(t_data *sys_data, t_token *token)
{
	while (token && token->content != NULL)
	{
		if ((find_types(token, "TAI") && (!token->next)) \
		|| (token->next && find_types(token->next, "TAIPE") \
		&& !token->next->next))
		{
			multi_print("Error: unrecognized token `", STDERR, RED, RESET);
			if (token->next)
				multi_print(token->next->content, STDERR, "'", NULL);
			else
				multi_print("newline", STDERR, "'", NULL);
			sys_data->ret = 258;
			return (0);
		}
		if (find_types(token, "PE") && (find_types(token->prev, "TAIPE") \
		|| !token->next || !token->prev))
		{
			ft_putstr_fd("Error: unrecognized token '", STDERR);
			multi_print(token->content, STDERR, "'", NULL);
			sys_data->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

static char	*enter_line(int ret)
{
	char	*console_ln;

	if (ret == 1)
		ft_putstr_fd("\033[47;31m🌋 \033[0m", STDERR);
	else
		ft_putstr_fd("\033[47;31m🏔 \033[0m", STDERR);
	console_ln = readline(g_sig.usrname);
	add_history(console_ln);
	return (console_ln);
}

static t_token	*check_and_shake(char *line, t_data *sys_data)
{
	t_token	*prev;
	t_token	*next;
	t_token	*token;

	prev = NULL;
	next = NULL;
	line = line_space(line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	sys_data->tokens = tokenization(line, prev, next);
	token = sys_data->tokens;
	shake_tokens(sys_data, prev, token);
	if (g_sig.sigint == 1)
		sys_data->ret = g_sig.exit_status;
	else
		sys_data->ret = sys_data->ret;
	return (sys_data->tokens);
}

int	receiver(t_data *sys_data)
{
	char	*console_ln;
	t_token	*token;

	signal(SIGQUIT, &signal_sigquit);
	signal(SIGINT, &signal_sigint);
	console_ln = enter_line(sys_data->ret);
	if (console_ln == NULL)
	{
		sys_data->exit = 1;
		ft_putendl_fd("exit", STDERR);
		return (1);
	}
	if (quotes_check(sys_data, &console_ln))
		return (1);
	token = check_and_shake(console_ln, sys_data);
	while (token)
	{
		if (find_type(token, ARG))
			classification(token, 0);
		token = token->next;
	}
	return (0);
}
