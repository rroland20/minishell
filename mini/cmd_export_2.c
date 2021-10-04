/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:01:08 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:49:49 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*cpy_lst(t_list *env)
{
	t_list	*e;

	e = 0;
	while (env)
	{
		ft_lstadd_back(&e, ft_lstnew(ft_strdup(env->line)));
		env = env->next;
	}
	return (e);
}

void	export_one(t_list *env)
{
	t_list	*env_new;

	env_new = cpy_lst(env);
	sort_env(env_new, ft_lstsize(env_new));
	print_quote(env_new, 0);
	free_full_lst(&env_new);
}

static void	sort_env_help(t_list *env, t_list *new_lst)
{
	char	*tmp;
	int		k;

	k = 0;
	while (1)
	{
		if (env->line[k] == new_lst->next->line[k])
		{
			k++;
			continue ;
		}
		if (env->line[k] > new_lst->next->line[k])
		{
			tmp = env->line;
			env->line = new_lst->next->line;
			new_lst->next->line = tmp;
			break ;
		}
		else
			break ;
	}
}

void	sort_env(t_list *env, int j)
{
	t_list	*new_lst;
	int		i;

	i = -1;
	while (++i < j && env)
	{
		new_lst = env;
		while (new_lst->next)
		{
			sort_env_help(env, new_lst);
			new_lst = new_lst->next;
		}
		env = env->next;
	}
}
