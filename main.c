/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 10:23:08 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/06 17:04:32 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	t_opt	*options = NULL;
	// DIR 	*dirptr;
	t_file 	*lst;	
	t_file	*start;

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
		if (*argv)
		{
		start = arg_to_lst(argv);
		lst = start;
		lst = fill_file(lst);
		lst = start;
		lst = sort_handle(lst, options);
		first = lst;
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