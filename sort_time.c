/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:25:31 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/09 19:46:55 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			sorted_list_t(t_file *lst)
{
	while (lst->next)
	{
		if (lst->infos->st_mtime == lst->next->infos->st_mtime)
		{
			if (ft_strcmp(lst->name, lst->next->name) > 0)
				return (0);
		}
		else if (lst->infos->st_mtime < lst->next->infos->st_mtime)
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_file		*sort_list_t(t_file *lst)
{
	t_file	*start;

	start = lst;
	while (lst->next)
	{
		if (lst->dir)
			lst->dir = sort_list_t(lst->dir);
		if (lst->infos->st_mtime == lst->next->infos->st_mtime)
		{
			if (ft_strcmp(lst->name, lst->next->name) > 0)
				swap_data(lst, lst->next);
		}
		else if (lst->infos->st_mtime < lst->next->infos->st_mtime)
			lst = swap_data(lst, lst->next);
		lst = lst->next;
	}
	if (lst->dir)
		lst->dir = sort_list_t(lst->dir);
	if (!sorted_list_t(start))
		start = sort_list_t(start);
	return (start);
}

int			sorted_r_list_t(t_file *lst)
{
	while (lst->next)
	{
		if (lst->infos->st_mtime == lst->next->infos->st_mtime)
		{
			if (ft_strcmp(lst->name, lst->next->name) < 0)
				return (0);
		}
		else if (lst->infos->st_mtime > lst->next->infos->st_mtime)
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_file		*sort_r_list_t(t_file *lst)
{
	t_file	*start;

	start = lst;
	while (lst->next)
	{
		if (lst->dir)
			lst->dir = sort_r_list_t(lst->dir);
		if (lst->infos->st_mtime == lst->next->infos->st_mtime)
		{
			if (ft_strcmp(lst->name, lst->next->name) < 0)
				swap_data(lst, lst->next);
		}
		else if (lst->infos->st_mtime > lst->next->infos->st_mtime)
			lst = swap_data(lst, lst->next);
		lst = lst->next;
	}
	if (lst->dir)
		lst->dir = sort_r_list_t(lst->dir);
	if (!sorted_r_list_t(start))
		start = sort_r_list_t(start);
	return (start);
}
