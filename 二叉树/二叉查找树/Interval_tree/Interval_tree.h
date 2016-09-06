/**
 * C++ 语言: 红黑树
 *
 * @author skywang
 * @date 2013/11/07
 */

#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

#include <iomanip>
#include <iostream>
using namespace std;

enum RBTColor{RED, BLACK};

template <class T>
class Interval{
public:T low;
T high;
Interval(T l,T h):low(l),high(h){}
};

template <class T>
class RBTNode{
    public:
        RBTColor color;    // 颜色
        T key;            // 关键字(键值)
        RBTNode *left;    // 左孩子
        RBTNode *right;    // 右孩子
        RBTNode *parent; // 父结点
/*****************order-statistic tree**********************************/
        Interval<T>* inter;
        T subtree_max;

        RBTNode(RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r,Interval<T> *i):
            key(i->low),color(c),parent(),left(l),right(r),inter(i),subtree_max(i->high){}
};

template <class T>
class RBTree {
    private:
        RBTNode<T> *mRoot;    // 根结点

    public:
        RBTree();
        ~RBTree();

        // 前序遍历"红黑树"
        void preOrder();
        // 中序遍历"红黑树"
        void inOrder();
        // 后序遍历"红黑树"
        void postOrder();
        T Max(T a,T b,T c);
        RBTNode<T>* Inter_search(Interval<T>* i);
        // (递归实现)查找"红黑树"中键值为key的节点
        RBTNode<T>* search(Interval<T>* i);
        //RBTNode<T>* Inter_remove_search(Interval i);
        // (非递归实现)查找"红黑树"中键值为key的节点
        RBTNode<T>* iterativeSearch(T key);

        // 查找最小结点：返回最小结点的键值。
        T minimum();
        // 查找最大结点：返回最大结点的键值。
        T maximum();

        // 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
        RBTNode<T>* successor(RBTNode<T> *x);
        // 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
        RBTNode<T>* predecessor(RBTNode<T> *x);


        // 将结点(key为节点键值)插入到红黑树中
        void Inter_insert(Interval<T>* i);

        // 删除结点(key为节点键值)
        void Inter_remove(Interval<T> *i);

        // 销毁红黑树
        void destroy();

        // 打印红黑树
        void Inter_print();
    private:
        // 前序遍历"红黑树"
        void preOrder(RBTNode<T>* tree) const;
        // 中序遍历"红黑树"
        void inOrder(RBTNode<T>* tree) const;
        // 后序遍历"红黑树"
        void postOrder(RBTNode<T>* tree) const;

        RBTNode<T>* Inter_search(RBTNode<T>* tree,Interval<T>* i);
        // (递归实现)查找"红黑树x"中键值为key的节点
        RBTNode<T>* search(RBTNode<T>* x, Interval<T>* i) const;
        void Inter_remove(RBTNode<T>* &root, RBTNode<T> *node);
        RBTNode<T>* OS_remove_search(RBTNode<T>* x, T key) const;
        // (非递归实现)查找"红黑树x"中键值为key的节点
        RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

        // 查找最小结点：返回tree为根结点的红黑树的最小结点。
        RBTNode<T>* minimum(RBTNode<T>* tree);
        // 查找最大结点：返回tree为根结点的红黑树的最大结点。
        RBTNode<T>* maximum(RBTNode<T>* tree);

        // 左旋
        void Inter_leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
        // 右旋
        void Inter_rightRotate(RBTNode<T>* &root, RBTNode<T>* y);

        // 插入函数
        void Inter_insert(RBTNode<T>* &root, RBTNode<T>* node);
        // 插入修正函数
        void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
        // 删除函数
        void OS_remove(RBTNode<T>* &root, RBTNode<T> *node);
        // 删除修正函数
        void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

        // 销毁红黑树
        void destroy(RBTNode<T>* &tree);

