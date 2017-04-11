/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:57:49 by moska             #+#    #+#             */
/*   Updated: 2017/04/11 17:48:42 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <termcap.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/acl.h>

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
# define BTN_SPACE  32
# define BTN_TAB	9
# define BTN_CTRL_D	4
# define BTN_S_TAB  5921563

# define BTN_CTRL_P 16
# define BTN_CTRL_I 9
# define BTN_CTRL_K 11
# define BTN_CTRL_L 12
# define BTN_CTRL_U	21
# define BTN_CTRL_H	8

# define BTN_Y      121
# define BTN_N      110
# define BTN_SLASH  47

/*
**	Termcaps commands
*/

# define MOVE_UP	ft_putstr(tgetstr("up", NULL));
# define MOVE_LEFT	ft_putstr(tgetstr("le", NULL));
# define MOVE_RIGHT	ft_putstr(tgetstr("nd", NULL));
# define MOVE_DOWN  ft_putstr(tgetstr("do", NULL));

# define SAVE_LINE	ft_putstr(tgetstr("sc", NULL));
# define LOAD_LINE	ft_putstr(tgetstr("rc", NULL));

# define CLEAR		ft_putstr(tgetstr("cl", NULL));
# define DEL		ft_putstr(tgetstr("dc", NULL));
# define CURS_LEFT	ft_putstr(tgetstr("cr", NULL));
# define DEL_LINE	ft_putstr(tgetstr("ce", NULL));
# define DEL_LINES	ft_putstr(tgetstr("cd", NULL));

/*
** COLOR codes
*/

# define RED "\e[91m"
# define YELL "\e[33m"
# define LCYA "\e[1m\e[1;96m"
# define MAGE "\e[35m"
# define CHAR "\e[31m\e[93m"
# define DGRE "\e[46m\e[34m"
# define BLCK "\e[46m\e[34m"
# define TEMP "\e[42m\e[30m"
# define NORM "\e[00m\e[40m"
# define LGRE "\e[1;92m"

/*
**	Types and Structs
*/

extern int g_exit_code;

typedef struct		s_heredoc
{
	int				type;
	char			*txt;
}					t_heredoc;

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

typedef struct		s_h_lst
{
	char			*cmd;
	int				index;
	struct s_h_lst	*next;
	struct s_h_lst	*prev;
}					t_h_lst;

typedef struct		s_hist
{
	int				size;
	int				at_index;
	struct s_h_lst	*list;
}					t_hist;

typedef struct		s_term
{
	struct termios	term;
	int				tc_ok;
	int				tc_in;
	int				tc_len;
	int				prompt_len;
	int				prompt_line;
	int				winsize_x;
}					t_term;

