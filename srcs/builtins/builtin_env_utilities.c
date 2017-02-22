/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utilities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 23:28:01 by moska             #+#    #+#             */
/*   Updated: 2017/02/22 10:41:04 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int   is_null(char *a)
{
  return (ft_strcmp("-0", a) == 0 || ft_strcmp("--null", a) == 0);
}

int   is_ignore(char *a)
{
  return(ft_strcmp(a, "-i") == 0 || ft_strcmp(a, "--ignore-environment") == 0);
}

int   is_setenv(char *a)
{
  return(ft_strchr(a, '=') != 0);
}

int   op_null(char **cmd)
{
  int i;

  i = 1;
  while (cmd[i])
  {
    if (i == 1 && is_null(cmd[i]))
      return (1);
    else if (is_setenv(cmd[i]))
      return (0);
    else if (ft_strcmp("-u", cmd[i - 1]) != 0 && is_null(cmd[i]))
      return (1);
    i++;
  }
  return (0);
}

int   op_unset(char **cmd)
{
  int i;
  int u;

  i = 1;
  u = 0;
  while (cmd[i])
  {
    if (ft_strcmp(cmd[i], "-u") == 0 && cmd[i + 1])
    {
      i += 2;
      u = 1;
    }
    else if (ft_strcmp(cmd[i], "-u") == 0)
      return (-1);
    else if (ft_strcmp("-u", cmd[i - 1]) != 0 && is_null(cmd[i]))
      return (u);
    else if (is_ignore(cmd[i]) || is_null(cmd[i]))
      i++;
    else
      break ;
  }
  return (u);
}

int   op_setenv(char **cmd)
{
  int i;

  i = 1;
  while (cmd[i])
  {
    if (i == 1 && is_setenv(cmd[i]))
      return (1);
    else if (ft_strcmp("-u", cmd[i - 1]) != 0 && is_setenv(cmd[i]))
      return (1);
    i++;
  }
  return (0);
}

int   op_ignore(char **cmd)
{
  int i;

  i = 1;
  while (cmd[i])
  {
    if (i == 1 && is_ignore(cmd[i]))
      return (1);
    else if (is_setenv(cmd[i]))
      return (0);
    else if (ft_strcmp("-u", cmd[i - 1]) != 0 &&
        is_ignore(cmd[i]))
      return (1);
    i++;
  }
  return (0);
}

int   op_cmd(char **cmd)
{
  int i;
  int set;

  i = 1;
  set = 0;
  while (cmd[i])
  {
    if (set == 0 && ft_strcmp(cmd[i], "-u") == 0 && cmd[i + 1])
      i += 2;
    else if (set == 0 && (is_ignore(cmd[i]) || is_null(cmd[i])))
      i++;
    else if (is_setenv(cmd[i]))
    {
      i++;
      set = 1;
    }
    else
      return (1);
  }
  return (0);
}
