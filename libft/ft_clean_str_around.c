/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_str_around.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 00:30:58 by moska             #+#    #+#             */
/*   Updated: 2017/02/16 20:55:57 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char *ft_clean_str_around(char *str, char c)
{
  size_t  len;
  int     beg;
  int     end;
  char    *new_str;

  len = ft_strlen(str);
  beg = 0;
  end = len;
  while (str[beg] == c)
    beg++;
  if (str[beg] == '\0')
    return (NULL);
  if (str[end - 1] == '\n')
    end--;
  while (str[end - 1] == c)
    end--;
  end = len - end;
  len = len - beg - end;
  new_str = ft_strnew(len);
  ft_strncpy(new_str, &str[beg], len);
  free (str);
  return (new_str);
}