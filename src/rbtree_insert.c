/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:27:18 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/05 11:07:01 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rbtree.h"

static t_rbnode	*ft_rbinsert_rassoc_rot(t_rbnode *node, t_rbtree *tree)
{
	t_rbnode	*temp;

	temp = node->parent->parent->left;
	if (temp && temp->color == RED)
	{
		node->parent->color = BLACK;
		temp ? (temp->color = BLACK) : 0;
		node->parent->parent->color = RED;
		node = node->parent->parent;
	}
	else
	{
		if (node == node->parent->left)
		{
			node = node->parent;
			ft_rightrot(node, tree);
		}
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		ft_leftrot(node->parent->parent, tree);
	}
	return (node);
}

static t_rbnode	*ft_rbinsert_lassoc_rot(t_rbnode *node, t_rbtree *tree)
{
	t_rbnode	*temp;

	temp = node->parent->parent->right;
	if (temp && temp->color == RED)
	{
		node->parent->color = BLACK;
		temp ? (temp->color = BLACK) : 0;
		node->parent->parent->color = RED;
		node = node->parent->parent;
	}
	else
	{
		if (node == node->parent->right)
		{
			node = node->parent;
			ft_leftrot(node, tree);
		}
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		ft_rightrot(node->parent->parent, tree);
	}
	return (node);
}

static void		ft_rbinsert_rot(t_rbtree *tree, t_rbnode *node)
{
	while (node->parent && node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)
			node = ft_rbinsert_lassoc_rot(node, tree);
		else
			node = ft_rbinsert_rassoc_rot(node, tree);
	}
	tree->root->color = BLACK;
}

int		ft_rbinsert(t_rbtree *tree, t_rbnode *new)
{
	t_rbnode	*parent;
	t_rbnode	*temp;

	if ((*tree).root == NULL)
	{
		(*tree).root = new;
		(*tree).root->color = BLACK;
		return (EXIT_SUCCESS);
	}
	temp = tree->root;
	while (temp != NULL)
	{
		parent = temp;
		if (new->content < temp->content)
			temp = temp->left;
		else
			temp = temp->right;
	}
	new->parent = parent;
	(new->content < parent->content) ? (parent->left = new) :
		(parent->right = new);
	new->color = RED;
	ft_rbinsert_rot(tree, new);
	return (EXIT_SUCCESS);
}
