/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:41:29 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/14 17:28:24 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*mem_area;
	size_t	i;

	i = 0;
	mem_area = malloc(size);
	if (mem_area == NULL)
		return (NULL);
	else
		while (i < size)
		{
			mem_area[i] = '\0';
			i++;
		}
	return (mem_area);
}
