/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:35:49 by vfrolich          #+#    #+#             */
/*   Updated: 2017/04/19 18:05:07 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*sort_handle(t_file *lst, t_opt *opt)
{
	if (opt->t && opt->reverse)
		return (sort_r_list_t(lst));
	if (opt->t && !opt->reverse)
		return (sort_list_t(lst));
	if (!opt->t && opt->reverse)
		return (sort_r_list(lst));
	return (sort_list(lst));
}
