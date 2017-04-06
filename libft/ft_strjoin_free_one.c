/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_one.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:04:16 by vfrolich          #+#    #+#             */
/*   Updated: 2017/03/08 12:11:32 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_one(char **s1, char *s2)
{
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	dst = ft_strnew(ft_strlen(*s1) + ft_strlen(s2));
	if (!dst)
		return (NULL);
	dst = ft_strcpy(dst, *s1);
	ft_strdel(s1);
	dst = ft_strcat(dst, s2);
	return (dst);
}
