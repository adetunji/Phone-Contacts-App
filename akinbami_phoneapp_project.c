#include <stdio.h>
#include <string.h>

// Adetunji Akinbami

// Define the node structure
typedef struct node
{
    char fname[20];
    char lname[20];
    char tel[11];
    struct node *next;
} Node, *NodePtr;

// Define a struct for the linked list
typedef struct
{
    NodePtr first, np, last;
} LinkedList;

// Add to Linked List
NodePtr addContact(char _fname[], char _lname[], char _tel[])
{
    NodePtr np= (NodePtr) malloc (sizeof(Node));
    strcpy(np->fname, _fname);
    strcpy(np->lname, _lname);
    strcpy(np->tel, _tel);
    np->next= NULL;
    return np;
}

// Print Linked List
void printList(NodePtr np)
{
    while(np!=NULL)   // as long as there's a node
    {
        printf("\n First Name: %s \n Last Name: %s \n Phone Number: %s \n", np->fname, np->lname, np->tel);
        np=np->next;    // go on to the next node
    }
}

// Retrieve from Linked List
void searchContact(NodePtr head, char name[])
{
    while (head != NULL)
    {
        if (_stricmp(head->fname ,name)== 0 || _stricmp(head->lname,name)== 0)
        {
            printf("Contact found");
            printf("\n First Name: %s \n Last Name: %s \n Phone Number: %s \n", head->fname, head->lname, head->tel);
            return;
        }
        else
            head = head->next;
    }
    printf("Contact not found\n");
}

// Delete Contact
void delContact(LinkedList *ll, char name[])
{
    NodePtr head = (*ll).first;
     if (_stricmp(head->fname, name) == 0 || _stricmp(head->lname, name)==0) {
        NodePtr temp = head;
        (*ll).first = (*ll).first->next;
        free(temp);
        printf("Contact has been deleted.\n");
        return;
    }
    NodePtr curr = head->next;
    NodePtr prev = head;
    while (curr != NULL && prev != NULL) {
        if (_stricmp(name, curr->fname) == 0 || _stricmp(name, curr->lname) == 0) {
            NodePtr temp = curr;
            prev->next = curr->next;
            free(temp);
            printf("Contact has been deleted.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }
	if (_stricmp(name, (*ll).first->fname) != 0 || _stricmp(name, (*ll).first->lname) != 0){
			printf("Contact does not exist.\n");
	}
    return;
}
// Switch the lists
NodePtr switchList( NodePtr l1, NodePtr l2 )
{
    l1->next = l2->next;
    l2->next = l1;
    return l2;
}
// Sort the lists using Non-recursive Bubble sort.
NodePtr sortContacts( NodePtr head )
{
    NodePtr p, q,top;
    int changed = 1;


    if( (top = (NodePtr)malloc(sizeof(Node))) == NULL)
    {
        fprintf( stderr, "Error in Memory Allocation.\n" );
        exit(1);
    }

    top->next = head;
    if( head != NULL && head->next != NULL )
    {

        while( changed )
        {
            changed = 0;
            q = top;
            p = top->next;
            while( p->next != NULL )
            {
                // Arrange the contacts in ascending order by first name.
                if( strcmp(p->fname, p->next->fname) > 0 )
                {
                    q->next = switchList( p, p->next );
                    changed = 1;
                }
                q = p;
                if( p->next != NULL )
                    p = p->next;
            }
        }
    }
    p = top->next;
    free( top );
    return p;
}
// Save contacts to file.
void saveContacts(NodePtr head)
{
    FILE *fout;
    fout = fopen("contacts.txt", "a+");
    if(fout == NULL)
    {
        printf("File doesn't exist.");
    }
   while(head != NULL)
    {
        fprintf(fout,"%s \n%s \n%s \n", head->fname, head->lname, head->tel);
        head = head->next;
    }
   //printf("NULL contacts in List. \n");

}

// Load Contacts from file.
void loadContacts(LinkedList list, FILE *fin)
{

    list.first = NULL;
    if(fin == NULL)
    {
        fprintf(stderr, "File doesn't exist");
		exit(0);
    }
    else
    {
        while(!feof(fin))
        {
            char fname[20];
            char lname[20];
            char tel[11];
            fscanf(fin,"%s \n%s \n%s \n", fname, lname, tel);


            list.np = addContact(fname,lname, tel);
            if(list.first==NULL)
                list.first=list.np;
            else
                list.last->next = list.np;
            list.last = list.np;

        }
    }
}

int main(int argc, char *argv[])
{
    char name[20];
    char fname[20];
    char lname[20];
    char tel[11];
    int choice;

    LinkedList ll;
    NodePtr node, sortedNode;
    sortedNode = NULL;
    node = NULL;
    ll.first = NULL;
    FILE *in = fopen("contacts.txt","r");



    do
    {
        printf("\n1. Enter 1 to add a contact: ");
        printf("\n2. Enter 2 to retrieve contact: ");
        printf("\n3. Enter 3 to delete a contact: ");
        printf("\n4. Enter 4 to load contacts: ");
        printf("\n5. Enter 5 to save contacts: ");
        printf("\n6. Enter 6 to sort the contacts: ");
        printf("\n7. Enter 7 to print the contacts: ");
        printf("\n8. Enter 8 to quit: ");
        scanf("%d", &choice);

        switch(choice)
        {


        case 1:

            printf("\nPlease add a First Name: ");
            scanf("%s", &fname);

            printf("\nPlease add a Last Name: ");
            scanf("%s", &lname);

            printf("\nPlease add a Tel Number: ");
            scanf("%s", &tel);

            ll.np = addContact(fname,lname,tel);
            if(ll.first==NULL)
                ll.first=ll.np;
            else
                ll.last->next = ll.np;
            ll.last = ll.np;
            printf("Contact Added.\n");
            break;

        case 2:
            printf("\nPlease enter the first or last name to be searched: ");
            scanf("%s", &name);
            searchContact(ll.first, name);

            break;

        case 3:
            printf("\nPlease enter the first or last name to be deleted: ");
            scanf("%s", &name);
            //deleteContact(ll.first, name);
            delContact(&ll, name);

            break;
        case 4:
            if(in == NULL)
            {
                perror("File doesn't exist.");
            }
            while(!feof(in))
            {

                fscanf(in,"%s \n%s \n%s \n", fname, lname, tel);


                ll.np = addContact(fname,lname, tel);
                if(ll.first==NULL)
                    ll.first=ll.np;
                else
                    ll.last->next = ll.np;
                ll.last = ll.np;

            }

            loadContacts(ll, in );
            printList(ll.first);
            printf("Contacts have been loaded.\n");
            break;
        case 5:
            if(ll.first == NULL)
                printf("NULL contacts in List. Nothing to save. \n");
            else {saveContacts(ll.first);
            printf("Contacts have been saved.\n");
            }
            break;

        case 6:
            node = ll.first;
            sortedNode = sortContacts(node);
            printList(sortedNode);
            printf("Contact List has been sorted");
            break;
        case 7:
            printList(ll.first);
        }

    }
    while(choice != 8);

   if(ll.first == NULL){
       printf("You do not have any saved contacts.");
   }
   else{

     printf("Here are your contacts:\n");
    printList(ll.first);
   }
}

// print the whole list starting from first








