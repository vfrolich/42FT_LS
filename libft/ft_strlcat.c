/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:06:35 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/09 21:12:09 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	size_t	j;
	int		max;

	i = 0;
	j = ft_strlen(dst);
	max = size - 1 - j;
	while ((i < max) && src[i])
	{
		dst[i + j] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	if (size < j)
		return (size + ft_strlen(src));
	else
		return (j + ft_strlen(src));
}
