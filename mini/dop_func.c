/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:46:23 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:03:30 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (-1);
	while (1)
	{	
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		if (str1[i] == 0 && str2[i] == 0)
			break ;
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*res;
	size_t	a;
	int		i;

	i = -1;
	if (!str)
		return (0);
	a = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (a + 1));
	if (!res)
		return (0);
	while (str[++i] != 0)
		res[i] = str[i];
	res[i] = 0;
	return (res);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	i = 0;
	a = (unsigned char *)str1;
	b = (unsigned char *)str2;
	while (i < n)
	{
		if (a[i] == '\0' && b[i] == '\0')
			return (0);
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}
