/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:14:15 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/17 20:15:05 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <argv.h>

int	argv_is(t_argv *argv, size_t index, int (*fptr)(int))
{
	int		i;
	char	*tmp;

	if (argv == NULL || fptr == NULL || index >= argv->len)
		return (-1);
	tmp = argv->array[index];
	i = 0;
	while (tmp[i])
	{
		if (fptr(tmp[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	argv_destroy(t_argv *argv, void (*del)(void *))
{
	if (argv == NULL)
		return (-1);
	array_destroy(argv->array, del);
	free(argv);
	return (0);
}

int	argv_try(t_argv *argv, void *addr, size_t index, int (*fptr)(void *,
			void *))
{
	if (argv == NULL || addr == NULL || fptr == NULL || argv->len <= index)
		return (-1);
	while (index < argv->len)
	{
		if (fptr(argv->array[index], addr) == argv->try_condition)
		{
			argv->try_index = index;
			return (0);
		}
		++index;
	}
	return (-1);
}

t_argv	*argv_splice(t_argv *argv, size_t index, size_t n)
{
	t_argv	*ret;

	if (argv == NULL || n == 0 || argv->len < index + n)
		return (NULL);
	ret = argv_new(NULL, NULL);
	argv_insert_array_n(ret, 0, &argv->array[index], n);
	argv_del_n(argv, index, NULL, n);
	return (ret);
}

t_argv	*argv_new(void *array[], void *(*fptr)(void *))
{
	t_argv	*argv;

	argv = malloc(sizeof(t_argv));
	if (argv == NULL)
		return (NULL);
	argv->try_index = 0;
	argv->try_condition = 0;
	argv->len = array_len(array);
	argv->capacity = 1 << find_max_bit(argv->len);
	if (fptr == NULL)
		argv->array = array_expand(array, argv->capacity);
	else
	{
		argv->array = array_expand(NULL, argv->capacity);
		array_deep_copy(argv->array, array, fptr);
	}
	return (argv);
}
