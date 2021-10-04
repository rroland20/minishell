/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:09:15 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:29:37 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_str(char const *s, int len)
{
	int	i;

	i = 0;
	if (count_hlp(s, i, 1))
	{
		if (count_hlp(s, i, 1) == 2)
			return (2);
		return (1);
	}
	while (count_hlp(s, i, 0) == 0 && s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
			{
				i++;
				len++;
			}
			len--;
		}
		else if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
			{
				i++;
				len++;
			}
			len--;
		}
		i++;
		len++;
	}
	return (len);
}

static char	**filling(char const *s, int word, char **mass)
{
	int		i;
	int		j;
	int		k;
	int		flag;
	int		flag1;

	i = 0;
	k = 0;
	flag = 0;
	flag1 = 0;
	while (i < word)
	{
		while (s[k] == ' ')
			k++;
		mass[i] = (char *)malloc(sizeof(char) * (len_str(&s[k], 0) + 1));
		if (!mass[i])
			return (my_free(mass, word));
		j = 0;
		if (count_hlp(s, k, 1))
		{
			if (count_hlp(s, k, 1) == 2)
			{
				mass[i][j] = s[k];
				j++;
				k++;
			}
			mass[i][j] = s[k];
			j++;
			k++;
		}
		else
			while (s[k] != 0)
			{
				if (s[k] == '\"' && flag1 % 2 == 0)
				{
					flag++;
					k++;
					if (s[k] == '\"')
						continue ;
				}
				if (s[k] == '\'' && flag % 2 == 0)
				{
					flag1++;
					k++;
					if (s[k] == '\'')
						continue ;
				}
				if (s[k] == '\\' && s[k + 1] == '$')
					k++;
				if (flag % 2 == 0 && flag1 % 2 == 0)
					if (count_hlp(s, k, 0))
						break ;
				mass[i][j] = s[k];
				j++;
				if (s[k] != 0)
					k++;
			}
		mass[i][j] = 0;
		i++;
	}
	return (mass);
}

static int	count_word(char const *s)
{
	int	i;
	int	j;
	int	flag;
	int	flag1;

	i = 0;
	j = 0;
	flag = 0;
	flag1 = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\"' && flag1 % 2 == 0)
			flag++;
		if (s[i] == '\'' && flag % 2 == 0)
			flag1++;
		if (flag % 2 != 1 && flag1 % 2 != 1)
		{
			if (!count_hlp(s, i, 0) && (s[i + 1] == '\0' || \
			count_hlp(s, i + 1, 0)))
			{
				if (count_hlp(s, i + 1, 0) == 2)
					i++;
				j++;
			}
			else if (count_hlp(s, i, 1))
			{
				if (count_hlp(s, i, 0) == 2)
					i++;
				j++;
			}
		}
		i++;
	}
	if (j == 0)
	{
		j = 1;
	}
	return (j);
}

char	**split_parser(char const *s)
{
	char	**my_mass;
	int		count;

	if (s == 0)
		return (0);
	count = count_word(s);
	my_mass = (char **)malloc(sizeof(char *) * (count + 1));
	if (!my_mass)
		return (0);
	my_mass[count] = 0;
	my_mass = filling(s, count, my_mass);
	return (my_mass);
}
