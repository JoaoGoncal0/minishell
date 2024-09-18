/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:12 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/18 17:53:57 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_update1(t_vars *mini)
{
	int i;
	
	i = 0;
	if (mini->env[i])
		free(mini->env);
	while (i < mini->env_len)
	{
		mini->env[i] = ft_strdup(mini->new_env[i]);
		i++;
	}
	mini->env[i] = NULL;
}

void	env_update(t_vars *mini, char *str)
{
	int	i;
	int j = -1;

	i = 0;
	
	while (i < mini->env_len)
	{
		if (ft_strncmp(mini->env[i], str, ft_strlen(str)) == 0)
			i++;
		else
		{
			mini->new_env[i] = ft_strdup(mini->env[i]);
			printf("mini->env = %s\n", mini->env[i]);
			i++;
		}
	}
	mini->new_env[i] = NULL;
	printf("\n\n\n\n\n");
	while (++j < mini->env_len)
	{
		if (!mini->new_env[j])
			j++;
		printf("%s\n", mini->new_env[j]);
	}
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
	if (!mini->env)
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
