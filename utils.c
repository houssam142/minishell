/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:16:12 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/27 23:38:26 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell()
{
	printf("Welcome to my minishell\n");
}

char	*join_with_newline(char *cmd, char *next)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(cmd, "\n");
	res = ft_strjoin(tmp, next);
	return (res);
}

