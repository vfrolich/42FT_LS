/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 10:23:08 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/13 17:43:13 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	current_ls(t_opt *opt)
{
	t_file	*lst;
	DIR		*dirptr;

	lst = ft_listnew(".");
	lst->path = ft_strdup(lst->name);
	dirptr = opendir(".");
	lst->erref = fill_stats(lst);
	if (!opt->recurs)
		lst->dir = fill_dir(lst, dirptr, opt);
	else
		lst->dir = ft_create_lst(dirptr, lst, ".", opt);
	lst = sort_handle(lst, opt);
	vanilla_ls(lst, opt);
	free_lst(lst);
}

void	ft_ls(char **argv, t_opt *opt, int i)
{
	t_file	*lst;

	while (i > 0)
	{
		i--;
		argv++;
	}
	lst = arg_to_lst(argv);
	lst = fill_file(lst, opt);
	lst = sort_handle(lst, opt);
	vanilla_ls(lst, opt);
	free_lst(lst);
}

int		main(int argc, char **argv)
{
	t_opt	*options;
	int		i;

	if (argc < 2)
	{
		simple_ft_ls(".");
		return (0);
	}
	i = 1;
	options = opt_init();
	while (i < argc && !opt_check(argv[i]))
	{
		options = opt_fill(argv[i], options);
		i++;
	}
	if (i == argc)
		current_ls(options);
	else
		ft_ls(argv, options, i);
	free(options);
	return (0);
}
