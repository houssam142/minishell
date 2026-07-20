/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:15:30 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/28 22:42:26 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <unistd.h>

# define ALIAS_INITIAL_SIZE 128

#define TOK_INCOMPLETE 1
# define TOK_COMPLETE 0
#define TOK_ERROR -1 

typedef enum e_modes
{
	NORMAL,
	DOUBLE_QUOTED,
	SINGLE_QUOTED
} t_modes;

typedef struct e_seg
{
	char			*str;
	t_modes			mode;
	struct e_seg	*next;
} t_seg;

typedef struct s_gc
{
	void				*data;
	struct s_gc			*next;
}						t_gc;

typedef struct s_token
{
	char				type;
	char				*quote;
	char				*value;
	int					strip;
	int					expanded;
	t_seg				*segments;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd_exec
{
	char				*name;
	char				meaning;
	char				*value;
	int					status;
	struct s_cmd_exec	*next;
}						t_cmd_exec;

typedef struct s_cmd
{
	int					id;
	int					builtin;
	char				**args;
	char				*op;
	char				*op_value;
	int					std_in;
	int					std_in_dup1;
	int					std_out_dup1;
	int					std_out;
	int					std_err;
	int					pipe_in;
	int					path_error;
	int					pipe_out;
	int					pipe;
	char				*path;
	char				delimiter;
	int					redir_error;
	struct s_cmd		*next;
}						t_cmd;


typedef struct s_buff
{
	char *buff;
	size_t	len;
	size_t	cap;
}	t_buff;

typedef struct s_alias
{
	char			*name;
	char			*value;
	struct s_alias	*next;
} t_alias;


typedef struct s_hash
{
	t_alias	**buckets;
	size_t	count;
	size_t	size;
}	t_hash;


typedef struct t_shell
{
	t_cmd_exec	*env;
	t_hash		aliases;
} t_shell;

int						arg_count(t_token **toks, t_cmd *cmd);
int						is_quoted_word(t_token *tok);
size_t					hash_alias_name(char *name);
void					init_alias_table(t_hash *alias);
t_seg					*new_seg(char *str, t_modes mode);
int						count_cmds(t_cmd *cmd);
void					minishell();
t_seg					*new_seg(char *str, t_modes mode);
void				    add_seg(t_token *tok, t_seg* seg);
int						len_till_expansion(char *s, int start_pos);
int						toks_arr(char *line, t_token **toks);
void					check_if_should_split(t_token *toks);
char					*expand_toks(t_token *tok, t_cmd_exec *env);
char					*join_with_newline(char *cmd, char *next);
int						parsing_line(char *line, t_token **toks,
							t_shell *shell);
int						copy_quotes(t_token *t, t_cmd_exec *env_lst, int i,
							int j);
t_token					*lst_new_ele_tok(char type, char *value);
void					toks_trim(t_token **toks);
t_token					*lst_last_tok(t_token *lst);
t_cmd_exec				*lst_new_ele(char *name, char *value);
void					lstadd_back_tok(t_token **lst, t_token *node);
int						tokens_count(char *line, char *chars);
int						toks_to_struct(t_token **toks, t_cmd **cmd,
							t_cmd_exec **env_lst);
int						parsing_opers(t_token **toks, t_cmd *cmd,
							t_cmd_exec **env_lst);
void					quote_del(t_token *toks);
int						get_exit_code(void);
void					set_exit_code(int code);
int						heredoc(t_cmd *cmd, t_cmd_exec **env_lst);
int						ft_cd(t_cmd *cmd, t_cmd_exec **env_lst);
int						ft_pwd(t_cmd_exec **env_lst);
int						ft_unset(t_cmd *cmd, t_cmd_exec **env_lst);
int						ft_echo(t_cmd *cmd, t_cmd_exec **env_lst);
int						ft_env(t_cmd_exec **env_lst);
int						ft_exit(t_cmd *cmd, t_cmd_exec **env_lst);
char					*check_dir(t_cmd_exec **env_lst, char *path);
int						ft_export(t_cmd *cmd, t_cmd_exec **env_lst);
int						is_valid_expansion(char c);
int						check_var_name(char *str, int *res,
							t_cmd_exec **env_lst);
void					child_proc(t_cmd **cmd, t_shell *shell, int id);
char					*find_cmd(t_cmd *cmd, t_cmd_exec *env_lst);
void					exec_built(t_cmd *cmd, t_shell *shell,
							int child_par);
void					ft_signals(void);
void					func(char *str, int *j);
void					dups(t_cmd *tmp);
void					check_if_dir(t_cmd *exec_cmd);
t_cmd					*close_pipes(t_cmd **cmd, int id);
char					*getold(t_cmd_exec **env_lst);
void					change_env(char *oldpwd, char *newpwd,
							t_cmd_exec *env_lst);
int						exec_run(t_cmd *cmd, t_shell *shell);
void					exec_run_par(t_cmd *cmd, t_shell *shell);
char					*resolve_dollar(char *str, int* i, t_cmd_exec* env);
void					append_str(t_buff* buff, char *str);
void					check_dir_exe(t_cmd *tmp, t_shell *shell, t_cmd **cmd);
int						parent_heredoc(pid_t pid, t_cmd *cmd, int *heredoc);
void					parent_proc(t_cmd_exec **env_lst, int idx,
							int *pids);
pid_t					*allocate_pid_array(t_cmd *cmd);
void					waiting(t_cmd_exec **env_lst, int idx,
							int *pids);
void					ft_exitt(int *status);
char					*file_random(void);
void					handle_ctrl_c_heredoc(int sig);
void					ft_handle_sigint(int sig);

void					*ft_malloc(size_t size);
void					free_grabage(void);
char					*check_is_path_fail(t_cmd *cmd);
void					append_char(t_buff* buf, char c);
int						env_to_lst(char **env, t_cmd_exec **env_lst);
void					restore_std_fds(void);
char					*get_alias_value(t_hash *table, char *name);
void					set_alias(t_hash *table, char *name, char *value);
t_alias					*lst_new_alias(char *name, char *value);
void					change_stat(t_cmd_exec **env_lst, int stat);
void					ft_lstadd_front(t_cmd_exec **lst, t_cmd_exec *new);
int						ft_alias(t_cmd *cmd, t_shell *shell);
void					ft_lstadd_back(t_cmd_exec **lst, t_cmd_exec *new);
t_cmd_exec				*ft_lstlast(t_cmd_exec *lst);
void					remove_empty_tokens(t_token **toks);
char					*ft_strjoin_sep(char *path, char *cmd, char c);
void					build_new_tok_val(t_token *toks, char *value, int i,
							int j);
char					**env_lst_to_arr(t_cmd_exec *env_lst, char meaning,
							int quote);
void					exec(t_cmd **cmd, t_shell *shell);
int						ft_type(t_cmd* cmd, t_cmd_exec **env_lst);

#endif
