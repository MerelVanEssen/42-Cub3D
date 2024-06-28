/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:09 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/10 17:33:31 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next_node;

	if (*lst == NULL)
		return ;
	node = *lst;
	while (node != NULL)
	{
		next_node = node->next;
		ft_lstdelone(node, del);
		node = next_node;
	}
	*lst = NULL;
}
