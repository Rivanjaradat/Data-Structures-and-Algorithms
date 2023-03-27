
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
struct tree_node
{
    char name[50]; // name of the medicine
    char active[50]; // active ingredient of the medicine
    char category[50]; // category of the medicine
    struct IndicationList*indcation ; // pointer to a list of indications for the medicine
    char expiry_date[50]; // expiry date of the medicine
    int count; // count of the medicine
    char company[50]; // company of the medicine
    struct tree_node* left; // pointer to left subtree
    struct tree_node* right; // pointer to right subtree
};

struct IndicationList
{
    char indication[1000]; // indication of the medicine
    struct IndicationList* next; // pointer to the next indication in the list
};

struct hashtable_item
{
    char key[4];
    char name[50];
    char active[50];
    char category[50];
    char indication[100];
    char expiry_date[50];
    int count;
    char company[50];

    struct hashtable_item* next;
};
struct hashtable
{
    int size;
    int countelement;
    int countcollision;
    int flag;

    struct hashtable_item** items;
};
//functions prototype
struct tree_node* insertNode(struct tree_node* T, char name[50], char active[50], char category[50], struct IndicationList* head, char expiry_date[50], int count, char company[50]);
struct tree_node* find_min( struct tree_node* T);
struct tree_node* deletenode (struct tree_node* T, char name[50]);
struct tree_node* deleteCompany(struct tree_node* T, char company[50]);
struct tree_node* find( char x[50],struct tree_node* T);
struct tree_node* findcatagory(struct tree_node*root, char category[50]);

struct hashtable* delete1(struct hashtable* table, char name [50]);
struct hashtable* create_table(int size) ;
int hash_function(struct hashtable* table,char key[3], int new_size );
struct hashtable* ht_insert(struct hashtable* table, char name[50], char active[50], char category[50], char indication[100], char expiry_date[50], int count, char company[50]);
struct hashtable* ht_resize_double(struct hashtable* table);
char* getkey(char name[50]);
unsigned int hash_function1(char *key, int table_size);
float LoadFactor (int counterr, int tableSize);
unsigned int hash_function2(char *key, int table_size);
struct hashtable_item* ht_searchdouble(struct hashtable* table, char name[50]);

