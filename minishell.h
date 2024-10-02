/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:42 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/02 16:46:08 by jomendes         ###   ########.fr       */
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
	char	*input;
	// builtins
	char	**env;
	char	**new_env;
	char	**export;
	char	**new_export;
	int		exp_len;
	int		env_len;
	// paths
	char	**flag;
	char	**trueflag;
	char	**allpaths;
	char	*check;
	// parsing
	char	*redrct;
	int		flagfd;
	int		*fd;
	int		pid;
	int		i;	
}	t_vars;

// parsing
int		numpipe(char *str);
int		inputnum(char *input);
void	arrangegoodsplit(t_vars *mini);
int		getpipepath(char **trueflag, t_vars *mini);

// path
int		fastcheckpath(t_vars *mini, int flag, int i);
void	checkpath(char *cmd, t_vars *mini);
void	checkhelp(char *comand, char **env, int i, t_vars *mini);
int		findcmdplace(char *input, t_vars *mini);
int		findcmdinmatrix(char **puzle, t_vars *mini);

// split
int		wordllllen(char const *s, char c);
int		checkimportant(char *s);
void	redirect(t_vars *mini, char *str);
char	**ft_goodsplit(char	*str);

// execute
void	allocfd(int p, t_vars *mini);
void	closeall(t_vars *mini);
void	execute(t_vars *mini, int i, int p);
void	executeone(t_vars *mini);
void	veryexecute(t_vars *mini, int i);

// builtin env
void	init_env(char **env, t_vars *mini);
void	env_builtin(t_vars *mini);
void	env_update(t_vars *mini, char *str);

// builtin export
void	init_export(t_vars *mini);
int		export_builtin(t_vars *mini);
void	swap_strings(char **a, char **b);
void	sorting_export(t_vars *mini);
void	free_split(char **str);
int		export_len(char **str);
int     export_check(char *str);
void    export_var(t_vars *mini);
void	export_update1(t_vars *mini);
void	export_update(t_vars *mini, char *str);
void	exp_update1(t_vars *mini);
void	exp_update(t_vars *mini, char *str);

// builtin exit
int		not_number(char *str);
void	exit_anyways(char **str);
int		exit_builtin(t_vars *mini);

// builtin echo
int		echo_builtin(t_vars *mini);
int		is_flag(char *str);
int		dollar_flag(char *str);
void	echo_dollar_finish(char *str, int k, t_vars *mini);
int		echo_compare(const char *s1, const char *s2);
char	*take_equal(char *str);
void	dollar_quote(t_vars *mini, char *str);

//quotes.c 

int		check_quotes(char *input);
void    remove_single_quote(char *cmd);
void    remove_double_quote(char *cmd);
char    *quotescrazy(char *input);
void    quote_together(char *cmd);

//builtin unset
int		unset_builtin(t_vars *mini);

#endif