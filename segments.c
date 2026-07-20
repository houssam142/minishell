#include "minishell.h"

t_seg *new_seg(char *str, t_modes mode)
{
    t_seg *s;

    s = ft_malloc(sizeof(t_seg));
    s->str = str;
    s->mode = mode;
    s->next = NULL;
    return (s);
}

void    add_seg(t_token *tok, t_seg* seg)
{
    t_seg   *tmp;

    if (!tok->segments)
        tok->segments = seg;
    else
    {
        tmp = tok->segments;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = seg;
    }
}
