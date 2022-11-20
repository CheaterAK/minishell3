/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:16:48 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:40:29 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <stdlib.h>

char	*check_dolar(char *line, int i)
{
	char	*tmp;

	tmp = str3join(ft_substr(line, 0, i), ft_strdup("$"), ft_strdup(""));
	free(line);
	return (tmp);
}

int	get_status(char **line, int status, int i)
{
	char	*tmp;

	tmp = str3join(ft_substr(*line, 0, i), ft_itoa(status), ft_strdup(*line + i
				+ 2));
	free(*line);
	*line = tmp;
	return (1);
}

char	*new_line(char *line, int i, int l)
{
	char	*tmp;

	tmp = str3join(ft_substr(line, 0, i), get_env(ft_substr(line, i, l)),
			ft_substr(line, i + l, ft_strlen(&line[i + l])));
	free(line);
	return (tmp);
}

char	*implement(char *line_s, int status)
{
	int		i;
	int		l;
	char	*line;

	line = ft_strdup(line_s);
	i = 0;
	while (line[i])
	{
		if (line && line[i] == '$')
		{
			if (!line[i + 1])
				return (check_dolar(line, i));
			else if (line[i + 1] == '?' && get_status(&line, status, i))
				continue ;
			l = 1;
			while (!ft_strchr(" <>|$\"\'", line[i + l]) && line[i + l])
				l++;
			line = new_line(line, i, l);
		}
		i++;
	}
	return (line);
}
