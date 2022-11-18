/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:23:12 by akocabas          #+#    #+#             */
/*   Updated: 2022/01/19 07:48:16 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lettercount(char const *s, char c)
{
	int	count;

	count = 0;
	while (s[count] && s[count] != c)
			count++;
	return (count);
}

int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	chk;
	int	count;

	i = 0;
	count = 0;
	chk = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		chk = ft_lettercount(s + i, c);
		i += chk;
		if (chk)
			count++;
	}
	return (count);
}

char	*ft_wordadd(char const *s, int letter_n, char **rtn)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word = malloc((sizeof(char) * letter_n) + 1);
	if (!word)
	{
		while (rtn[j] != NULL)
		{
			free(rtn[j]);
			j++;
		}
		return (NULL);
	}
	while (i < letter_n && s[i])
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**rtn;
	int		word_n;
	int		letter_n;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word_n = ft_wordcount(s, c);
	rtn = malloc(sizeof(char *) * (word_n + 1));
	if (!rtn)
		return (NULL);
	while (j < word_n)
	{
		while (s[i] == c)
			i++;
		letter_n = ft_lettercount(s + i, c);
		rtn[j] = ft_wordadd(s + i, letter_n, rtn);
		i += letter_n;
		j++;
	}
	rtn[j] = NULL;
	return (rtn);
}
