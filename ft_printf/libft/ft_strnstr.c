/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:48:34 by akocabas          #+#    #+#             */
/*   Updated: 2022/01/17 06:51:37 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *mstr, const char *sstr, size_t n)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	if (!(*sstr))
		return ((char *)mstr);
	while (mstr[i] && i < n)
	{
		if (mstr[i] == sstr[0])
		{
			while (i + y < n && mstr[i + y] == sstr[y])
			{
				y++;
				if (!sstr[y])
					return ((char *)&mstr[i]);
			}
		}
		i++;
	}
	return (NULL);
}
