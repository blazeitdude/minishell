/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:18:44 by ldione            #+#    #+#             */
/*   Updated: 2022/10/11 19:41:12 by otttisss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_realloc(void *inp, int size, int len)
{
	void	*dst;

	free(inp);
	dst = malloc(size * len);
	ft_bzero(dst, len);
	return (dst);
}
