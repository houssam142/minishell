/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:00:18 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/28 14:05:37 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_proc(t_cmd_exec **env_lst, int idx, int *pids)
{
	restore_std_fds();
	waiting(env_lst, idx, pids);
}

pid_t	*allocate_pid_array(t_cmd *cmd)
{
	pid_t	*pids;

	pids = ft_malloc(sizeof(pid_t) * count_cmds(cmd));
	if (!pids)
		exit(EXIT_FAILURE);
	return (pids);
}

void	check_dir_exe(t_cmd *tmp, t_shell *shell, t_cmd **cmd)
{
	if (tmp->redir_error && tmp->redir_error != 3)
	{
		restore_std_fds();
		free_grabage();
		exit(1);
	}
	child_proc(cmd, shell, tmp->id);
}
