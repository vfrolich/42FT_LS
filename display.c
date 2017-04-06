/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:22:52 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/06 16:19:21 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	vanilla_ls(t_file *lst, t_opt *opt)
{
	t_file	*start;

	start = lst;
	print_list(lst, opt);
	if (start->dir && !start->next)
	{
		print_dir_one(start->dir, opt);
		return ;
	}
	lst = start;
	while (start)
	{
		if (S_ISDIR(start->infos->st_mode))
		{
			ft_print_dir(start, opt);
			if (!last_dir(start))
				ft_putchar('\n');
		}
 		start = start->next;
	}
}

// void	recursive_listed(t_file *lst)
// {
// 	lst = sort_list(lst);
// 	print_listed(lst);
// 	while (lst)
// 	{
// 		if (lst->dir && lst->name[0] != '.')
// 		{
// 			ft_putstr(lst->path);
// 			ft_putendl(":");
// 			recursive_listed(lst->dir);
// 		}
// 		if (!lst->dir && lst->erref)
// 		{
// 			ft_putstr(lst->path);
// 			ft_putendl(":");
// 			print_errors(lst);
// 			ft_putchar('\n');
// 		}
// 		lst = lst->next;
// 	}
// }

int		check_for_empty(t_file *lst)
{
	while (lst)
	{
		if (ft_strcmp(lst->name, ".") && ft_strcmp(lst->name, ".."))
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	print_listed(t_file *lst, t_opt *opt)
{
	t_file	*start;
	t_file	*tmp;

	start = lst;
	if (!check_for_empty(lst) && opt->list)
	{
		ft_putstr("total ");
		ft_putnbr(get_total_size(start));		
		ft_putchar('\n');
	}
	while (lst)
	{
		tmp = lst;
		display_line(lst, opt, start);
		lst = lst->next;
		lst_free_one(tmp);
	}
	lst = start;
	ft_putchar('\n');
}

void	print_errors(t_file *lst)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(lst->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(lst->erref), 2);
}
