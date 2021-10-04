/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:08:14 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:47:43 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	vsp(unsigned char *ss, int *k)
{
	int	i;

	i = 0;
	while (ss[i] == '\t' || ss[i] == '\n' || ss[i] == '\v' \
	|| ss[i] == '\f' || ss[i] == '\r' || ss[i] == ' ')
		i++;
	if (ss[i] == '+')
		i++;
	else if (ss[i] == '-')
	{
		*k = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	unsigned char	*ss;
	int				res;
	int				i;
	int				k;
	int				r;

	res = 0;
	k = 1;
	r = 0;
	ss = (unsigned char *)str;
	i = vsp(ss, &k);
	while (ss[i] >= '0' && ss[i] <= '9')
	{
		res = res * 10 + (ss[i] - '0');
		i++;
		if (res != 0)
		{
			r++;
		}
	}
	if (ss[i] != 0)
		return (-1);
	return (res * k);
}

char	*ft_strndup(const char *str, int qq)
{
	char	*res;
	size_t	a;
	int		i;

	i = -1;
	if (!str)
		return (0);
	a = ft_strlen(str);
	if (qq > (int)a)
		qq = a;
	res = (char *)malloc(sizeof(char) * (qq + 1));
	if (!res)
		return (0);
	while (str[++i] != 0 && i < qq)
		res[i] = str[i];
	res[i] = 0;
	return (res);
}

char	*ft_strjoin_dollar(char const *s1, int i, char const *s2)
{
	char	*buf;
	size_t	len;
	int		j;
	int		k;

	j = 0;
	if (!s1 || !s2)
		return (0);
	if (*s1 == '\0')
		return (ft_strdup(s2));
	if (*s2 == '\0')
		return (ft_strdup(s1));
	len = i + 1 + ft_strlen(s2);
	buf = (char *)malloc((len + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (j < i)
	{
		buf[j] = s1[j];
		j++;
	}
	k = 0;
	while (j < i + (int)ft_strlen(s2))
	{
		buf[j] = s2[k];
		j++;
		k++;
	}
	buf[j] = 0;
	return (buf);
}
