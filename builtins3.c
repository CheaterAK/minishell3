/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:32:39 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:31:12 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>

int	env_cmp(char *s1, char *s2)
{
	int		res;

	res = ft_strncmp(s2, s1, ft_strlen(s2));
	return (res);
}

char	**clone(t_argv *env, t_argv *exp)
{
	char		**tmparr;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	tmparr = (char **)malloc(sizeof(char *) * (env->len + exp->len + 1));
	while (i < env->len)
	{
		tmparr[i] = (char *)ft_strdup(env->array[i]);
		i++;
	}
	while (j < exp->len)
	{
		tmparr[i] = (char *)ft_strdup(exp->array[j]);
		i++;
		j++;
	}
	tmparr[i] = NULL;
	return (tmparr);
}

void	sort_array(char **tmparr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tmparr[i])
	{
		j = i + 1;
		while (tmparr[j])
		{
			if (ft_strcmp(tmparr[i], tmparr[j]) > 0)
			{
				tmp = tmparr[i];
				tmparr[i] = tmparr[j];
				tmparr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	set_sorted_tmp(t_argv **tmp, t_argv *env, t_argv *exp)
{
	char	**tmparr;
	int		i;

	i = 0;
	tmparr = clone(env, exp);
	sort_array(tmparr);
	*tmp = argv_new((void **)tmparr, (void *(*)(void *))ft_strdup);
	i = 0;
	while (tmparr[i])
	{
		free(tmparr[i]);
		i++;
	}
	free(tmparr);
}

void	env_print(t_argv *env)
{
	size_t	i;
	t_argv	*tmp;
	t_argv	*exp;

	exp = g_et->array[1];
	set_sorted_tmp(&tmp, env, exp);
	i = 0;
	while (i < tmp->len)
		ft_printf("declare -x %s\n", tmp->array[i++]);
	argv_destroy(tmp, free);
}
