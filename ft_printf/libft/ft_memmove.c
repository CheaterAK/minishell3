/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:33:31 by akocabas          #+#    #+#             */
/*   Updated: 2022/01/05 21:35:48 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t		i;

	if (!str1 && !str2)
		return (NULL);
	if (str1 > str2)
	{
		i = n - 1;
		while ((i + 1) > 0)
		{
			*(unsigned char *)(str1 + i) = *(unsigned char *)(str2 + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			*(unsigned char *)(str1 + i) = *(unsigned char *)(str2 + i);
			i++;
		}
	}
	return (str1);
}
