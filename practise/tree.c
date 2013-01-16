/*
    usage: to practice the basic operation on binary-tree,
    including creating, inserting, deleting, traveling, etc
    author: ydzhang
    date: 2008年12月7日
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    void *data_p;
    struct tree *left;
    struct tree *right;
}tree_t;


//初始化一个节点, 初值置为data
int tree_make_node(tree_t **root, void *data)
{
    *root = (tree_t*) malloc(sizeof(tree_t));
    if(*root == NULL)
    {
        printf("malloc error\n");
        return -1;
    }
    (*root)->left = NULL;
    (*root)->right = NULL;
    (*root)->data_p = data;
    return 0;
}


//将new_node插入树中作为where_to的左孩子, 返回新插入结点的指针
tree_t* tree_insert_left(tree_t *new_node, tree_t *where_to)
{
    if(new_node != NULL)
    {
        tree_t *tmp;
        tmp = where_to->left;
        where_to->left = new_node;
        new_node->left = tmp;
    }
    return new_node;
}

//将new_node插入树中作为where_to的右孩子, 返回新插入结点的指针
tree_t* tree_insert_right(tree_t *new_node, tree_t *where_to)
{
    if(new_node != NULL)
    {
        tree_t *tmp;
        tmp = where_to->right;
        where_to->right = new_node;
        new_node->right = tmp;
    }
    return new_node;
}

//删除entry结点的左子树
void tree_del_left(tree_t *entry)
{
    entry->left = NULL;
    free(entry);
}

//删除entry结点的右子树
void tree_del_right(tree_t *entry)
{
    entry->right = NULL;
    free(entry);
}

#define VISIT(x) do { printf("%c", *(char*)((x)->data_p)); }while(0)
#define MAX_ELE 100

//前序遍历二叉树
void tree_pre_order(tree_t *root)
{
    if(root != NULL)
    {
        VISIT(root);
        tree_pre_order(root->left);
        tree_pre_order(root->right);
    }
}

/*
非递归思路： 先遍历左子树，遍历过程中
那个访问遍历结点，并将其入栈，返回时
退出当前栈顶元素遍历其其右子树
*/


void tree_pre_order_norec(tree_t *root)
{
      tree_t *stack[MAX_ELE];
      int top = 0;

      while(root != NULL || top != 0)
      {
          if(root != NULL)
          {
              VISIT(root);
              stack[top++] = root; //入栈
              root = root->left;
          }
          else
          {
              root = stack[--top]; //出栈
              root = root->right;
          }
      }
}


//中序遍历二叉树
void tree_in_order(tree_t *root)
{
    if(root != NULL)
    {
        tree_in_order(root->left);
        VISIT(root);
        tree_in_order(root->right);
    }
}

/*
非递归思路： 先遍历左子树，并将遍历结点入栈，返回时
退出当前栈顶元素并访问，再遍历其其右子树
*/

void tree_in_order_norec(tree_t *root)
{
    tree_t *stack[MAX_ELE];
    int top = 0;

    while(root != NULL || top != 0)
    {
        if(root != NULL)
        {
            stack[top++] = root;
            root = root->left;
        }
        else
        {
            root = stack[--top];
            VISIT(root);
            root = root->right;
        }
    }
}



//后序遍历二叉树
void tree_pos_order(tree_t *root)
{
    if(root != NULL)
    {
        tree_pos_order(root->left);
        tree_pos_order(root->right);
        VISIT(root);
    }
}


/*
   思路：先遍历左子树，并将遍历结点入栈，返回时
   去栈顶元素，如果该元素的右子树已经被访问(flag为1)，
   访问该结点，否则标记flag为1
*/
void tree_pos_order_norec(tree_t *root)
{
    typedef struct
    {
        tree_t *node;
        int flag;   //该结点的右子树是否被访问
    }pos_order;

    pos_order stack[MAX_ELE];
    int top = 0;

    while(root != NULL || top!= 0)
    {
        if(root != NULL)
        {
            stack[top].node = root;
            stack[top].flag = 0;
            top++;

            root = root->left;
        }
        else
        {
            pos_order tmp = stack[top-1];
            if(tmp.flag == 0)  //没有访问其右子树，访问之
            {
                stack[top-1].flag = 1;
                root = tmp.node->right;
            }
            else  //如果已经出栈访问了其右子树，访问该结点
            {
                VISIT(tmp.node);
                top--;
            }
        }
    }
}


//二叉树的层序遍历
void tree_layer_order(tree_t *root)
{
    tree_t *queue[MAX_ELE];
    int front = 0;
    int rear = 0;

    if(root == NULL) return;
    queue[rear++] = root;
    while(front != rear)
    {
        root = queue[front++];
        VISIT(root);
        if(root->left != NULL)
           queue[rear++] = root->left;
        if(root->right != NULL)
           queue[rear++] = root->right;
    }
}
//打印二叉树，逆时针旋转90读， 遍历顺序为 右根左， 参数n为层数
void tree_print(tree_t *root, int n)
{
    if(root != NULL)
    {
        tree_print(root->right, n+1);
        for(int i = -1; i < n; i++)
        {
            printf("--");
        }
        VISIT(root);
        printf("\n");
        tree_print(root->left, n+1);
    }
}

//释放以root为根的二叉树
void tree_free(tree_t *root)
{
    if(root != NULL)
    {
        tree_free(root->left);
        tree_free(root->right);
        free(root);
    }
}

/*********************test code*******************************/
int make_tree(tree_t **root)
{
    char *node = "ABCDEFGH";
    tree_make_node(root, (void*)(&node[0])); //根结点A

    tree_t *tmp;
    tree_t *p;

    tree_make_node(&tmp, (void*)(&node[1])); //B作为A的左子树
    p = tree_insert_left(tmp, *root);

    tree_make_node(&tmp, (void*)(&node[3]));  //D作为B的左子树
    p = tree_insert_left(tmp, p);

    tree_make_node(&tmp, (void*)(&node[5]));  //F作为D的右子树
    p = tree_insert_right(tmp, p);

    tree_make_node(&tmp, (void*)(&node[7]));  //H作为F的左子树
    p = tree_insert_left(tmp, p);

    tree_make_node(&tmp, (void*)(&node[2])); //C作为A的右子树
    p = tree_insert_right(tmp, *root);

    tree_make_node(&tmp, (void*)(&node[4])); //E作为C的右子树
    p = tree_insert_right(tmp, p);

    tree_make_node(&tmp, (void*)(&node[6])); //G作为E的左子树
    p = tree_insert_left(tmp, p);

    return 0;
}


int main()
{
  tree_t *root;
  make_tree(&root);

  tree_print(root, 0);
  printf("\n\n");

  printf("前序遍历序列\n");
  tree_pre_order(root);
  printf("\n");
  tree_pre_order_norec(root);
  printf("\n\n");

  printf("中序遍历序列\n");
  tree_in_order_norec(root);
  printf("\n");
  tree_in_order(root);
  printf("\n\n");

  printf("后序遍历序列\n");
  tree_pos_order(root);
  printf("\n");
  tree_pos_order_norec(root);
  printf("\n\n");

  printf("层序遍历序列\n");
  tree_layer_order(root);
  printf("\n\n");
  return 0;
}

/*********************test code*******************************/
