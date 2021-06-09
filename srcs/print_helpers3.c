/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:54:53 by student           #+#    #+#             */
/*   Updated: 2020/04/13 17:01:54 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_link(t_file *cur)
{
	char	buf[NAME_MAX + 1];
	int		i;

	i = 0;
	while (i < NAME_MAX + 1)
		buf[i++] = '\0';
	ft_putstr(" -> ");
	readlink(cur->full_path, buf, NAME_MAX);
	ft_putstr(buf);
}
