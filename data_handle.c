/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:54:40 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/09 19:47:09 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_get_type(struct stat *filestat)
{
	if (S_ISDIR(filestat->st_mode))
		return ('d');
	if (S_ISSOCK(filestat->st_mode))
		return ('s');
	if (S_ISREG(filestat->st_mode))
		return ('-');
	if (S_ISBLK(filestat->st_mode))
		return ('b');
	if (S_ISFIFO(filestat->st_mode))
		return ('p');
	if (S_ISCHR(filestat->st_mode))
		return ('c');
	if (S_ISLNK(filestat->st_mode))
		return ('l');
	else
		return ('\0');
}

char	*ft_get_rights(struct stat *filestat)
{
	char	*str;

	if (!(str = ft_strnew(10)))
		return (NULL);
	str[0] = ft_get_type(filestat);
	str[1] = ((filestat->st_mode & S_IRUSR) == S_IRUSR) ? 'r' : '-';
	str[2] = ((filestat->st_mode & S_IWUSR) == S_IWUSR) ? 'w' : '-';
	if ((filestat->st_mode & S_ISUID) == S_ISUID)
		str[3] = ((filestat->st_mode & S_IXUSR) == S_IXUSR) ? 's' : 'S';
	else
		str[3] = ((filestat->st_mode & S_IXUSR) == S_IXUSR) ? 'x' : '-';
	str[4] = ((filestat->st_mode & S_IRGRP) == S_IRGRP) ? 'r' : '-';
	str[5] = ((filestat->st_mode & S_IWGRP) == S_IWGRP) ? 'w' : '-';
	if ((filestat->st_mode & S_ISGID) == S_ISGID)
		str[6] = ((filestat->st_mode & S_IXGRP) == S_IXGRP) ? 's' : 'S';
	else
		str[6] = ((filestat->st_mode & S_IXGRP) == S_IXGRP) ? 'x' : '-';
	str[7] = ((filestat->st_mode & S_IROTH) == S_IROTH) ? 'r' : '-';
	str[8] = ((filestat->st_mode & S_IWOTH) == S_IWOTH) ? 'w' : '-';
	if ((filestat->st_mode & S_ISVTX) == S_ISVTX)
		str[9] = ((filestat->st_mode & S_IXOTH) == S_IXOTH) ? 't' : 'T';
	else
		str[9] = ((filestat->st_mode & S_IXOTH) == S_IXOTH) ? 'x' : '-';
	return (str);
}

int		get_total_size(t_file *lst, t_opt *opt)
{
	int		total;
	t_file	*start;

	total = 0;
	start = lst;
	while (lst)
	{
		if (lst->name[0] == '.')
		{
			if (opt->all)
				total = total + lst->infos->st_blocks;
		}
		else
			total = total + lst->infos->st_blocks;
		lst = lst->next;
	}
	lst = start;
	return (total);
}

void	read_link_path(t_file *lst)
{
	char	buff[1024];
	int		ret;
	char	*tmp;

	if (S_ISLNK(lst->infos->st_mode))
	{
		errno = 0;
		ret = readlink(lst->path, buff, 1024);
		if (ret > 0)
		{
			buff[ret] = '\0';
			ft_putchar(' ');
			tmp = ft_strjoin("-> ", buff);
			ft_putendl(tmp);
			ft_strdel(&tmp);
			return ;
		}
		ft_putendl(strerror(errno));
	}
	else
		ft_putchar('\n');
}
