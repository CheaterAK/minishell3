/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:08:48 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:36:40 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <stdlib.h>

char	*clear_this(char *line, int c, int status)
{
	int		i;
	char	*ret;

	ret = line;
	while (*line)
	{
		if (*line == (char)c)
		{
			i = 0;
			while (line[i])
			{
				line[i] = line[i + 1];
				i++;
			}
		}
		else
			line++;
	}
	if (c == '\"')
		return (implement(ret, status));
	return (ft_strdup(ret));
}

char	*lexer_quote(char **string, int status)
{
	char	*tmp;
	char	*res;
	char	*ret;

	tmp = NULL;
	if (**string)
	{
		if (**string == '\"')
			tmp = jump_to_double_quote(*string);
		else if (**string == '\'')
			tmp = jump_to_single_quote(*string);
		if (tmp == NULL)
			return (NULL);
		res = tmp;
		(*string) += ft_strlen(tmp);
		if (*res == '\"')
			ret = clear_this(res, '\"', status);
		else
			ret = clear_this(res, '\'', status);
		free(res);
		return (ret);
	}
	return (NULL);
}

char	*free_join(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}

int	func(char *line, char **tmp, int *status, char **str)
{
	int		res;
	char	*tmp2;

	res = 0;
	while (!ft_strchr("\"\' |<>", *(line + res)))
		res++;
	*tmp = ft_substr(line, 0, res);
	tmp2 = implement(*tmp, *status);
	free(*tmp);
	*tmp = ft_strjoin(*str, tmp2);
	free(*str);
	*str = *tmp;
	return (res);
}

char	*lexer_word_plus_quote(t_argv *cmd, char *line, int status)
{
	char	*rr;
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	while (!ft_strchr(" |<>", *line))
	{
		if (ft_strchr("\"\'", *line))
		{
			rr = lexer_quote(&line, status);
			if (rr == NULL)
			{
				free(str);
				return (NULL);
			}
			tmp = free_join(str, rr);
			str = tmp;
		}
		line += func(line, &tmp, &status, &str);
	}
	argv_push(cmd, str);
	return (line);
}
