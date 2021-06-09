/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:29:02 by dteemo            #+#    #+#             */
/*   Updated: 2020/01/29 14:29:03 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*swap(t_file *a, t_file *b, t_file *prev)
{
	a->next = b->next;
	b->next = a;
	if (prev)
	{
		prev->next = b;
		return (prev);
	}
	else
	{
		return (b);
	}
}

t_file	*sort_t(t_file *lst)
{
	t_file	*begin;
	t_file	*prev;

	begin = lst;
	prev = NULL;
	while (lst)
	{
		if (lst->next && lst->time < lst->next->time)
		{
			lst = swap(lst, lst->next, prev);
			prev = get_prev(begin, lst);
			if (prev == NULL)
				begin = lst;
			continue ;
		}
		if (lst)
		{
			prev = lst;
			lst = lst->next;
		}
	}
	return (begin);
}

t_file	*sort_asc(t_file *lst)
{
	t_file	*begin;
	t_file	*prev;

	begin = lst;
	prev = NULL;
	while (lst)
	{
		if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
		{
			lst = swap(lst, lst->next, prev);
			prev = get_prev(begin, lst);
			if (prev == NULL)
				begin = lst;
			continue ;
		}
		if (lst)
		{
			prev = lst;
			lst = lst->next;
		}
	}
	return (begin);
}

t_file	*rev_lst(t_file *lst)
{
	t_file	*a;
	t_file	*b;
	t_file	*c;

	a = NULL;
	b = lst;
	c = lst->next;
	while (b)
	{
		c = b->next;
		b->next = a;
		a = b;
		b = c;
	}
	return (a);
}

t_file	*sort(t_file *lst, int opt)
{
	lst = sort_asc(lst);
	if ((opt & OPT_T) != 0)
		lst = sort_t(lst);
	if ((opt & OPT_R) != 0)
		lst = rev_lst(lst);
	return (lst);
}
