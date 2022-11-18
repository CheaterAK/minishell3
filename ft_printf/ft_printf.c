/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:29:37 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/16 17:58:44 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_put(unsigned long nbr, char *s_n, int chk, int fd)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	if (chk == 3)
	{
		if (!s_n)
			return (write(fd, "(null)", 6));
		else
			while (s_n[++i])
				len += write(fd, &s_n[i], 1);
		return (len);
	}
	if (chk == 1)
		len += write(fd, "0x", 2);
	if ((int)nbr < 0 && chk == 2)
	{
		nbr *= -1;
		len += write(fd, "-", 1);
	}
	if (nbr / ft_strlen(s_n) != 0)
		len += ft_put(nbr / ft_strlen(s_n), s_n, 0, ft_strlen(s_n));
	len += write(fd, &s_n[nbr % ft_strlen(s_n)], 1);
	return (len);
}

int	ft_control(char c, va_list args, int fd)
{
	int	chr;

	if (c == 'c')
	{
		chr = va_arg(args, int);
		return (write(fd, &chr, 1));
	}
	else if (c == 's')
		return (ft_put(0, va_arg(args, char *), 3, fd));
	else if (c == 'p')
		return (ft_put(va_arg(args, unsigned long), "0123456789abcdef", \
		1, fd));
	else if (c == 'd' || c == 'i')
		return (ft_put(va_arg(args, int), "0123456789", 2, fd));
	else if (c == 'u')
		return (ft_put(va_arg(args, unsigned), "0123456789", 0, fd));
	else if (c == 'x')
		return (ft_put(va_arg(args, unsigned), "0123456789abcdef", 0, fd));
	else if (c == 'X')
		return (ft_put(va_arg(args, unsigned), "0123456789ABCDEF", 0, fd));
	else if (c == '%')
		return (write(fd, &c, 1));
	else
		return (write(fd, &c, 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	args;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			while (str[++i] == ' ')
				;
			len += ft_control(str[i], args, 1);
		}
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	int		len;
	int		i;
	va_list	args;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			while (str[++i] == ' ')
				;
			len += ft_control(str[i], args, fd);
		}
		else
			len += write(fd, &str[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
