/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exclamation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 06:51:00 by moska             #+#    #+#             */
/*   Updated: 2017/03/27 14:27:25 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	single_excl_find_end(char *str, int type, int *till_end)
{
	if (type == 3)
	{
		(*till_end)++;
		while (!(*(str + *till_end) == '\0' || *(str + *till_end) == '?'))
			(*till_end)++;
	}
	else if (type == 2)
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

char		*excl_nb(t_shell **shell, int nb)
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

char		*get_repl_value(char **cmd, char **arg, int type, int i)
{
	t_shell	*shell;

	shell = get_shell(NULL);
	if (type == 3)
	{
		ft_str_replace(arg, "?", "", 0);
		return (history_search_first_arg_match(&shell, *arg));
	}
	if (type == 2)
		return (ft_strndup(*cmd, i - 1));
	else if (type == 1)
		return (excl_nb(&shell, ft_atoi(*arg)));
	else if (type == 0)
		return (history_search_first_match(&shell, *arg));
	else
		return (NULL);
}

int			start_replacing(char **cmd, int *till_end, int *type, int *i)
{
	char	*arg;
	char	*repl;
	char	*old;
	t_shell	*shell;

	shell = get_shell(NULL);
	arg = ft_strndup(*cmd + *i, *till_end);
	repl = NULL;
	if (!(repl = get_repl_value(cmd, &arg, *type, *i)) && no_history_err(arg))
		return (-1);
	if (*type == 3)
		old = ft_strndup(*cmd + *i - 1, 3 + ft_strlen(arg));
	else
		old = ft_strndup(*cmd + *i - 1, 1 + ft_strlen(arg));
	ft_str_replace(cmd, old, repl, 1);
	ft_strdel(&arg);
	ft_strdel(&old);
	(*type == 2) ? ft_strdel(&repl) : (0);
	*i += ft_strlen(repl);
	return (0);
}

int			replace_single_exclamation(char **cmd)
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
