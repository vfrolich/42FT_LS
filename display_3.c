/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:33:43 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/06 16:27:31 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_line(t_file *lst, t_opt *opt, t_file *start)
{
	if (lst->erref)
		return ;
	if (lst->name[0] == '.')
	{
		if (opt->all && !opt->list)
			ft_putendl(lst->name);
		if (opt->all && opt->list)
			display_infos(lst, opt, start);
		return ;
	}
	if (opt->list)
		display_infos(lst, opt ,start);
	else
		ft_putendl(lst->name);
}

void	display_infos(t_file *lst, t_opt *opt, t_file *start)
{
	char	*str;
	t_file	*tmp;

	tmp = start;
	str = display_fill(lst->infos, start);
	ft_putstr(str);
	ft_strdel(&str);
	str = ft_strjoin(" ", lst->name);
	ft_putstr(str);
	ft_strdel(&str);
	read_link_path(lst);
	if (opt->recurs)
		ft_putendl("lol NOPE");
	start = tmp;
}

void	print_dir_one(t_file *lst, t_opt *opt)
{
	t_file	*start;
	
	start = lst;
	if (!check_for_empty(lst) && opt->list)
	{
		ft_putstr("total ");
		ft_putnbr(get_total_size(start));		
		ft_putchar('\n');
	}
	while (lst)
	{
		display_line(lst, opt, start);
		lst = lst->next;
	}
}