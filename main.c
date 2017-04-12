/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 10:23:08 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/12 15:50:26 by vfrolich         ###   ########.fr       */
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
		lst->dir = ft_create_lst(dirptr, lst, ".");
	lst = sort_handle(lst, opt);
	vanilla_ls(lst, opt);
	free_lst(lst);
}

int main(int argc, char **argv)
{
	t_opt	*options = NULL;
	// DIR 	*dirptr;
	t_file 	*lst;	
	// t_file	*start;

	if (argc < 2)
	{
		simple_ft_ls(".");
		return (0);
	}
	else
	{
		options = opt_init();		
		if (!opt_check(argv[1]))
		{
			options = opt_fill(argv[1]);			
			argv++;
		}
		argv++;
		if (!*argv)
			current_ls(options);
		else
		{
		lst = arg_to_lst(argv);
		lst = fill_file(lst, options);
		lst = sort_handle(lst, options);
		vanilla_ls(lst, options);
		free_lst(lst);
		}
	}
		// if (!(dirptr = opendir(argv[1])))
		// {
		// 	ft_putstr_fd("ft_ls: ", 2);
		// 	ft_putstr_fd(argv[1], 2);
		// 	ft_putstr_fd(": ", 2);
		// 	ft_putendl_fd(strerror(errno), 2);
		// 	return (-1);
		// }
		// lst = ft_create_lst(dirptr, NULL, argv[1]);
		// closedir(dirptr);
		// start = lst;
		// recursive_listed(lst);
		// free_lst(start);
	return (0);
}
