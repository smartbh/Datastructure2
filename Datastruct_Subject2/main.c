#include <stdio.h>

typedef struct {
	int row;  //���ȣ
	int col;   //����ȣ
	int value; //��
}element;

typedef struct ListNode {
	element data;
	struct ListNode *link;
}ListNode;

typedef struct {
	int rows;//���� ����
	int cols;//���� ����
	ListNode *head;//���Ḯ��Ʈ�� ����
	ListNode *tail;//���Ḯ��Ʈ�� ��. ������ ���� ����� ������ ������ ����
}ListHeader;

void init(ListHeader *plist, int r, int c)
{
	plist->rows = r;
	plist->cols = c;
	plist->head = NULL;
	plist->tail = NULL;
}
void print_matrix(ListHeader *plist)
{
	ListNode *p = plist->head;
	while (p != NULL) {
		printf("%d %d %d\n", p->data.row, p->data.col, p->data.value);
		p = p->link;
	}
}

void insert_node_last(ListHeader *plist, element a)
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));

	if (temp == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}

	if (a.row > plist->rows || a.col > plist->cols) {
		fprintf(stderr, "�־��� �� �� ���� Ů�ϴ�.\n");
		exit(1);
	}

	temp->data = a;
	temp->link = NULL;

	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
}

ListNode *add_sparse_matrix(ListHeader *plist1, ListHeader *plist2)
{
	ListNode *temp1 = (ListNode *)malloc(sizeof(ListNode));
	ListNode *temp2 = (ListNode *)malloc(sizeof(ListNode));
	ListNode *temp3 = (ListNode *)malloc(sizeof(ListNode));

	temp1 = plist1, temp2 = plist2;

	init(&temp3, (plist1->rows > plist2->rows ? plist1->rows: plist2->rows), (plist1->cols > plist2->cols ? plist1->cols : plist2->cols));			//temp3�� �ʱ�ȭ �Ҷ� �ΰ��� ����Ʈ �� ū ��� ���� �ʱ� �࿭�� ��

	while (temp1 != NULL && temp2 != NULL)
	{
		if (temp1->data.col == temp2->data.col && temp1->data.row == temp2->data.row) //��, ���� ������ ���� ���Ѵ�. col = �� row = ��
		{

			temp3->data.value = temp1->data.value + temp2->data.value;		//temp3 ������ ����� temp1, temp2 ����� ���ؼ� �ֱ�
			temp3->data.col = temp1->data.col;								//temp3 ������ col(��)�� temp1 (temp2�� ����) �� �� �ֱ�
			temp3->data.row = temp1->data.row;								//temp3 ������ row(��)�� temp1 (temp2�� ����) �� �� �ֱ�
			insert_node_last(&temp3, temp3->data);							//temp3�� �� ��� �߰�
			temp1 = temp1->link, temp2 = temp2->link;						//temp1, temp2 ���� ���� �̵�
		}
		/*
		else if (temp1->data.row == temp2->data.row && temp1->data.col > temp2->data.col) //���� ���� ���� �ٸ��� 1 ex 0�� 1��, 0�� 2��...
		{

		}

		else if (temp1->data.row == temp2->data.row && temp1->data.col < temp2->data.col) //���� ���� ���� �ٸ��� 2
		{

		}
		*/
		temp1 = temp1->link, temp2 = temp2->link;
	}
	return temp3;
}

void main()
{
	ListHeader list1;
	ListHeader list2;

	init(&list1, 6, 6);
	init(&list2, 4, 4);

	//������ ���� ������� ��� A�� �Է��Ͻÿ�
	element x = { 0,0,2 };					//0�� 0���� 2���� ���� �Ӽ�
	insert_node_last(&list1, x);			//������ ��忡 

	element x2 = { 5,1,3 };
	insert_node_last(&list1, x2);

	element x3 = {4,2,4 };
	insert_node_last(&list1, x3); //���� ���� list1 ����

	element x4 = { 0,3,5 };
	insert_node_last(&list2, x4);
	element x5 = { 3,4,6 };
	insert_node_last(&list2, x5); //������� list2 ����

	
								  
	
								  //������ ���Ѽ� �Է�
	print_matrix(&list1);
	print_matrix(&list2);
	//......�� ������ ����


	add_sparse_matrix(&list1, &list2);

}