/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_delstart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:08:52 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/05 11:09:04 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rbtree.h"

static inline __attribute__((always_inline))t_rbnode	
*ft_subdeletemov(t_rbtree *tree, t_rbnode *move, t_rbnode *node,
		uint32_t *og_color)
{
	t_rbnode	*temp;

	temp = ft_bstminnode(node->right);
	*og_color = temp->color;
	move = temp->right;
	if (temp->parent == node)
		move->parent = temp;
	else
	{
		ft_rbsubtransfer(tree, temp, temp->right);
		temp->right = node->right;
		temp->right->parent = temp;
	}
	ft_rbsubtransfer(tree, node, temp);
	temp->left = node->left;
	temp->left->parent = temp;
	temp->color = node->color;
	return (move);
}

void		ft_rbdelete(t_rbtree *tree, t_rbnode *node)
{
	t_rbnode	*move;
	uint32_t	og_color;

	og_color = node->color;
	move = NULL;
	if (node && node->left == NULL)
	{
		move = node->right;
		ft_rbsubtransfer(tree, node, node->right);
	}
	else if (node->right == NULL)
	{
		move = node->left;
		ft_rbsubtransfer(tree, node, node->left);
	}
	else
		move = ft_subdeletemov(tree, move, node, &og_color);
	if (og_color == BLACK)
		ft_rbdelete_rot(tree, move);	
}

/*
int		main(int argc, char **argv)
{
	t_rbtree	tree;
	t_rbnode	*new;
	t_rbnode	*temp;
	int32_t		i;

	i = 1;
	bzero(&tree, sizeof(t_rbtree));
	if (argc < 2)
	{
		dprintf(2, "Please enter a valid string of ints\n");
		return (-1);
	}
	else
	{
		while (argv[i])
		{
			if (i == 12)
				temp = new;
			if ((new = ft_rbnewnode(atoi(argv[i]))) == NULL)
				return (-1);
			ft_rbinsert(&tree, new);
			i++;
		}
		ft_rbdelete(&tree, temp);
	}
	return (1);
}
*/
