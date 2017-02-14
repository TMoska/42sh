/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 23:23:40 by moska             #+#    #+#             */
/*   Updated: 2017/01/30 17:31:03 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lst_clear(void **list_content, size_t *content_size)
{
  if (list_content)
    ft_memdel((void**)&(*list_content));
  (void)content_size;
}
