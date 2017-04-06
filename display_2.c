/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 16:07:05 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/06 16:17:45 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_dir(t_file *lst, t_opt* opt)
{
	t_file	*start;
	t_file	*tmp;

	if (count_files(first) == 1 && !lst->dir && !lst->erref)
		return ;
	if (count_files(first) > 1)
	{
		ft_putstr(lst->name);
		ft_putendl(":");
	}
	if (S_ISDIR(lst->infos->st_mode) && lst->erref)
	{
		print_errors(lst);
		return ;
	}
	start = lst;
	while (lst->dir)
	{
		tmp = lst->dir;
		if (!lst->dir->erref)
			display_line(lst->dir, opt, start);
		lst->dir = lst->dir->next;
		lst_free_one(tmp);
	}
}

void		print_list(t_file *lst, t_opt *opt)
{
	t_file	*start;

	start = lst;
	while (start)
	{
		if (start->erref && !S_ISDIR(start->infos->st_mode))
			print_errors(start);
		start = start->next;
	}
	start = lst;
	while (lst)
	{
		if (!S_ISDIR(lst->infos->st_mode) && !lst->erref)
			display_line(lst, opt, start);
		lst = lst->next;
	}
	lst = start;
	if (!last_dir(start))
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
	int 		count;
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