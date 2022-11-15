/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:56:45 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/11 18:24:22 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	varcopy(char *new, const char *val, int pos)
{
	int	i;

	i = 0;
	while (val[i])
		new[pos++] = val[i++];
	return (i);
}

static void	insert_var(t_expand *exp, char *arg, t_env_list *env, int ret)
{
	char	*env_val;

	env_val = get_var_val(arg, exp->j, env, ret);
	if (env_val)
		exp->i += varcopy(exp->new_arg, env_val, exp->i);
	ft_free(env_val);
	if (arg[exp->j] == '?')
		exp->j++;
	if (ft_isdigit(arg[exp->j]) == 0 && arg[exp->j - 1] != '?')
	{
		while (is_env_char(arg[exp->j]) == 1)
			exp->j++;
	}
	else
	{
		if (arg[exp->j - 1] != '?')
			exp->j++;
	}
}

char	*expand(char *arg, t_env_list *env, int ret)
{
	t_expand	ex;
	int			arg_len;

	arg_len = arg_alloc_len(arg, env, ret);
	ex.new_arg = malloc(sizeof(char) * arg_len + 1);
	if (!ex.new_arg)
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.new_arg[ex.i++] = '$';
			else
				insert_var(&ex, arg, env, ret);
		}
		ex.new_arg[ex.i++] = arg[ex.j++];
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}
