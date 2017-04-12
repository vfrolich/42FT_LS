/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 11:43:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/10 17:53:23 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*ft_listnew(char *name)
{
	t_file	*new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
	{
		ft_putendl_fd("malloc of t_file* has failed", 2);
		exit(1);
	}
	if (!(new->name = (char *)malloc(sizeof(char) * ft_strlen(name) + 1)))
	{
		ft_putendl_fd("malloc of new->name(char *) has failed", 2);
		exit(1);
	}
	new->name = ft_strcpy(new->name, name);
	if (!(new->infos = (struct stat *)malloc(sizeof(struct stat))))
	{
		ft_putendl_fd("malloc of stat* has failed", 2);
		exit(1);
	}
	new->erref = 0;
	new->path = NULL;
	new->dir = NULL;
	new->next = NULL;
	return (new);
}

t_file		*ft_create_lst(DIR *dirp, t_file *lst, char *base_dir)
{
	t_file			*start;
	t_file			*new;
	t_file			*tmp;
	struct dirent	*dinfo;

	dinfo = readdir(dirp);
	start = ft_listnew(dinfo->d_name);
	start->path = ft_get_path(start, lst, base_dir);
	start->dir = ft_fill_info(start, base_dir);
	tmp = start;
	while ((dinfo = readdir(dirp)))
	{
		new = ft_listnew(dinfo->d_name);
		new->path = ft_get_path(new, lst, base_dir);
		new->dir = ft_fill_info(new, base_dir);
		tmp->next = new;
		tmp = new;
	}
	return (start);
}

t_file		*ft_fill_info(t_file *lst, char *base_dir)
{
	DIR				*dirp;

	lstat(lst->path, lst->infos);
	if (S_ISDIR(lst->infos->st_mode) && lst->name[0] != '.')
	{
		errno = 0;
		dirp = opendir(lst->path);
		if (dirp)
		{
			lst->dir = ft_create_lst(dirp, lst, base_dir);
			closedir(dirp);
			return (lst->dir);
		}
		lst->erref = errno;
	}
	return (NULL);
}

char		*ft_get_path(t_file *lst, t_file *dir, char *base_dir)
{
	char			*str;
	char			*tmp;

	if (!dir)
	{
		tmp = ft_strdup(base_dir);
		str = ft_strjoin(tmp, "/");
		ft_strdel(&tmp);
		tmp = str;
		str = ft_strjoin(tmp, lst->name);
		ft_strdel(&tmp);
		return (str);
	}
	tmp = ft_strdup(dir->path);
	str = ft_strjoin(tmp, "/");
	ft_strdel(&tmp);
	tmp = str;
	str = ft_strjoin(tmp, lst->name);
	ft_strdel(&tmp);
	return (str);
}
