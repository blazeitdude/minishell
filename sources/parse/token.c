/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:06:50 by ldione            #+#    #+#             */
/*   Updated: 2022/10/15 16:09:18 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shake_tokens(t_data *sys_data, t_token *prev, t_token *token)
{
	while (token)
	{
		prev = find_prev_sep(token, 1);
		if (find_type(token, ARG) && find_types(prev, "TAI"))
		{
			while (is_valid(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			if (prev)
				token->next = prev->next;
			else
			{
				token->next = sys_data->tokens;
				prev = token;
			}
			if (sys_data->tokens->prev)
				sys_data->tokens = sys_data->tokens->prev;
			else
				prev->next = token;
		}
		token = token->next;
	}
}

void	classification(t_token *token, int sep)
{
	if (ft_strncmp(token->content, "", INT_MAX) == 0 && sep == 0)
		token->type = EMPTY;
	else if (ft_strncmp(token->content, ">", INT_MAX) == 0 && sep == 0)
		token->type = TRUNC;
	else if (ft_strncmp(token->content, ">>", INT_MAX) == 0 && sep == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->content, "<", INT_MAX) == 0 && sep == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->content, "|", INT_MAX) == 0 && sep == 0)
		token->type = PIPE;
	else if (ft_strncmp(token->content, ";", INT_MAX) == 0 && sep == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = COMND;
	else
		token->type = ARG;
}

static int	next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

static t_token	*next_token(char *line, int *i, int j)
{
	t_token	*token;
	char	c;

	c = ' ';
	token = ft_allocate(1, sizeof(t_token));
	token->content = ft_allocate(next_alloc(line, i), sizeof(char));
	if (!token || !token->content)
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->content[j++] = line[(*i)++];
		else
			token->content[j++] = line[(*i)++];
	}
	token->content[j] = '\0';
	return (token);
}

t_token	*tokenization(char *line, t_token *prev, t_token *next)
{
	int		i;
	int		sep;

	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = sep_ignore(line, i);
		next = next_token(line, &i, 0);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		classification(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
	ft_clean_str(&line);
}
