/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:11:27 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/28 21:33:51 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_operator_as_token(char *line, int *i, t_token **toks)
{
	char	op[3];

	ft_memset(op, 0, sizeof(op));
	if (line[*i + 1] && line[*i] == '>')
	{
		if (line[*i + 1] == '>')
		{
			op[0] = '>';
			op[1] = '>';
			op[2] = '\0';
			*i += 2;
		}
		else
		{
			op[0] = '>';
			op[1] = '\0';
			(*i)++;
		}
	}
	else if (line[*i + 1] && line[*i] == '<')
	{
		if (line[*i + 1] == '<')
		{
			op[0] = '<';
			op[1] = '<';
			op[2] = '\0';
			*i += 2;
		}
		else
		{
			op[0] = '<';
			op[1] = '\0';
			(*i)++;
		}
	}
	else
	{
		op[0] = line[*i];
		op[1] = '\0';
		(*i)++;
	}
	lstadd_back_tok(toks, lst_new_ele_tok('o', ft_strdup(op)));
}

static char	*join_segments_raw(t_seg *seg)
{
	t_buff	buff;

	buff.buff = NULL;
	buff.len = 0;
	buff.cap = 0;
	while (seg)
	{
		append_str(&buff, seg->str);
		seg = seg->next;
	}
	if (!buff.buff)
		return (ft_strdup(""));
	return (buff.buff);
}

static bool	ft_isoperator(int c)
{
	return (c == '|' || c == '>' || c == '<');
}

void	append_char(t_buff *buf, char c)
{
	char	*new;
	size_t	new_cap;

	if (!buf->buff)
	{
		buf->cap = 8;
		buf->len = 0;
		buf->buff = ft_malloc(buf->cap);
	}
	if (buf->len + 1 >= buf->cap)
	{
		new_cap = buf->cap * 2;
		new = ft_malloc(new_cap);
		ft_strlcpy(new, buf->buff, buf->cap);
		buf->buff = new;
		buf->cap = new_cap;
	}
	buf->buff[buf->len++] = c;
	buf->buff[buf->len] = '\0';
}

static void	flush_seg(t_token *tok, t_buff *buff, t_modes mode, int allow_empty)
{
	t_seg	*segment;
	char	*str;

	if (!tok || !buff)
		return ;
	if (!buff->len && !allow_empty)
		return ;
	if (buff->buff)
		str = ft_strdup(buff->buff);
	else
		str = ft_strdup("");
	segment = new_seg(str, mode);
	add_seg(tok, segment);
	buff->len = 0;
	if (buff->buff)
		buff->buff[0] = '\0';
}

static t_token	*ensure_word(t_token **curr)
{
	if (!*curr)
		*curr = lst_new_ele_tok('w', NULL);
	return (*curr);
}

static void	finalize_word(t_token **toks, t_token **curr)
{
	if (!curr || !*curr)
		return ;
	if ((*curr)->segments)
	{
		(*curr)->value = join_segments_raw((*curr)->segments);
		lstadd_back_tok(toks, *curr);
	}
	*curr = NULL;
}

int	toks_arr(char *line, t_token **toks)
{
	int		i;
	t_modes	mode;
	t_buff	buff;
	t_token	*curr;

	i = 0;
	mode = NORMAL;
	buff.buff = NULL;
	buff.len = 0;
	buff.cap = 0;
	curr = NULL;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (mode == NORMAL)
		{
			if (line[i] == '\'')
			{
				flush_seg(curr, &buff, mode, 0);
				mode = SINGLE_QUOTED;
				i++;
				continue ;
			}
			if (line[i] == '\"')
			{
				flush_seg(curr, &buff, mode, 0);
				mode = DOUBLE_QUOTED;
				i++;
				continue ;
			}
			if (ft_isspace(line[i]))
			{
				flush_seg(curr, &buff, mode, 0);
				finalize_word(toks, &curr);
				i++;
				continue ;
			}
			if (ft_isoperator(line[i]))
			{
				flush_seg(curr, &buff, mode, 0);
				finalize_word(toks, &curr);
				append_operator_as_token(line, &i, toks);
				continue ;
			}
			ensure_word(&curr);
			append_char(&buff, line[i++]);
			continue ;
		}
		if (mode == SINGLE_QUOTED)
		{
			ensure_word(&curr);
			while (line[i] && line[i] != '\'')
				append_char(&buff, line[i++]);
			if (!line[i])
				return (TOK_INCOMPLETE);
			i++;
			flush_seg(curr, &buff, mode, 1);
			mode = NORMAL;
			continue ;
		}
		if (mode == DOUBLE_QUOTED)
		{
			ensure_word(&curr);
			while (line[i] && line[i] != '\"')
				append_char(&buff, line[i++]);
			if (!line[i])
				return (TOK_INCOMPLETE);
			i++;
			flush_seg(curr, &buff, mode, 1);
			mode = NORMAL;
			continue ;
		}
	}
	flush_seg(curr, &buff, mode, 0);
	finalize_word(toks, &curr);
	return (TOK_COMPLETE);
}
