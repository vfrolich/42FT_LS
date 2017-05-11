/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 16:07:05 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/11 18:24:16 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_dir(t_file *lst, t_opt *opt, t_file *start)
{
	t_file	*tmp;

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
	tmp = lst->dir;
	while (lst->dir)
	{
		if (recursable(lst->dir, opt))
			ft_print_dir_r(lst->dir, opt);
		lst->dir = lst->dir->next;
	}
	lst->dir = tmp;
}

void		ft_print_dir_r(t_file *lst, t_opt *opt)
{
	t_file	*start;

	ft_putchar('\n');
	ft_putstr(lst->path);
	ft_putendl(":");
	if (S_ISDIR(lst->infos->st_mode) && lst->erref)
	{
		print_errors(lst);
		return ;
	}
	print_listed(lst->dir, opt);
	start = lst->dir;
	while (lst->dir)
	{
		if (recursable(lst->dir, opt))
			ft_print_dir_r(lst->dir, opt);
		lst->dir = lst->dir->next;
	}
	lst->dir = start;
}

void		print_list(t_file *lst, t_opt *opt)
{
	t_padd	*padding;
	int		flag;
	t_file	*start;

	flag = 0;
	start = lst;
	padding = padding_init(lst);
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
			display_line(lst, opt, padding);
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
