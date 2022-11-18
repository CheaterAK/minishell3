/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:14:40 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/17 20:14:44 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <argv.h>

int	argv_insert(t_argv *argv, size_t index, void *addr)
{
	if (argv == NULL || addr == NULL || index > argv->len)
		return (-1);
	argv_check_capacity(argv, argv->len + 1);
	if (-1 == array_insert(&argv->array[index], addr))
		return (-1);
	++argv->len;
	return (0);
}

int	argv_insert_array(t_argv *argv, size_t index, void *addr[])
{
	size_t	len;
	int		res;

	if (argv == NULL || addr == NULL || index > argv->len)
		return (-1);
	len = array_len(addr);
	argv_check_capacity(argv, argv->len + len);
	res = array_insert_array(&argv->array[index], addr);
	if (-1 == res)
		return (-1);
	argv->len += res;
	return (0);
}

int	argv_insert_array_n(t_argv *argv, size_t index, void *addr[], size_t n)
{
	size_t	len;
	int		res;

	if (argv == NULL || addr == NULL || index > argv->len || !n)
		return (-1);
	len = array_len(addr);
	if (len < n)
		n = len;
	argv_check_capacity(argv, argv->len + n);
	res = array_insert_array_n(&argv->array[index], addr, n);
	if (-1 == res)
		return (-1);
	argv->len += res;
	return (0);
}

int	argv_push(t_argv *argv, void *addr)
{
	if (argv == NULL || addr == NULL)
		return (-1);
	argv_check_capacity(argv, argv->len + 1);
	argv->array[argv->len] = addr;
	++argv->len;
	return (0);
}

void	*argv_pull(t_argv *argv)
{
	void	*tmp;

	if (argv == NULL)
		return (NULL);
	if (argv->len)
	{
		tmp = argv->array[argv->len - 1];
		argv->array[argv->len - 1] = NULL;
		--argv->len;
		return (tmp);
	}
	return (NULL);
}
