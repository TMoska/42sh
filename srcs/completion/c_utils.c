/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/25 23:53:59 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t      binary_directories(t_shell *shell)
{
  char      **split;

  while (shell->tc_in != 0 && (shell->buff + shell->tc_in) != '|' &&
          (shell->buff + shell->tc_in) != '||' &&
          (shell->buff + shell->tc_in) != '&&' &&
          (shell->buff + shell->tc_in) != ';')
          shell->tc_in--;
  (shell->tc_in != 0 ? shell->tc_in++ : 0);
  if (!(split = ft_strsplit(&(shell->buff + shell->tc_in), ' ')))
    return (0);
  if (split[1] != NULL && split[2] == NULL)
    return (1);
  return (0);
}

char      *search_cmd(t_shell *shell)
{
  char      **split;

  while (shell->tc_in != 0 && (shell->buff + shell->tc_in) != '|' &&
          (shell->buff + shell->tc_in) != '||' &&
          (shell->buff + shell->tc_in) != '&&' &&
          (shell->buff + shell->tc_in) != ';')
          shell->tc_in--;
  (shell->tc_in != 0 ? shell->tc_in++ : 0);
  if (!(split = ft_strsplit(&(shell->buff + shell->tc_in), ' ')))
    return (NULL);
  if (split[1] != NULL && split[2] == NULL)
      return (split[1]);
  while (split[i + 1] != NULL)
    i++;
  ft_str2del(&split);
  return (ft_strdup(split[i]););
}

c_tab     *search_on_dir(char *path, t_shel *shell, c_tab list)
{
  DIR           *dir;
  char          *cmd;
  struct dirent *dp;
  size_t        len;

  cmd = search_cmd(shell);
  len = ft_strlen(cmd);
  if (!(dir = opendir(path)))
    return (NULL);
  while ((dp = readdir(dir)) != NULL)
    if (!(ft_strncmp(dp->d_name, cmd, len)))
        cmd_option(dp->d_name, &list);
  return (list);
}
