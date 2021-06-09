/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:13:49 by dteemo            #+#    #+#             */
/*   Updated: 2020/02/19 13:13:50 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*f_name(const char *name)
{
	char	*res;
	int		i;
	int		j;
	int		count;

	res = (char*)malloc(sizeof(char) * PATH_MAX);
	i = 0;
	count = 0;
	while (name[i] != '\0')
		if (name[i++] == '/')
			count++;
	i = 0;
	j = 0;
	while (name[i] != '\0')
	{
		if (count == 0)
			res[j++] = name[i];
		if (name[i] == '/')
			count--;
		i++;
	}
	res[j] = '\0';
	return (res);
}

int		get_path(char path[PATH_MAX], const char *arg)
{
	int		j;

	j = -1;
	if (arg[0] == '.' && arg[1] == '\0')
		arg++;
	if (arg[0] != '/')
	{
		path[1] = '/';
		while (arg[++j] != '\0')
			path[j + 2] = arg[j];
		path[j + 2] = '\0';
		if (path[2] == '\0' && path[1] == '/')
			path[1] = '\0';
	}
	else
	{
		while (arg[++j] != '\0')
			path[j] = arg[j];
		path[j] = '\0';
	}
	return (1);
}

char	**rev_argv(char **argv, int argc, int i, int er[1024])
{
	int		j;
	int		a;
	char	*s;

	j = 0;
	while (j < (argc - i) / 2)
	{
		a = er[i + j];
		er[i + j] = er[argc - j - 1];
		er[argc - j - 1] = a;
		s = argv[i + j];
		argv[i + j] = argv[argc - j - 1];
		argv[argc - j - 1] = s;
		j++;
	}
	return (argv);
}

int		put_error(char *name, int error)
{
	char	*s;

	if (error == 1)
	{
		ft_putstr("ft_ls: illegal option -- ");
		ft_putchar(*name);
		ft_putstr("\nusage: ft_ls [-Ralrt] [file ...]\n");
		exit(EXIT_FAILURE);
	}
	if (error == 2)
	{
		if (errno == 20)
			return (0);
		s = f_name(name);
		ft_putstr("ft_ls: ");
		ft_putstr(s);
		ft_putstr(": ");
		ft_putstr(strerror(errno));
		ft_putchar('\n');
		ft_memdel((void**)&s);
	}
	if (error == 0)
		exit(EXIT_FAILURE);
	return (0);
}

void	print_head(char *path, int fst)
{
	if (fst != 0)
		ft_putstr("\n");
	ft_putstr(path);
	ft_putstr(":\n");
}
