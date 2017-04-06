/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:43:42 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/09 14:58:34 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_t;
	char	*src_t;

	i = 0;
	dst_t = dst;
	src_t = (char *)src;
	while (i < n)
	{
		dst_t[i] = src_t[i];
		i++;
	}
	return (dst);
}
