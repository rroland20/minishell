/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 22:28:03 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:29:55 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**my_free(char **my_mass, int word)
{
	int	i;

	i = 0;
	while (i < word)
	{
		free(my_mass[i]);
		i++;
	}
	free(my_mass);
	return (0);
}

int	ft_strcmp_a(const char *str, char *sim)
{
	int	i;

	i = 0;
	while (1)
	{
		if (sim[i] == 0)
			break ;
		if (str[i] != sim[i])
			return (0);
		i++;
	}
	return (1);
}

int	count_hlp(const char *s, int i, int flag)
{
	if (flag == 0)
		if (ft_strcmp_a(&s[i], " "))
			return (1);
	if (ft_strcmp_a(&s[i], "|"))
		return (1);
	if (ft_strcmp_a(&s[i], "<<"))
		return (2);
	if (ft_strcmp_a(&s[i], ">>"))
		return (2);
	if (ft_strcmp_a(&s[i], "<"))
		return (1);
	if (ft_strcmp_a(&s[i], ">"))
		return (1);
	return (0);
}
