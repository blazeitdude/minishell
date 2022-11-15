/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:47:44 by ldione            #+#    #+#             */
/*   Updated: 2022/10/15 16:21:28 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

void	init_envi(t_data *sys_data, char **envi)
{
	t_env_list	*new;
	t_env_list	*env_copy;
	int			i;

	env_copy = ft_allocate(1, sizeof(t_env_list));
	env_copy->content = ft_strdup(envi[0]);
	env_copy->next = NULL;
	sys_data->env = env_copy;
	i = 1;
	while (envi[i] && envi)
	{
		new = ft_allocate(1, sizeof(t_env_list));
		new->content = ft_strdup(envi[i]);
		new->next = NULL;
		env_copy->next = new;
		env_copy = new;
		i++;
	}
	init_usrname(sys_data->env);
	init_shlvl(sys_data);
}

void	init_usrname(t_env_list *env)
{
	char		*mid;

	mid = get_env_value("USER", env);
	mid = ft_strjoin(START_C, mid);
	mid = ft_strjoin(mid, END_C);
	g_sig.usrname = mid;
}

void	init_fd(t_data *sys_data)
{
	sys_data->fdin = -1;
	sys_data->fdout = -1;
	sys_data->pid = -1;
	sys_data->pipin = -1;
	sys_data->pipout = -1;
}

void	init_shlvl(t_data *sys_data)
{
	char		*sub_name;
	char		*lvl;
	int			d_lvl;
	t_env_list	*env_copy;

	env_copy = sys_data->env;
	lvl = get_env_value("SHLVL", env_copy);
	d_lvl = get_lvl(lvl) + 1;
	free(lvl);
	while (env_copy)
	{
		sub_name = get_env_name(env_copy->content);
		if (ft_strncmp(sub_name, "SHLVL", BUFF_SIZE) == 0)
		{
			lvl = ft_itoa(d_lvl);
			free(env_copy->content);
			env_copy->content = ft_strjoin("SHLVL=", lvl);
		}
		env_copy = env_copy->next;
	}
}
