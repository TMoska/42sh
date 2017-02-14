/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 22:32:02 by moska             #+#    #+#             */
/*   Updated: 2017/02/09 00:30:12 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int command_is_good(char *cmd)
{
  // Todo: syntax checking
  if (!shell->buff || ft_strisblank(shell->buff))
    return (0);
  return (1);
}

static format_cmd(t_shell **shell)
{
  
}

int validate_and_prep_cmd(t_shell *shell)
{
  if (command_is_good)
  {
    format_cmd(&shell);
    return (1)
  }
  return (0);
}