/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:52:52 by dteemo            #+#    #+#             */
/*   Updated: 2020/02/19 13:52:54 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_max_len(long long int max_len[5], t_file *lst, int opt)
{
	t_file		*cur;

	cur = lst;
	if (cur->next && cur->next->next == NULL && (opt & OPT_A) == 0)
		return (0);
	while (cur)
	{
		if ((opt & OPT_A) == 0 && cur->name[0] == '.')
		{
			cur = cur->next;
			continue;
		}
		if (get_ilen(cur->nlink) > max_len[0])
			max_len[0] = get_ilen(cur->nlink);
		if (get_ilen(cur->size) > max_len[1])
			max_len[1] = get_ilen(cur->size);
		if (ft_strlen(getpwuid(cur->uid)->pw_name) > (size_t)max_len[3])
			max_len[3] = ft_strlen(getpwuid(cur->uid)->pw_name);
		if (ft_strlen(getgrgid(cur->gid)->gr_name) > (size_t)max_len[4])
			max_len[4] = ft_strlen(getgrgid(cur->gid)->gr_name);
		if (cur->name[0] != '.' || (opt & OPT_A) != 0)
			max_len[2] += cur->blocks;
		cur = cur->next;
	}
	return (1);
}

int		print_time(time_t time)
{
	char	*s;
	char	**t_pars;
	int		i;

	ft_putchar(' ');
	s = ctime(&time);
	t_pars = ft_strsplit(s, ' ');
	s += 4;
	write(1, s, 6);
	ft_putstr(" ");
	if (ft_strcmp(t_pars[4], "2020\n") == 0)
		write(1, t_pars[3], 5);
	else
	{
		ft_putstr(" ");
		write(1, t_pars[4], 4);
	}
	ft_putstr(" ");
	i = 0;
	while (t_pars[i] != NULL)
		ft_memdel((void**)&t_pars[i++]);
	free(t_pars);
	return (1);
}

char	get_type(mode_t mode)
{
	mode = (mode & S_IFMT);
	if (S_ISREG(mode))
		return ('-');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISFIFO(mode))
		return ('p');
	return ('-');
}

char	get_acl(char full_path[PATH_MAX])
{
	acl_t	tmp;
	char	buf[101];

	if (listxattr(full_path, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_link_np(full_path, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}

int		get_mode(char m[12], mode_t mode, t_file *file)
{
	m[0] = get_type(mode);
	m[1] = (mode & S_IRUSR) ? 'r' : '-';
	m[2] = (mode & S_IWUSR) ? 'w' : '-';
	m[3] = (mode & S_IXUSR) ? 'x' : '-';
	m[4] = (mode & S_IRGRP) ? 'r' : '-';
	m[5] = (mode & S_IWGRP) ? 'w' : '-';
	m[6] = (mode & S_IXGRP) ? 'x' : '-';
	m[7] = (mode & S_IROTH) ? 'r' : '-';
	m[8] = (mode & S_IWOTH) ? 'w' : '-';
	m[9] = (mode & S_IXOTH) ? 'x' : '-';
	m[10] = get_acl(file->full_path);
	m[11] = '\0';
	if (S_ISUID & mode)
		m[3] = m[3] == '-' ? 'S' : 's';
	if (S_ISGID & mode)
		m[6] = m[6] == '-' ? 'S' : 's';
	if (S_ISVTX & mode)
		m[9] = m[9] == '-' ? 'T' : 't';
	ft_putstr(m);
	return (1);
}
