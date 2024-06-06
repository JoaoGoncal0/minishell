/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:42 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/06 12:48:42 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_vars
{
	char	**env;
	char	**export;
	char	*input;
	char	**flag;
	char	*cmdt;
	char	*check;
	char	*redrct;
	int		flagfd;
	int		fd[2];
	int		pid;
	int		env_len;
} t_vars;

int		inputnum(char **input);
void	redirect(t_vars *mini);
void	init_env(char **env, t_vars *mini);
int		env_builtin(t_vars *mini);
void	init_export(t_vars *mini);
int		export_builtin(t_vars *mini);
void	swap_strings(char **a, char **b);
void	sorting_export(t_vars *mini);
void	free_split(char **str);
int		not_number(char *str);
void	exit_anyways(char **str);
int		exit_builtin(t_vars *mini);
int		is_flag(char *str);
int		echo_builtin(t_vars *mini);

#endif