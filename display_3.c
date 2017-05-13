/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:33:43 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/13 15:02:32 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_line(t_file *lst, t_opt *opt, t_padd *padding)
{
	if (lst->name[0] == '.')
	{
		if (opt->all && !opt->list)
			ft_putendl(lst->name);
		else if (opt->all && opt->list)
			display_infos(lst, padding, opt);
		return ;
	}
	if (opt->list)
		display_infos(lst, padding, opt);
	else
		ft_putendl(lst->name);
}

void	display_infos(t_file *lst, t_padd *padding, t_opt *opt)
{
	char	*str;

	if (S_ISBLK(lst->infos->st_mode) || S_ISCHR(lst->infos->st_mode))
		str = get_min_maj(lst->infos, padding);
	else
		str = listed_display(lst->infos, padding);
	str = time_check(lst->infos, str);
	ft_putstr(str);
	ft_strdel(&str);
	str = ft_strjoin(" ", lst->name);
	if (opt->color && S_ISDIR(lst->infos->st_mode))
		color(CYAN, str, 1);
	else
		ft_putstr(str);
	ft_strdel(&str);
	read_link_path(lst);
}

void	print_dir_one(t_file *lst, t_opt *opt)
{
	t_padd	*padding;

	padding = padding_init(lst);
	if (!check_for_empty(lst, opt) && opt->list)
	{
		ft_putstr("total ");
		ft_putnbr(get_total_size(lst, opt));
		ft_putchar('\n');
	}
	while (lst)
	{
		display_line(lst, opt, padding);
		lst = lst->next;
	}
	if (padding)
		free(padding);
}

t_padd	*padding_init(t_file *lst)
{
	t_padd	*padding;

	if (!lst)
		return (NULL);
	if (!(padding = (t_padd *)malloc(sizeof(t_padd))))
	{
		ft_putendl_fd("malloc of t_padd* has failed", 2);
		exit(1);
	}
	padding->links = 0;
	padding->user = 0;
	padding->group = 0;
	padding->size = 0;
	padding->maj = 0;
	padding->min = 0;
	padding = get_padding(lst, padding);
	return (padding);
}

t_padd	*get_padding(t_file *lst, t_padd *padd)
{
	t_file *tmp;

	tmp = lst;
	padd->links = get_largest_links(tmp) + 2;
	tmp = lst;
	padd->user = get_largest_user(tmp) + 2;
	tmp = lst;
	padd->group = get_largest_group(tmp) + 2;
	tmp = lst;
	padd->size = get_largest_size(tmp);
	tmp = lst;
	padd->maj = get_largest_maj(tmp);
	tmp = lst;
	padd->min = get_largest_min(tmp);
	return (padd);
}
