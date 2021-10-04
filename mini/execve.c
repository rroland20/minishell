/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:08:19 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:44:50 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tmp_buf(char **tmp, char **buf)
{
	if (*tmp)
		free(*tmp);
	if (*buf)
		free(*buf);
}

void	run_command(char **argv)
{
	char	**path;
	char	*buf;
	char	*tmp;
	char	**env;
	int		i;

	i = 0;
	env = list_to_array(g_sh->env);
	while (ft_strncmp(env[i], "PATH", 4))
		i++;
	path = split_org(env[i], ':');
	i = 0;
	execve(argv[0], argv, env);
	while (path[i] != 0)
	{
		tmp = ft_strjoin(path[i], "/");
		buf = ft_strjoin(tmp, argv[0]);
		execve(buf, argv, env);
		free_tmp_buf(&tmp, &buf);
		i++;
	}
	free_array((void **)env);
	free_array((void **)path);
}

void	fork_execve(char **argv, int i, t_cmd *command)
{
	command->pids[i] = fork();
	if (command->pids[i] == 0)
	{
		if (command->count_pipes)
		{
			if (i != 0)
			{
				dup2(command->pipes[i - 1][0], 0);
				close(command->pipes[i - 1][0]);
			}
			if (i != command->count_pipes)
			{
				dup2(command->pipes[i][1], 1);
				close(command->pipes[i][1]);
			}
		}
		if (find_command())
			run_command(argv);
		exit(1);
	}
	else if (command->pids[i] < 0)
		perror("execve");
	if (i != command->count_pipes)
		close(command->pipes[i][1]);
}

static void	init(t_cmd *command)
{
	command->fd_in = dup(0);
	command->fd_out = dup(1);
	command->count_pipes = count_pipe(g_sh->first_list);
	if (command->count_pipes)
		command->pipes = init_pipe(command->count_pipes);
	command->pids = malloc(sizeof(pid_t *) * (command->count_pipes + 1));
	if (!command->pids)
		exit(1);
}

void	execve_processing(void)
{
	t_cmd	command;
	char	**argv;
	t_list	*list;
	int		i;

	init(&command);
	list = g_sh->first_list;
	argv = 0;
	i = 0;
	while (list)
	{
		argv = split_argv(&list);
		if (list && check_redirect(list->line))
			break ;
		if (argv != 0 && find_command())
			fork_execve(argv, i, &command);
		if (argv != 0)
			free_array((void **)argv);
		if (list)
			list = list->next;
		dup2(command.fd_in, 0);
		dup2(command.fd_out, 1);
		i++;
	}
	wait_pids(&command);
	close(command.fd_in);
	close(command.fd_out);
	if (command.count_pipes)
	{
		close_pipes(&command);
		free_array((void **)command.pipes);
	}
	free(command.pids);
}
