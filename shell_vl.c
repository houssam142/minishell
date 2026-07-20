/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:15:49 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/28 17:18:07 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_dollar(char* str, int* i, t_cmd_exec* env)
{
	char	*name;
	int		start;
	char	*val;

	if (str[*i] != '$')
		return (NULL);
	start = *i + 1;
	if (!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_'
		&& str[*i + 1] == '?')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	(*i)++;
	func(str, i);
	name = ft_substr(str, start, *i - start);
	if (!name)
		return (NULL);
	while (env && ft_strncmp(env->name, name, ft_strlen(name) + 1))
		env = env->next;
	if (!env)
		return (ft_strdup(""));
	val = ft_strdup(env->value);
	return (val);
}

void	append_str(t_buff* buff, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		append_char(buff, str[i]);
		i++;
	}
}

void	init_alias_table(t_hash *alias)
{
	size_t	i;
	
	alias->size = ALIAS_INITIAL_SIZE;
	alias->count = 0;
	alias->buckets = ft_malloc(sizeof(t_alias *) * alias->size);
	i = 0;
	while (i < alias->size)
		alias->buckets[i++] = NULL;
}