int main()
{
    struct tree_node*root=NULL;
    phase1(root);
    return 0;
}
void choice1()
{
    printf("1-	Read File and save data in Binary search tree \n");
    printf("2-	Insert a new medicine\n");
    printf("3-	search &update\n");
    printf("4-	List the medicines in the tree in alphabetical order with their associated information\n");
    printf("5-  List all medicines of same category\n");
    printf("6-  List all medicines that treat a specific disease\n");
    printf("7-  Delete all medicines from a specific company\n");
    printf("8- Delete a medicine from the tree. \n");
    printf("9-	Save all information to a file\n");
    printf ("10.Print hashed tables\n");
    printf("11.Print out table size and the load factor.\n");
    printf("12. Print out the used hash functions.  \n");
    printf("13. insert.  \n");
    printf("14.Search for a specific medicine and print the number of collisions to reach the medicine.\n");
    printf ("15.Delete a specific record\n");
    printf("16.Save the data back to the file Pharmacy.txt \n");
    printf("17-	Exit\n");
}
void phase1(struct tree_node*root )
{
    char name[50] ;
    char active[50] ;
    char category[50];
    char indication[1000];
    char expiry_date[50];
    int count ;
    char key[4];
    char company[50] ;
    int flag1=0;
    int flag2=0;
    int x;
    int i=0;
    FILE*IN;
    root = NULL;
    struct IndicationList* head;
    struct tree_node*search;
    FILE*out;
    int Size=arraySize();
    struct hashtable* table=create_table(Size) ;
    struct hashtable_item* result;

    printf(" please choose one choice:\n");


    while (true)
    {
        choice1();
        scanf("%d",&x);
        printf("--------------------------------------\n");

        switch (x)
        {

        case 1:

            readFile1(&root);
            flag1=1;
            printf("-----------------------------------\n");
            break;
        case 2:
            head = NULL;

            printf(" enter the name \n ");
            fflush(stdin);
            scanf("%[^\n]s",name);
            fflush(stdin);
            printf(" enter the active\n");
            fflush(stdin);
            scanf("%[^\n]s",active);

            printf(" enter the catagory\n");
            fflush(stdin);
            scanf("%[^\n]s",category);

            printf(" enter the indication (or enter 'done' to stop)\n");
            fflush(stdin);
            scanf("%[^\n]s",indication);

            while (strcmp(indication, "done") != 0)
            {
                struct IndicationList* new_node = (struct IndicationList*)malloc(sizeof(struct IndicationList));
                if (new_node == NULL)
                {
                    printf("Error: Memory allocation failed\n");
                    exit(1);
                }
                strcpy(new_node->indication, indication);
                new_node->next = head;
                head = new_node;

                printf(" enter the indication (or enter 'done' to stop)\n");
                fflush(stdin);
                scanf("%[^\n]s",indication);
            }

            printf(" enter the expiry date\n");
            fflush(stdin);
            scanf("%[^\n]s",expiry_date);

            printf(" enter the count\n");
            fflush(stdin);
            scanf("%d",&count);

            printf(" enter the company name\n");
            fflush(stdin);
            scanf("%[^\n]s",company);

            root = insertNode(root, name, active, category, head, expiry_date, count, company);

            printf("-----------------------------------\n");
            break;

        case 3:

            searchAndUpdate(root);


            break;
        case 4:

            printData(root);

            printf("-----------------------------------\n");
            break;

        case 5:

            printf(" enter the catagory\n");
            fflush(stdin);
            scanf("%[^\n]s", category);

            listMedsByCategory(root,category);



            break;
            int dis;
        case 6:

            printf(" enter the indication\n");
            fflush(stdin);
            scanf("%[^\n]s", indication);

            listdis(root,  indication);


            printf("-----------------------------------\n");

            break;
        case 7:

            printf("Enter the company of medicine to delete\n");
            fflush(stdin);
            scanf("%[^\n]s",& company);

            root=deleteCompany(root, company);

            break;
        case 8:

            printf("Enter the name of medicine to delete\n");
            fflush(stdin);
            scanf("%[^\n]s", name);

            root=deletenode (root, name);
            printf("-----------------------------------\n");

            break;
        case 9:
            out = fopen("Pharmacy.txt", "w");
            if (out == NULL)
            {
                printf("Error opening file!\n");
                return;
            }
            writeout(out,root);
            fclose(out);
            printf("-----------------------------------\n");
            break;
            double m;
        case 10:
            IN = fopen("Pharmacy.txt", "r");
            if (IN == NULL)
            {
                printf("THE FILE NOT FOUND");
                return;
            }
            else
            {
                readFilehash(table,IN);
            }
            fclose(IN);

            print_table(table);
            printf("-----------------------------------\n");
            break;
        case 11:
            m  =   LoadFactor (table->countelement,table->size);

            printf("The load factor = %f\n",m);
            printf("The table size :%d\n",table->size);
            break;
        case 12:

            printf("hi(key) = [h(key) + i*hp(key)] mod tableSize  \n");
            printf("-----------------------------\n");
            break;
        case 13:

            printf(" enter the name \n ");
            fflush(stdin);
            scanf("%[^\n]s",&name);
            fflush(stdin);
            printf(" enter the active\n");
            fflush(stdin);
            scanf("%[^\n]s",&active);

            printf(" enter the catagory\n");
            fflush(stdin);
            scanf("%[^\n]s",&category);

            printf(" enter the indication \n");
            fflush(stdin);
            scanf("%[^\n]s",&indication);


            printf(" enter the expiry date\n");
            fflush(stdin);
            scanf("%[^\n]s",&expiry_date);

            printf(" enter the count\n");
            fflush(stdin);
            scanf("%d",&count);

            printf(" enter the company name\n");
            fflush(stdin);
            scanf("%[^\n]s",&company);

            table=       ht_insert(table,name,active,category,indication,expiry_date,count,company);



            print_table(table);
            printf("-----------------------------------\n");

            break;
        case 14:

            printf("\nWrite The Name  : ");
            fflush(stdin);
            scanf("%[^\n]s",&name);

            printf("-----------------------------\n");

            result=     ht_searchdouble(table, name);

            printf("-----------------------------------\n");
            break;
        case 15:
            printf("\nWrite The Name : ");
            fflush(stdin);
            scanf("%[^\n]s",&name);

            table= delete1( table,name);
            print_table(table);
            printf("-----------------------------------\n");
            break;
        case 16:
            out = fopen("Pharmacy.txt", "w");
            if (out == NULL)
            {
                printf("Error opening file!\n");
                return;
            }

            else
            {
                WriteToFile(out,table);
            }
            fclose(out);
            printf("-----------------------------------\n");
            break;
        case 17:
            exit(0);
            break;
        default:
            printf(" just  number from 1 to 17\n");

        }
    }
}
//read data from file and save it in bst
void readFile1(struct tree_node** root)
{
    //define variables
    FILE* IN;
    char line[1000];
    char* token;
    char name[50];
    char active[50];
    char category[50];
    char expiry_date[50];
    int count;
    char company[50];
    char indication[1000];
    struct IndicationList* head = NULL;
    struct IndicationList* current = NULL;
//open file
    IN = fopen("Meds.txt", "r");
    //check if file found or not
    if (IN == NULL)
    {
        printf("THE FILE NOT FOUND");
        return;
    }
//spilt data in file
    while (fgets(line, 1000, IN) != NULL)
    {
        token = strtok(line, ":");
        if (token != NULL)
        {
            strcpy(name, token);
        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            strcpy(active, token);
        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            strcpy(category, token);
        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            strcpy(indication, token);
        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            strcpy(expiry_date, token);
        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            count = atoi(token);
        }

        token = strtok(NULL, "\n");
        if (token != NULL)
        {
            strcpy(company, token);
        }

        // Split indication string into a list of indications
        token = strtok(indication, ",");
        while (token != NULL)
        {
            struct IndicationList* newNode = (struct IndicationList*)malloc(sizeof(struct IndicationList));
            strcpy(newNode->indication, token);
            newNode->next = NULL;

            if (head == NULL)
            {
                head = newNode;
                current = head;
            }
            else
            {
                current->next = newNode;
                current = newNode;
            }

            token = strtok(NULL, ",");
        }
//insert data in tree
        *root = insertNode(*root, name, active, category, head, expiry_date, count, company);
        head = NULL;
    }
    //close the file
    fclose(IN);
    // Free memory allocated for indications list
    struct IndicationList* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}


