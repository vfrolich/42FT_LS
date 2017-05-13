/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:22:52 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/13 15:11:43 by vfrolich         ###   ########.fr       */
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
			print_errors(lst, opt);
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
	t_file *tmp;

	tmp = lst;
	if (opt->all)
		return (0);
	while (lst)
	{
		if (ft_strcmp(lst->name, ".") && ft_strcmp(lst->name, ".."))
		{
			lst = tmp;
			return (0);
		}
		lst = lst->next;
	}
	lst = tmp;
	return (1);
}

void	print_listed(t_file *lst, t_opt *opt)
{
	t_padd	*padding;

	padding = padding_init(lst);
	if (lst)
		lst = sort_handle(lst, opt);
	if (!check_for_empty(lst, opt) && opt->list)
	{
		ft_putstr("total ");
		ft_putnbr(get_total_size(lst, opt));
		ft_putchar('\n');
	}
	while (lst)
	{
		display_line(lst, opt, padding);
		lst = lst->next;
	}
	if (padding)
		free(padding);
}

void	print_errors(t_file *lst, t_opt *opt)
{
	if (!opt->color)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(lst->name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(lst->erref), 2);
		return ;
	}
	color(RED, "ft_ls: ", 2);
	color(RED, lst->name, 2);
	color(RED, ": ", 2);
	color(RED, strerror(lst->erref), 2);
	ft_putchar_fd('\n', 2);
}
