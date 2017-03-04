/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:14:49 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/05 00:24:46 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		quote_incomplete(t_quotes **q, char *buff)
{
	*q = (t_quotes*)ft_memalloc(sizeof(t_quotes*) + 1);
	while (buff && *buff)
	{
		if (*buff == '\\' && !*(buff + 1))
			(*q)->oneline ^= 1;
		else if (*buff == '\\')
			(*q)->escape ^= 1;
		else if (*buff == '"' && !(*q)->squote && !(*q)->bquote)
			(*q)->dquote ^= !(*q)->escape;
		else if (*buff == '\'' && !(*q)->dquote && !(*q)->bquote)
			(*q)->squote ^= !(*q)->escape;
		else if (*buff == '`' && !(*q)->squote)
			(*q)->bquote ^= !(*q)->escape;
		else
			(*q)->escape = 0;
		buff++;
	}
	return ((*q)->oneline || (*q)->bquote || (*q)->squote || (*q)->dquote);
}

int		ask_for_more_input(t_shell **shell, t_quotes **q)
{
	char	*str;

	if ((*q)->oneline)
		str = ft_strdup("> ");
	else if ((*q)->bquote)
		str = ft_strdup("bquote> ");
	else if ((*q)->dquote)
		str = ft_strdup("dquote> ");
	if ((*q)->squote)
		str = ft_strdup("squote> ");
	print_prompt(shell, str);
	read_input(shell);
	return (0);
}

int		do_quotes(t_shell **shell)
{
	char		*tmp;

	if (!(*shell)->buff)
		return (0);
	while (quote_incomplete(&(*shell)->q, (*shell)->buff))
	{
		(*shell)->prev_line_buff = ft_strdup((*shell)->buff);
		ft_strdel(&(*shell)->buff);
		ask_for_more_input(shell, &(*shell)->q);
		tmp = (*shell)->buff;
		if ((*shell)->q->oneline)
		{
			tmp = (*shell)->prev_line_buff;
			(*shell)->prev_line_buff = ft_strndelat(tmp, ft_strlen(tmp) - 1, 1);
			(*shell)->buff = ft_strjoin((*shell)->prev_line_buff, (*shell)->buff);
			ft_strdel(&tmp);
		}
		else
			(*shell)->buff = ft_str3join((*shell)->prev_line_buff, "\n", (*shell)->buff);
		ft_strdel(&tmp);
		ft_strdel(&(*shell)->prev_line_buff);
	}
	ft_strndelat((*shell)->buff, 0, 1);
	ft_strndelat((*shell)->buff, ft_strlen(((*shell)->buff)) - 1, 1);
	return (0);
}