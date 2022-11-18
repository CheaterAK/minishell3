/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 06:23:56 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/01 12:24:19 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rtn;
	size_t	i;
	size_t	ii;

	rtn = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(rtn))
		return (NULL);
	i = 0;
	ii = 0;
	while (s1 && s1[i] != '\0')
	{
			rtn[i] = s1[i];
			i++;
	}
	while (s2 && s2[ii] != '\0')
	{
		rtn[i + ii] = s2[ii];
		ii++;
	}
	rtn[ii + i] = '\0';
	return (rtn);
}
