/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:15:11 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/17 20:16:19 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H
# define ARGV_H

# include <array.h>
# include <stddef.h>
# include <stdlib.h>

typedef struct argv_s
{
	int		try_condition;
	size_t	len;
	size_t	capacity;
	void	**array;
	size_t	try_index;
}			t_argv;

int			argv_del_one(t_argv *argv, size_t index, void (*del)(void *));
int			argv_del_n(t_argv *argv, size_t index, void (*del)(void *),
				size_t n);
int			argv_del_all(t_argv *argv, void (*del)(void *));

int			argv_check_capacity(t_argv *argv, size_t len);

int			argv_is_unique(t_argv *argv, void *addr);
int			argv_reverse(t_argv *argv);

int			argv_insert(t_argv *argv, size_t index, void *addr);
int			argv_insert_array(t_argv *argv, size_t index, void *addr[]);
int			argv_insert_array_n(t_argv *argv, size_t index, void *addr[],
				size_t n);
int			argv_push(t_argv *argv, void *address);
void		*argv_pull(t_argv *argv);

int			argv_try(t_argv *argv, void *addr, size_t index, int (*fptr)(void *,
					void *));
t_argv		*argv_splice(t_argv *argv, size_t index, size_t n);
t_argv		*argv_new(void *array[], void *(*fptr)(void *));
int			argv_destroy(t_argv *argv, void (*del)(void *));
int			argv_is(t_argv *argv, size_t index, int (*fptr)(int));
#endif
