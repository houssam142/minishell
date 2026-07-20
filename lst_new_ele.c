/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_ele.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:14:26 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/28 00:25:30 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_alias	*lst_new_alias(char *name, char *value)
{
	t_alias	*new_alias;

	new_alias = ft_malloc(sizeof(sizeof(t_alias)));
	new_alias->name = name;
	new_alias->value = value;
	new_alias->next = NULL;
	return (new_alias);
}

t_cmd_exec	*lst_new_ele(char *name, char *value)
{
	t_cmd_exec	*new_ele;

	new_ele = ft_malloc(sizeof(t_cmd_exec));
	new_ele->name = name;
	new_ele->value = value;
	new_ele->meaning = 'e';
	new_ele->status = 0;
	new_ele->next = NULL;
	return (new_ele);
}

t_token	*lst_new_ele_tok(char type, char *value)
{
	t_token	*new_ele;

	new_ele = ft_malloc(sizeof(t_token));
	if (!new_ele)
		return (NULL);
	new_ele->type = type;
	new_ele->value = value;
	new_ele->quote = ft_calloc(sizeof(char), (ft_strlen(value) + 1));
	new_ele->quote[sizeof(char) * ft_strlen(value)] = '\0';
	new_ele->strip = 1;
	new_ele->expanded = 0;
	new_ele->segments = NULL;
	new_ele->next = NULL;
	return (new_ele);
}
