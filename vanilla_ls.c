/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vanilla_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 20:18:00 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/13 17:41:23 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*arg_to_lst(char **argv)
{
	t_file	*start;
	t_file	*new;
	t_file	*tmp;

	start = ft_listnew(*argv);
	start->path = ft_strdup(start->name);
	tmp = start;
	argv++;
	while (*argv)
	{
		new = ft_listnew(*argv);
		new->path = ft_strdup(new->name);
		tmp->next = new;
		tmp = new;
		argv++;
	}
	return (start);
}

t_file	*fill_file(t_file *lst, t_opt *opt)
{
	t_file			*start;
	DIR				*dirptr;

	start = lst;
	while (lst)
	{
		lst->erref = fill_stats(lst);
		if (S_ISDIR(lst->infos->st_mode))
		{
			errno = 0;
			if (!(dirptr = opendir(lst->path)))
				lst->erref = errno;
			else if (!opt->recurs)
				lst->dir = fill_dir(lst, dirptr, opt);
			else
				lst->dir = ft_create_lst(dirptr, lst, lst->name, opt);
		}
		lst = lst->next;
	}
	return (start);
}

t_file	*fill_dir(t_file *lst, DIR *dirptr, t_opt *opt)
{
	t_file	*start;
	t_file	*new;
	t_file	*tmp;

	if (!opt->all)
	{
 		readdir(dirptr);
		readdir(dirptr);
	}
	if (!(start = rd_dir(dirptr)))
		return (NULL);
	start->path = ft_get_path(start, lst, NULL);
	start->erref = fill_stats(start);
	tmp = start;
	while ((new = rd_dir(dirptr)))
	{
		new->path = ft_get_path(new, lst, NULL);
		new->erref = fill_stats(new);
		tmp->next = new;
		tmp = new;
	}
	closedir(dirptr);
	return (start);
}

t_file	*rd_dir(DIR *dirptr)
{
	struct dirent	*info;
	t_file			*new;

	errno = 0;
	info = readdir(dirptr);
	if (errno)
	{
		new = ft_listnew("error");
		new->erref = errno;
		print_errors(new);
		return (new);
	}
	if (!info && !errno)
		return (NULL);
	new = ft_listnew(info->d_name);
	return (new);
}

int		fill_stats(t_file *lst)
{
	errno = 0;
	lstat(lst->path, lst->infos);
	return (errno);
}
