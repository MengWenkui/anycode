#include <stdio.h>
#include <stdlib.h>

typedef struct mem_node {
	int start;
	int num;
	struct mem_node* next;
}mem_node;

typedef struct free_mem {
	mem_node* first;
}free_mem;

free_mem* mem_init()
{
	free_mem* mem = (free_mem*)malloc(sizeof(free_mem));
	if(mem == NULL)
		return NULL;
	mem->first = (mem_node*)malloc(sizeof(mem_node));
	if(mem->first == NULL)
		return NULL;

	mem->first->start = 1;
	mem->first->num = 100;
	mem->first->next = NULL;
	
	return mem;
}

int mem_alloc(free_mem* mem, int n) 
{
	mem_node* pre = mem->first;
	mem_node* cur = mem->first;
	int start = -1;
	
	while(cur != NULL) {
		if(cur->num < n) {
			pre = cur;
			cur = cur->next;
		}
		else {
			start = cur->start;
			if(cur->num > n) {
				cur->start += n;
				cur->num -= n;
			}
			else {
				if(cur == mem->first) {
					mem->first = cur->next;
				}
				else {
					pre->next = cur->next;
				}
				free(cur);
			}
			return start;
		}
	}
	return start;
}

mem_node* get_mem_node(int start, int n)
{
	mem_node* node = (mem_node*)malloc(sizeof(mem_node));
	if(node == NULL) 
		return NULL;
	node->start = start;
	node->num = n;
	node->next = NULL;
	
	return node;
}

void mem_free(free_mem* mem, int start, int n)
{
	mem_node* pre = mem->first;
	mem_node* cur = mem->first;
	
	/* 链表为空 */
	if(mem->first == NULL) {
		mem_node* node = get_mem_node(start, n);
		mem->first = node;
		return;
	}
	
	while(cur != NULL && start > cur->start) {
		pre = cur;
		cur = cur->next;
	}
	
	/* 应该加到链表末尾 */
	if(cur == NULL) {
		if(pre->start + n == start) {
			pre->num += n;
		}
		else {
			mem_node* node = get_mem_node(start, n);
			pre->next = node;
		}
		return;
	}
	
	/* 只有一个元素 */
	if(pre == cur) {
		if(start + n == cur->start) {
			cur->start = start;
			cur->num += n;
		}
		else {
			mem_node* node = get_mem_node(start, n);
			node->next = cur;
			mem->first = node;
		}
		return;
	}
	
	/* 插到pre与next之间 */
	if(pre->start + pre->num == start &&
		start + n == cur->start) {
		pre->num += n + cur->num;
		pre->next = cur->next;
		free(cur);	
	}
	else if(pre->start + pre->num == start) {
		pre->num += n;
	}
	else if(start + n == cur->start) {
		cur->start = start;
		cur->num += n;
	}
	else {
		mem_node* node = get_mem_node(start, n);
		node->next = cur;
		pre->next = node;
	}
	
	return;
} 

int main()
{
	int op;
	int start, n;
	
	free_mem* mem = mem_init();
	
	/* alloc 5 */
	int res = mem_alloc(mem, 5);
	printf("%d\n", res);
	
	res = mem_alloc(mem, 15);
	printf("%d\n", res);
	
	res = mem_alloc(mem, 10);
	printf("%d\n", res);
	
	mem_free(mem, 6, 15);
	
	res = mem_alloc(mem, 5);
	printf("%d\n", res);
	
	res = mem_alloc(mem, 10);
	printf("%d\n", res);
	
	res = mem_alloc(mem, 100);
	printf("%d\n", res);
	
	res = mem_alloc(mem, 70);
	printf("%d\n", res);
	
	mem_free(mem, 1, 100);
	
	res = mem_alloc(mem, 10);
	printf("%d\n", res);
	
	res = mem_alloc(mem, 10);
	printf("%d\n", res);
	
	res = mem_alloc(mem, 10);
	printf("%d\n", res);
	
	mem_free(mem, 1, 10);
	
	res = mem_alloc(mem,30);
	printf("%d\n", res);
	
	mem_free(mem, 11, 10);
	mem_free(mem, 21, 10);
	
	res = mem_alloc(mem,30);
	printf("%d\n", res);
	
	
	return 0;
}

