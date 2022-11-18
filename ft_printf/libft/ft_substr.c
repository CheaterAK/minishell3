/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:32:08 by akocabas          #+#    #+#             */
/*   Updated: 2022/02/12 04:50:23 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (len >= ft_strlen(s))
		str = malloc(sizeof(char) * ft_strlen(s) + 1);
	else
		str = malloc(sizeof(char) * len + 1);
	if (!s || !str)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str[i] = '\0';
		return (str);
	}
	while (i < len && i < ft_strlen(s))
	{
		str[i] = *(s + start + i);
		i++;
	}
	str[i] = '\0';
	return (str);
}
// 01234567890 7 7
