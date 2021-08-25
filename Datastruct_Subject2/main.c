#include <stdio.h>

typedef struct {
	int row;  //행번호
	int col;   //열번호
	int value; //값
}element;

typedef struct ListNode {
	element data;
	struct ListNode *link;
}ListNode;

typedef struct {
	int rows;//행의 갯수
	int cols;//열의 개수
	ListNode *head;//연결리스트의 시작
	ListNode *tail;//연결리스트의 끝. 문제에 따라 사용할 건지는 본인이 선택
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
		fprintf(stderr, "메모리 할당 에러\n");
		exit(1);
	}

	if (a.row > plist->rows || a.col > plist->cols) {
		fprintf(stderr, "주어진 행 열 보다 큽니다.\n");
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

	init(&temp3, (plist1->rows > plist2->rows ? plist1->rows: plist2->rows), (plist1->cols > plist2->cols ? plist1->cols : plist2->cols));			//temp3을 초기화 할때 두개의 리스트 중 큰 행과 열을 초기 행열로 줌

	while (temp1 != NULL && temp2 != NULL)
	{
		if (temp1->data.col == temp2->data.col && temp1->data.row == temp2->data.row) //행, 열이 같을때 값을 더한다. col = 열 row = 행
		{

			temp3->data.value = temp1->data.value + temp2->data.value;		//temp3 데이터 밸류에 temp1, temp2 밸류값 더해서 넣기
			temp3->data.col = temp1->data.col;								//temp3 데이터 col(열)에 temp1 (temp2와 같음) 열 값 넣기
			temp3->data.row = temp1->data.row;								//temp3 데이터 row(열)에 temp1 (temp2와 같음) 행 값 넣기
			insert_node_last(&temp3, temp3->data);							//temp3에 새 노드 추가
			temp1 = temp1->link, temp2 = temp2->link;						//temp1, temp2 다음 노드로 이동
		}
		/*
		else if (temp1->data.row == temp2->data.row && temp1->data.col > temp2->data.col) //행은 같고 열이 다를때 1 ex 0행 1열, 0행 2열...
		{

		}

		else if (temp1->data.row == temp2->data.row && temp1->data.col < temp2->data.col) //행은 같고 열이 다를때 2
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

	//다음과 같은 방법으로 행렬 A를 입력하시오
	element x = { 0,0,2 };					//0행 0열에 2값을 가진 속성
	insert_node_last(&list1, x);			//마지막 노드에 

	element x2 = { 5,1,3 };
	insert_node_last(&list1, x2);

	element x3 = {4,2,4 };
	insert_node_last(&list1, x3); //여기 까지 list1 원소

	element x4 = { 0,3,5 };
	insert_node_last(&list2, x4);
	element x5 = { 3,4,6 };
	insert_node_last(&list2, x5); //여기까지 list2 원소

	
								  
	
								  //순서를 지켜서 입력
	print_matrix(&list1);
	print_matrix(&list2);
	//......그 다음일 수행


	add_sparse_matrix(&list1, &list2);

}