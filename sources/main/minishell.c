/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:13:28 by ldione            #+#    #+#             */
/*   Updated: 2022/10/20 17:29:15 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

int	main(int argc, char **argv, char **env)
{
	t_data	sys_data;

	rl_catch_signals = 0;
	(void)argc;
	(void)argv;
	sys_data.stdin = dup(STDIN);
	sys_data.stdout = dup(STDOUT);
	sys_data.ret = 0;
	sys_data.exit = 0;
	sys_data.no_exec = 0;
	init_fd(&sys_data);
	init_envi(&sys_data, env);
	init_secret_envi(&sys_data, env);
	while (sys_data.exit == 0)
	{
		init_signal();
		if (receiver(&sys_data))
			continue ;
		if (sys_data.tokens != NULL && token_verify(&sys_data, sys_data.tokens))
			shell_include(&sys_data);
		free_tokens(sys_data.tokens, &sys_data);
	}
	free_env(sys_data.env);
	free_env(sys_data.secret);
	return (sys_data.ret);
}
