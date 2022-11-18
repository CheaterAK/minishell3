/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:05:00 by akocabas          #+#    #+#             */
/*   Updated: 2022/01/05 19:24:51 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*destt;
	unsigned char	*srcc;

	if ((!src) && (!dest))
		return (NULL);
	i = 0;
	destt = (unsigned char *) dest;
	srcc = (unsigned char *) src;
	while (i < n)
	{
		destt[i] = srcc[i];
		i++;
	}
	return (destt);
}
