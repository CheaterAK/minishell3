/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:55:28 by akocabas          #+#    #+#             */
/*   Updated: 2022/02/12 01:12:11 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_digit_size(int n)
{
	int	i;

	i = 0;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char	*ft_invertnum(char *s, int sign)
{
	size_t	len;
	int		i;
	char	*rs;

	i = 0;
	len = ft_strlen(s);
	rs = malloc(sizeof(char) * ((int)len + sign + 1));
	if (sign == 1)
	{
		rs[i++] = '-';
	}
	while (len--)
	{
		rs[i] = s[len];
		i++;
	}
	rs[i] = 0;
	return (rs);
}

char	*ft_itoa(int n)
{
	char	sn[11];
	int		sign;
	int		sn_i;
	int		digit;

	sign = 0;
	sn_i = -1;
	digit = ft_digit_size(n);
	if (n < 0)
	{
		sign = 1;
		if (n == -2147483648)
			return (ft_invertnum("8463847412", sign));
		n = -n;
	}
	while (++sn_i < digit)
	{
		sn[sn_i] = (n % 10) + '0';
		n = n / 10;
	}
	sn[sn_i] = 0;
	return (ft_invertnum(sn, sign));
}
