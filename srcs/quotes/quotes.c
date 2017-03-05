/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:14:49 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/05 18:43:13 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotes	**init_quotes(t_quotes **q)
{
	t_bool tmp;

	tmp = FALSE;
	if (*q)
		tmp = (*q)->was_quoted;
	ft_memdel((void**)q);
	*q = (t_quotes*)ft_memalloc(sizeof(t_quotes*) + 1);
	(*q)->was_quoted = ((!!tmp) ? tmp : FALSE);
	(*q)->dquote = FALSE;
	(*q)->squote = FALSE;
	(*q)->bquote = FALSE;
	(*q)->escape = FALSE;
	(*q)->oneline = FALSE;
	return (q);
}

int			quote_incomplete(t_quotes **q, char *buff)
{
	q = init_quotes(q);
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

int			ask_for_more_input(t_shell **shell, t_quotes **q)
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

int			do_quotes(t_shell **shell)
{
	char		*tmp;

	if (!(*shell)->buff)
		return (0);
	while (quote_incomplete(&(*shell)->q, (*shell)->buff))
	{
		(*shell)->tmp_buff = ft_strdup((*shell)->buff);
		ft_strdel(&(*shell)->buff);
		ask_for_more_input(shell, &(*shell)->q);
		tmp = (*shell)->buff;
		if ((*shell)->q->oneline)
		{
			tmp = (*shell)->tmp_buff;
			(*shell)->tmp_buff = ft_strndelat(tmp, ft_strlen(tmp) - 1, 1);
			ft_strdel(&tmp);
			tmp = (*shell)->buff;
			(*shell)->buff = ft_strjoin((*shell)->tmp_buff, (*shell)->buff);
		}
		else
		{
			(*shell)->q->was_quoted = 1;
			hist_add(&(*shell)->history, (*shell)->buff);
			(*shell)->buff = ft_str3join((*shell)->tmp_buff,\
					"\n", (*shell)->buff);
		}
		ft_strdel(&tmp);
		ft_strdel(&(*shell)->tmp_buff);
	}
	return (0);
}