//function to insert a node in tree
struct tree_node* insertNode(struct tree_node* T, char name[50], char active[50], char category[50], struct IndicationList* head, char expiry_date[50], int count, char company[50])
{
    if (T == NULL)
    {
        T = (struct tree_node*)malloc(sizeof(struct tree_node));
        strcpy(T->name, name);
        strcpy(T->active, active);
        strcpy(T->category, category);
        T->indcation = NULL;
        struct IndicationList* current = head;
        while (current != NULL)
        {
// create new indication node and copy data
            struct IndicationList* newNode = (struct IndicationList*)malloc(sizeof(struct IndicationList));
            strcpy(newNode->indication, current->indication);
            newNode->next = T->indcation;
            T->indcation = newNode;
            current = current->next;
        }
        strcpy(T->expiry_date, expiry_date);
        T->count = count;
        strcpy(T->company, company);
        T->left = NULL;
        T->right = NULL;
    }
    else
    {
        int comp = strcmp(name, T->name);
        if (comp == 0)
        {
            printf("Error: Name already exists in the tree.\n");
            return T;
        }
        else if (comp < 0)
        {
            T->left = insertNode(T->left, name, active, category, head, expiry_date, count, company);
        }
        else
        {
            T->right = insertNode(T->right, name, active, category, head, expiry_date, count, company);
        }
    }
    return T;
}
//print data pre order
void printData(struct tree_node* root)
{
    // if the tree not empty
    if (root != NULL)
    {
        //print data in root
        printf("Name: %s\n", root->name);
        printf("Active: %s\n", root->active);
        printf("Category: %s\n", root->category);
        printf("Indications: ");
        struct IndicationList* current = root->indcation;
        while (current != NULL)
        {
            printf("%s\t", current->indication);
            current = current->next;
        }
        printf("\nExpiry Date: %s\n", root->expiry_date);
        printf("Count: %d\n", root->count);
        printf("Company: %s\n\n", root->company);

        // print data in left subtree
        printData(root->left);
        // print data in right subtree
        printData(root->right);
    }
}

