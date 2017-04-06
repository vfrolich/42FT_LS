/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 19:20:29 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/17 11:32:04 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *start;
	t_list *new;

	if (!(start = f(lst)))
		return (NULL);
	new = start;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (!(new->next = f(lst)))
			return (NULL);
		new = new->next;
	}
	return (start);
}
