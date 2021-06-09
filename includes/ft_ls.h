/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:18:09 by dteemo            #+#    #+#             */
/*   Updated: 2020/01/22 17:18:11 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <errno.h>
# include <pwd.h>
# include <time.h>
# include <grp.h>
# include <unistd.h>
# include "libft.h"

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_file{
	char			*name;
	char			*full_path;
	time_t			time;
	long			ntime;
	uid_t			uid;
	gid_t			gid;
	off_t			size;
	nlink_t			nlink;
	dev_t			rdev;
	mode_t			mode;
	blkcnt_t		blocks;
	struct s_file	*next;
}						t_file;

# define OPT_L 1
# define OPT_RR 2
# define OPT_A 4
# define OPT_R 8
# define OPT_T 16

t_file					*init_files_list(DIR *dir, const char path[PATH_MAX]);
t_file					*print_list(t_file *lst, int opt);
char					*ft_llitoa(long long int a);
int						get_ilen(long long int a);
void					put_nchar(char c, int n);
t_file					*sort(t_file *lst, int opt);
char					**rev_argv(char **argv, int argc, int i, int er[1024]);
void					lst_del(t_file *lst);
char					get_type(mode_t mode);
int						put_error(char *name, int error);
int						read_dir(char full_path[PATH_MAX], unsigned int opt,
int head, int fst);
int						do_opt_rr(t_file *lst, char *full_path, int opt);
t_file					*add_new_file(char *name, char full_path[PATH_MAX]);
int						get_path(char path[PATH_MAX], const char *arg);
int						ndir_file(char full_path[PATH_MAX], int opt);
char					*f_name(const char *name);
void					print_head(char *path, int fst);
int						get_opt(char *s, int opt);
int						get_max_len(long long int max_len[5],
t_file *lst, int opt);
int						print_time(time_t time);
char					get_acl(char full_path[PATH_MAX]);
int						get_mode(char m[12], mode_t mode, t_file *file);
char					**sort_argv(char **av, int i, int ac);
t_file					*get_prev(t_file *lst, t_file *cur);
void					put_link(t_file *cur);

#endif