//List all medicines of same category
void listMedsByCategory(struct tree_node* root, char category[50])
{
    int found = 0;
    // if the tree not empty
    if (root != NULL)
    {
        // check if the value in the tree
        if (strcmp(category, root->category) == 0)
        {


            //print the data for this node
            printf("Name: %s\n", root->name);
            printf("Active: %s\n", root->active);
            printf("Category: %s\n", root->category);
            printf("Indications: ");
            struct IndicationList* current = root->indcation;
            while (current != NULL)
            {
                printf("%s, ", current->indication);
                current = current->next;
            }
            printf("\nExpiry Date: %s\n", root->expiry_date);
            printf("Count: %d\n", root->count);
            printf("Company: %s\n\n", root->company);
        }

        // check in  the left
        listMedsByCategory(root->left, category);
        //check in the write
        listMedsByCategory(root->right, category);
    }

}

//List all medicines that treat a specific disease
//in oreder
void listdis(struct tree_node* root, char dis[50])
{
    int found=0;
    // if tree not empty
    if (root != NULL)
    {
        listdis(root->left, dis);
        struct IndicationList* current = root->indcation;
        while (current != NULL)
        {
            if (strcmp(dis, current->indication) == 0)
            {
                found=1;
                printf("Name: %s\n", root->name);
                printf("Active: %s\n", root->active);
                printf("Category: %s\n", root->category);
                printf("Indications: ");
                struct IndicationList* current = root->indcation;
                while (current != NULL)
                {
                    printf("%s, ", current->indication);
                    current = current->next;
                }
                printf("\nExpiry Date: %s\n", root->expiry_date);
                printf("Count: %d\n", root->count);
                printf("Company: %s\n\n", root->company);
                break;
            }
            current = current->next;
        }
        listdis(root->right, dis);
    }


}


// function to print in file
void writeout(FILE*out, struct tree_node* T)
{
    if (T != NULL)
    {
        struct IndicationList* current = T->indcation;
        char indications[1000] = ""; // string to store all indications for a given medicine
        while (current != NULL)
        {
            strcat(indications, current->indication);
            strcat(indications, ",");
            current = current->next;
        }
        // remove the last comma
        indications[strlen(indications) - 1] = '\0';
        fprintf(out, "%s:%s:%s:%s:%s:%d:%s\n", T->name, T->active, T->category, indications, T->expiry_date, T->count, T->company);
        writeout(out, T->left);
        writeout(out, T->right);
    }
}


//Delete a medicine from the tree
struct tree_node* deletenode (struct tree_node* root, char x[50])
{
    // If the tree is empty or the node is not found
    if (root == NULL)
    {
        return root;
    }

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcmp(x, root->name) < 0)
    {
        root->left = deletenode(root->left, x);
    }
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcmp(x, root->name) > 0)
    {
        root->right = deletenode(root->right, x);
    }
    // If key is same as root's key, then this is the node
    // to be deleted
    else
    {
        // Node with only one child or no child
        if (root->left == NULL)
        {
            struct tree_node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct tree_node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct tree_node* temp = find_min(root->right);

        // Copy the inorder successor's content to this node
        strcpy(root->name, temp->name);

        // Delete the inorder successor
        root->right = deletenode(root->right, temp->name);
    }

    return root;
}

struct tree_node* deleteCompany(struct tree_node* T, char company[50])
{
    if (T == NULL)
    {

        return T;
    }
    else if (strcmp(T->company, company) == 0)
    {
        // free current node and all its indications
        struct IndicationList* current = T->indcation;
        while (current != NULL)
        {
            struct IndicationList* temp = current;
            current = current->next;
            free(temp);
        }
        // free T node
        free(T);
        return NULL;
    }
    else
    {
        //Check in left
        T->left = deleteCompany(T->left, company);
        //check in right
        T->right = deleteCompany(T->right, company);
        return T;
    }
}

