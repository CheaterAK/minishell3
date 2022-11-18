/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:15:29 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/17 20:15:30 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array.h>

void	**array_copy_addr(void *dest[], void *src[])
{
	size_t	i;

	if (dest == NULL || src == NULL)
		return (NULL);
	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = NULL;
	return (dest);
}

void	**array_copy_addr_n(void *dest[], void *src[], size_t n)
{
	size_t	i;

	if (dest == NULL || src == NULL || !n)
		return (NULL);
	i = 0;
	while (src[i] != NULL && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = NULL;
	return (dest);
}

void	**array_deep_copy(void *dest[], void *src[], void *(*copy)(void *))
{
	size_t	i;

	if (dest == NULL || src == NULL || copy == NULL)
		return (NULL);
	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = copy(src[i]);
		++i;
	}
	dest[i] = NULL;
	return (dest);
}

void	**array_deep_copy_n(void *dest[], void *src[],
			void *(*copy)(void *), size_t n)
{
	size_t	i;

	if (dest == NULL || src == NULL || !n || copy == NULL)
		return (NULL);
	i = 0;
	while (src[i] != NULL && i < n)
	{
		dest[i] = copy(src[i]);
		++i;
	}
	dest[i] = NULL;
	return (dest);
}
