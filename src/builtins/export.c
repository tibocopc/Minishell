/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:23:42 by aaiache           #+#    #+#             */
/*   Updated: 2025/08/19 17:38:03 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"



// #include <stdio.h>

// t_env_list    *env_push_front(t_env_list *env, const char *key, char *value,
//         bool is_private)
// {
//     t_env_list    *node;

//     node = malloc(sizeof(t_env_list));
//     if (!node)
//         return (NULL);
//     node->next = env;
//     node->is_private = is_private;
//     node->key = key;
//     node->value = value;
//     return (node);
// }

// int    main(int ac, char **av, char **envp)
// {
//     t_env_list    *env;
//     char        *sp;

//     env = NULL;
//     while (*envp)
//     {
//         sp = ft_split(*envp++, '=');
//         env = env_push_front(env, sp[0], sp[1], false);
//     }
// }

// void export(tah)