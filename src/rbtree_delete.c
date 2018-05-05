/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:02:29 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/05 10:56:15 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rbtree.h"

static inline __attribute__((always_inline))t_rbnode	
			*del_rrot(t_rbnode *temp, t_rbnode *move, t_rbtree *tree)
{
	if (temp->left->color == BLACK)
	{
		temp->right->color = BLACK;
		temp->color = RED;
		ft_leftrot(temp, tree);
		temp = move->parent->right;
	}
	temp->color = move->parent->color;
	move->parent->color = BLACK;
	temp->left->color = BLACK;
	ft_rightrot(move->parent, tree);
	move = tree->root;
	return (move);
}

static inline __attribute__((always_inline))t_rbnode	
			*del_lrot(t_rbnode *temp, t_rbnode *move, t_rbtree *tree)
{
	if (temp->right->color == BLACK)
	{
		temp->left->color = BLACK;
		temp->color = RED;
		ft_rightrot(temp, tree);
		temp = move->parent->right;
	}
	temp->color = move->parent->color;
	move->parent->color = BLACK;
	temp->right->color = BLACK;
	ft_leftrot(move->parent, tree);
	move = tree->root;
	return (move);
}

static t_rbnode	*ft_rbdelete_rassoc_rot(t_rbnode *move, t_rbtree *tree)
{
	t_rbnode	*temp;

	temp = move->parent->right;
	if (temp->color == RED)
	{
		temp->color = BLACK;
		move->parent->color = RED;
		ft_rightrot(move->parent, tree);
		temp = move->parent->left;
	}
	if (temp->right->color == BLACK && temp->left->color == BLACK)
	{
		temp->color = RED;
		move = move->parent->left;
	}
	else
		del_rrot(temp, move, tree);
	return (move);
}

static t_rbnode	*ft_rbdelete_lassoc_rot(t_rbnode *move, t_rbtree *tree)
{
	t_rbnode	*temp;

	temp = move->parent->left;
	if (temp->color == RED)
	{
		temp->color = BLACK;
		move->parent->color = RED;
		ft_leftrot(move->parent, tree);
		temp = move->parent->right;
	}
	if (temp->left->color == BLACK && temp->right->color == BLACK)
	{
		temp->color = RED;
		move = move->parent->right;
	}
	else
		del_lrot(temp, move, tree);
	return (move);
}

void		ft_rbdelete_rot(t_rbtree *tree, t_rbnode *move)
{
	while (move && move != tree->root && move->color == BLACK)
	{
		if (move == move->parent->left)
			move = ft_rbdelete_lassoc_rot(move, tree);
		else
			move = ft_rbdelete_rassoc_rot(move, tree);
	}
	tree->root->color = BLACK;
}
