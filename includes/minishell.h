/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:57:49 by moska             #+#    #+#             */
/*   Updated: 2017/03/09 12:03:52 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <termcap.h>
# include <sys/wait.h>

# define BUFF_SIZE 1024

/*
**	Button Key codes
*/

# define BTN_DEL	2117294875
# define BTN_BACK	127

# define BTN_HOME	4741915
# define BTN_END	4610843

# define BTN_ALEFT	1146821403
# define BTN_ARIGHT	1130044187

# define BTN_LEFT	4479771
# define BTN_RIGHT	4414235
# define BTN_UP		4283163
# define BTN_DOWN	4348699

# define BTN_ESC	27
# define BTN_ENTER	10
# define BTN_TAB	9
# define BTN_CTRL_D	4

# define BTN_CTRL_P 16
# define BTN_CTRL_I 9
# define BTN_CTRL_K 11
# define BTN_CTRL_L	12

/*
**	Termcaps commands
*/

# define MOVE_LEFT	ft_putstr(tgetstr("le", NULL));
# define MOVE_RIGHT	ft_putstr(tgetstr("nd", NULL));

# define DEL		ft_putstr(tgetstr("dc", NULL));
# define CURS_LEFT	ft_putstr(tgetstr("cr", NULL));
# define DEL_LINE	ft_putstr(tgetstr("ce", NULL));

/*
**	Types and Structs
*/

extern int g_exit_code;

typedef struct		s_envl
{
	struct s_envl	*next;
	char			*name;
	char			*value;
}					t_envl;

typedef struct		s_quotes
{
	t_bool			was_quoted;
	t_bool			dquote;
	t_bool			squote;
	t_bool			bquote;
	t_bool			escape;
	t_bool			oneline;
}					t_quotes;

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_shell
{
	char			*buff;
	char			*hist_buff_tmp;
	t_list			*commands;
	char			**cmd;
	int				cmd_len;
	int				ret;
	int				exit;
	char			**env;
	t_envl			*env_list;
	struct termios	term;
	int				tc_ok;
	int				tc_in;
	int				tc_len;
	int				prompt_len;
	t_hist			*history;
	char			*clipboard;
	char			*tmp_buff;
	t_quotes		*q;
	struct s_tkn	*tkns;
}					t_shell;

typedef struct		s_tkn
{
	char			*data;
	int				type;
	struct s_tkn	*left;
	struct s_tkn	*right;
}					t_tkn;

typedef struct		s_env_s
{
	int				set;
	int				unset;
	int				ignore;
	int				cmd;
	int				null;
}					t_env_s;

/*
**	Core function prototypes
*/

void				print_prompt(t_shell **shell, char *prompt);
t_shell				*get_shell(char **env);
int					validate_and_prep_cmd(t_shell **shell);
void				interpret_line(t_shell **shell);
char				*loop_through_paths(char ***paths, int *i, char *cmd);
void				clean_shell(t_shell **shell);
void				command_not_found(t_shell **shell);
void				mid_clean_shell(t_shell **shell);
void				permission_denied(t_shell **shell, char *path);
void				must_exec(t_shell **shell, char *exec, \
					char **ptr, char **env);
void				print_env(t_envl *env_list);
t_envl				*built_env_list(char **env);
void				no_file_or_dir(t_shell **shell);
void				not_a_dir(t_shell **shell);
void				sig_callback(int s_num);

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
void				builtin_echo(t_shell **shell);
void				join_back(char ***split_tab, char **new, int *size, int *i);
void				builtin_export(t_shell **shell);

/*
**	Reading
*/

void				read_input(t_shell **shell);
void				work_buffer(t_shell **shell, char *buffer);
int					reset_line(t_shell **shell);

/*
**	Terminall
*/

int					term_init(t_shell **shell);
int					term_trigger(t_shell **shell, int off);
void				move_cursor_sides(t_shell **shell, unsigned int key);
void				move_cursor_alt(t_shell **shell, unsigned int key);
void				modify_buffer(t_shell **shell, unsigned int key);
void				clean_buffer(t_shell **shell);
void				cut_line(t_shell **shell, unsigned int key);
void				clean_input(t_shell **shell);
void				paste(t_shell **shell);
void				copy(t_shell **shell);
void				clean_terminal(void);

/*
**	History
*/

void				hist_add(t_hist **begin_list, char *cmd);
void				print_history(t_shell **shell);
void				history(t_shell **shell, unsigned int key);
void				rewind_history(t_hist **hist);

/*
**	Quotes
*/

int					do_quotes(t_shell **shell);

/*
**	Tokenizing
*/

t_tkn				*tkn_new(char *data, int type);
int					tkn_new_to_back(t_tkn **lst, char *data, int type);
char				**split_command(char *cmd);
int					if_op_find_priority(char *s);
void				tokenize(t_shell **shell);
void				get_tokens(t_shell **shell);
void				tkn_merge_nodes(t_tkn **dst, t_tkn **src);

#endif
