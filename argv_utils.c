/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:15:20 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/17 20:15:21 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <argv.h>

int	argv_is_unique(t_argv *argv, void *addr)
{
	size_t	i;

	if (argv == NULL || addr == NULL)
		return (0);
	i = 0;
	while (i < argv->len)
		if (argv->array[i++] == addr)
			return (0);
	return (1);
}

int	argv_check_capacity(t_argv *argv, size_t len)
{
	void	**tmp;
	size_t	ex_len;

	if (argv == NULL || !len)
		return (-1);
	tmp = NULL;
	ex_len = argv->capacity;
	while (ex_len <= len)
	{
		ex_len *= 2;
		if (ex_len <= len)
			continue ;
		tmp = array_expand(argv->array, ex_len);
		if (tmp == NULL)
			return (-1);
		argv->capacity = ex_len;
		free(argv->array);
		argv->array = tmp;
		break ;
	}
	return (0);
}

int	argv_reverse(t_argv	*argv)
{
	if (argv == NULL)
		return (-1);
	return (array_reverse_all(argv->array));
}
