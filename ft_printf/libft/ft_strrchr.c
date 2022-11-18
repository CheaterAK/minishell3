/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 04:55:47 by akocabas          #+#    #+#             */
/*   Updated: 2022/01/19 03:11:56 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*hold;

	hold = NULL;
	len = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s)
		if (*s++ == (char)c)
			hold = (char *)(s - 1);
	return ((char *)hold);
}
