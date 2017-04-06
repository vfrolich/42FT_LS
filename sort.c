/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 10:42:33 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/05 17:13:38 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sorted_list(t_file *lst)
{
	while (lst->next)
	{
		if (ft_strcmp(lst->name, lst->next->name) > 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_file	*swap_data(t_file *lst, t_file *lst2)
{
	t_file			*tmp;
	char			*tmp2;
	int				tmp3;
	struct stat		*tmp4;

	tmp2 = lst->name;
	lst->name = lst2->name;
	lst2->name = tmp2;
	tmp2 = lst->path;
	lst->path = lst2->path;
	lst2->path = tmp2;
	tmp4 = lst->infos;
	lst->infos = lst2->infos;
	lst2->infos = tmp4;
	tmp = lst->dir;
	lst->dir = lst2->dir;
	lst2->dir = tmp;
	tmp3 = lst->erref;
	lst->erref = lst2->erref;
	lst2->erref = tmp3;
	return (lst);
}

t_file	*sort_list(t_file *lst)
{
	t_file	*start;

	start = lst;
	while (lst->next)
	{
		if (lst->dir)
			lst->dir = sort_list(lst->dir);
		if (ft_strcmp(lst->name, lst->next->name) > 0)
			lst = swap_data(lst, lst->next);
		lst = lst->next;
	}
	if (lst->dir)
		lst->dir = sort_list(lst->dir);
	if (!sorted_list(start))
		start = sort_list(start);
	return (start);
}

int		sorted_r_list(t_file *lst)
{
	while (lst->next)
	{
		if (ft_strcmp(lst->name, lst->next->name) < 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_file	*sort_r_list(t_file *lst)
{
	t_file	*start;

	start = lst;
	while (lst->next)
	{
		if (lst->dir)
			lst->dir = sort_r_list(lst->dir);
		if (ft_strcmp(lst->name, lst->next->name) < 0)
			lst = swap_data(lst, lst->next);
		lst = lst->next;
	}
	if (lst->dir)
		lst->dir = sort_r_list(lst->dir);
	if (!sorted_r_list(start))
		start = sort_r_list(start);
	return (start);
}
