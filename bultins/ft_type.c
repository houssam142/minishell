/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 22:33:39 by hounejja          #+#    #+#             */
/*   Updated: 2026/05/27 22:33:40 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flags(char *arg, int *flag)
{
	int	i;

	(void)flag;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-' && !i)
			continue ;
		i++;
	}
	return (0);
}

int	ft_type(t_cmd *cmd, t_cmd_exec **env)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd->args[i])
	{
		if (check_flags(cmd->args[i], &flag) == 1)
		{
			i++;
			continue ;
		}
		i++;
	}
	change_stat(env, 0);
	return (0);
}
