/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 16:07:05 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/13 18:45:12 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_dir(t_file *lst, t_opt *opt, t_file *start)
{
	if (count_files(start) == 1 && !lst->dir && !lst->erref)
		return ;
	if (count_files(start) > 1)
	{
		ft_putstr(lst->path);
		ft_putendl(":");
	}
	if (S_ISDIR(lst->infos->st_mode) && lst->erref)
	{
		print_errors(lst);
		return ;
	}
	print_listed(lst->dir, opt);
	while (lst->dir)
	{
		if (recursable(lst->dir, opt))
			ft_print_dir_r(lst->dir, opt);
		lst->dir = lst->dir->next;
	}
}

void		ft_print_dir_r(t_file *lst, t_opt *opt)
{
	ft_putchar('\n');
	ft_putstr(lst->path);
	ft_putendl(":");
	if (S_ISDIR(lst->infos->st_mode) && lst->erref)
	{
		print_errors(lst);
		return ;
	}
	print_listed(lst->dir, opt);
	while (lst->dir)
	{
		if (recursable(lst->dir, opt))
			ft_print_dir_r(lst->dir, opt);
		lst->dir = lst->dir->next;
	}
}

void		print_list(t_file *lst, t_opt *opt)
{
	t_file	*start;
	int		flag;

	flag = 0;
	start = lst;
	while (lst)
	{
		if (lst->erref && !S_ISDIR(lst->infos->st_mode))
			print_errors(lst);
		lst = lst->next;
	}
	lst = start;
	while (lst)
	{
		if (!S_ISDIR(lst->infos->st_mode) && !lst->erref)
		{
			display_line(lst, opt, start);
			flag = 1;
		}
		lst = lst->next;
	}
	if (flag)
		ft_putchar('\n');
}

int			last_dir(t_file *lst)
{
	t_file		*start;

	start = lst;
	if (S_ISDIR(lst->infos->st_mode))
		lst = lst->next;
	while (lst)
	{
		if (S_ISDIR(lst->infos->st_mode))
		{
			lst = start;
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}

int			count_files(t_file *lst)
{
	int			count;
	t_file		*start;

	start = lst;
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	lst = start;
	return (count);
}
