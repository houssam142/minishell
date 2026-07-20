/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:13:02 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/28 22:42:17 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_expansion(char c)
{
	return ((ft_isalpha(c) || c == '_' || c == '?'));
}

void	func(char *str, int *j)
{
	if (str[*j] == '?')
	{
		(*j)++;
		return ;
	}
	if (ft_isalpha(str[*j]) || str[*j] == '_')
	{
		(*j)++;
		while (str[*j] && (ft_isalnum(str[*j]) || str[*j] == '_'))
			(*j)++;
	}
}

static int	should_remove_token(t_token *tok)
{
	int	i;

	i = 0;
	if (!tok || tok->type == 'r' || tok->type == 'c')
		return (0);
	if (!tok->value)
		return (1);
	if (!tok->value[0])
		return (1);
	while (tok->value[i])
	{
		if (tok->value[i] != ' ' && tok->value[i] != '\t'
			&& tok->value[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	remove_empty_tokens(t_token **toks)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	if (!toks || !*toks)
		return ;
	curr = *toks;
	prev = NULL;
	while (curr && curr->type != 'c')
	{
		next = curr->next;
		if (curr->type == 'r')
			prev = curr;
		else if (should_remove_token(curr))
		{
			if (prev)
				prev->next = next;
			else
				*toks = next;
		}
		else
			prev = curr;
		curr = next;
	}
}

int	is_quoted_word(t_token *tok)
{
	t_seg	*seg;

	if (!tok || tok->type != 'w')
		return (1);
	seg = tok->segments;
	while (seg)
	{
		if (seg->mode != NORMAL)
			return (1);
		seg = seg->next;
	}
	return (0);
}
