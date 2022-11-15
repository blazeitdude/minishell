/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:26:25 by cmilagro          #+#    #+#             */
/*   Updated: 2022/10/11 19:34:29 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_array(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return ;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_free(tab[i]);
		i++;
	}
	if (tab)
		ft_free(tab);
}

void	init_secret_envi(t_data *data, char **envi)
{
	t_env_list	*new;
	t_env_list	*env_copy;
	int			i;

	env_copy = malloc(sizeof (t_env_list));
	env_copy->content = ft_strdup(envi[0]);
	env_copy->next = NULL;
	data->secret = env_copy;
	i = 1;
	while (envi && envi[i])
	{
		new = malloc(sizeof (t_env_list));
		new->content = ft_strdup(envi[i]);
		new->next = NULL;
		env_copy->next = new;
		env_copy = new;
		i++;
	}
}

int	my_lstsize(t_env_list *lst)
{
	t_env_list	*p;
	int			i;

	p = NULL;
	p = lst;
	i = 0;
	while (p != NULL)
	{
		p = p->next;
		i++;
	}
	return (i);
}
