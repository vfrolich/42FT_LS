/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:08:36 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/10 12:02:40 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t				get_largest_links(t_file *lst)
{
	size_t			largest;
	char			*tmp;

	largest = 0;
	if (lst->infos)
	{
		tmp = ft_itoa(lst->infos->st_nlink);
		largest = ft_strlen(tmp);
		ft_strdel(&tmp);
	}
	while (lst)
	{
		if (lst->infos)
		{
			tmp = ft_itoa(lst->infos->st_nlink);
			if (largest < ft_strlen(tmp))
				largest = ft_strlen(tmp);
			ft_strdel(&tmp);
		}
		lst = lst->next;
	}
	return (largest);
}

size_t				get_largest_user(t_file *lst)
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

size_t				get_largest_group(t_file *lst)
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

size_t				get_largest_size(t_file *lst)
{
	size_t			largest;
	char			*tmp2;
	t_file			*ltmp;

	ltmp = lst;
	largest = 0;
	tmp2 = ft_itoa(lst->infos->st_size);
	largest = ft_strlen(tmp2);
	ft_strdel(&tmp2);
	while (lst)
	{
		tmp2 = ft_itoa(lst->infos->st_size);
		if (ft_strlen(tmp2) > largest)
			largest = ft_strlen(tmp2);
		ft_strdel(&tmp2);
		lst = lst->next;
	}
	largest = largest + get_largest_min(ltmp) + get_largest_maj(ltmp);
	return (largest);
}
