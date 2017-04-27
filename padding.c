/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:06:14 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/27 16:42:54 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*listed_display(struct stat *filestat, t_file *lst)
{
	char			*str;
	struct passwd	*uid;
	int				max;
	char			*tmp;
	char			*tmp2;

	str = ft_get_rights(filestat);
	max = get_largest_links(lst) + 2;
	tmp2 = ft_itoa(filestat->st_nlink);
	tmp = padd_it(tmp2, max);
	ft_strdel(&tmp2);
	str = ft_strjoin_free_one(&str, tmp);
	ft_strdel(&tmp);
	str = ft_strjoin_free_one(&str, " ");
	max = get_largest_user(lst) + 2;
	uid = getpwuid(filestat->st_uid);
	tmp = padd_it_left(uid->pw_name, max);
	str = ft_strjoin_free(&str, &tmp);
	return (str);
}

char	*listed_add_groups(struct stat *filestat, t_file *lst)
{
	int				max;
	struct group	*g_id;
	char			*tmp;
	char			*str;

	str = listed_display(filestat, lst);
	g_id = getgrgid(filestat->st_gid);
	max = get_largest_group(lst) + 2;
	tmp = padd_it_left(g_id->gr_name, max);
	str = ft_strjoin_free(&str, &tmp);
	return (str);
}

char	*display_fill(struct stat *filestat, t_file *lst)
{
	char	*str;
	int		max;
	char	*time;
	char	*tmp;


	if (S_ISBLK(filestat->st_mode) || S_ISCHR(filestat->st_mode))
		str = get_min_maj(filestat, lst);
	else
	{

		str = listed_add_groups(filestat, lst);
		max = get_largest_size(lst);
		time = ft_itoa(filestat->st_size);
		tmp = padd_it(time, max);
		ft_strdel(&time);
		str = ft_strjoin_free_one(&str, tmp);
		ft_strdel(&tmp);
	}
	str = time_check(filestat, str);
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
