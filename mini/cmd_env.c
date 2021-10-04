/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:07:53 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 21:39:11 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst_env(t_list *env)
{
	int	flag;
	int	i;

	while (env)
	{
		i = 0;
		flag = 0;
		while (env->line[i])
		{
			if (env->line[i] == '=')
				flag++;
			i++;
		}
		if (flag != 0)
			printf("%s\n", env->line);
		env = env->next;
	}
}

void	print_new_env(t_list *env, char *str)
{
	while (env)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
	printf("%s\n", str);
}

void	print_replace_env(t_list *env, t_list *str, int i)
{
	t_list	*lst_cpy;
	int		flag;

	flag = 0;
	while (env)
	{
		flag = 0;
		lst_cpy = str;
		while (lst_cpy && ft_strcmp(lst_cpy->line, "|") != 0)
		{
			i = 0;
			while (lst_cpy->line[i] != 0 && lst_cpy->line[i] != '=')
				i++;
			if (!ft_strncmp(env->line, lst_cpy->line, i))
			{
				printf("%s\n", lst_cpy->line);
				flag++;
			}
			lst_cpy = lst_cpy->next;
		}
		if (flag == 0)
			printf("%s\n", env->line);
		env = env->next;
	}
}

t_list	*env_cmd_help(t_list *lst_cpy, int *flag)
{
	int	i;

	while (lst_cpy && ft_strcmp(lst_cpy->line, "|") != 0)
	{
		*flag = 0;
		i = -1;
		while (lst_cpy->line[++i] != 0)
		{
			if (lst_cpy->line[i] == '=')
			{
				(*flag)++;
				break ;
			}
		}
		if (*flag == 0)
			break ;
		lst_cpy = lst_cpy->next;
	}
	return (lst_cpy);
}

void	env_cmd(int flag)
{
	int		i;
	t_list	*lst_cpy;

	if (!g_sh->first_list->next || g_sh->first_list->next->line[0] == '|')
		print_lst_env(g_sh->env);
	else
	{
		g_sh->first_list = g_sh->first_list->next;
		lst_cpy = g_sh->first_list;
		lst_cpy = env_cmd_help(lst_cpy, &flag);
		if (flag == 0)
			printf("env: %s: No such file or directory\n", lst_cpy->line);
		else
		{
			i = 0;
			while (g_sh->first_list->line[i] != 0 && \
			g_sh->first_list->line[i] != '=')
				i++;
			if (!find_key_in_env(g_sh->env, g_sh->first_list->line, i))
				print_new_env(g_sh->env, g_sh->first_list->line);
			else
				print_replace_env(g_sh->env, g_sh->first_list, i);
		}
	}
}
