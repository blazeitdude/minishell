/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:20:01 by ldione            #+#    #+#             */
/*   Updated: 2022/10/11 19:26:38 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sep_ignore(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>' \
			&& line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

static char	*space_allocate(char *line)
{
	char	*new;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (sep_check(line, i))
			count++;
		i++;
	}
	new = ft_allocate(i + 2 * count + 1, sizeof(char));
	if (!new)
		return (NULL);
	return (new);
}

char	*line_space(char *line)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = space_allocate(line);
	while (line[i] && ret)
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			ret[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && sep_check(line, i))
		{
			ret[j++] = ' ';
			ret[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				ret[j++] = line[i++];
			ret[j++] = ' ';
		}
		else
			ret[j++] = line[i++];
	}
	ret[j] = '\0';
	ft_free(line);
	return (ret);
}
