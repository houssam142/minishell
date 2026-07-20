#include "../minishell.h"

static void	print_all_aliases(t_hash *alias)
{
	size_t	i;
	t_alias	*curr;

	i = 0;
	curr = NULL;
	if (!alias || !alias->count)
		return ;
	else
	{
		while (i < alias->size)
		{
			curr = alias->buckets[i];
			while (curr)
			{
				printf("alias %s='%s'\n", curr->name, curr->value);
				curr = curr->next;
			}
			i++;
		}
	}
}

char	*get_alias_value(t_hash *table, char *name)
{
	t_alias	*curr;
	size_t	idx;

	if (!table || !table->buckets || !name)
		return (NULL);
	idx = hash_alias_name(name) % table->size;
	curr = table->buckets[idx];
	while (curr)
	{
		if (!ft_strncmp(curr->name, name, ft_strlen(name) + 1))
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

static int	valid_alias_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (1);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (1);
	i = 1;
	while (name && name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	has_equal(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	equal_pos(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '=')
		i++;
	return (i);
}

static void	set_aliases(t_cmd *cmd, t_shell *shell)
{
	char    *name;
	char	*value;
	char	*lookup;
	int		i;
	int		j;

	i = 1;
	lookup = NULL;
	while (cmd->args[i])
	{
		if (!has_equal(cmd->args[i]))
		{
			lookup = get_alias_value(&shell->aliases, cmd->args[i]);
			if (!lookup)
				printf("minishell: alias: %s: not found\n", cmd->args[i]);
			else
				printf("alias %s='%s'\n", cmd->args[i], lookup);
			i++;
			continue;
		}
		j = equal_pos(cmd->args[i]);
		name = ft_substr(cmd->args[i], 0, j);
		value = ft_substr(cmd->args[i], j + 1, ft_strlen(cmd->args[i]));
		if (!valid_alias_name(name))
			set_alias(&shell->aliases, name, value);
		else
			printf("minishell: alias: '%s': is invalid alias name\n", name);
        i++;
    }
}

int ft_alias(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->args[1])
		print_all_aliases(&shell->aliases);
	else
		set_aliases(cmd, shell);
	return (0);
}
