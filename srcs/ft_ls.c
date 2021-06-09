/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:12:21 by dteemo            #+#    #+#             */
/*   Updated: 2020/01/22 17:12:23 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		read_dir(char full_path[PATH_MAX], unsigned int opt, int head, int fst)
{
	DIR		*dir;
	t_file	*lst;

	dir = opendir(full_path);
	if (head == 1)
		print_head(full_path, fst);
	if (!dir)
	{
		put_error(full_path, 2);
		return (0);
	}
	lst = init_files_list(dir, full_path);
	closedir(dir);
	lst = print_list(lst, opt);
	if ((opt & OPT_RR) != 0)
		do_opt_rr(lst, full_path, opt);
	lst_del(lst);
	return (1);
}

void	p_er(int er[1024], char path[PATH_MAX], int i, char **av)
{
	DIR		*dir;

	dir = opendir(path);
	if (!dir)
	{
		if (errno == 2 || errno == 20)
		{
			er[0] = 1;
			er[i] = 1;
			(er[1022] == 0) ? put_error(av[i], 2) : ndir_file(path, er[1023]);
		}
	}
	else
		closedir(dir);
}

void	get_ers(int er[1024], int ac, char **av, int i)
{
	int		j;
	int		a;
	char	path[PATH_MAX];

	j = 1;
	a = i;
	while (j < 1023)
		er[j++] = 0;
	path[0] = '.';
	while (i < ac)
	{
		get_path(path, av[i]);
		p_er(er, path, i, av);
		i++;
	}
	i = a;
	er[1022]++;
	while (i < ac)
	{
		get_path(path, av[i]);
		p_er(er, path, i, av);
		i++;
	}
}

int		opt_er(int *opt, int argc, char **argv, int er[1024])
{
	int		i;
	int		j;
	char	path[1024];

	i = 1;
	*opt = 0;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
		*opt = get_opt(argv[i++], *opt);
	argv = sort_argv(argv, i, argc);
	if (i == argc)
	{
		path[0] = '.';
		path[1] = '\0';
		read_dir(path, *opt, 0, 1);
	}
	er[1023] = *opt;
	get_ers(er, argc, argv, i);
	if (*opt & OPT_R)
		argv = rev_argv(argv, argc, i, er);
	j = i;
	return (j);
}

int		main(int argc, char **argv)
{
	char	path[PATH_MAX];
	int		i;
	int		j;
	int		opt;
	int		er[1024];

	path[0] = '.';
	er[0] = 0;
	i = opt_er(&opt, argc, argv, er);
	j = i;
	while (i < argc)
	{
		if (er[i] == 0)
		{
			get_path(path, argv[i]);
			if (argc - j > 1)
				(er[0] == 0) ? print_head(argv[i], 0) : print_head(argv[i], 1);
			read_dir(path, opt, 0, 1);
			er[0] = 1;
		}
		i++;
	}
	return (0);
}