        // 打印红黑树
        void Inter_print(RBTNode<T>* tree, T key, int direction);
        void updata_onebranch(RBTNode<T> *node);
        void updata_leaf(RBTNode<T> *node);
        void updata_twobranch(RBTNode<T> *node,RBTNode<T> *rep);


#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};

/*
 * 构造函数
 */
template <class T>
RBTree<T>::RBTree():mRoot(NULL)
{
    mRoot = NULL;
}

/*
 * 析构函数
 */
template <class T>
RBTree<T>::~RBTree()
{
    destroy();
}
template <class T>
T RBTree<T>::Max(T a,T b,T c)
{
    if(a>b)
        return (a>c)?a:c;
    else return (b>c)?b:c;
}

template <class T>
RBTNode<T>* RBTree<T>::Inter_search(RBTNode<T>* tree,Interval<T>* i)
{
    while(tree!=NULL&&(tree->inter->high<i->low||i->high<tree->inter->low))
        if(tree->left!=NULL&&tree->left->subtree_max>=i->low)
            tree=tree->left;
        else tree=tree->right;
    return tree;
}
template <class T>
RBTNode<T>* RBTree<T>::Inter_search(Interval<T>* i)
{
    Inter_search(mRoot,i);
}
/*
 * 前序遍历"红黑树"
 */
template <class T>
void RBTree<T>::preOrder(RBTNode<T>* tree) const
{
    if(tree != NULL)
    {
        cout<< tree->key << " " ;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void RBTree<T>::preOrder()
{
    preOrder(mRoot);
}

/*
 * 中序遍历"红黑树"
 */
template <class T>
void RBTree<T>::inOrder(RBTNode<T>* tree) const
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        cout<< tree->key << " " ;
        inOrder(tree->right);
    }
}

template <class T>
void RBTree<T>::inOrder()
{
    inOrder(mRoot);
}

/*
 * 后序遍历"红黑树"
 */
template <class T>
void RBTree<T>::postOrder(RBTNode<T>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout<< tree->key << " " ;
    }
}

template <class T>
void RBTree<T>::postOrder()
{
    postOrder(mRoot);
}

/*
 * (递归实现)查找"红黑树x"中键值为key的节点
 */
template <class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x, Interval<T>* i) const
{
    if (x==NULL || (x->inter->high==i->high&&x->key==i->low))
        return x;

    if (i->low < x->key)
        return search(x->left, i);
    else
        return search(x->right, i);
}

template <class T>
RBTNode<T>* RBTree<T>::search(Interval<T>* i)
{
    search(mRoot,i);
}



/*
 * (非递归实现)查找"红黑树x"中键值为key的节点
 */
template <class T>
RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T>* x, T key) const
{
    while ((x!=NULL) && (x->key!=key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

template <class T>
RBTNode<T>* RBTree<T>::iterativeSearch(T key)
{
    iterativeSearch(mRoot, key);
}

/*
 * 查找最小结点：返回tree为根结点的红黑树的最小结点。
 */
template <class T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <class T>
T RBTree<T>::minimum()
{
    RBTNode<T> *p = minimum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}

/*
 * 查找最大结点：返回tree为根结点的红黑树的最大结点。
 */
template <class T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T>
T RBTree<T>::maximum()
{
    RBTNode<T> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}

/*
 * 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
 */
template <class T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T> *x)
{
    // 如果x存在右孩子，则"x的后继结点"为 "以其右孩子为根的子树的最小结点"。
    if (x->right != NULL)
        return minimum(x->right);

    // 如果x没有右孩子。则x有以下两种可能：
    // (01) x是"一个左孩子"，则"x的后继结点"为 "它的父结点"。
    // (02) x是"一个右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
    RBTNode<T>* y = x->parent;
    while ((y!=NULL) && (x==y->right))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/*
 * 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
 */
template <class T>
RBTNode<T>* RBTree<T>::predecessor(RBTNode<T> *x)
{
    // 如果x存在左孩子，则"x的前驱结点"为 "以其左孩子为根的子树的最大结点"。
    if (x->left != NULL)
        return maximum(x->left);

    // 如果x没有左孩子。则x有以下两种可能：
    // (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
    // (01) x是"一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
    RBTNode<T>* y = x->parent;
    while ((y!=NULL) && (x==y->left))
    {
        x = y;
        y = y->parent;
    }

    return y;
}



/*
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 *
 *
 */
template <class T>
void RBTree<T>::Inter_leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
    // 设置x的右孩子为y
    RBTNode<T> *y = x->right;

    // 将 “y的左孩子” 设为 “x的右孩子”；
    // 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    // 将 “x的父亲” 设为 “y的父亲”
    y->parent = x->parent;

    if (x->parent == NULL)
    {
        root = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
        else
            x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
    }

    // 将 “x” 设为 “y的左孩子”
    y->left = x;
    // 将 “x的父节点” 设为 “y”
    x->parent = y;
    y->subtree_max=x->subtree_max;
    if(x->left==NULL||x->right==NULL)
    {
        if(x->left==NULL&&x->right!=NULL)
            x->subtree_max=(x->inter->high>x->right->subtree_max)?x->inter->high:x->right->subtree_max;
        else if(x->left!=NULL&&x->right==NULL)
            x->subtree_max=(x->inter->high>x->left->subtree_max)?x->inter->high:x->left->subtree_max;
        else x->subtree_max=x->inter->high;
    }
    else    x->subtree_max=Max(x->inter->high,x->left->subtree_max,x->right->subtree_max);

}

/*
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 *
 */
template <class T>
void RBTree<T>::Inter_rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
    // 设置x是当前节点的左孩子。
    RBTNode<T> *x = y->left;

    // 将 “x的右孩子” 设为 “y的左孩子”；
    // 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    // 将 “y的父亲” 设为 “x的父亲”
    x->parent = y->parent;

    if (y->parent == NULL)
    {
        root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
        else
            y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
    }

    // 将 “y” 设为 “x的右孩子”
    x->right = y;

    // 将 “y的父节点” 设为 “x”
    y->parent = x;
    x->subtree_max=y->subtree_max;
    if(y->left==NULL||y->right==NULL)
    {
        if(y->left==NULL&&y->right!=NULL)
            y->subtree_max=(y->inter->high>y->right->subtree_max)?y->inter->high:y->right->subtree_max;
        else if(y->left!=NULL&&y->right==NULL)
            y->subtree_max=(y->inter->high>y->left->subtree_max)?y->inter->high:y->left->subtree_max;
        else y->subtree_max=y->inter->high;
    }
    else    y->subtree_max=Max(y->inter->high,y->left->subtree_max,y->right->subtree_max);

}

/*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点        // 对应《算法导论》中的z
 */
template <class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
    RBTNode<T> *parent, *gparent;

    // 若“父节点存在，并且父节点的颜色是红色”
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
            // Case 1条件：叔叔节点是红色
            {
                RBTNode<T> *uncle = gparent->right;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                RBTNode<T> *tmp;
                Inter_leftRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            Inter_rightRotate(root, gparent);
        }
        else//若“z的父节点”是“z的祖父节点的右孩子”
        {
            // Case 1条件：叔叔节点是红色
            {
                RBTNode<T> *uncle = gparent->left;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                RBTNode<T> *tmp;
                Inter_rightRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是右孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            Inter_leftRotate(root, gparent);
        }
    }

    // 将根节点设为黑色
    rb_set_black(root);
}

