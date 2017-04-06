/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:42:43 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/09 17:19:35 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*tmp_d;
	unsigned char	*tmp_s;

	i = 0;
	tmp_d = dst;
	tmp_s = (unsigned char *)src;
	while (i < len)
	{
		if (&tmp_s[i] == tmp_d)
		{
			while (len-- > 0)
				tmp_d[len] = tmp_s[len];
			return (dst);
		}
		i++;
	}
	i = 0;
	while (i < len)
	{
		tmp_d[i] = tmp_s[i];
		i++;
	}
	return (dst);
}
