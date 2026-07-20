/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 22:02:56 by hounejja          #+#    #+#             */
/*   Updated: 2026/05/27 22:24:06 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_segments(char *str, t_buff *buff, t_cmd_exec *env)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_valid_expansion(str[i + 1]))
		{
			value = resolve_dollar(str, &i, env);
			if (value)
				append_str(buff, value);
			continue;
		}
		append_char(buff, str[i]);
		i++;
	}
}

char	*expand_toks(t_token *tok, t_cmd_exec *env)
{
	t_seg	*seg;
	t_buff	buff;
	
	buff.buff = NULL;
	buff.len = 0;
	buff.cap = 0;
	seg = tok->segments;
	while (seg)
	{
		if (seg->mode == SINGLE_QUOTED)
			append_str(&buff, seg->str);
		else
			expand_segments(seg->str, &buff, env);
		seg = seg->next;
	}
	if (!buff.buff)	
		return (ft_strdup(""));
	return (buff.buff);
}
