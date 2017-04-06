/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maj_min_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 16:02:02 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/06 16:48:00 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_min_maj(struct stat *filestat, t_file *lst)
{
	char	*tmp;
	char	*tmp2;
	char	*str;
	int		max;

	str = listed_add_groups(filestat, lst);
	max = get_largest_maj(lst) + 1;
	tmp = ft_itoa(major(filestat->st_rdev));
	tmp2 = padd_it(tmp, max);
	str = ft_strjoin_free(&str, &tmp2);
	ft_strdel(&tmp);
	str = ft_strjoin_free_one(&str, ",");
	max = get_largest_min(lst) + 1;
	tmp = ft_itoa(minor(filestat->st_rdev));
	tmp2 = padd_it(tmp, max);
	str = ft_strjoin_free(&str, &tmp2);
	ft_strdel(&tmp);
	return (str);
}

size_t	get_largest_maj(t_file *lst)
{
	size_t	largest;
	char	*tmp;

	tmp = ft_itoa(major(lst->infos->st_dev));
	largest = ft_strlen(tmp);
	ft_strdel(&tmp);
	while (lst)
	{
		if (lst->name[0] != '.')
		{
			tmp = ft_itoa(major(lst->infos->st_dev));
			if (ft_strlen(tmp) > largest)
				largest = ft_strlen(tmp);
			ft_strdel(&tmp);
		}
		lst = lst->next;
	}
	if (largest == 1)
		largest = 0;
	return (largest);
}

size_t	get_largest_min(t_file *lst)
{
	size_t	largest;
	char	*tmp;

	tmp = ft_itoa(minor(lst->infos->st_dev));
	largest = ft_strlen(tmp);
	ft_strdel(&tmp);
	while (lst)
	{
		if (lst->name[0] != '.')
		{
			tmp = ft_itoa(minor(lst->infos->st_dev));
			if (ft_strlen(tmp) > largest)
				largest = ft_strlen(tmp);
			ft_strdel(&tmp);
		}
		lst = lst->next;
	}
	if (largest == 1)
		largest = 0;
	return (largest);
}

// t_file	*lst_add(t_file *new, t_file *start)
// {
// 	if (!start)
// 	{
// 		start = new;
// 		return (start);
// 	}
// 	while (start->next)
// 		start = start->next;
// 	start->next = new;
// 	return (start);
// }