// find the min value in tree
struct tree_node* find_min( struct tree_node* T)
{
    if ( T == NULL )
        return NULL;
    else if ( T->left == NULL )
        return ( T );
    else
        return ( find_min ( T->left ));
}
// search in tree
struct tree_node* find( char x[50],struct tree_node* T)
{
    if ( T == NULL)
        return NULL;
    if (strcmp( x, T->name)<0)
        return ( find (x, T->left));
    else if (strcmp( x, T->name)>0)
        return ( find ( x, T->right));
    else
        return T;
}
// function to update value in tree
void updateTeam(struct tree_node *temp )
{

    int x;


    if (temp == NULL)
    {
        printf("Node not found!\n");
        return;
    }

    choiceUpdate();
    printf(" enter x\n");
    scanf(" %d", &x);

    switch (x)
    {
    case 1:
        printf(" enter the name  ");
        scanf("%s", temp->name);
        break;
    case 2:
        printf(" enter the active");
        scanf("%s", temp->active);
        break;
    case 3:
        printf(" enter the catagory\n");
        scanf("%s", temp->category);
        break;
    case 4:
        printf(" enter the indication\n");

        break;
    case 5:
        printf(" enter the expiry date\n");
        scanf("%s", temp->expiry_date);
        break;
    case 6:
        printf(" enter the count\n");
        scanf("%d", &temp->count);
        break;
    case 7:
        printf(" enter the company name\n");
        scanf("%s", temp->company);
        break;
    case 8:
        return;
    default:
        printf("error");
    }

    printf("Updation Successful!!!\n");
}



void searchAndUpdate(struct tree_node *root)
{
    char name[50];
    struct tree_node *search;
    char choice;
//ask user to enter name of medicine to search
    printf("Enter the name of medicine to search and update: ");
    fflush(stdin);
    scanf("%[^\n]s", name);

    search = find(name, root);
    printf("Name: %s\n", search->name);
    printf("Active: %s\n", search->active);
    printf("Category: %s\n", search->category);
    printf("Indications: ");
    struct IndicationList* current = root->indcation;
    while (current != NULL)
    {
        printf("%s\t", current->indication);
        current = current->next;
    }
    printf("\nExpiry Date: %s\n", search->expiry_date);
    printf("Count: %d\n", search->count);
    printf("Company: %s\n\n", search->company);

    if (search == NULL)
    {
        printf("Node not found!\n");
        return;
    }


//ask user if want to update data
    printf("Do you want to update the data? (y/n) ");
    scanf(" %c", &choice);
    if (choice == 'y')
    {
        updateTeam(search);
    }
}
// choice to update data
void choiceUpdate()
{
    printf("1-	Update name \n");
    printf("2-	 Updat active ingredient\n");
    printf("3-	Update category\n");
    printf("4-	Update indication\n");
    printf("5-  Update expiry date\n");
    printf("6-  Update count\n");

    printf("7-  Update company name\n");
    printf("8-  to 	Exit\n");
}
//*****************phase 2 functions*******************************
//creat hash table
struct hashtable* create_table(int size)
{
    struct hashtable* table = (struct hashtable*) malloc(sizeof(struct hashtable));
    if (table == NULL)
    {
        printf("Error allocating memory for the hash table\n");
        return NULL;
    }
    table->size = size;
    table->countelement = 0;

    table->items = (struct hashtable_item**) calloc(size, sizeof(struct hashtable_item*));
    if (table->items == NULL)
    {
        printf("Error allocating memory for the hash table items\n");
        free(table);
        return NULL;
    }
    return table;
}
//creat item for hash table
struct hashtable_item* create_item(char key[3], char name[50], char active[50], char category[50], char indication[100], char expiry_date[50], int count, char company[50])
{
    struct hashtable_item* item = (struct hashtable_item*) malloc(sizeof(struct hashtable_item));
    strcpy(item->key, key);
    strcpy(item->name, name);
    strcpy(item->active, active);
    strcpy(item->category, category);
    strcpy(item->indication, indication);
    strcpy(item->expiry_date, expiry_date);
    item->count = count;

