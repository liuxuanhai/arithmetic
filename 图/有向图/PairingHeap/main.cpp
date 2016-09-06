#include <stdlib.h>

typedef struct PairingHeapNode
{
	int							key;
	struct	PairingHeapNode*	child;
	struct	PairingHeapNode*	sibling;
	struct	PairingHeapNode*	prev;

}PairHeap;

static PairHeap* merge_subheaps(PairHeap *p, PairHeap *q);
static PairHeap* combine_siblings(PairHeap *p);

PairHeap* PairHeap_insert(PairHeap *p, int key)
{
	PairHeap *node;

	node = (PairHeap*)malloc(sizeof(*node));
	if(node == NULL)
		return NULL;

	node->key = key;
	node->child = node->sibling = node->prev = NULL;

	if(p == NULL)
		return node;
	else
		return merge_subheaps(p, node);
}

PairHeap* PairHeap_DecreaseKey(PairHeap *p, PairHeap *pos, int d)
{
	if(d < 0)
		return p;

	pos->key = pos->key - d;
	if(p == pos)
		return p;

	if(pos->sibling != NULL)
		pos->sibling->prev = pos->prev;

	if(pos->prev->child == pos)
		pos->prev->child = pos->sibling;
	else
		pos->prev->sibling = p->sibling;

	p->sibling = NULL;
	return merge_subheaps(p, pos);
}

PairHeap* PairHeap_DeleteMin(int *key, PairHeap *p)
{
	PairHeap *new_root;

	if(p == NULL)
		return NULL;
	else
	{
		*key = p->key;
		if(p->child != NULL)
			new_root = combine_siblings(p->child);

		free(p);
	}
	return new_root;
}

static PairHeap* combine_siblings(PairHeap *p)
{
	PairHeap *tree_array[1024];
	int i, count;

	if(p->sibling == NULL)
		return p;

	for(count = 0; p != NULL; count++)
	{
		tree_array[count] = p;
		p->prev->sibling = NULL;
		p = p->sibling;
	}
	tree_array[count] = NULL;

	for(i = 1; i < count; i++)
		tree_array[i] = merge_subheaps(tree_array[i-1], tree_array[i]);

	return tree_array[count-1];
}

static PairHeap* merge_subheaps(PairHeap *p, PairHeap *q)
{
	if(q == NULL)
		return p;
	else if(p->key <= q->key)
	{
		q->prev = p;
		p->sibling = q->sibling;
		if(p->sibling != NULL)
			p->sibling->prev = p;

		q->sibling = p->child;
		if(q->sibling != NULL)
			q->sibling->prev = q;

		p->child = q;
		return p;
	}
	else
	{
		q->prev = p->prev;
		p->prev = q;
		p->sibling = q->child;
		if(p->sibling != NULL)
			p->sibling->prev = p;

		q->child = p;
		return q;
	}
}
