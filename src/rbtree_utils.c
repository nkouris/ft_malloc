/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:39:29 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/05 12:07:05 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_rbnode	*ft_rbnewnode(int content)
{
	t_rbnode	*new;
	if (!(new = (t_rbnode *)calloc(1, sizeof(t_rbnode))))
		return (NULL);
	new->content = content;
	new->color = RED;
	return (new);
}

void		ft_rightrot(t_rbnode *node, t_rbtree *tree)
{
	t_rbnode	*temp;

	temp = node->left;
	node->left = temp->right;
	if (temp->right != NULL)
		temp->right->parent = node;
	temp->parent = node->parent;
	if (node->parent == NULL)
		tree->root = temp;
	else if (node == node->parent->right)
		node->parent->right = temp;
	else
		node->parent->left = temp;
	temp->left = node;
	node->parent = temp;
}

void		ft_leftrot(t_rbnode *node, t_rbtree *tree)
{
	t_rbnode	*temp;

	temp = node->right;
	node->right = temp->left;
	if (temp->left != NULL)
		temp->left->parent = node;
	temp->parent = node->parent;
	if (node->parent == NULL)
		tree->root = temp;
	else if (node == node->parent->left)
		node->parent->left = temp;
	else
		node->parent->right = temp;
	temp->left = node;
	node->parent = temp;
}

t_rbnode	*ft_bstminnode(t_rbnode *node)
{
	t_rbnode	*temp;

	temp = node;
	while (temp->left != NULL)
		temp = temp->left;
	return (temp);
}

void		ft_rbsubtransfer(t_rbtree *tree, t_rbnode *node, t_rbnode *temp)
{
	if (node->parent == NULL)
		tree->root = temp;
	else if (node == node->parent->left)
		node->parent->left = temp;
	else
		node->parent->right = temp;
	temp ? temp->parent = node->parent : 0;
}
