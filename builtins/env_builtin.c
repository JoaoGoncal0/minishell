/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:12 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/22 01:38:15 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_update1(t_vars *mini)
{
	int i;
	int len;
	int j;
	
	i = 0;
	j = 0;
	while (i < mini->env_len && mini->env[i] != NULL)
		free(mini->env[i++]);	
	i = 0;
	while (mini->new_env[i])
		i++;
	len = i;
	mini->env = realloc(mini->env, sizeof(char *) * (len + 1));
	if (!mini->env)
		return;
	while (j < len)
	{
		mini->env[j] = ft_strdup(mini->new_env[j]);
		j++;
	}
	mini->env[j] = NULL;
	printf("\n\n----- UPDATED ENV ------\n\n\n");
	j = -1;
	while (++j < mini->env_len)
	{
		if (!mini->new_env[j])
			j++;
		printf("%s\n", mini->new_env[j]);
	}
}

void	env_update(t_vars *mini, char *str)
{
	int	i;

	i = 0;
	while (i < mini->env_len)
	{
		if (mini->env[i] && 
		ft_strncmp(mini->env[i], str, ft_strlen(str)) == 0)
		{
				i++;
				continue;
		}
		if (mini->env[i])
		{
			mini->new_env[i] = ft_strdup(mini->env[i]);
			printf("mini->env = %s\n", mini->env[i]);
			i++;
		}
	}
	mini->new_env[i] = NULL;
	env_update1(mini);
}
		

void	init_env(char **env, t_vars *mini)
{
	int	i;
	
	i = 0;
	while (env[i])
		i++;
	mini->env = malloc(sizeof(char *) * (i + 1));
	mini->new_env = malloc(sizeof(char *) * (i + 10));
	if (!mini->env || !mini->new_env)
		return ;
	mini->env_len = i;
	i = 0;
	while (i < mini->env_len)
	{
		mini->env[i] = ft_strdup(env[i]);
		i++;
	}
	mini->env[i] = NULL;
}

int	env_builtin(t_vars *mini)
{
	int	i;

	i = -1;
	while (++i < mini->env_len)
		printf("%s\n", mini->env[i]);
	return (0);
}