/*
 * 将结点插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 插入的结点        // 对应《算法导论》中的node
 */
template <class T>
void RBTree<T>::Inter_insert(RBTNode<T>* &root, RBTNode<T>* node)
{
    RBTNode<T> *y = NULL;
    RBTNode<T> *x = root;

    // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
    while (x != NULL)
    {
        y = x;
        if(y->subtree_max<node->subtree_max) y->subtree_max=node->subtree_max;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y!=NULL)
    {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    else
        root = node;



    // 2. 设置节点的颜色为红色
    node->color = RED;

    // 3. 将它重新修正为一颗二叉查找树
    insertFixUp(root, node);
}

/*
 * 将结点(key为节点键值)插入到红黑树中
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 插入结点的键值
 */
template <class T>
void RBTree<T>::Inter_insert(Interval<T>* i)
{
    RBTNode<T> *z=NULL;

    // 如果新建结点失败，则返回。
    if ((z=new RBTNode<T>(BLACK,NULL,NULL,NULL,i)) == NULL)
        return ;

    Inter_insert(mRoot, z);
}

/*
 * 红黑树删除修正函数
 *
 * 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 待修正的节点
 */
template <class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
    RBTNode<T> *other;

    while ((!node || rb_is_black(node)) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的
                rb_set_black(other);
                rb_set_red(parent);
                Inter_leftRotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    rb_set_black(other->left);
                    rb_set_red(other);
                    Inter_rightRotate(root, other);
                    other = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                Inter_leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的
                rb_set_black(other);
                rb_set_red(parent);
                Inter_rightRotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    rb_set_black(other->right);
                    rb_set_red(other);
                    Inter_leftRotate(root, other);
                    other = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                Inter_rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

/*
 * 删除结点(node)，并返回被删除的结点
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 删除的结点
 */
template <class T>
void RBTree<T>::Inter_remove(RBTNode<T>* &root, RBTNode<T> *node)
{
    RBTNode<T> *child, *parent,*delete_p;
    RBTColor color;

    // 被删除节点的"左右孩子都不为空"的情况。
    if ( (node->left!=NULL) && (node->right!=NULL) )
    {
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        RBTNode<T> *replace = node;

        // 获取后继节点
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        updata_leaf(replace);

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        }
        else
            // "node节点"是根节点，更新根节点。
            root = replace;

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = rb_parent(replace);
        // 保存"取代节点"的颜色
        color = rb_color(replace);

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        }
        else
        {
            // child不为空
            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        updata_twobranch(node,replace);

        if (color == BLACK)
            removeFixUp(root, child, parent);

        delete node;
        return ;
    }

    if( (node->left==NULL) && (node->right==NULL) ) updata_leaf(node);
    else updata_onebranch(node);

    if (node->left !=NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
        child->parent = parent;

    // "node节点"不是根节点
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root = child;

    if (color == BLACK)
        removeFixUp(root, child, parent);
    delete node;
}
template <class T>
void RBTree<T>::updata_twobranch(RBTNode<T> *node,RBTNode<T> *rep)
{
    RBTNode<T> *parent,*child,*brother;
    T bigger_branch=(node->left->subtree_max>node->right->subtree_max)?node->left->subtree_max:node->right->subtree_max;
    cout<<" in updata_twobranch"<<endl;
    if(node->inter->high>bigger_branch)
    {
        rep->subtree_max=bigger_branch;
        parent=rep;

        while(parent->parent!=NULL&&parent->parent->subtree_max==node->inter->high)
        {
            child=parent;
            parent=parent->parent;
            brother=(child==parent->left)?parent->right:parent->left;
            if(brother==NULL)
            {
                parent->subtree_max=(child->subtree_max>parent->inter->high)?child->subtree_max:child->subtree_max;
            }
            else{parent->subtree_max=Max(child->subtree_max,parent->inter->high,brother->subtree_max);}
        }
    }

}
template <class T>
void RBTree<T>::updata_leaf(RBTNode<T> *node)
{

    RBTNode<T> *parent,*child,*brother;
    parent=node->parent;
    if(parent->subtree_max==node->subtree_max)
        parent->subtree_max=parent->inter->high;
    cout<<" in updata_leaf"<<endl;
    while(parent->parent!=NULL&&parent->parent->subtree_max==node->subtree_max)
        {
            child=parent;
            parent=parent->parent;
            brother=(child==parent->left)?parent->right:parent->left;
            if(brother==NULL)
            {
                parent->subtree_max=(child->subtree_max>parent->inter->high)?child->subtree_max:child->subtree_max;
            }
            else{parent->subtree_max=Max(child->subtree_max,parent->inter->high,brother->subtree_max);}
        }
}
template <class T>
void RBTree<T>::updata_onebranch(RBTNode<T> *node)
{
    RBTNode<T> *parent,*child,*brother;
    parent=node->parent;
    cout<<" in updata_onebranch"<<endl;
    if(parent->subtree_max==node->subtree_max)
    {
        brother=(node==parent->left)?parent->right:parent->left;
        child=(node->left==NULL)?node->right:node->left;
        if(brother==NULL)
        {
            parent->subtree_max=(child->subtree_max>parent->inter->high)?child->subtree_max:child->subtree_max;
        }
        else{parent->subtree_max=Max(child->subtree_max,parent->inter->high,brother->subtree_max);}
        while(parent->parent!=NULL&&parent->parent->subtree_max==node->subtree_max)
        {
            child=parent;
            parent=parent->parent;
            brother=(child==parent->left)?parent->right:parent->left;
            if(brother==NULL)
            {
                parent->subtree_max=(child->subtree_max>parent->inter->high)?child->subtree_max:child->subtree_max;
            }
            else{parent->subtree_max=Max(child->subtree_max,parent->inter->high,brother->subtree_max);}
        }
    }
}
/*
 * 删除红黑树中键值为key的节点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 */
template <class T>
void RBTree<T>::Inter_remove(Interval<T> *i)
{
    RBTNode<T> *node;

    // 查找key对应的节点(node)，找到的话就删除该节点
    if ((node = search(mRoot, i)) != NULL)
        Inter_remove(mRoot, node);
}

/*
 * 销毁红黑树
 */
template <class T>
void RBTree<T>::destroy(RBTNode<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        return destroy(tree->left);
    if (tree->right != NULL)
        return destroy(tree->right);

    delete tree;
    tree=NULL;
}

template <class T>
void RBTree<T>::destroy()
{
    destroy(mRoot);
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void RBTree<T>::Inter_print(RBTNode<T>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            cout << setw(2) << "["<<tree->key<<","<<tree->inter->high<<"]  " << "(B) is root" << "  subtree_max is"<<tree->subtree_max<< endl;
        else                // tree是分支节点
            cout << setw(2) <<  "["<<tree->key<<","<<tree->inter->high<<"]  "<<  (rb_is_red(tree)?"(R)":"(B)") << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << "  subtree_max is"<<tree->subtree_max<< endl;

        Inter_print(tree->left, tree->key, -1);
        Inter_print(tree->right,tree->key,  1);
    }
}

template <class T>
void RBTree<T>::Inter_print()
{
    if (mRoot != NULL)
        Inter_print(mRoot, mRoot->key, 0);
}

#endif


