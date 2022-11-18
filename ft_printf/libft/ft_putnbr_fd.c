/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:58:39 by akocabas          #+#    #+#             */
/*   Updated: 2022/01/07 04:37:08 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd_r(int nb, int fd)
{
	if (nb == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd_r(nb * -1, fd);
	}
	if (nb > 0)
	{
		ft_putnbr_fd_r(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
	return ;
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == 0)
		ft_putchar_fd('0', fd);
	else
		ft_putnbr_fd_r(nb, fd);
	return ;
}
