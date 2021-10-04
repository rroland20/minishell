/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:08:25 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:12:27 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count(int d)
{
	int	j;

	j = 0;
	while (d != 0)
	{
		d = d / 10;
		j++;
	}
	return (j);
}

char	*ft_neg(int nb)
{
	int		n_len;
	char	*dup;

	n_len = ft_count(nb) + 1;
	dup = (char *)malloc(sizeof(char) * (n_len + 1));
	if (!dup)
		return (0);
	dup[0] = '-';
	dup[n_len] = '\0';
	while (nb != 0 && n_len)
	{
		n_len--;
		dup[n_len] = (nb % 10) * (-1) + 48;
		nb = nb / 10;
	}
	return (dup);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*buf;

	if (n < 0)
		return (ft_neg(n));
	len = ft_count(n);
	if (n == 0)
		len = 1;
	buf = (char *)malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (0);
	buf[len] = '\0';
	if (n == 0)
		buf[0] = 0 + 48;
	while (n != 0 && len)
	{
		len--;
		buf[len] = n % 10 + 48;
		n = n / 10;
	}
	return (buf);
}