typedef struct		s_shell
{
	char			*buff;
	t_list			*commands;
	char			**cmd;
	int				cmd_len;
	int				ret;
	int				exit;
	char			**env;
	t_envl			*env_list;
	t_term			*term;
	t_hist			*history;
	char			*clipboard;
	char			*tmp_buff;
	t_quotes		*q;
	struct s_tkn	*tkns;
	struct s_tkn	*tree;
	int				token_count;
	t_list			*heredoc;
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

typedef struct		s_tab
{
	char			*content;
	char			*name;
	char			*perm;
	size_t			cursor;
	size_t			place;
	size_t			col;
	size_t			page;
	struct s_tab	*next;
	struct s_tab	*prev;
}					t_c_tab;

struct				s_put
{
	int				c_line;
	size_t			c_col;
	size_t			len;
	size_t			m_len;
	int				max_len;
}					;

struct				s_pad
{
	size_t			line_s;
	size_t			col_s;
	size_t			page_s;
	size_t			cols;
	size_t			pages;
	size_t			largest;
	size_t			len_x;
	size_t			len_y;
	size_t			max_x;
	size_t			max_y;
}					;

/*
**	Core function prototypes
*/

void				print_prompt(t_shell **shell, char *prompt);
char				*get_git_branch(void);
void				build_prompt(t_shell **shell);
t_shell				*get_shell(char **env);
int					validate_and_prep_cmd(t_shell **shell);
int					interpret_line(char *cmd);
char				*loop_through_paths(char ***paths, int *i, char *cmd);
int					command_not_found(t_shell **shell);
int					permission_denied(t_shell **shell, t_bool name, char *path);
int					must_exec(t_shell **shell, char *exec, char **ptr,\
		char **env);
void				print_env(t_envl *env_list);
t_envl				*built_env_list(char **env);
void				no_file_or_dir(t_shell **shell, t_bool name);
void				not_a_dir(t_shell **shell);
void				sig_callback(int s_num);
void				catch_signals(void);

/*
**	Cleaning
*/

void				clean_shell(t_shell **shell);
void				mid_clean_shell(t_shell **shell);
void				clean_btree(t_tkn *tree);
void				del_lst_str(void **content, size_t *content_size);
void				clean_c_list(t_c_tab **lst);
char				*treat_quotes(char *cmd);
char				**ft_splittreat(char *cmd, char c);
void				del_heredoc(void **content, size_t *content_size);

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

int					try_a_builtin(t_shell **shell, char *base_cmd);
int					builtin_exit(t_shell **shell);
int					builtin_env(t_shell **shell);
int					builtin_getenv (t_shell **shell);
int					builtin_setenv(t_shell **shell);
int					builtin_unsetenv(t_shell **shell);
int					builtin_cd(t_shell **shell);
int					op_setenv(char **cmd);
int					op_ignore(char **cmd);
int					op_cmd(char **cmd);
int					is_setenv(char *a);
int					is_ignore(char *a);
char				**build_tmp_environment(char **cmd);
void				print_setenv(char **cmd);
void				work_as_newenv(char **cmd, t_shell **shell);
void				work_with_alterenv(char **cmd, t_shell **shell);
void				work_environ_and_display(char **cmd, t_shell **shell,\
		t_env_s *env_s);
void				do_setenv(t_shell **shell, char *name, char *value);
void				change_symlink_directory(t_shell **shell, char *path);
int					prep_and_change(t_shell **shell);
int					builtin_echo(t_shell **shell);
void				join_back(char ***split_tab, char **new, int *size, int *i);
int					parse_cd_options(t_shell **shell, int *p_option,\
		char **path);
void				builtin_export(t_shell **shell);
char				**join_envs(char **env, char **new);
char				**remove_duplicate_envs(char **env);
void				execute_further(t_shell **shell, char **cmd, char ***env);
char				**get_command(char **command);
size_t				setenvs_count(char **cmd);

/*
**	Reading
*/

void				read_input(t_shell **shell, char *heredoc);
int					replace_env_vals(t_shell **shell);
void				work_buffer(t_shell **shell, char *buffer);
int					reset_line(t_shell **shell);

/*
**	Heredoc
*/

void				scan_heredocs(t_shell **shell);
t_list				*last_matching_opening(t_shell **shell, char *txt);

/*
**	Terminall
*/

int					term_init(t_shell **shell);
int					term_trigger(t_shell **shell, int off);
int					ft_numberline(t_shell **shell);
void				move_cursor_sides(t_shell **shell, unsigned int key);
void				move_cursor_alt(t_shell **shell, unsigned int key);
void				modify_buffer(t_shell **shell, unsigned int key);
void				clean_buffer(t_shell **shell);
void				cut_line(t_shell **shell, unsigned int key);
void				paste(t_shell **shell);
void				copy(t_shell **shell);
int					clean_terminal(void);

/*
**	Edition
*/

void				ft_printbuffer(t_shell **shell);
int					ft_linesize(void);
void				move_right(t_shell **shell, char *buff, int offset);
void				move_left(t_shell **shell);
void				back_to_prompt(t_shell **shell, int keep);
void				clear_cmdline(t_shell **shell);
void				goto_endcmdline(t_shell **shell);
int					ft_isfirstline(t_shell **shell);
int					ft_currentline(t_shell **shell);
int					ft_getpart(t_shell **shell, char **str);
void				cmd_rewrite(t_shell **shell);

/*
**	History
*/

void				hist_add(t_shell **shell);
void				history(t_shell **shell, unsigned int key);
int					print_history(t_shell **shell);
char				*history_search_first_match(t_shell **shell, char *s);
int					replace_double_exclamation(t_shell **shell, char *tmp);
int					replace_single_exclamation(char **cmd);
void				replace_ation(t_shell **shell, char *cmd);
void				set_hist_of_index(t_shell **shell, int index);
t_h_lst				*hist_at_index(t_shell **shell, int index);
int					no_history_err(char *arg);
char				*history_search_first_arg_match(t_shell **shell, char *s);
int					single_excl_type(char *str);

/*
**	Quotes
*/

char				*quotes_env(char *str, t_shell *shell);
int					do_quotes(t_shell **shell);
int					ft_isescapechar(char c);
char				**splitquote_str2(char *cmd);

/*
**	Tokenizing
*/

t_tkn				*tkn_new(char *data, int type);
int					tkn_new_to_back(t_tkn **lst, char *data, int type);
char				**split_command(char *cmd);
int					if_op_find_priority(char *s);
int					tokenize(t_shell **shell);
int					get_tokens(t_shell **shell);
void				tkn_move_args_to_start(t_tkn **dst, t_tkn **src);
void				reorganize_tokens(t_shell **shell);
void				move_pointers(t_tkn *init, t_tkn **start, t_tkn **ptr1, \
		t_tkn **ptr2);
void				arrange_nodes_in_priority(t_shell **shell);
void				syn_error(void);
t_tkn				*build_tree(t_tkn *tree);
int					in_range(int i, int start, int end);
void				add_cmds(char ***cmds, char *cmd, int *offset, int *len);
int					is_op(char *c);
void				add_command(char ***cmds, char *cmd, int *offset, int *len);
t_tkn				*tkn_pre_last(t_tkn *lst);
t_tkn				*tkn_search_node(t_tkn *node, char *data);
t_tkn				*tkn_last(t_tkn *node);
void				skip_and_sort(t_tkn **tkns, t_tkn **lst_sep);
void				tkns_sort(t_tkn **begin_list);
int					prev_node_not_fd_aggr(t_tkn *start, t_tkn *end);
void				tkn_del(t_tkn *start, t_tkn **tkn);

/*
**	Execution
*/

int					test_n_execute(char *exec, char **ptr,\
					char **env);
int					execute_node(t_tkn *node);
int					execute_right_redirection(t_tkn *node);
int					execute_logic_operators(t_tkn *node);
int					execute_semicolon(t_tkn *node);
int					execute_left_redirection(t_tkn *node);
int					execute_pipe(t_tkn *node);
int					execute_fd_aggregation(t_tkn *node);
int					get_and_test_executable(t_shell **shell, char **exec, \
		char **env);
int					open_tmp_heredoc(int *fd);
int					redirection_type(t_tkn *node);
int					execute_two_left(t_tkn *node, char *out);
int					fork_error(void);
int					fix_path_if_going_home(t_shell **shell);
char				*get_env_val_2str(char **env, char *name);
int					env_var_error_checking(char *env_str);

/*
**	Completion
*/

void				tab_completion(t_shell **shell, t_c_tab *list, size_t val);
size_t				binary_directories(t_shell *shell);
char				*search_cmd(t_shell *shell);
t_c_tab				*search_on_dir(char *path, t_shell *shell, t_c_tab *list,
					size_t bin);
t_c_tab				*cmd_option(char *cmd, t_c_tab *list);
t_c_tab				*define_pading(t_c_tab *list, size_t *val);
int					put_options(t_c_tab *list, size_t val);
void				put_question(size_t i);
struct s_pad		start_pad(struct winsize w, size_t nb_files);
t_c_tab				*move_select(t_c_tab *list, size_t val);
t_c_tab				*tab_binary(t_c_tab *list, t_shell *shell);
t_c_tab				**init_left(t_c_tab **tmp, size_t *c, size_t *l,
					size_t *page);
t_c_tab				**init_right(t_c_tab **tmp, size_t *c, size_t *l,
					size_t *page);
int					treat_tab_c(size_t *v, t_shell **shell, t_c_tab **list);
void				tab_term(int v, t_shell *shell, int put);
void				tab_lst_sort(t_c_tab **begin_list);
int					check_dir(char *tmp);
t_c_tab				*tab_name(t_c_tab *list, char *cmd);
void				ft_print(t_c_tab *list);
void				get_info(t_c_tab *list);
void				get_acl(t_c_tab *list);
void				get_extention(t_c_tab *list);
int					get_dir(t_shell **shell);
t_c_tab				*get_list(t_c_tab *list, int i);
void				clean_list(t_c_tab *list);
void				try_up(t_shell **shell);
size_t				nb_pages(t_c_tab *tmp);
int					check_winsize(t_shell **shell, t_c_tab *list);
t_c_tab				*name_completion(t_c_tab *list, char **str);
char				*fix_cmdname(char **cmd);
t_c_tab				*get_matching(t_c_tab *list, char *path,
		char *tofind);
char				*completion_buffer(t_c_tab *list, t_shell *shell,
		char *tmp);
struct s_pad		get_largest(struct s_pad pad, t_c_tab *list);
t_c_tab				*get_matching_binary(t_c_tab *list, char *path,
		char *tofind);
t_c_tab				*binary_directory(t_c_tab *list, t_shell *shell);
t_c_tab				*name_fill(t_c_tab *list, char *path, char *tofind);
void				tab_cursor_fix(t_c_tab **list);
int					big_enough(t_c_tab *list);
void				begin_resize_tab(t_c_tab **list, size_t number);
void				put_space(t_shell **shell);
int					compare_tab_str(char *s1, char *s2, size_t len);

#endif
