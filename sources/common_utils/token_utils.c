/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:12:30 by ldione            #+#    #+#             */
/*   Updated: 2022/10/11 19:17:42 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(t_token *token)
{
	t_token	*prev;

	if (!token || find_type(token, ARG) || find_type(token, COMND))
	{
		prev = find_next_sep(token, NOSKIP);
		if (!prev || find_type(prev, END) || find_type(prev, PIPE))
			return (1);
		return (0);
	}
	return (0);
}
