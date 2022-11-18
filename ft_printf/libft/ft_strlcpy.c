/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 06:18:39 by akocabas          #+#    #+#             */
/*   Updated: 2022/02/12 05:25:53 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *str2, const char *str1, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dstsize)
		return (ft_strlen(str1));
	dstsize -= 1;
	while (str1[i] && i < dstsize)
	{
		str2[i] = str1[i];
		i++;
	}
	if (dstsize < ft_strlen(str1))
		str2[dstsize] = '\0';
	else
		str2[i] = '\0';
	return (ft_strlen(str1));
}
