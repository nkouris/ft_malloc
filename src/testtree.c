#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

struct jsw_node
{
    int red;
    int data;
    struct jsw_node *link[2];
};

struct jsw_tree
{
    struct jsw_node *root;
};

struct jsw_node *make_node(int data)
{
	struct jsw_node	*new;

	if (!(new = (struct jsw_node *)(malloc(data))))
	{
		perror(strerror(errno));
		exit (1);
	}
	new->data = data;
	new->red = 1;
	new->link[0] = NULL;
	new->link[1] = NULL;
	return (new);
}

struct jsw_node *jsw_single(struct jsw_node *root, int dir)
{
    struct jsw_node *save = root->link[!dir];

    root->link[!dir] = save->link[dir];
    save->link[dir] = root;

    root->red = 1;
    save->red = 0;

    return (save);
}

struct jsw_node *jsw_double(struct jsw_node *root, int dir)
{
    root->link[!dir] = jsw_single(root->link[!dir], !dir);

    return (jsw_single(root, dir));
}

int is_red(struct jsw_node *root)
{
    return (root != NULL && root->red == 1);
}

struct jsw_node *jsw_insert_r(struct jsw_node *root, int data)
{
    if (root == NULL)
        root = make_node(data);
    else if (data != root->data)
    {
        int dir = root->data < data;

        root->link[dir] = jsw_insert_r(root->link[dir], data);

        if (is_red(root->link[dir]))
        {
            if (is_red(root->link[!dir]))
            {
                /* Case 1 */
                root->red = 1;
                root->link[0]->red = 0;
                root->link[1]->red = 0;
            }
            else
            {
                /* Cases 2 & 3 */
                if (is_red(root->link[dir]->link[dir]))
                    root = jsw_single(root, !dir);
                else if (is_red(root->link[dir]->link[!dir]))
                    root = jsw_double(root, !dir);
            }
        }
    }
    return root;
}

int jsw_insert(struct jsw_tree *tree, int data)
{
    tree->root = jsw_insert_r(tree->root, data);
    tree->root->red = 0;

    return 1;
}

/* TEST TREE BALANCE  ......................................................*/

int jsw_rb_assert(struct jsw_node *root)
{
    int lh, rh;

    if (root == NULL)
    {
        return 1;
    }
    else
    {
        struct jsw_node *ln = root->link[0];
        struct jsw_node *rn = root->link[1];

        /* Consecutive red links */
        if (is_red(root))
        {
            if (is_red(ln) || is_red(rn))
            {
                puts("Red violation");
                return 0;
            }
        }

        lh = jsw_rb_assert(ln);
        rh = jsw_rb_assert(rn);

        /* Invalid binary search tree */
        if ((ln != NULL && ln->data >= root->data) || (rn != NULL && rn->data <= root->data))
        {
            puts("Binary tree violation");
            return 0;
        }

        /* Black height mismatch */
        if (lh != 0 && rh != 0 && lh != rh)
        {
            puts("Black violation");
            return 0;
        }

        /* Only count black links */
        if (lh != 0 && rh != 0)
        {
            return is_red(root) ? lh : lh + 1;
        }
        else
        {
            return 0;
        }
    }
}

int		main(int argc, char **argv)
{
	int	i = 1;
	struct jsw_tree	*tree;

	if (argc < 2)
		printf("no, insert a list of random numbers\n");
	if (!(tree = (struct jsw_tree *)calloc(1, sizeof(struct jsw_tree))))
	{
		perror(strerror(errno));
		return (-1);
	}
	while (argv[i])
	{
		printf("go\n");
		jsw_insert(tree, atoi(argv[i]));
		i++;
	}
	return (1);
}
