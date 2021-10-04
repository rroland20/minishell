/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:07:46 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:51:41 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_quote(t_list *env, int i)
{
	while (env)
	{
		write(1, "declare -x ", 11);
		while (env->line[i] != 0)
		{
			write(1, &env->line[i], 1);
			if (env->line[i] == '=')
			{
				write(1, "\"", 1);
				i++;
				while (env->line[i] != 0)
				{
					write(1, &env->line[i], 1);
					i++;
				}
				write(1, "\"", 1);
				break ;
			}
			i++;
		}
		write(1, "\n", 1);
		env = env->next;
	}
}

void	export_cmp_help(t_list *env, char *key, t_pair pair)
{
	int	len1;

	len1 = 0;
	while (env)
	{
		if (!ft_strncmp(env->line, key, pair.two))
		{
			if (env->line[pair.one] == '=' || env->line[pair.one] == 0)
			{
				free(env->line);
				env->line = ft_strdup(g_sh->first_list->line);
				len1++;
			}
		}
		env = env->next;
	}
	if (len1 == 0)
		ft_lstadd_back(&g_sh->env, \
		ft_lstnew(ft_strdup(g_sh->first_list->line)));
}

void	export_cmd(t_list *env, int len1)
{
	char	*key;
	t_pair	pair;

	pair.one = -1;
	pair.two = 0;
	if (g_sh->first_list->next == NULL)
		export_one(env);
	else
	{
		g_sh->first_list = g_sh->first_list->next;
		while (g_sh->first_list->line[++pair.one] != '=' \
		&& g_sh->first_list->line[pair.one] != 0)
			pair.two++;
		pair.one = -1;
		while (g_sh->first_list->line[++pair.one] != '\0')
			len1++;
		key = malloc(pair.two + 1);
		pair.one = -1;
		while (g_sh->first_list->line[++pair.one] != '=' \
		&& g_sh->first_list->line[pair.one] != 0)
			key[pair.one] = g_sh->first_list->line[pair.one];
		key[pair.one] = 0;
		export_cmp_help(env, key, pair);
	}
}
