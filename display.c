/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:22:52 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/09 15:25:20 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	vanilla_ls(t_file *lst, t_opt *opt)
{
	t_file	*start;

	start = lst;
	print_list(lst, opt);
	if (start->dir && !start->next && !opt->recurs)
	{
		print_dir_one(start->dir, opt);
		return ;
	}
	while (lst)
	{
		if (!lst->erref)
		{
			if (S_ISDIR(lst->infos->st_mode))
			{
				ft_print_dir(lst, opt, start);
				if (!last_dir(lst))
					ft_putchar('\n');
			}
		}
		if (lst->erref && S_ISDIR(lst->infos->st_mode))
			print_errors(lst);
		lst = lst->next;
	}
}

int		recursable(t_file *lst, t_opt *opt)
{
	if (!lst || !S_ISDIR(lst->infos->st_mode))
		return (0);
	if (!ft_strcmp(lst->name, ".") || !ft_strcmp(lst->name, ".."))
		return (0);
	if (!opt->recurs)
		return (0);
	return (1);
}

int		check_for_empty(t_file *lst, t_opt *opt)
{
	if (opt->all)
		return (0);
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

	if (lst)
		lst = sort_handle(lst, opt);
	start = lst;
	if (!check_for_empty(lst, opt) && opt->list)
	{
		ft_putstr("total ");
		ft_putnbr(get_total_size(start, opt));
		ft_putchar('\n');
	}
	while (lst)
	{
		display_line(lst, opt, start);
		lst = lst->next;
	}
}

void	print_errors(t_file *lst)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(lst->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(lst->erref), 2);
}
