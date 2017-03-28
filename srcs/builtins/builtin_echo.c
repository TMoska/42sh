/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:38:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/28 05:45:36 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
   static int	echo_with_env(t_shell **shell, char *cmd)
   {
   int		len;
   int		len1;
   char	*tmp;
   char	*env;

   len = 0;
   len1 = 0;
   while (cmd[len1] != '$')
   len1++;
   tmp = ft_strsub(cmd, 0, len1);
   ft_putstr(tmp);
   ft_strdel(&tmp);
   len1++;
   while (ft_isalnum(cmd[len1 + len]) || cmd[len1 + len] == '_')
   len++;
   tmp = ft_strsub(cmd, len1, len);
   env = get_env_val(shell, tmp);
   ft_strdel(&tmp);
   if (env)
   ft_putstr(env);
   return (len1 + len + 1);
   }

   static void	echo_simple(t_shell **shell, char *cmd)
   {
   char	**tmp;
   int		i;

   i = 0;
   if ((tmp = ft_strsplit(cmd, ' ')))
   {
   while (tmp[i])
   {
   if (tmp[i][0] == '$')
   echo_with_env(shell, tmp[i]);
   else
   ft_putstr(tmp[i]);
   i++;
   if (tmp[i])
   ft_putchar(' ');
   }
   ft_str2del(&tmp);
   }
   }

   static void	echo_words_within(t_shell **shell, char *tmp, int quote)
   {
   int		i;
   char	**tmp_dep;

   tmp_dep = ft_strsplit(tmp, ' ');
   i = 0;
   while (tmp_dep[i])
   {
   ((ft_strchr(tmp_dep[i], '$') && quote == '\"') ?
   echo_with_env(shell, tmp_dep[i]) : ft_putstr(tmp_dep[i]));
   i++;
   if (tmp_dep[i])
   ft_putchar(' ');
   }
   ft_strdel(&tmp);
   ft_str2del(&tmp_dep);
   }

   static void	echo_quote(t_shell **shell, char *cmd, char quote)
   {
   char	*tmp;
   int		offset;
int		len;

tmp = NULL;
offset = 1;
while (cmd[offset])
{
	len = 0;
	while (cmd[offset + len] && cmd[offset + len] != quote)
		len++;
	tmp = ft_strsub(cmd, offset, len);
	((offset >= 2) && cmd[offset - 2] == ' ') ? ft_putchar(' ') : (0);
	echo_words_within(shell, tmp, quote);
	offset += len + 1;
	if (cmd[offset] == ' ')
	{
		ft_putchar(' ');
		len = 0;
		continue;
	}
	while (cmd[offset] && cmd[offset] != quote)
		offset++;
	((cmd[offset] == quote) ? offset++ : (0));
}
}

int			builtin_echo(t_shell **shell, char *cmd)
{
	char *tmp;

	ft_putstr(cmd);
	tmp = (cmd + 5);
	if (tmp[0] == '\"' || tmp[0] == '\'')
		echo_quote(shell, tmp, tmp[0]);
	else
		echo_simple(shell, tmp);
	ft_putchar('\n');
	return (0);
}
*/

int		*ft_setquotes(int *array, const char *s, char c)
{
	int		found;
	int		wc;
	int		i;

	i = -1;
	wc = 0;
	found = 0;
	while (s[++i])
		if (s[i] == c)
			found = 0;
		else
		{
			if ((s[i] == '`' || s[i] == '"' || s[i] == 39) && s[i - 1] != '\\')
			{
				if (s[i] == '\'')
					array[wc] = 1;
				i = ft_endquo(s, i);
			}
			if (found == 0)
				wc++;
			found = 1;
		}
	return (array);
}

void	ft_echo(t_shell **shell, char *str, int flag)
{
	int i;
	int i2;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !flag)
		{
			if (ft_strncmp(&str[i], "$?", 2) == 0)
			{
				ft_putnbr((*shell)->ret);
				i += 2;
			}
			else
			{
				i2 = i;
				while (str[i] && (!ft_isspace(str[i]) && !ft_isquotes(str[i + 1])))
					++i;
				ft_putstr(get_env_val(shell, ft_strsub(str, i2 + 1, i - 1)));
			}
		}
		if (str[i])
		{
			ft_putchar(str[i]);
			++i;
		}
	}
}

int		builtin_echo(t_shell **shell, char *cmd)
{
	int		i;
	char	**array;
	int		*iarray;

	array = ft_splitquotes(cmd, ' ');
	i = 1;
	iarray = ft_memalloc(sizeof(int) * (ft_str2len(array) + 1));
	iarray = ft_setquotes(iarray, (cmd + 4), ' ');
	if (ft_strcmp(array[1], "-n") == 0)
		++i;
	while (array[i])
	{
		ft_echo(shell, array[i], iarray[i - 1]);
		++i;
		ft_putchar(' ');
	}
	if (ft_strcmp(array[1], "-n") != 0)
		ft_putchar('\n');
	return (0);
}
