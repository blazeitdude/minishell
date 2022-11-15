/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consol_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:17:20 by ldione            #+#    #+#             */
/*   Updated: 2022/10/15 16:26:57 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	signal_sigint(int sig_code)
{
	sig_code = 0;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b \b ", STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("\033[47;31m🌋\033[0m", STDERR);
		ft_putstr_fd(g_sig.usrname, STDERR);
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	signal_sigquit(int sig_code)
{
	char	*code;

	code = ft_itoa(sig_code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(code, STDERR);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	free (code);
}

int	is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int	check_eof(char *input_line)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(input_line))
		if (input_line[i++] == EOF)
			return (1);
	return (0);
}

void	multi_print(char *s, int fd, char *start, char *end)
{
	int		count;

	count = 0;
	if (start)
	{
		while (start[count])
			write(fd, &start[count++], 1);
	}
	count = 0;
	if (s && fd)
	{
		while (s[count])
			write(fd, &s[count++], 1);
	}
	count = 0;
	if (end)
	{
		while (end[count])
			write(fd, &end[count++], 1);
	}
}
