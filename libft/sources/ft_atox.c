/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalien <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 19:21:53 by aalien            #+#    #+#             */
/*   Updated: 2022/04/17 19:22:10 by aalien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static unsigned int	ft_pow(unsigned int x, int i)
{
	int	c;

	c = x;
	if (i == 0)
		return (1);
	while (i > 1)
	{
		x *= c;
		i--;
	}
	return (x);
}

static int	checker(char c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 87);
	else if (c >= 'A' && c <= 'F')
		return (c - 55);
	else if (c >= '0' && c <= '9')
		return (c - 48);
	return (-1);
}

unsigned int	ft_atox(const char *s)
{
	int					l;
	unsigned int		answ;

	answ = 0;
	l = ft_strlen(s);
	while (l >= 1)
		answ += checker(*s++) * ft_pow(16, --l);
	return (answ);
}
