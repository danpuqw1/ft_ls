/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:01:11 by dteemo            #+#    #+#             */
/*   Updated: 2020/01/27 14:01:13 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putstr_del(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
		ft_putchar(s[i++]);
	ft_memdel((void**)&s);
}

int		print(t_file *lst, int opt)
{
	t_file			*cur;

	cur = lst;
	while (cur)
	{
		if ((opt & OPT_A) == 0 && cur->name[0] == '.')
		{
			cur = cur->next;
			continue ;
		}
		ft_putstr(cur->name);
		ft_putchar('\n');
		cur = cur->next;
	}
	return (1);
}

int		put_all_pars(t_file *cur, long long int max_len[5], int opt)
{
	char			m[12];

	if ((opt & OPT_A) == 0 && cur->name[0] == '.')
		return (0);
	get_mode(m, cur->mode, cur);
	put_nchar(' ', 1 + max_len[0] - get_ilen(cur->nlink));
	ft_putstr_del(ft_llitoa(cur->nlink));
	put_nchar(' ', 1);
	ft_putstr(getpwuid(cur->uid)->pw_name);
	put_nchar(' ', 2 + max_len[3] - ft_strlen(getpwuid(cur->uid)->pw_name));
	ft_putstr(getgrgid(cur->gid)->gr_name);
	put_nchar(' ', max_len[4] - ft_strlen(getgrgid(cur->gid)->gr_name));
	put_nchar(' ', max_len[1] - get_ilen(cur->size) + 2);
	ft_putstr_del(ft_llitoa(cur->size));
	print_time(cur->time);
	ft_putstr(cur->name);
	if (m[0] == 'l')
		put_link(cur);
	ft_putchar('\n');
	return (1);
}

int		print_l(t_file *lst, int opt)
{
	t_file			*cur;
	long long int	max_len[5];

	cur = lst;
	max_len[0] = 0;
	max_len[1] = 0;
	max_len[2] = 0;
	max_len[3] = 0;
	max_len[4] = 0;
	if (get_max_len(max_len, lst, opt) == 0)
		return (0);
	if (cur->next)
	{
		ft_putstr("total ");
		ft_putstr_del(ft_llitoa(max_len[2]));
		ft_putstr("\n");
	}
	while (cur)
	{
		put_all_pars(cur, max_len, opt);
		cur = cur->next;
	}
	return (1);
}

t_file	*print_list(t_file *lst, int opt)
{
	lst = sort(lst, opt);
	if ((opt & OPT_L) != 0)
		print_l(lst, opt);
	else
		print(lst, opt);
	return (lst);
}
