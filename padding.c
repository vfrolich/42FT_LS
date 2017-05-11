/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:06:14 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/11 15:21:53 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*listed_display(struct stat *filestat, t_padd *padding)
{
	char			*str;
	struct passwd	*uid;
	struct group	*g_id;
	char			*tmp;
	char			*tmp2;

	str = ft_get_rights(filestat);
	tmp2 = ft_itoa(filestat->st_nlink);
	tmp = padd_it(tmp2, padding->links);
	ft_strdel(&tmp2);
	str = ft_strjoin_free(&str, &tmp);
	str = ft_strjoin_free_one(&str, " ");
	uid = getpwuid(filestat->st_uid);
	tmp = padd_it_left(uid->pw_name, padding->user);
	str = ft_strjoin_free(&str, &tmp);
	g_id = getgrgid(filestat->st_gid);
	tmp = padd_it_left(g_id->gr_name, padding->group);
	str = ft_strjoin_free(&str, &tmp);
	tmp2 = ft_itoa(filestat->st_size);
	tmp = padd_it(tmp2, padding->size);
	ft_strdel(&tmp2);
	str = ft_strjoin_free(&str, &tmp);
	return (str);
}

char	*padd_it(char *str, int max)
{
	char	*tmp;
	int		lenght;

	tmp = ft_strnew(max);
	lenght = ft_strlen(str);
	while (max >= 0)
	{
		if (lenght >= 0)
			tmp[max] = str[lenght];
		else
			tmp[max] = ' ';
		lenght--;
		max--;
	}
	return (tmp);
}

char	*padd_it_left(char *str, int max)
{
	char	*tmp;
	int		lenght;
	int		i;

	i = 0;
	tmp = ft_strnew(max);
	lenght = ft_strlen(str);
	while (i < lenght)
	{
		tmp[i] = str[i];
		i++;
	}
	while (i < max)
	{
		tmp[i] = ' ';
		i++;
	}
	return (tmp);
}
