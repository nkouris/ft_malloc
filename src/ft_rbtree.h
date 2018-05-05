/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 10:54:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/05 11:23:45 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RBTREE_H
# define FT_RBTREE_H

# define RED 0x01
# define BLACK 0x02

typedef struct		s_rbnode
{
	void			*pad;
	struct s_rbnode	*parent;
	struct s_rbnode	*left;
	struct s_rbnode	*right;
	uint64_t		content;
	uint8_t			color;
}					t_rbnode;

typedef struct		s_rbtree
{
	t_rbnode		*root;
}					t_rbtree;


void		ft_rbdelete(t_rbtree *tree, t_rbnode *node);

void		ft_rbdelete_rot(t_rbtree *tree, t_rbnode *move);

int			ft_rbinsert(t_rbtree *tree, t_rbnode *new);

void		ft_rbsubtransfer(t_rbtree *tree, t_rbnode *node, t_rbnode *temp);
t_rbnode	*ft_bstminnode(t_rbnode *node);
void		ft_leftrot(t_rbnode *node, t_rbtree *tree);
void		ft_rightrot(t_rbnode *node, t_rbtree *tree);
t_rbnode	*ft_rbnewnode(int content);

#endif
