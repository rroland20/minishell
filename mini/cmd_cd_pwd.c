/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:01:00 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:50:30 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		strerror(errno);
	printf("%s\n", pwd);
	free(pwd);
}

void	cd_cmd(t_list *env)
{
	char	*oldpwd;
	char	*pwd;

	if (g_sh->first_list && g_sh->first_list->next)
	{
		g_sh->first_list = g_sh->first_list->next;
		if (chdir(g_sh->first_list->line))
			printf("minishell: cd: %s: No such file or directory\n", \
			g_sh->first_list->line);
		else
		{
			oldpwd = find_key_in_env(env, "PWD", 3);
			fill_new_value(env, "OLDPWD", oldpwd, 6);
			free(oldpwd);
			pwd = getcwd(NULL, 0);
			if (!pwd)
				strerror(errno);
			fill_new_value(env, "PWD", pwd, 3);
			free(pwd);
		}
	}
}
