/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:46:26 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/27 00:09:15 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// verificar o numero de argumentos e o formato dos mesmos
// só aceito letras ou o _ 
// seguidas de letras minus Maius ou numeros ou _
// adicionar ao export

int     export_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((!(str[i] >= 'a' && str[i] <= 'z')) || 
        (!(str[i] >= 'A' && str[i] <= 'Z')) || (str[i] != '_'))
            return (1, printf("export: `%c': \ 
            not a valid identifier\n", str[i]));
    }
    return (0);
}

void    export_var(t_vars *mini)
{
    int     i;
    char    **split;

    i = 0;
    if (ft_strchr (mini->input, ' '))
    {
        split = ft_split(mini->input[i], ' ');
        while (split[i]) 
        {
            if (export_check(split[i]) == 0)
            {
                // add no export 
                // fazer um export_len que é diferente do env
                // o numero do export len aumenta tendo em conta 
                // o numero de args a dar export
                // mandar para o export no final 
            }
            i++;
        }
    }
}