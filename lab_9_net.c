#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N 32

#define TRUE 1


typedef struct node {
 int id;
 char name[N]; //N should be defined as 32 at the beginning 
 struct node *next;
} list ;

list *head = NULL, *end = NULL;

void Insert (int id, char name[N]);
void Listing ();
void Remove (int key);
void Search (int wanted);


void Clearscreen () {
 // For Windows: 
 system("cls");
 // For Linux -->"clear"
}
void Wait () {
 char temp_data;
 printf ("Press Enter to continue!!!\n");
 temp_data = getchar ();
 temp_data = getchar ();
 Clearscreen ();
}

int main()
{

	int i;
    int select;
    char name[N];
    int id;
     
        
        
        while(1) {
		
        printf("-----------------------------------------------------------\n");
        printf("\t\t\t 1- Insert\n");
        printf("\t\t\t 2- Listing\n");
        printf("\t\t\t 3- Search\n");
        printf("\t\t\t 4- Remove\n");
        printf("\t\t\t 0- Exit\n");
        printf("-----------------------------------------------------------\n");	
        printf("\n Please Choose an option -->  ");
        scanf("%d", &select);
        switch (select)
        {
            case 1:
                printf("Enter the student Number: ");
                scanf("%d", &id);
                printf("Enter the student Name: ");
                scanf("%s", name);
                Insert(id, name );
                Wait ();
                break;
            case 2:
				Listing();
				Wait ();
                break;
            case 3:
				printf("Enter id number to search: ");
                scanf("%d", &id);
                search(id);
                Wait ();
                break;
            case 4:
                printf("Which do you want to delete ID? ");
                scanf("%d", &id);
                Remove(id);
                Wait ();
                break;
            case 0:
            	printf("\nFinish Programming! :)");
                exit(0);
                break;
                
            default:
        	printf("\nFALSE CHOOSE...\n");
        	Wait ();
        	break;
        
        }
        
		}	
		

}



void Insert(int id, char name[N] )
{
    
   	struct node * node = (struct node *) malloc(sizeof(struct node)); // struct alaný kadar bellekte yer açýyoruz.
    node->id = id;
    strcpy(node->name, name);
    node->next = NULL;
    
    if(head == NULL){
        head = node;
    }
    else{
        node->next = head;
        head = node;
    }
    
}

void search(int id)
{
    struct node * temp = head;
    while(temp != NULL){
        if(temp->id == id){
            printf("Student ID Number: %d\n", temp->id);
            printf("Student Name: %s\n", temp->name);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID number %d is not found !!!\n", id);
}

void Remove(int id)
{
    struct node * temp1 = head;
    struct node * temp2 = head; 
    while(temp1 != NULL){
        
        if(temp1->id==id){
            
            printf(" Student ID number %d Found !!!\n", id);
            
            if(temp1 == temp2){
                head = head->next;
                free(temp1);
            }
            else{
            
                temp2->next = temp1->next;
                free(temp1); 
            }         
            printf(" %d Student ID Successfully Deleted !!!\n", id);
            return;           
        }
        temp2 = temp1;
        temp1 = temp1->next;        
    }
    printf("Student with id number %d is not found !!!\n", id);
    
}

void Listing () {
	
	struct node * temp = head;
	printf("Names \t");
	printf("Numbers \n");
	printf("----------------------------------\n");
    while(temp != NULL){
    	
        printf(" %s \t", temp->name);
        printf(" %d \n", temp->id);       
        temp = temp->next;
	
}
}

