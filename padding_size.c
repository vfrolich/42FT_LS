/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:08:36 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/12 15:30:55 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "stdio.h"

size_t		get_largest_links(t_file *lst)
{
	size_t		largest;

	largest = 0;
	if (lst->infos)
		largest = ft_strlen(ft_itoa(lst->infos->st_nlink));
	while (lst)
	{
		if (lst->infos)
			if (largest < ft_strlen(ft_itoa(lst->infos->st_nlink)))
				largest = ft_strlen(ft_itoa(lst->infos->st_nlink));
		lst = lst->next;
	}
	return (largest);
}

size_t		get_largest_user(t_file *lst)
{
	size_t			largest;
	struct passwd	*uid;

	largest = 0;
	if (lst->infos)
	{
		uid = getpwuid(lst->infos->st_uid);
		if (uid)
			largest = ft_strlen(uid->pw_name);
	}
	while (lst)
	{
		if (lst->infos)
		{
			uid = getpwuid(lst->infos->st_uid);
			if (uid)
				if (ft_strlen(uid->pw_name) > largest)
					largest = ft_strlen(uid->pw_name);
		}
		lst = lst->next;
	}
	return (largest);
}

size_t		get_largest_group(t_file *lst)
{
	size_t			largest;
	struct group	*g_id;

	largest = 0;
	if (lst->infos)
	{	
		g_id = getgrgid(lst->infos->st_gid);
		if (g_id)
			largest = ft_strlen(g_id->gr_name);
	}
	while (lst)
	{
		if (lst->infos)
		{
			g_id = getgrgid(lst->infos->st_gid);
			if (g_id)
				if (ft_strlen(g_id->gr_name) > largest)
					largest = ft_strlen(g_id->gr_name);
		}	
		lst = lst->next;
	}
	return (largest);
}

size_t		get_largest_size(t_file *lst)
{
	size_t	largest;
	char	*tmp2;
	t_file	*ltmp;

	ltmp = lst;
	largest = 0;
	tmp2 = ft_itoa(lst->infos->st_size);
	if (lst->name[0] != '.')
		largest = ft_strlen(tmp2);
	ft_strdel(&tmp2);
	while (lst)
	{
		if (lst->name[0] != '.')
		{
			tmp2 = ft_itoa(lst->infos->st_size);
			if (ft_strlen(tmp2) > largest)
				largest = ft_strlen(tmp2);
			ft_strdel(&tmp2);
		}
		lst = lst->next;
	}
	largest = largest + get_largest_min(ltmp) + get_largest_maj(ltmp);
	return (largest);
}
