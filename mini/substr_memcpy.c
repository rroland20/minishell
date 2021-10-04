/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_memcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:09:21 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 21:09:23 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *p_src;
	unsigned char *p_dst;

	p_src = (unsigned char *)src;
	p_dst = (unsigned char *)dst;
	if (!n || p_src == p_dst)
		return (dst);
	while (n--)
	{
		*p_dst = *p_src;
		p_dst++;
		p_src++;
	}
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *dup;

	if (s == 0)
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (!(dup = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dup = ft_memcpy(dup, &s[start], len);
	dup[len] = '\0';
	return (dup);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	size_t			j;
	unsigned char	*p_d;
	unsigned char	*p_s;

	i = 0;
	j = 0;
	p_d = (unsigned char *)dst;
	p_s = (unsigned char *)src;
	while (p_d[i] != '\0' && i < dstsize)
		i++;
	while (p_s[j] != '\0' && (i + j + 1 < dstsize))
	{
		p_d[i + j + 1] = '\0';
		p_d[i + j] = p_s[j];
		j++;
	}
	return (ft_strlen(src) + i);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	unsigned char	*p_d;
	unsigned char	*p_s;

	i = 0;
	p_d = (unsigned char *)dst;
	p_s = (unsigned char *)src;
	if (!dst)
		return (0);
	if (p_s == p_d || dstsize == 0)
		return (ft_strlen(src));
	while (p_s[i] && i < (dstsize - 1))
	{
		p_d[i] = p_s[i];
		i++;
	}
	p_d[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	if (*s1 == '\0')
		return (ft_strdup(s2));
	if (*s2 == '\0')
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(buf = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (ft_strlcpy(buf, s1, len) && ft_strlcat(buf, s2, len + 1))
		return (buf);
	return (NULL);
}
