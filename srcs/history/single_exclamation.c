/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exclamation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 06:51:00 by moska             #+#    #+#             */
/*   Updated: 2017/03/26 14:51:49 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Returns a type of a single exclamation mark token
**	# = 2;
**	numbers = 1;
**	string = 0;
*/

static int		single_excl_type(char *str)
{
	if (*str == '#')
		return (2);
	else if (ft_isdigit(*str) || (*str == '-' && ft_isdigit(*(str + 1))))
		return (1);
	else if (ft_isalpha(*(str + 1)))
		return (0);
	else
		return (-1);
}

static void		single_excl_find_end(char *str, int type, int *till_end)
{
	if (type == 2)
		(*till_end) = 1;
	else if (type == 1)
	{
		while (ft_isdigit(*(str + *till_end)) || (*till_end == 0 &&
			*(str + *till_end) == '-' && ft_isdigit(*(str + *till_end + 1))))
			(*till_end)++;
	}
	else
	{
		while (!(*(str + *till_end) == ' ' || *(str + *till_end)) == '\0')
			(*till_end)++;
	}
}

char			*excl_nb(t_shell **shell, int nb)
{
	t_h_lst	*lst;
	int		index;

	if (nb < 0)
		index = (*shell)->history->size + nb;
	else
		index = nb;
	if (!(lst = hist_at_index(shell, index)))
		return (NULL);
	return (lst->cmd);
}

int				start_replacing(char **cmd, int *till_end, int *type, int *i)
{
	char	*arg;
	char	*repl;
	char	*old;
	t_shell	*shell;

	shell = get_shell(NULL);
	arg = ft_strndup(*cmd + *i, *till_end);
	repl = NULL;
	if (*type == 2)
		repl = ft_strndup(*cmd, *i - 1);
	else if (*type == 1)
		repl = excl_nb(&shell, ft_atoi(arg));
	else if (*type == 0)
		repl = history_search_first_match(&shell, arg);
	if (!repl && no_history_err(arg))
		return (-1);
	old = ft_strndup(*cmd + *i - 1, 1 + ft_strlen(arg));
	ft_str_replace(cmd, old, repl, 1);
	ft_strdel(&arg);
	ft_strdel(&old);
	*i += ft_strlen(repl);
	return (0);
}

int				replace_single_exclamation(char **cmd)
{
	int		i;
	int		till_end;
	int		type;

	i = 0;
	while (*((*cmd) + i))
	{
		till_end = 0;
		while (*((*cmd) + i) && *((*cmd) + i) != '!')
			i++;
		if (!(*((*cmd) + i)))
			break ;
		i++;
		if (*((*cmd) + i) == ' ' || *((*cmd) + i) == '\0')
			return (0);
		type = single_excl_type(*cmd + i);
		single_excl_find_end(*cmd + i, type, &till_end);
		if (!till_end)
			return (0);
		if (start_replacing(cmd, &till_end, &type, &i) == -1)
			return (-1);
	}
	return (0);
}
