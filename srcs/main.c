/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 21:39:49 by moska             #+#    #+#             */
/*   Updated: 2017/02/16 23:38:35 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_callback(int s_num)
{
  if (s_num == SIGINT) // Todo: Support more terimnation signals
  {
    print_prompt(1);
    printf("%s\n", "TERMINATIING");
    exit(0);
  }
}

int  run_shell(t_shell **shell)
{
  while(1)
  {
    print_prompt(0);
    signal(SIGINT, sig_callback);
    read_line(shell);
    if (!validate_and_prep_cmd(shell))
      continue ;
    // construct_command(shell);
    (*shell)->cmd = ft_strsplit((*shell)->buff, ' ');
    interpret_line(shell);
    clean_shell(shell);
    if ((*shell)->exit)
      return (0);
  }
}

int		main(void)
{
  t_shell *shell;

  create_shell(&shell);
  run_shell(&shell);
  // clean_shell(&shell);
	return (0);
}
