/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:33:29 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:50:20 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_list *h)
{
	while (h)
	{
		printf("<%s>\n", h->line);
		h = h->next;
	}
}

int	find_command(void)
{
	if (!ft_strcmp(g_sh->first_list->line, "env"))
		env_cmd(0);
	else if (!ft_strcmp(g_sh->first_list->line, "exit"))
		exit_cmd();
	else if (!ft_strcmp(g_sh->first_list->line, "echo"))
		echo_cmd();
	else if (!ft_strcmp(g_sh->first_list->line, "pwd"))
		pwd_cmd();
	else if (!ft_strcmp(g_sh->first_list->line, "cd"))
		cd_cmd(g_sh->env);
	else if (!ft_strcmp(g_sh->first_list->line, "export"))
		export_cmd(g_sh->env, 0);
	else if (!ft_strcmp(g_sh->first_list->line, "unset"))
		unset_cmd();
	else
		return (1);
	return (0);
}

void	main_loop(void)
{
	while (1)
	{
		g_sh->str = readline("Minishell >> ");
		if (g_sh->str == '\0')
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(g_sh->str);
		if (parser())
		{	
			clear_all();
			continue ;
		}
		execve_processing();
		clear_all();
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;

	i = -1;
	(void)argc;
	(void)argv;
	signal_processing();
	g_sh = malloc(sizeof(t_shell));
	g_sh->str = NULL;
	g_sh->envp = envp;
	g_sh->first_list = NULL;
	g_sh->env = NULL;
	while (envp[++i] != 0)
		ft_lstadd_back(&g_sh->env, ft_lstnew(ft_strdup(envp[i])));
	shlvl_plus(g_sh->env);
	shell_pwd(g_sh->env);
	main_loop();
	return (0);
}
