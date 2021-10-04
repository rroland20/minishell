/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:11:16 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:49:15 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_hlp(void)
{
	printf("%s", g_sh->first_list->line);
	g_sh->first_list = g_sh->first_list->next;
	if (g_sh->first_list != NULL)
		printf(" ");
}

void	echo_cmd(void)
{
	int	argc;

	argc = ft_lstsize(g_sh->first_list);
	if (argc == 1)
		printf("\n");
	else if (!ft_strcmp(g_sh->first_list->next->line, "-n"))
	{
		g_sh->first_list = g_sh->first_list->next;
		g_sh->first_list = g_sh->first_list->next;
		while (g_sh->first_list)
			echo_hlp();
	}
	else
	{
		g_sh->first_list = g_sh->first_list->next;
		while (g_sh->first_list)
			echo_hlp();
		printf("\n");
	}
}

void	del_env(t_list *env, char *key)
{
	int	len;

	len = ft_strlen(key);
	while (env)
	{
		if (env->next && !strncmp(env->next->line, key, len) \
		&& env->next->line[len] == '=')
		{
			free(env->next->line);
			free(env->next);
			env->next = env->next->next;
			break ;
		}
		env = env->next;
	}
}

void	unset_cmd(void)
{
	int	argc;

	argc = ft_lstsize(g_sh->first_list);
	if (argc == 1)
		printf("\n");
	else
	{
		g_sh->first_list = g_sh->first_list->next;
		while (g_sh->first_list)
		{
			del_env(g_sh->env, g_sh->first_list->line);
			g_sh->first_list = g_sh->first_list->next;
		}
	}
}
