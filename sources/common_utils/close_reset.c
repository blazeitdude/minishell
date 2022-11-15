/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:57:36 by cmilagro          #+#    #+#             */
/*   Updated: 2022/09/24 16:08:47 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closefd(int fd)
{
	if (fd > 0)
		close(fd);
}

void	close_inout(t_data *data)
{
	closefd(data->fdin);
	closefd(data->fdout);
	closefd(data->pipin);
	closefd(data->pipout);
}

void	reset_std(t_data *data)
{
	dup2(data->stdin, STDIN);
	dup2(data->stdout, STDOUT);
}
