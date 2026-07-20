/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:14:36 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/28 21:13:04 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_cmd_exec **lst, t_cmd_exec *new)
{
	t_cmd_exec	*tmp;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			tmp = ft_lstlast(*lst);
			tmp->next = new;
		}
	}
}

size_t	hash_alias_name(char *name)
{
	size_t	hash;

	hash = 5381;
	while (*name)
	{
		hash = ((hash << 5) + hash) + (unsigned char)*name;
		name++;
	}
	return (hash);
}

static void	resize_alias_table(t_hash *table)
{
	t_alias	**new_buckets;
	t_alias	*cur;
	t_alias	*next;
	size_t	new_size;
	size_t	i;
	size_t	idx;

	if (!table || !table->buckets || !table->size)
		return ;
	new_size = table->size * 2;
	new_buckets = ft_malloc(sizeof(t_alias *) * new_size);
	i = 0;
	while (i < new_size)
		new_buckets[i++] = NULL;
	i = 0;
	while (i < table->size)
	{
		cur = table->buckets[i];
		while (cur)
		{
			next = cur->next;
			idx = hash_alias_name(cur->name) % new_size;
			cur->next = new_buckets[idx];
			new_buckets[idx] = cur;
			cur = next;
		}
		i++;
	}
	table->buckets = new_buckets;
	table->size = new_size;
}

void	set_alias(t_hash *table, char *name, char *value)
{
	t_alias	*curr;
	t_alias	*new;
	size_t	idx;

	idx = hash_alias_name(name) % table->size;
	curr = table->buckets[idx];
	while (curr)
	{
		if (!ft_strncmp(curr->name, name, ft_strlen(name) + 1))
		{
			curr->value = value;
			return ;
		}
		curr = curr->next;
	}
	new = ft_malloc(sizeof(t_alias));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = table->buckets[idx];
	table->buckets[idx] = new;
	table->count++;
	if (table->count * 4 >= table->size * 3)
		resize_alias_table(table);
}
