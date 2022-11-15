/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:35:37 by ldione            #+#    #+#             */
/*   Updated: 2022/07/10 17:46:14 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_space(char *line, int *len)
{
	while ((line[*len] == ' ' || line[*len] == '\t' || line[*len] == '\n')
		|| (line[*len] == '\r' || line[*len] == '\v' || line[*len] == '\f'))
		(*len)++;
}
