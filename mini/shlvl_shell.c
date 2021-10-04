/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:08:57 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:24:20 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_plus(t_list *env)
{
	char	*value;
	char	*val;
	int		num;

	value = find_key_in_env(env, "SHLVL", 5);
	num = ft_atoi(value);
	if (num != -1)
	{
		num++;
		val = ft_itoa(num);
		fill_new_value(env, "SHLVL", val, 5);
	}
}

void	shell_pwd(t_list *env)
{
	char	*pwd;
	char	*tmp;

	pwd = find_key_in_env(g_sh->env, "PWD", 3);
	while (env)
	{
		if (!ft_strncmp(env->line, "SHELL", 5))
		{
			if (env->line[5] == '=')
			{
				free(env->line);
				tmp = ft_strjoin("SHELL=", pwd);
				env->line = ft_strjoin(tmp, "/minishell");
			}
		}
		env = env->next;
	}
	free(pwd);
	free(tmp);
}

char	*find_key_in_env(t_list *env, char *key, int i)
{
	char	*value;

	value = 0;
	while (env)
	{
		if (!ft_strncmp(env->line, key, i) && env->line[i] == '=')
		{	
			value = ft_strdup(&env->line[i + 1]);
			break ;
		}
		env = env->next;
	}
	return (value);
}

void	fill_new_value(t_list *env, char *key, char *new, int i)
{
	char	*tmp;

	while (env)
	{
		if (!ft_strncmp(env->line, key, i))
		{
			if (env->line[i] == '=')
			{
				free(env->line);
				tmp = ft_strjoin(key, "=");
				env->line = ft_strjoin(tmp, new);
			}
		}
		env = env->next;
	}
	free(tmp);
}
