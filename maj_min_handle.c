/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maj_min_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 16:02:02 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/11 15:20:47 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_min_maj(struct stat *filestat, t_padd *padding)
{
	char	*tmp;
	char	*tmp2;
	char	*str;

	str = listed_display(filestat, padding);
	tmp = ft_itoa(major(filestat->st_rdev));
	tmp2 = padd_it(tmp, padding->maj);
	str = ft_strjoin_free(&str, &tmp2);
	ft_strdel(&tmp);
	str = ft_strjoin_free_one(&str, ",");
	tmp = ft_itoa(minor(filestat->st_rdev));
	tmp2 = padd_it(tmp, padding->min);
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
