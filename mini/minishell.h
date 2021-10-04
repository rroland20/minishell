/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:26:43 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:52:27 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h> 
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pair
{
	int				one;
	int				two;
}					t_pair;

typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}					t_list;

typedef struct s_shell
{
	char			*str;
	char			**envp;
	t_list			*first_list;
	t_list			*env;
	t_pair			*pair;
}					t_shell;
t_shell				*g_sh;

typedef struct s_cmd
{
	int		**pipes;
	pid_t	*pids;
	int		count_pipes;
	int		fd_in;
	int		fd_out;
}					t_cmd;

void	signal_processing(void);
void	terminal_setup(void);
void	execve_processing(void);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**split_org(char const *s, char c);
void	free_array(void **ar);
char	*ft_strjoin(char const *s1, char const *s2);
int		**init_pipe(int count);
void	bunch_of_pipes(int **pipes, int count);
void	close_pipes(t_cmd *command);
int		find_command(void);
void	run_command(char **argv);
size_t	ft_strlen(const char *c);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, int qq);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strjoin_dollar(char const *s1, int i, char const *s2);
void	main_loop(void);
void	print_lst(t_list *h);
char	**split_parser(char const *s);
int		parser(void);
char	*ft_readline(void);
int		lexis(void);
int		check_quote_pipe(int i, int res, int res1, int res2);
int		check_dollar(int i);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	**split_argv(t_list **list);
int		ft_atoi(const char *str);
void	clear_all(void);
void	free_lst(t_list **first_list);
void	free_full_lst(t_list **first_list);
void	env_cmd(int flag);
void	exit_cmd(void);
void	echo_cmd(void);
void	pwd_cmd(void);
void	export_cmd(t_list *env, int len1);
void	sort_env(t_list *env, int j);
void	export_one(t_list *env);
t_list	*cpy_lst(t_list *env);
void	print_quote(t_list *env, int i);
void	unset_cmd(void);
void	cd_cmd(t_list *env);
void	shell_pwd(t_list *env);
void	shlvl_plus(t_list *env);
char	*ft_itoa(int n);
char	*find_key_in_env(t_list *env, char *key, int i);
void	fill_new_value(t_list *env, char *key, char *new, int i);
int		count_pipe(t_list *list);
int		redirect(t_list *list);
int		check_redirect(char *line);
char	**list_to_array(t_list *list);
void	wait_pids(t_cmd *command);
char	**my_free(char **my_mass, int word);
int		ft_strcmp_a(const char *str, char *sim);
int		count_hlp(const char *s, int i, int flag);
void	close_execve(t_cmd *command);

#endif
