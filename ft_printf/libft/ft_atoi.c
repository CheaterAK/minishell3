/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:50:12 by akocabas          #+#    #+#             */
/*   Updated: 2022/01/07 08:45:44 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v');
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	nb;
	int		f;

	nb = 0;
	i = 0;
	f = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			f = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb > 2147483647 && f == 1)
			return (-1);
		if (nb > 2147483648 && f == -1)
			return (0);
		i++;
	}
	return (nb * f);
}
