/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:42:30 by cmilagro          #+#    #+#             */
/*   Updated: 2022/09/24 18:32:28 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_type(t_token *token, int type)
{
	while (token)
	{
		if (find_type(token, type))
			return (1);
		token = token->next;
	}
	return (0);
}

int	has_pipe(t_token *token)
{
	while (token && find_type(token, END) == 0)
	{
		if (find_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

t_token	*next_type(t_token *token, int type, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != type)
		token = token->next;
	return (token);
}
