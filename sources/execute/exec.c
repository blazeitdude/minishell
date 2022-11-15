/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:40:19 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/11 15:26:22 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = start->content;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->content;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	executor(t_data *data, t_token *token)
{
	char	**cmd;
	int		i;

	if (data->charge == 0)
		return ;
	cmd = cmd_tab(token);
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expand(cmd[i], data->env, data->ret);
		i++;
	}
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		my_exit(data, cmd);
	else if (cmd && is_builtin(cmd[0]))
		data->ret = exec_cmd(cmd, data);
	else if (cmd)
		data->ret = exec_bin(cmd, data->env, data);
	free_tab(cmd);
	closefd(data->pipin);
	closefd(data->pipout);
	data->pipin = -1;
	data->pipout = -1;
	data->charge = 0;
}
