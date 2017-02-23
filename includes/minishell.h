/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:57:49 by moska             #+#    #+#             */
/*   Updated: 2017/02/23 22:11:31 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>

# define BUFF_SIZE 1024

extern int g_exit_code;

typedef struct		s_envl
{
	struct s_envl	*next;
	char			*name;
	char			*value;
}					t_envl;

typedef struct		s_shell
{
	char			*buff;
	char			**cmd;
	int				cmd_len;
	int				ret;
	int				exit;
	char			**env;
	t_envl			*env_list;
}					t_shell;

typedef struct		s_env_s
{
	int				set;
	int				unset;
	int				ignore;
	int				cmd;
	int				null;
}					t_env_s;

void				print_prompt(t_shell **shell);
void				read_line(t_shell **shell);
void				create_shell(t_shell **shell, char **env);
int					validate_and_prep_cmd(t_shell **shell);
void				interpret_line(t_shell **shell);
void				clean_shell(t_shell **shell);
void				command_not_found(t_shell **shell);
void				construct_command(t_shell **shell);
void				mid_clean_shell(t_shell **shell);
void				permission_denied(t_shell **shell, char *path);
void				must_exec(t_shell **shell, char *exec, \
					char **ptr, char **env);
void				print_env(t_envl *env_list);
t_envl				*built_env_list(char **env);
void				no_file_or_dir(t_shell **shell);
void				not_a_dir(t_shell **shell);

/*
**	Environment list custom struct & functions
*/

void				envladd(t_envl **begin_list, t_envl *new);
t_envl				*envlnew(char *name, char *value);
int					envladd_back(t_envl **begin_list, t_envl *new);
char				*get_env_val(t_shell **shell, char *name);
void				clean_env_list(t_envl **begin_list);
int					env_lst_size(t_envl *begin_list);
void				rebuild_str2env(t_shell **shell);

/*
**	Builtins
*/

int					try_a_builtin(t_shell **shell);
void				builtin_exit(t_shell **shell);
void				builtin_env(t_shell **shell);
void				builtin_getenv (t_shell **shell);
void				builtin_setenv(t_shell **shell);
void				builtin_unsetenv(t_shell **shell);
void				builtin_cd(t_shell **shell);
int					op_null(char **cmd);
int					op_unset(char **cmd);
int					op_setenv(char **cmd);
int					op_ignore(char **cmd);
int					op_cmd(char **cmd);
int					is_setenv(char *a);
int					is_null(char *a);
int					is_ignore(char *a);
char				**build_tmp_environment(char **cmd);
void				print_setenv(char **cmd);
void				work_as_newenv(char **cmd, t_shell **shell);
void				work_with_alterenv(char **cmd, t_shell **shell);
void				work_environ_and_display(char **cmd, t_shell **shell);
void				do_setenv(t_shell **shell, char *name, char *value);
void				change_symlink_directory(t_shell **shell, char *path);
void				prep_and_change(t_shell **shell);
#endif
