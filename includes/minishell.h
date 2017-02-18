/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:57:49 by moska             #+#    #+#             */
/*   Updated: 2017/02/18 20:25:40 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>

# define BUFF_SIZE 2

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

void				print_prompt(t_shell **shell, int terminated);
void				read_line(t_shell **shell);
void				create_shell(t_shell **shell, char **env);
int					validate_and_prep_cmd(t_shell **shell);
void				interpret_line(t_shell **shell);
void				clean_shell(t_shell **shell);
int					try_a_builtin(t_shell **shell);
void				builtin_exit(t_shell **shell);
void				command_not_found(t_shell **shell);
void				builtin_env(t_shell **shell);
void				construct_command(t_shell **shell);
void				mid_clean_shell(t_shell **shell);
void				permission_denied(t_shell **shell);

/*
**	Environment list custom struct & functions
*/

void				envladd(t_envl **begin_list, t_envl *new);
t_envl				*envlnew(char *name, char *value);
int					envladd_back(t_envl **begin_list, t_envl *new);
char				*get_env_val(t_envl *begin_list, char *name);
void				clean_env_list(t_envl **begin_list);

#endif
