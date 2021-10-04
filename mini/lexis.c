/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:08:29 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:52:11 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_pipe(int i, int res, int res1, int res2)
{
	int	flag;
	int	flag1;
	int	k;

	k = 0;
	flag = 0;
	flag1 = 0;
	while (g_sh->str[++i])
	{
		if (g_sh->str[i] == '|')
		{
			k = i + 1;
			while (g_sh->str[k] == ' ')
				k++;
			if (g_sh->str[k] == '|')
				res2++;
		}
		if (g_sh->str[i] == '\"' && flag % 2 == 0)
			flag1++;
		if (g_sh->str[i] == '\'' && flag1 % 2 == 0)
			flag++;
		if (flag % 2 == 0)
			res = 0;
		else
			res = 1;
		if (flag1 % 2 == 0)
			res1 = 0;
		else
			res1 = 1;
	}
	return (res2 + res + res1);
}

char	*find_env(char *str, t_list *env)
{
	int	i;

	i = 0;
	while (str[i] != 0 || str[i] != ' ' || str[i] != '\'' || str[i] != '\"')
	{
		if (env->line[i] == '=')
		{
			if (str[i] != 0 && str[i] != ' ' && str[i] != '\'' && \
			str[i] != '\"' && str[i] != '$' && str[i] != '=')
				return ("");
			else
				return (&env->line[i + 1]);
		}
		if (env->line[i] != str[i])
		{
			i = 0;
			env = env->next;
			if (env->line[i] == 0)
				return ("");
			continue ;
		}
		i++;
	}
	return (0);
}

int	find_env_int(char *str, t_list *env)
{
	int	i;

	i = 0;
	while (str[i] != 0 || str[i] != ' ' || str[i] != '\'' || str[i] != '\"')
	{
		if (env->line[i] == '=')
		{
			if (str[i] != 0 && str[i] != ' ' && str[i] != '\'' && \
			str[i] != '\"' && str[i] != '$' && str[i] != '=')
				return (0);
			else
				return (i);
		}
		if (env->line[i] != str[i])
		{
			i = 0;
			env = env->next;
			if (env->line[i] == 0)
				return (0);
			continue ;
		}
		i++;
	}
	return (0);
}

int	check_dollar(int i)
{
	int		flag;
	char	*tmp;
	char	*tmp2;

	flag = 0;
	while (g_sh->str[++i])
	{
		if (g_sh->str[i] == '\'')
			flag++;
		if (flag % 2 == 0)
			if (g_sh->str[i] == '$' && (i != 0 && g_sh->str[i - 1] != '\\'))
			{
				if (g_sh->str[i] == '$' && (g_sh->str[i + 1] == ' ' || \
				g_sh->str[i + 1] == '\"' || g_sh->str[i + 1] == 0))
					continue ;
				tmp2 = find_env(&g_sh->str[i + 1], g_sh->env);
				if (tmp2[0] != 0)
				{
					tmp2 = ft_strjoin_dollar(g_sh->str, i, tmp2);
					tmp = ft_strjoin(tmp2, &g_sh->str[i + 1 + \
					find_env_int(&g_sh->str[i + 1], g_sh->env)]);
					if (tmp2)
						free(tmp2);
					tmp2 = g_sh->str;
					g_sh->str = ft_strdup(tmp);
					if (tmp)
						free(tmp);
					if (tmp2)
						free(tmp2);
					i = 0;
				}
				else
				{
					tmp2 = ft_strndup(g_sh->str, i);
					printf("%s\n", tmp2);
					while (g_sh->str[i] != 0 && g_sh->str[i] != ' ' && \
					g_sh->str[i] != '\'' && g_sh->str[i] != '\"')
						i++;
					if (g_sh->str[i] != 0)
					{
						tmp = ft_strjoin(tmp2, &g_sh->str[i]);
						if (tmp2)
							free(tmp2);
					}
					else
						tmp = tmp2;
					tmp2 = g_sh->str;
					g_sh->str = ft_strdup(tmp);
					if (tmp)
						free(tmp);
					if (tmp2)
						free(tmp2);
					i = 0;
				}
			}
	}
	return (0);
}
