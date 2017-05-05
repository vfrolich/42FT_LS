/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:00:29 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/05 17:07:52 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_opt		*opt_fill(char *argv, t_opt *options)
{
	if (*argv != '-')
		return (options);
	while (*argv)
	{
		if (*argv == 'a')
			options->all = 1;
		if (*argv == 'l')
			options->list = 1;
		if (*argv == 'R')
			options->recurs = 1;
		if (*argv == 'r')
			options->reverse = 1;
		if (*argv == 't')
			options->t = 1;
		argv++;
	}
	return (options);
}

int			opt_check(char *av)
{
	char *tmp;

	tmp = av;
	if (*tmp == '-' && *(tmp + 1) == '-' && !*(tmp + 2))
		simple_ft_ls(".");
	if (av[0] != '-' || (av[0] == '-' && !av[1]))
		return (1);
	if (*av == '-')
	{
		av++;
		while (*av)
		{
			if (*av != 'a' && *av != 'l' && *av != 'R' && *av != 'r' &&
				*av != 't')
			{
				ft_putstr_fd("ft_ls: illegal option -- ", 2);
				ft_putchar_fd(*av, 2);
				ft_putchar_fd('\n', 2);
				ft_putendl_fd("usage: ft_ls [-lrRat] [file ...]", 2);
				exit(1);
			}
			av++;
		}
	}
	return (0);
}

t_opt		*opt_init(void)
{
	t_opt	*opt;

	if (!(opt = (t_opt *)malloc(sizeof(t_opt))))
	{
		ft_putendl_fd("malloc of t_opt* has failed", 2);
		exit(1);
	}
	opt->all = 0;
	opt->recurs = 0;
	opt->list = 0;
	opt->reverse = 0;
	opt->t = 0;
	return (opt);
}

void		simple_ft_ls(char *dir)
{
	DIR		*dirptr;
	t_file	*lst;
	t_file	*start;

	errno = 0;
	if (!(dirptr = opendir(dir)))
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	lst = get_files(dirptr, dir);
	start = lst;
	lst = sort_list(lst);
	while (lst)
	{
		if (lst->name[0] != '.')
			ft_putendl(lst->name);
		lst = lst->next;
	}
	closedir(dirptr);
	free_lst(start);
	exit(0);
}

t_file		*get_files(DIR *dirp, char *base_dir)
{
	t_file			*start;
	t_file			*new;
	t_file			*tmp;
	struct dirent	*dinfo;

	dinfo = readdir(dirp);
	start = ft_listnew(dinfo->d_name);
	start->path = ft_get_path(start, NULL, base_dir);
	lstat(start->path, start->infos);
	tmp = start;
	while ((dinfo = readdir(dirp)))
	{
		new = ft_listnew(dinfo->d_name);
		new->path = ft_get_path(new, NULL, base_dir);
		lstat(new->path, new->infos);
		tmp->next = new;
		tmp = new;
	}
	return (start);
}
