/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:42:08 by elemesmo          #+#    #+#             */
/*   Updated: 2024/10/17 14:47:06 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closeall(t_vars *mini)
{
	int	i;

	i = 0;
	while (i < (numpipe(mini->input) + 1) * 2 && mini->fd[i])
	{
		close(mini->fd[i]);
		i++;
	}
	if (mini->fd)
		free(mini->fd);
}

void	allocfd(int p, t_vars *mini)
{
	int	i;

	i = 0;
	mini->fd = malloc(sizeof(int) * (p + 1));
	while (i < p)
	{
		if (pipe(mini->fd + 2 * i) < 0)
			return ;
		i++;
	}
}

void	checkpath(char *cmd, t_vars *mini)
{
	int		i;
	char	*boas;

	i = 0;
	printf("cmd = %s\n", cmd);
	boas = ft_strdup(trimtrimtrim(mini->input, 0));
	if (access(boas, X_OK) == 0)
	{
		mini->check = ft_strdup(boas);
		free(boas);
		return ;
	}
	if (access(cmd, X_OK) == 0)
	{
		mini->check = ft_strdup(cmd);
		return ;
	}
	if (access(mini->check, X_OK) == 0)
		return ;
	checkhelp(cmd, mini->env, i, mini);
	return ;
}

void	checkhelp(char *comand, char **env, int i, t_vars *mini)
{
	int	p;

	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			mini->allpaths = ft_split(env[i] + 5, ':');
			p = 0;
			while (mini->allpaths[p])
			{
				mini->check = ft_strjoin(mini->allpaths[p], comand);
				if (access(mini->check, X_OK) == 0)
				{
					free_split(mini->allpaths);
					return ;
				}
				free(mini->check);
				mini->check = NULL;
				p++;
			}
			free_split(mini->allpaths);
		}
		i++;
	}
	return ;
}

int	fastcheckpath(t_vars *mini, int flag, int i)
{
	if (flag == 0)
	{
		mini->flag = ft_split(mini->input, ' ');
		mini->trueflag = ft_goodsplit(mini->input);
		checkpath(ft_strjoin("/", mini->trueflag
			[findcmdinmatrix(mini->trueflag, mini)]), mini);
		if (mini->check != NULL)
			return (1);
	}
	else
	{
		mini->flag = ft_split(mini->input, '|');
		while (mini->flag[i])
		{
			mini->trueflag = ft_goodsplit(mini->flag[i]);
			checkpath(ft_strjoin("/", \
				mini->trueflag[0]), mini);
			if (mini->check != NULL)
				i++;
			else
				return (0);
		}
	}
	return (2);
}