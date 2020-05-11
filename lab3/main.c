#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Node{
	struct Node* next;
	struct Node* prev;
	char str[100];
};

struct Node* EOL;
int isEmpty=1;
void showList(struct Node* begin)
{
	struct Node* current=begin;
	while(current!=EOL)
	{
		printf("%s\n",current->str);
		current=current->next;
	}
	
}

void AddAsBegin(struct Node* newElement,struct Node** begin)
{
	if(isEmpty)
	{
		strcpy((*begin)->str,newElement->str);
		free(newElement);
		isEmpty=0;
		return;
	}
	newElement->next=(*begin);
	newElement->prev=(*begin)->prev;
	(*begin)->prev=newElement;
	(*begin)=newElement;
}

void AddAtEnd(struct Node* newElement,struct Node** begin)
{
	if(isEmpty)
	{
		strcpy((*begin)->str,newElement->str);
		free(newElement);
		isEmpty=0;
		return;
	}
	struct Node* current=(*begin);

	while(current->next!=EOL)
	{
		current=current->next;
	}
	newElement->next=current->next;
	newElement->prev=current;
	current->next=newElement;
	
}

void FlushList(struct Node** begin)
{
	if(!isEmpty)
	{	
		(*begin)->str[0]='\0';
		struct Node* current=(*begin)->next;
		(*begin)->next=EOL;
		struct Node* forDeleting=current;
		while(current!=EOL)
		{
			current=current->next;
			free(forDeleting);
			forDeleting=current;
		}
		isEmpty=1;
	}	
}

void DeleteByIndex(struct Node** begin,int index)
{
	struct Node* current=(*begin);
	int i=0;
	if(index==0 && (*begin)->next==EOL)
	{
		(*begin)->str[0]='\0';
		return;
	}
	while(i<index)
	{
		if(current==EOL)
		{
			printf("Element with that index not found");
			return;
		}
		i++;
		current=current->next;
	}
	if(index==0)
	{
		*begin=current->next;
	}else
	{
		begin=current->prev;
	}
	if(current->next!=EOL)
	{
		current->next->prev=current->prev;
	}
	if(current->prev!=EOL)
	{
		current->prev->next=current->next;
	}
	free(current);
}
struct Node* GetElement()
{
	struct Node* newElement=malloc(sizeof(struct Node));
	printf("Enter string:");
	scanf("%s",newElement->str);
	return newElement;
}

void ShowMenu(struct Node** begin){
	int i=11;
	int j=0;
	while (1)
	{
		printf("1) Add new string at being\n");
		printf("2) Add new string at the end\n");
		printf("3) Delete element by index\n");
		printf("4) Flush list\n");
		printf("5) Show list\n");
		printf("6) Exit\n");
		scanf("%i",&i);
		switch(i)
		{
			case 1: 
			{
				struct Node* newElement = GetElement();
				AddAsBegin(newElement,begin);
				break;
			}	
			case 2: 
			{
				struct Node* newElement = GetElement();
				AddAtEnd(newElement,begin);
				break;
			}
			case 3: 
			{
				printf("Enter index:");
				scanf("%d",&j);
				DeleteByIndex(begin,j);
				break;
			}
			case 4: 
			{
				FlushList(begin);
				break;
			}
			case 5: 
			{
				showList((*begin));
				break;
			}
			case 6: 
			{
				return;
			}		
		}
	}
	
}

int main(){

	struct Node* Begin;
	int i;
	int j;
	
	EOL = malloc(sizeof(struct Node));
	Begin = malloc(sizeof(struct Node));
	EOL->next=EOL;
	EOL->prev=EOL;
	EOL->str[0]='\0';
	Begin->next=EOL;
	Begin->prev=EOL;
	isEmpty=1;
	ShowMenu(&Begin);	
	
	return 0;
}
