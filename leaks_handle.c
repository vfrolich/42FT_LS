/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 11:30:27 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/06 14:22:19 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		lst_free_one(t_file *lst)
{
	ft_strdel(&lst->name);
	ft_strdel(&lst->path);
	if (lst->infos)
		free(lst->infos);
	lst->next = NULL;
	if (lst->dir)
		free_lst(lst->dir);
	free(lst);
}

void		free_lst(t_file *lst)
{
	t_file	*tmp;

	while (lst)
	{
		tmp = lst->next;
		lst_free_one(lst);
		lst = tmp;
	}
	lst = NULL;
}
