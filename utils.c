/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:32:10 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 12:06:53 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*str3join(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(s1, s2);
	str = ft_strjoin(tmp, s3);
	free(s1);
	free(s2);
	free(s3);
	free(tmp);
	return (str);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		++i;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

int	ft_is_valid_env(const char *str)
{
	int		i;
	char	*tmp;

	if (ft_strchr(str, '=') == NULL || str[0] == '=')
		return (0);
	tmp = ft_substr(str, 0, ft_strchr(str, '=') - str);
	i = 0;
	while ((ft_isalnum(tmp[i]) || tmp[i] == '_') && tmp[i]
		&& !ft_isdigit(tmp[0]) && tmp[0] != '=')
		i++;
	if (tmp[i] == '\0')
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	ft_isstring(const char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
