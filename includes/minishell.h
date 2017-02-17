/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:57:49 by moska             #+#    #+#             */
/*   Updated: 2017/02/17 12:40:30 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>

# define BUFF_SIZE 2

typedef struct	s_shell
{
  char					*buff;
  char          **cmd;
  int           ret;
  int           exit;
}								t_shell;

void						print_prompt(int terminated);
void            read_line(t_shell **shell);
void            create_shell(t_shell **shell);
int             validate_and_prep_cmd(t_shell **shell);
void            interpret_line(t_shell **shell);
void            clean_shell(t_shell **shell);
int             try_a_builtin(t_shell **shell);
void            builtin_exit(t_shell **shell);
void            command_not_found(t_shell **shell);
#endif
