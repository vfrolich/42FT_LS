/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:35:49 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/27 16:53:44 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_file		*sort_handle(t_file *lst, t_opt *opt)
{
	if (opt->t && opt->reverse)
		return (sort_r_list_t(lst));
	if (opt->t && !opt->reverse)
		return (sort_list_t(lst));
	if (!opt->t && opt->reverse)
		return (sort_r_list(lst));
	return (sort_list(lst));
}

char		*time_check(struct stat *filestat, char *str)
{
	time_t 	t;
	char	*time_str;
	char	*tmp;

	time_str = ctime(&filestat->st_mtime);
	str = ft_strjoin_free_one(&str, " ");
	t = time(NULL);
	if (filestat->st_mtime > t || (t - filestat->st_mtime) > 15724800)
	{
		tmp = ft_strsub(time_str, 4, 7);
		str = ft_strjoin_free(&str, &tmp);
		str = ft_strjoin_free_one(&str, " ");
		tmp = ft_strsub(time_str, 20, 4);
		str = ft_strjoin_free(&str, &tmp);
		return (str);
	}
	tmp = ft_strsub(time_str, 4, 12);
	str = ft_strjoin_free(&str, &tmp);
	return (str);
}
