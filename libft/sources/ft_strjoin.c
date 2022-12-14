/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:45:52 by ldione            #+#    #+#             */
/*   Updated: 2022/10/11 19:39:59 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *reminder, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!reminder)
	{
		reminder = (char *)malloc(1 * sizeof (char));
		reminder [0] = '\0';
	}
	if (!reminder || !buff)
		return (NULL);
	str = malloc(sizeof (char) * ((ft_strlen(reminder) + ft_strlen(buff)) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	if (reminder)
		while (reminder[++i] != '\0')
			str[i] = reminder[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(reminder) + ft_strlen(buff)] = '\0';
	return (str);
}
