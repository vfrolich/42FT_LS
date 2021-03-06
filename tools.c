/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 11:30:27 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/13 17:46:38 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		lst_free_one(t_file *lst)
{
	ft_strdel(&lst->name);
	ft_strdel(&lst->path);
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

t_file		*check_for_opt(char *name, t_opt *opt, char *base_dir, t_file *lst)
{
	t_file	*new;

	if (name[0] == '.' && !opt->all)
		return (NULL);
	new = ft_listnew(name);
	new->path = ft_get_path(new, lst, base_dir);
	new->dir = ft_fill_info(new, base_dir, opt);
	return (new);
}

void		color(char *color, char *target, int fd)
{
	ft_putchar_fd('\033', fd);
	ft_putstr_fd(color, fd);
	ft_putstr_fd(target, fd);
	ft_putchar_fd('\033', fd);
	ft_putstr_fd(RESET, fd);
}
