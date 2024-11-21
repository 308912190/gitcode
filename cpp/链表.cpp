#include <iostream>
using namespace std;

class node {
public:
	int data;
	node* next;
};
class list {
public:
	node* head;
	int size;
};
list* initlist()
{
	list* l = new list;
	l->size = 0;
	l->head = new node;
	l->head->data = NULL;
	l->head->next = NULL;
	return l;
}
void listinsert(list* l, int pos, int data)
{
	if (l == NULL)
	{
		pos = 0;
	}
	node* newnode = new node;
	newnode->next = NULL;
	newnode->data = data;
	node* pos_node = l->head;
	for (int i = 0; i < pos; i++)
	{
		pos_node = pos_node->next;
	}
	newnode->next = pos_node->next;
	pos_node->next = newnode;
	l->size++;
}
void listremove(list* l, int pos)
{
	if(l == NULL)
	{
		return;
	}
	node* pos_node = l->head;
	for (int i = 0; i < pos; i++)
	{
		pos_node = pos_node->next;
	}
	pos_node->next = pos_node->next->next;
	l->size--;
}
void listprint(list* l)
{
	if (l->size == 0)
	{
		cout << "¿ÕÁ´±í" << endl;
		return;
	}
	node* pcurrent = l->head->next;
	while (pcurrent != NULL)
	{
		cout << pcurrent->data;
		pcurrent = pcurrent->next;
	}
}
int main()
{
	list* l = initlist();
	for (int i = 0; i < 10; i++)
	{
		listinsert(l, i, i);
	}
	listprint(l);
	cout << endl;
	listremove(l, 5);
	listprint(l);
}