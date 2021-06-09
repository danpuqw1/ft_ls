/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:27:34 by dteemo            #+#    #+#             */
/*   Updated: 2020/01/27 14:27:36 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*rev_s(char *s)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	res = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		res[i] = s[len - i - 1];
		i++;
	}
	res[i] = '\0';
	ft_memdel((void**)&s);
	return (res);
}

char	*ft_llitoa(long long int a)
{
	char	*res;
	int		otr;
	int		i;

	if (a < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	otr = (a < 0) ? -1 : 1;
	a *= otr;
	i = 0;
	if (a == 0)
		return (ft_strdup("0"));
	res = (char*)malloc(sizeof(char) * 21);
	while (a > 0)
	{
		res[i++] = '0' + a % 10;
		a = a / 10;
	}
	if (otr == -1)
		res[i++] = '-';
	res[i] = '\0';
	res = rev_s(res);
	return (res);
}

int		get_ilen(long long int a)
{
	int		res;

	res = 0;
	while (a > 0)
	{
		res++;
		a = a / 10;
	}
	return (res);
}

void	put_nchar(char c, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

char	**sort_argv(char **av, int i, int ac)
{
	int		j;
	int		b;
	char	*a;

	b = i;
	while (i < ac - 1)
	{
		j = b;
		while (j < ac - 1)
		{
			if (ft_strcmp(av[j], av[j + 1]) > 0)
			{
				a = av[j];
				av[j] = av[j + 1];
				av[j + 1] = a;
			}
			j++;
		}
		i++;
	}
	return (av);
}
