/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_org.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:09:10 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:42:02 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_let(char const *sr, char ch, int i)
{
	while (sr[i] != ch && sr[i])
		i++;
	return (i);
}

static int	ft_ch_split(char const *sr, char ch, int i)
{
	while (sr[i] == ch && sr[i])
		i++;
	return (i);
}

static int	ft_count_word(const char *st, char ch)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (st[i])
	{
		i = ft_ch_split(st, ch, i);
		i = ft_let(st, ch, i);
		++n;
	}
	return (n);
}

char	**split_org(char const *s, char c)
{
	char	**ar;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == 0)
		return (0);
	ar = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!ar)
		return (0);
	if (ft_ch_split(s, c, i) != (int)ft_strlen(s))
	{
		while (s[i])
		{
			i = ft_ch_split(s, c, i);
			ar[j++] = ft_substr(s, i, ft_let(s, c, i) - i);
			if (!ar)
			{
				free_array((void **)ar);
				return (NULL);
			}
			i = ft_let(s, c, i);
			i = ft_ch_split(s, c, i);
		}
	}
	ar[j] = 0;
	return (ar);
}
