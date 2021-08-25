#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;
	int eng;
	int math;
}student;

typedef student element;

typedef struct ListNode {
	element data; //¶Ç´Â student data;
	struct ListNode *link;
}ListNode;

ListNode *create_node(int id, int eng, int math)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	new_node->data.eng = eng;
	new_node->data.math = math;
	new_node->data.id = id;

	return (new_node);
}

void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node;
	}
}

void ascending_insert_node(ListNode **phead, ListNode *new_node) {

	ListNode *temp = *phead;
	ListNode *p = *phead;
	int i;

	if (*phead != NULL) {
		temp = temp->link;
	}

	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (temp == NULL) {
		if ((*phead)->data.id > new_node->data.id) {
			new_node->link = *phead;
			*phead = new_node;
		}
		else {
			new_node->link = p->link;
			p->link = new_node;
		}
	}
	else {
		int cnt = 0;
		while (p) {
			if (p->data.id > new_node->data.id) {
				break;
			}
			p = p->link;
			cnt++;
		}
		p = *phead;

		for (i = 0; i < cnt - 1; i++) {
			p = p->link;
		}

		if (cnt == 0)
			p = NULL;

		insert_node(phead, p, new_node);

	}
}

void display(ListNode *phead) {
	ListNode *p = phead;

	while (p) {
		printf("%d  %d  %d\n", p->data.id, p->data.eng, p->data.math);
		p = p->link;
	}
}

int main() {
	ListNode *p[5];
	ListNode *head = NULL;
	int i;

	p[0] = create_node(124, 78, 55);
	p[1] = create_node(135, 65, 70);
	p[2] = create_node(147, 80, 85);
	p[3] = create_node(115, 95, 90);
	p[4] = create_node(144, 90, 80);


	for (i = 0; i < 5; i++) {
		ascending_insert_node(&head, p[i]);
	}

	display(head);

	for (i = 0; i < 5; i++) {
		free(p[i]);
	}

	return 0;
}