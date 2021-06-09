/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:23:18 by dteemo            #+#    #+#             */
/*   Updated: 2020/01/22 18:23:21 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*get_prev(t_file *lst, t_file *cur)
{
	t_file	*a;
	t_file	*prev;

	a = lst;
	prev = NULL;
	while (a)
	{
		if (ft_strcmp(a->full_path, cur->full_path) == 0)
			return (prev);
		prev = a;
		if (a)
			a = a->next;
	}
	return (NULL);
}

void	lst_del(t_file *lst)
{
	t_file	*next;

	while (lst)
	{
		next = lst->next;
		ft_memdel((void **)&lst->name);
		ft_memdel((void **)&lst->full_path);
		free(lst);
		lst = next;
	}
}

int		get_full_path(char full_path[PATH_MAX], const char path[PATH_MAX]
, char *name)
{
	int		i;
	int		j;

	i = 0;
	while (path[i] != '\0')
	{
		full_path[i] = path[i];
		i++;
	}
	if (full_path[i - 1] != '/')
		full_path[i++] = '/';
	j = 0;
	while (name[j] != '\0')
	{
		full_path[i + j] = name[j];
		j++;
	}
	full_path[i + j] = name[j];
	return (1);
}

t_file	*add_new_file(char *name, char full_path[PATH_MAX])
{
	t_file	*new;
	t_stat	*stat;

	stat = (t_stat*)malloc(sizeof(t_stat));
	lstat(full_path, stat);
	if (!(new = (t_file*)malloc(sizeof(t_file))))
		put_error(name, 0);
	if ((!(new->name = ft_strdup(name))))
		put_error(name, 0);
	new->full_path = ft_strdup(full_path);
	new->time = stat->st_mtimespec.tv_sec;
	new->ntime = stat->st_mtimespec.tv_nsec;
	new->gid = stat->st_gid;
	new->uid = stat->st_uid;
	new->mode = stat->st_mode;
	new->nlink = stat->st_nlink;
	new->rdev = stat->st_rdev;
	new->blocks = stat->st_blocks;
	new->size = stat->st_size;
	new->next = NULL;
	free(stat);
	return (new);
}

t_file	*init_files_list(DIR *dir, const char path[PATH_MAX])
{
	t_dirent	*cur;
	t_file		*first;
	t_file		*cur_f;
	t_file		*new;
	char		full_path[PATH_MAX];

	first = NULL;
	cur_f = NULL;
	while ((cur = readdir(dir)) != NULL)
	{
		get_full_path(full_path, path, cur->d_name);
		if (!first)
			first = add_new_file(cur->d_name, full_path);
		else
		{
			if (!cur_f)
				cur_f = first;
			new = add_new_file(cur->d_name, full_path);
			cur_f->next = new;
			cur_f = cur_f->next;
		}
	}
	return (first);
}
