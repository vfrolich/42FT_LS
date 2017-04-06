/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 12:36:02 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/17 18:41:09 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_check_str(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			k = i;
			while (big[k] == little[j] && big[k] && little[j]
					&& j < ft_strlen(little) && k < len)
			{
				j++;
				k++;
			}
			if (j == ft_strlen(little))
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	char *ret;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	ret = ft_check_str(big, little, len);
	return (ret);
}
