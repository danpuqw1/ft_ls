/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:50:07 by dteemo            #+#    #+#             */
/*   Updated: 2020/02/05 14:50:08 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		add_full_path(char full_path[PATH_MAX], char *s)
{
	int		i;

	i = 0;
	while (full_path[i] != '\0')
		i++;
	if (full_path[i - 1] != '/')
		full_path[i++] = '/';
	while (*s != '\0')
		full_path[i++] = *s++;
	full_path[i] = '\0';
	return (1);
}

int		do_opt_rr(t_file *lst, char *full_path, int opt)
{
	char	*full_path_modif;

	while (lst)
	{
		if (get_type(lst->mode) == 'd' && ft_strcmp(lst->name, "..") != 0
		&& ft_strcmp(lst->name, ".") != 0)
		{
			if ((opt & OPT_A) == 0 && lst->name[0] == '.')
			{
				lst = lst->next;
				continue;
			}
			full_path_modif = (char*)malloc(sizeof(char) * PATH_MAX);
			ft_strcpy(full_path_modif, full_path);
			add_full_path(full_path_modif, lst->name);
			read_dir(full_path_modif, opt, 1, 1);
			ft_memdel((void**)&full_path_modif);
		}
		lst = lst->next;
	}
	return (1);
}

int		get_opt(char *s, int opt)
{
	int		res;
	int		i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i] != '\0')
	{
		if (ft_strchr("lrtaR", s[i]) == 0)
			put_error(&s[i], 1);
		i++;
	}
	res = opt;
	if (ft_strchr(s, 'l') != 0 && (opt & OPT_L) == 0)
		res += OPT_L;
	if (ft_strchr(s, 'R') != 0 && (opt & OPT_RR) == 0)
		res += OPT_RR;
	if (ft_strchr(s, 'r') != 0 && (opt & OPT_R) == 0)
		res += OPT_R;
	if (ft_strchr(s, 't') != 0 && (opt & OPT_T) == 0)
		res += OPT_T;
	if (ft_strchr(s, 'a') != 0 && (opt & OPT_A) == 0)
		res += OPT_A;
	return (res);
}

int		get_name(char full_path[PATH_MAX], char name[PATH_MAX])
{
	int		i;
	int		c[3];

	i = 0;
	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	while (full_path[i++] != 0)
		if (full_path[i] == '/')
			c[0]++;
	i = 0;
	while (full_path[i] != '\0')
	{
		if (c[0] == c[1])
			name[c[2]++] = full_path[i];
		if (full_path[i] == '/')
			c[1]++;
		i++;
	}
	name[c[2]] = '\0';
	return (1);
}

int		ndir_file(char full_path[PATH_MAX], int opt)
{
	char	name[PATH_MAX];
	t_file	*f;

	if (errno != 20)
		return (1);
	get_name(full_path, name);
	f = add_new_file(name, full_path);
	f = print_list(f, opt);
	lst_del(f);
	return (1);
}