    strcpy(item->company, company);
    item->next = NULL;
    return item;
}
//find the first size for hash table
int arraySize()
{
    //get the number of line in file
    int size= numline();
    //check if its prime
    int k=isPrime(size);
    if (k==0)
    {
        if(size%2==0)
            size++;
        else
            size +=2;
    }
    return size;
}
struct hashtable* ht_insert(struct hashtable* table, char name[50], char active[50], char category[50], char indication[100], char expiry_date[50], int count, char company[50])
{
    // Check if table is full and resize if necessary
    if (table->countelement == table->size)
    {
        table = ht_resize_double(table);
        if(table==NULL)
        {
            printf("Error: Resizing failed.");
            return NULL;
        }
    }


    // Create the item
    char key[3];
    strcpy(key,getkey(name));
    struct hashtable_item* item = create_item(key, name, active, category, indication, expiry_date, count, company);
    // Compute the index
    int index = hash_function1(key,table->size);
    int step_size = hash_function2(key, table->size);

    // Check if the name already exists in the table
    while (table->items[index] != NULL)
    {
        if (strcmp(table->items[index]->name, name) == 0)
        {
            printf("Error: Name already exists in the table.\n");
            return table;
        }
        table->countcollision++;
        index = (index + step_size) % table->size;
    }

    // Insert the item
    table->items[index] = item;
    table->countelement++;
    return table;
}

// resize the hash table if it become full
struct hashtable* ht_resize_double(struct hashtable* table)
{
    //find the new size
    int new_size = table ->size * 2;
    struct hashtable_item** new_items = calloc(new_size, sizeof(struct hashtable_item*));
    struct hashtable_item** old_items = table->items;
    int i;
    for (i = 0; i < table->size; i++)
    {
        if (old_items[i] != NULL)
        {
            int index =hash_function1(old_items[i]->key, new_size);
            int step_size = hash_function2(old_items[i]->key, new_size);
            while(new_items[index] != NULL)
            {
                index = (index + step_size) % new_size;
            }
            new_items[index] = old_items[i];
        }
    }
    table->countelement = 0;
    for (i = 0; i < new_size; i++)
    {
        if (new_items[i] != NULL)
        {
            table->countelement++;
        }
    }
    free(old_items);
    table->items = new_items;
    table->size = new_size;
    return table;
}

