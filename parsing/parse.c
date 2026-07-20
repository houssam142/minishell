/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:10:34 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/28 22:16:11 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_aliases(t_token **toks, t_hash *aliases)
{
	char	*value;
	t_token	*cur;

	if (!aliases->count)
		return ;
	cur = *toks;
	while (cur)
	{
		value = get_alias_value(aliases, cur->value);
		if (value)
		{
			//remove_empty_tokens();
		}
		cur = cur->next;
	}
}

static int	opers(t_token *toks, t_cmd_exec **env_lst)
{
	t_token	*prev;

	prev = toks;
	while (toks)
	{
		if (toks->type == 'o')
		{
			if (ft_strncmp(toks->value, ">", 2) == 0 || ft_strncmp(toks->value,
					">>", 3) == 0 || ft_strncmp(toks->value, "<", 2) == 0
				|| ft_strncmp(toks->value, "<<", 3) == 0)
				toks->type = 'r';
			else if (prev->type == 'w' && !ft_strncmp(toks->value, "|", 2)
				&& toks->next)
				toks->type = 'c';
			else
			{
				ft_putstr_fd("Minishell: Syntax error: unexpected token '", 2);
				ft_putstr_fd(toks->value, 2);
				return (ft_putstr_fd("'\n", 2), change_stat(env_lst, 2), -1);
			}
		}
		prev = toks;
		toks = toks->next;
	}
	return (0);
}

int	parsing_line(char *line, t_token **toks, t_shell *shell)
{
	t_cmd	*cmd;
	int		status;

	cmd = NULL;
	*toks = NULL;
	status = toks_arr(line, toks);
	if (status == -1 || status == TOK_INCOMPLETE)
		return (status);
	expand_aliases(toks, &shell->aliases);
	if (opers(*toks, &shell->env) == -1)
		return (-1);
	if (toks_to_struct(toks, &cmd, &shell->env) == 0)
		exec(&cmd, shell);
	return (status);
}
