/*
    usage: to practice the basic operation on binary-tree,
    including creating, inserting, deleting, traveling, etc
    author: ydzhang
    date: 2008��12��7��
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    void *data_p;
    struct tree *left;
    struct tree *right;
}tree_t;


//��ʼ��һ���ڵ�, ��ֵ��Ϊdata
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


//��new_node����������Ϊwhere_to������, �����²������ָ��
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

//��new_node����������Ϊwhere_to���Һ���, �����²������ָ��
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

//ɾ��entry����������
void tree_del_left(tree_t *entry)
{
    entry->left = NULL;
    free(entry);
}

//ɾ��entry����������
void tree_del_right(tree_t *entry)
{
    entry->right = NULL;
    free(entry);
}

#define VISIT(x) do { printf("%c", *(char*)((x)->data_p)); }while(0)
#define MAX_ELE 100

//ǰ�����������
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
�ǵݹ�˼·�� �ȱ���������������������
�Ǹ����ʱ�����㣬��������ջ������ʱ
�˳���ǰջ��Ԫ�ر�������������
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
              stack[top++] = root; //��ջ
              root = root->left;
          }
          else
          {
              root = stack[--top]; //��ջ
              root = root->right;
          }
      }
}


//�������������
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
�ǵݹ�˼·�� �ȱ������������������������ջ������ʱ
�˳���ǰջ��Ԫ�ز����ʣ��ٱ�������������
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



//�������������
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
   ˼·���ȱ������������������������ջ������ʱ
   ȥջ��Ԫ�أ������Ԫ�ص��������Ѿ�������(flagΪ1)��
   ���ʸý�㣬������flagΪ1
*/
void tree_pos_order_norec(tree_t *root)
{
    typedef struct
    {
        tree_t *node;
        int flag;   //�ý����������Ƿ񱻷���
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
            if(tmp.flag == 0)  //û�з�����������������֮
            {
                stack[top-1].flag = 1;
                root = tmp.node->right;
            }
            else  //����Ѿ���ջ�������������������ʸý��
            {
                VISIT(tmp.node);
                top--;
            }
        }
    }
}


//�������Ĳ������
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
//��ӡ����������ʱ����ת90���� ����˳��Ϊ �Ҹ��� ����nΪ����
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

//�ͷ���rootΪ���Ķ�����
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
    tree_make_node(root, (void*)(&node[0])); //�����A

    tree_t *tmp;
    tree_t *p;

    tree_make_node(&tmp, (void*)(&node[1])); //B��ΪA��������
    p = tree_insert_left(tmp, *root);

    tree_make_node(&tmp, (void*)(&node[3]));  //D��ΪB��������
    p = tree_insert_left(tmp, p);

    tree_make_node(&tmp, (void*)(&node[5]));  //F��ΪD��������
    p = tree_insert_right(tmp, p);

    tree_make_node(&tmp, (void*)(&node[7]));  //H��ΪF��������
    p = tree_insert_left(tmp, p);

    tree_make_node(&tmp, (void*)(&node[2])); //C��ΪA��������
    p = tree_insert_right(tmp, *root);

    tree_make_node(&tmp, (void*)(&node[4])); //E��ΪC��������
    p = tree_insert_right(tmp, p);

    tree_make_node(&tmp, (void*)(&node[6])); //G��ΪE��������
    p = tree_insert_left(tmp, p);

    return 0;
}


int main()
{
  tree_t *root;
  make_tree(&root);

  tree_print(root, 0);
  printf("\n\n");

  printf("ǰ���������\n");
  tree_pre_order(root);
  printf("\n");
  tree_pre_order_norec(root);
  printf("\n\n");

  printf("�����������\n");
  tree_in_order_norec(root);
  printf("\n");
  tree_in_order(root);
  printf("\n\n");

  printf("�����������\n");
  tree_pos_order(root);
  printf("\n");
  tree_pos_order_norec(root);
  printf("\n\n");

  printf("�����������\n");
  tree_layer_order(root);
  printf("\n\n");
  return 0;
}

/*********************test code*******************************/
