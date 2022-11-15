/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:23:55 by ldione            #+#    #+#             */
/*   Updated: 2022/10/11 19:24:36 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_prev_sep(t_token *token, int flag)
{
	if (flag)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*find_next_sep(t_token *token, int flag)
{
	if (flag)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != COMND)
	{
		token = token->next;
		if (token && token->type == COMND && token->prev == NULL)
			;
		else if (token && token->type == COMND && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

int	find_type(t_token *token, int type)
{
	if (!token)
		return (0);
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	find_types(t_token *token, char *type)
{
	if (ft_strchr(type, ' ') && find_type(token, EMPTY))
		return (1);
	else if (ft_strchr(type, 'C') && find_type(token, COMND))
		return (1);
	else if (ft_strchr(type, 'a') && find_type(token, ARG))
		return (1);
	else if (ft_strchr(type, 'T') && find_type(token, TRUNC))
		return (1);
	else if (ft_strchr(type, 'A') && find_type(token, APPEND))
		return (1);
	else if (ft_strchr(type, 'I') && find_type(token, INPUT))
		return (1);
	else if (ft_strchr(type, 'P') && find_type(token, PIPE))
		return (1);
	else if (ft_strchr(type, 'E') && find_type(token, END))
		return (1);
	return (0);
}
