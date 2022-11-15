/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:29:05 by ldione            #+#    #+#             */
/*   Updated: 2022/10/15 16:20:06 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sep_check(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;", line[i]))
		return (0);
	else if (quotes(line, i) == 0 && ft_strchr("<>|;", line[i]))
		return (1);
	return (0);
}

int	quotes(char *line, int len)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (line[i] && i != len)
	{
		if (line[i - 1] == '\\' && i > 0)
			;
		else if (line[i] == '\"' && ret == 0)
			ret = 1;
		else if (line[i] == '\'' && ret == 0)
			ret = 2;
		else if (line[i] == '\"' && ret == 1)
			ret = 0;
		else if (line[i] == '\'' && ret == 2)
			ret = 0;
		i++;
	}
	return (ret);
}

int	quotes_check(t_data *sys_data, char **line)
{
	if (quotes(*line, INT_MAX))
	{
		ft_putendl_fd("syntax error: not a closed quotation mark", STDERR);
		ft_clean_str(line);
		*line = NULL;
		sys_data->ret = 2;
		return (1);
	}
	return (0);
}
