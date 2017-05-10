/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 11:43:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/10 12:14:47 by vfrolich         ###   ########.fr       */
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

void		lst_add(t_file *new, t_file **start)
{
	t_file *tmp;

	tmp = NULL;
	if (!new)
		return ;
	if (start)
		tmp = *start;
	if (!tmp)
	{
		*start = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_file		*ft_create_lst(DIR *dirp, t_file *lst, char *base_dir, t_opt *opt)
{
	t_file			*start;
	t_file			*new;
	struct dirent	*dinfo;

	dinfo = readdir(dirp);
	start = check_for_opt(dinfo->d_name, opt, base_dir, lst);
	lst_add(NULL, &start);
	while ((dinfo = readdir(dirp)))
	{
		new = check_for_opt(dinfo->d_name, opt, base_dir, lst);
		lst_add(new, &start);
	}
	closedir(dirp);
	return (start);
}

t_file		*ft_fill_info(t_file *lst, char *base_dir, t_opt *opt)
{
	DIR				*dirp;

	lstat(lst->path, lst->infos);
	if ((lst->name[0] == '.' && !opt->all) ||
		(!ft_strcmp(lst->name, ".") || !ft_strcmp(lst->name, "..")))
		return (NULL);
	if (S_ISDIR(lst->infos->st_mode) && opt->recurs)
	{
		errno = 0;
		dirp = opendir(lst->path);
		if (dirp)
		{
			lst->dir = ft_create_lst(dirp, lst, base_dir, opt);
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
