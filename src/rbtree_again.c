# include <stdint.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

# define RED 0x01
# define BLACK 0x02
# define LEFT 0x01
# define RIGHT 0x02

typedef struct		s_rbnode
{
	struct s_rbnode	*parent;
	struct s_rbnode	*left;
	struct s_rbnode	*right;
	uint32_t		color;
	int32_t			content;
}					t_rbnode;

typedef struct		s_rbtree
{
	t_rbnode		*root;
}					t_rbtree;

void		ft_rightrot(t_rbnode *node, t_rbtree *tree)
{
	t_rbnode	*temp;

	temp = node->left;
	node->left = temp->right;
//	temp->parent ? (temp->parent->right = node) : 0;
	temp->parent = node->parent;

	if (node->parent == tree->root)
		tree->root = temp;
	else
	{
		if (node == node->parent->left)
			node->parent = temp;
		else
			node->parent->right = temp;
	}
	temp->right = node;
	node->parent = temp;
}

void		ft_leftrot(t_rbnode *node, t_rbtree *tree)
{
	t_rbnode	*temp;

	temp = node->right;
	node->right = temp->left;
//	temp->parent ? (temp->parent->left = node) : 0;
	temp->parent = node->parent;

	if (node->parent == NULL)
		tree->root = temp;
	else
	{
		if (node == node->parent->left)
			node->parent->left = temp;
		else
			node->parent->right = temp;
	}
	temp->left = node;
	node->parent = temp;
}

void		ft_rbinsert_rot(t_rbtree *tree, t_rbnode *node)
{
	t_rbnode	*temp;

	while (node->parent && node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			temp = node->parent->parent->right;
			if (!temp || temp->color == RED)
			{
				node->parent->color = BLACK;
				temp ? (temp->color = BLACK) : 0;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node->parent->right != NULL)
				{
					node = node->parent;
					ft_leftrot(node, tree);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				ft_rightrot(node->parent->parent, tree);
			}
		}
		else
		{
			temp = node->parent->parent->left;
			if (!temp || temp->color == RED)
			{
				node->parent->color = BLACK;
				temp ? (temp->color = BLACK) : 0;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node->parent->left != NULL)
				{
					node = node->parent;
					ft_rightrot(node, tree);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				ft_leftrot(node->parent->parent, tree);
			}
		}
	}
	tree->root->color = BLACK;
}

/*
void		ft_rbinsert_rot(t_rbtree *tree, t_rbnode *node)
{
	t_rbnode	*temp;

	while (node->parent && node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			temp = node->parent->parent->right;
			if (temp && temp->color == RED)
			{
				node->parent->color = BLACK;
				temp->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node->parent->right != NULL)
				{
					node = node->parent;
					ft_leftrot(node, tree);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				ft_rightrot(node->parent->parent, tree);
			}
		}
		else
		{
			temp = node->parent->parent->left;
			if (temp && temp->color == RED)
			{
				node->parent->color = BLACK;
				temp->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node->parent->left != NULL)
				{
					node = node->parent;
					ft_rightrot(node, tree);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				ft_leftrot(node->parent->parent, tree);
			}
		}
	}
	tree->root->color = BLACK;
}
*/

t_rbnode	*ft_rbnewnode(int content)
{
	t_rbnode	*new;
	if (!(new = (t_rbnode *)calloc(1, sizeof(t_rbnode))))
		return (NULL);
	new->content = content;
	new->color = RED;
	return (new);
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
	if (new->content < parent->content)
		parent->left = new;
	else
		parent->right = new;
	new->color |= RED;
	ft_rbinsert_rot(tree, new);
	return (EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	/* tree instantiate */
	t_rbtree	tree;
	t_rbnode	*new;
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
			if ((new = ft_rbnewnode(atoi(argv[i]))) == NULL)
				return (-1);
			ft_rbinsert(&tree, new);
			i++;
		}
	}
	return (1);
}