//check if the number is prime
int isPrime(int n)
{
    int j, flag = 1;
    for (j = 2; j <= n / 2; ++j)
    {
        if (n % j == 0)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}
//count the number of line in the file
int numline()
{
    int counter=0;
    char line[10000];
    FILE*   IN = fopen("Pharmacy.txt", "r");
    if(IN == NULL)
    {
        printf("THE FILE NOT FOUNDED");
    }

    while (fgets(line,1000,IN)!= NULL)
    {
        if(strcmp(line, "") == 0 || strcmp(line, " ") == 0 || strcmp(line, "\n") == 0)
        {
            continue;
        }
        counter++;
    }

    return counter;
}
//search in hash table

struct hashtable_item* ht_searchdouble(struct hashtable* table, char name[50])
{
    int collisions = 0;
    char key[3];
    strcpy(key,getkey(name));
    int index = hash_function1(key, table->size);  // first hash function
    int f2 = hash_function2(key, table->size);  // second hash function
    while (table->items[index] != NULL)
    {
        if (strcmp(table->items[index]->name, name) == 0)
        {
            printf("\nMedicine found with %d collisions\n", collisions);
            printf("Name: %s\n", table->items[index]->name);
            printf("Active: %s\n", table->items[index]->active);
            printf("Category: %s\n", table->items[index]->category);
            printf("Indications: ");

            printf("%s ", table->items[index]->indication);

            printf("\nExpiry Date: %s\n",table->items[index]->expiry_date);
            printf("Count: %d\n", table->items[index]->count);
            printf("Company: %s\n\n", table->items[index]->company);
            return table->items[index];
        }
        collisions++;
        index = (index + f2) % table->size;  // use the second hash function to determine the step size
    }
    printf("\nMedicine not found in the table\n");
    return NULL;
}


void print_table( struct hashtable* root)
{
    printf("\nHash Table\n-------------------\n");
    for (int i=0; i<root->size; i++)
    {
        if (root->items[i])
        {
            printf("index %d\n",i);
            printf("Name: %s\n", root->items[i]->name);
            printf("Active: %s\n", root->items[i]->active);
            printf("Category: %s\n", root->items[i]->category);
            printf("Indications: ");

            printf("%s ", root->items[i]->indication);

            printf("\nExpiry Date: %s\n",root->items[i]->expiry_date);
            printf("Count: %d\n", root->items[i]->count);
            printf("Company: %s\n\n", root->items[i]->company);

        }
        else
        {
            printf("index %d: Empty\n", i);
        }
    }
    printf("-------------------\n\n");
}


float LoadFactor (int counterr, int tableSize)
{
    float v= (float )counterr/tableSize;
    return v;
}

struct hashtable* delete1(struct hashtable* table, char name [50])
{
    if (table->countelement == 0)   // check if the table is empty
    {
        printf("\nThe table is empty, cannot delete item\n");
        return table;
    }
    char key[3];
    strcpy(key,getkey(name));

    int item_found = 0;
    int index = hash_function1(key,table->size);
    int step_size = hash_function2(key,table->size);

    while (table->items[index] != NULL)
    {
        if (strcmp(table->items[index]->name, name) == 0)   // check if the key is found
        {
            item_found = 1;
            break;
        }
        index = (index + step_size) % table->size;

    }
    if (item_found==1)
    {
        free(table->items[index]); // free the memory allocated for the item
        table->items[index] = NULL; // set the item to NULL to indicate it has been deleted
        table->countelement--;
        printf("\nThe item with name %s has been deleted from the table\n", name);
    }
    else
    {
        printf("\nThere is no item with name %s in the table\n", name);
    }

    return table;
}

char* getkey(char name[50])
{
    // check if name string is at least 3 characters long
    if (strlen(name) < 3)
    {
        printf("Error: name string must be at least 3 characters long\n");
        return NULL;
    }
    // allocate memory for key variable using malloc()
    char* key = (char*) malloc(sizeof(char) * 4);
    // copy the first 3 characters of name to key
    strncpy(key, name, 3);
    key[3] = '\0';

    return key;
}


//read file for hash table
void readFilehash(struct hashtable*table,FILE* IN)
{

    char line[1000];
    char* token;
    char name[50];
    char active[50];
    char category[50];
    char expiry_date[50];
    int count;
    char company[50];
    char indication[100];


    while (fgets(line, 1000, IN) != NULL)
    {
//spilt data by :
        token = strtok(line, ":");
        if (token != NULL)
        {
            strcpy(name, token);
        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            strcpy(active, token);
        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            strcpy(category, token);
        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            strcpy(indication,token);

        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            strcpy(expiry_date, token);
        }

        token = strtok(NULL, ":");
        if (token != NULL)
        {
            count = atoi(token);
        }

        token = strtok(NULL, "\n");
        if (token != NULL)
        {
            strcpy(company, token);
        }
        //insert in hashtable

        table=  ht_insert(table,name,active,category,indication,expiry_date,count,company);

    }


}
void WriteToFile (FILE*out,struct hashtable * table)
{

    if (out != NULL)//Check if the pointer is NULL.
    {
        for(int i = 0; i < table->size; i++)
        {
            if (table->items[i])
            {
                fprintf(out,"%s:%s:%s:%s:%s:%d:%s\n",table->items[i]->name,table->items[i]->active,table->items[i]->category,table->items[i]->indication,table->items[i]->expiry_date,table->items[i]->count,table->items[i]->company);
            }
        }

        printf("The operation of writing the data in the output file is done!\n\n");//Print this to let the user know that the data become in the output file.
    }

    else //Print this for user if the file can not be accessed.
    {
        printf("Error ! There's a problem with the file.\n\n");
    }


}

unsigned int hash_function1(char *key, int table_size)
{
    unsigned int hash_val = 0; // initialize hash value to 0
    while (*key)   // iterate through the key
    {
        hash_val = hash_val * 31 + *key++; // update hash value using the current character
    }
    return hash_val % table_size; // return the hash value modulo the table size
}

unsigned int hash_function2(char *key, int table_size)
{
    unsigned int hash_val = 0; // initialize hash value to 0
    while (*key)   // iterate through the key
    {
        hash_val = hash_val * 37 + *key++; // update hash value using the current character
    }
    return hash_val % (table_size - 1) + 1; // return the hash value modulo the table size minus 1, plus 1
}
