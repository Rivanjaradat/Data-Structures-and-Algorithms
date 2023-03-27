#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#define QUEUE_SIZE 11
//this code defines a Queue struct
typedef struct Queue
{
    int front;
    int rear;
    int count;
    int index;
    char* array[QUEUE_SIZE];
    char code [3];
} Queue;
struct TEAM *deleten(struct TEAM *head, char *value);
void createMatch(struct TEAM *p,struct Queue*q);
struct TEAM *radixSort(struct TEAM *head) ;
struct Queue* initQueue();
char* dequeue(Queue* q);
//this code defines a Team struct(LinkedList)
struct TEAM
{
    char name[50];
    char code[3];
    int No_wins;
    int No_draws ;

    int   No_loses;
    int  Goals_difference;
    int point;
    int Size;
    struct TEAM *next;
    struct Queue*spare;
    struct PLAYER1*player1;


};
//this code defines aPlayer1 struct(LinkedList)
struct PLAYER1
{
    char code[3];
    int index;
    char nameP1[50];
    struct PLAYER1*next;
};

struct TEAM*head= NULL;
int main()
{

//calling function phase1()
    phase1();

    return 0;
}
//****************************PHASE1 FUNCTION***************************************************
// this function to spilt file txt data and save it in a linked list
void readfile( struct TEAM*l)
{
    FILE *IN;
    char line [1000];
    int indix;
    char*token;
    char name[50];
    char code[3];
    int No_wins;
    int No_draws ;
    int   No_loses;
    int  Goals_difference;
//check if the file exist
    IN = fopen("teams.txt", "r");
    if(IN == NULL)
    {
        printf("THE FILE NOT FOUNDED");
    }

// while loop to spilt txt
    while (fgets(line,1000,IN)!= NULL)
    {


        token= strtok(line, ",");
        strcpy( name,token);
        token= strtok(NULL, ",");
        strcpy( code,token);
        token= strtok(NULL, ",");
        No_wins=atoi(token);
        token= strtok(NULL, ",");
        No_draws=atoi(token);
        token= strtok(NULL, ",");
        No_loses=atoi(token);
        token= strtok(NULL, "/n");
        Goals_difference=atoi(token);



// calling function creat to creat a node in linked list
        creat(l,name, code, No_wins, No_draws,   No_loses,  Goals_difference);


    }
    printf("done\n");
}
//function creat to creat a node in linked list
void creat ( struct TEAM*L, char name[50],char code[3],int No_wins,int No_draws,int   No_loses,int  Goals_difference)

{




    struct TEAM* temp;
    temp =(struct TEAM*) malloc(sizeof(struct TEAM));
    if(temp !=NULL)
    {

        strcpy(temp->name,name);
        strcpy(temp->code,code);
        temp->No_wins=No_wins;
        temp->No_draws=No_draws;
        temp->No_loses=No_loses;
        temp->Goals_difference=Goals_difference;

    }
    else
    {
        printf("ERROR out of memory\n");

    }
    insert(L, L, temp);

}
void insert(struct TEAM* L, struct TEAM* p, struct TEAM* temp)
{

    if(temp !=NULL && L != NULL)
    {

        temp->next=p->next;
        p->next=temp;


    }
    else
    {
        printf("ERROR either Linked List L or the new node is NULL \n");
    }

}
// function to print linked list element
void printSortedList(struct TEAM *head)
{
    struct TEAM *current = head;
    while (current != NULL)
    {
        printf("Team name: %s, Code: %s, No_wins: %d, No_draws: %d, No_loses: %d, Goals_difference: %d, point: %d\n", current->name, current->code, current->No_wins, current->No_draws, current->No_loses, current->Goals_difference, current->point);
        current = current->next;
    }
}
void choice1()
{
    printf("1-	Read File and save data in linkedlist \n");
    printf("2-	 calculate and store the points for each Team\n");
    printf("3-	sort the teams based on the attained points using the Radix Sort\n");
    printf("4-	Insert new Team\n");
    printf("5-  Delete Team\n");
    printf("6-  update team info\n");
    printf("7-  print teams information\n");
    printf("8-	Save the teams info sorted  back to the file\n");

    printf("9-	create a match \n");
    printf("10-	 print player elementary info and spare\n");
    printf("11-	Give red card to player\n");
    printf("12-   change the players between elementary and spare\n");
    printf("13-  Save back the players information to the file \n");
    printf("14-	Exit\n");
}

// function to find the point for each team
void pointTeam(struct TEAM* L)
{

    L=head->next;
    while(L != NULL)
    {
        int point =3*L->No_wins+1*L->No_draws;
        L->point=point;
        printf(" %s,%d \n",L->code,L->point );
        L = L->next;
    }
}
// function to print in file
void writeout(struct  TEAM*current)
{
    FILE *out;
    out = fopen("teamsInfo.txt","w");
    while ((current != NULL))
    {

        fprintf(out,"Team name: %s, Code: %s, No_wins: %d, No_draws: %d, No_loses: %d, Goals_difference: %d, point: %d\n", current->name, current->code, current->No_wins, current->No_draws, current->No_loses, current->Goals_difference, current->point);
        current=current->next;
    }
    fclose(out);
}





// function to update team info
void updateTeam( struct TEAM *temp )
{

    int x ;

    char name[50];
    char code1[3];
    char code[3];
    int No_wins;
    int No_draws ;
    int   No_loses;
    int  Goals_difference;
    printf(" enter the team code");
    scanf("%s",&code1);
    if(head==NULL)
    {
        printf("Linked List not initialized");
        return;
    }
    temp=head->next;
    while(temp!=NULL)
    {

        if(strcmp(temp->code,code1)==0)
        {
            printf("Team with code %s Found !!!\n", code1);
            choiceUpdate();
            printf(" enter x\n");
            scanf(" %d",&x);

            switch(x)
            {
            case 1:
                printf("enter new name \n");

                scanf("%s",&temp->name);
                break;
            case 2:
                printf("enter new code\n");

                scanf("%s",&temp->code);
                break;
            case 3:
                printf("enter new now\n");
                scanf(" %d",&temp->No_wins);
                break;
            case 4:
                printf("enter new nol\n");
                scanf(" %d",&temp->No_loses);
                break;
            case 5:
                printf("enter new nod\n");
                scanf(" %d",&temp->No_draws);
                break;
            case 6:
                printf("enter new gd\n");
                scanf(" %d",&temp->Goals_difference);
                break;

            default :
                printf("error");

            }

            printf("Updation Successful!!!\n");

            return;
        }
        temp = temp->next;
    }
    printf("THE TEAM WITH CODE %s is not found !!!\n", code1);

}

int isLastT(struct TEAM *n, struct TEAM *head)
{

    return n->next == NULL;

}
void phase1()
{
    char name[50];
    char code[3];
    int NoW;
    int NoD ;
    int   NoL;
    int  GD;
    int m;
    head= (struct TEAM*)malloc (sizeof(struct TEAM));
    head->next =NULL;
    struct PLAYER1  * headP= (struct TEAM*)malloc (sizeof(struct TEAM));
    headP->next =NULL;
    struct TEAM *p=head;
    struct TEAM*sorted=p;
    struct Queue*q=initQueue();
    int flag1=0;
    int flag2=0;
    int x;
    printf(" please choose one choice:\n");


    while (true)
    {
        choice1();
        scanf("%d",&x);
        printf("--------------------------------------\n");

        switch (x)
        {

        case 1:

            readfile(p);
            flag1=1;

            break;

        case 2:
            if(flag1==1)
            {
                pointTeam(p);
            }
            else
                printf(" please enter 1\n");

            break;
        case 3:
            if(flag1==1)
            {
                p=radixSort(p);
            }
            else
                printf(" please enter 1\n");

            break;
        case 4:
            if(flag1==1)
            {

                printf(" enter the team name  ");
                scanf("%s",&name);
                printf(" enter the team code");
                scanf("%s",&code);

                printf(" enter the No. of wins\n");
                scanf("%d",&NoW);
                printf(" enter the No. of draws\n");
                scanf("%d",&NoD);
                printf(" enter the No. of loses\n");
                scanf("%d",&NoL);
                printf(" enter the Goals difference\n");
                scanf("%d",&GD);
                creat(p,name,code,NoW,NoD,NoL,GD);
                printf("the inseart is done\n");
            }
            else
                printf(" please enter 1\n");

            break;
        case 5:
            if (flag1==1)
            {
                printf(" enter the team code\n");
                scanf("%s",&code);
                p=deleten(p, code);
            }
            else
                printf(" please enter 1\n");
            break;

        case 6:
            if (flag1==1)
            {

                updateTeam( p);
            }
            else
                printf("please enter 1\n");


            break;
        case 7:
            if (flag1==1)
            {
                printTeams(p);
            }
            else
                printf(" please enter 1\n");
            break;
        case 8:
            if (flag1==1)
            {
                writeout(p);
            }
            else
                printf("please enter 1\n");

            break;
        case 9:
            createMatch(p,q);
            flag2=1;
            break;
        case 10:
            if (flag2==1)
            {
                displayqueue(q);
                printf("*******************************");
                printPlayers(p);
            }

            else
                printf(" please enter 9\n");
            break;
        case 11:
            if (flag2==1)
            {
                redCard(p);
            }
            else
                printf(" please enter 9\n");
            break;
        case 12:
            if (flag2==1)
            {
                changPlayer(p,q);
            }
            else
                printf("please  enter 9\n");
            break;
        case 13:
            if (flag2==1)
            {
                writeoutp(p);
            }
            else
                printf(" please enter 9\n");
            break;

        case 14:
            exit(0);
            break;
        default:
            printf(" just  number from 1 to 14\n");

        }
    }
}
//delete node
struct TEAM *deleten(struct TEAM *head, char *value)
{
    // If the linked list is empty
    if (head == NULL)
    {
        printf("linked list is empty\n");
        return NULL;
    }

    // If the element to be removed is the first element, update the head of the linked list
    if (strcmp(head->code, value) == 0)
    {
        struct TEAM *new_head = head->next;
        free(head);
        return new_head;
    }

    // Find the element to be removed
    struct TEAM *current = head;
    while (current->next != NULL && strcmp(current->next->code, value) != 0)
    {
        current = current->next;
    }

    // If the element is not in the linked list, there is nothing to do
    if (current->next == NULL)
    {
        printf(" the team not found");
        return head;
    }

    // Remove the element
    struct TEAM *temp = current->next;
    current->next = temp->next;
    free(temp);

    return head;
}
void choiceUpdate()
{
    printf("1-	Update name \n");
    printf("2-	 Updat code\n");
    printf("3-	Update now\n");
    printf("4-	Update nol\n");
    printf("5-  Update Nod\n");
    printf("6-  Update gd\n");

    printf("7-  to 	Exit\n");
}
//*******************************radix sort function*************************************
// function to get maximum value in the linked list
int getMax(struct TEAM *p)
{
    int max = p->point;
    while (p != NULL)
    {
        if (p->point > max)
        {
            max = p->point;
        }
        p = p->next;
    }
    return max;
}

int numDigit(int number)
{
    int count = 0;
    while (number != 0)
    {
        number /= 10;
        count++;
    }
    return count;
}
// function to get the number of digits in the maximum value
struct TEAM *radixSort(struct TEAM *head)
{
    int max = getMax(head);  // function to get maximum value in the linked list
    int digits = numDigit(max);  // function to get the number of digits in the maximum value

    for (int div = 1; digits > 0; div *= 10, digits--)
    {
        struct TEAM *sorted[10] = {0};  // create array of 10 "buckets"
        struct TEAM *current = head;

        while (current != NULL)
        {
            int bucket = (current->point / div) % 10;  // determine which bucket to place element in
            struct TEAM *next = current->next;
            current->next = sorted[bucket];  // place element in the appropriate bucket
            sorted[bucket] = current;
            current = next;
        }

        head = NULL;
        for (int i = 0; i < 10; i++)    // concatenate elements in each bucket to build the sorted linked list
        {
            if (sorted[i] == NULL)
                continue;

            if (head == NULL)
            {
                head = sorted[i];
            }
            else
            {
                current->next = sorted[i];
            }

            current = sorted[i];
            while (current->next != NULL)
            {
                current = current->next;
            }
        }
    }

    return head;
}

//***********************phase2 function*************************************************
// function to creat match between 2 team

void createMatch(struct TEAM *p, struct Queue* q)
{
    FILE *IN;
    char line[1000];
    char *token;
    char code[3];
    char name[50];
    char code1[50], code2[50];
    int flage1 = 0;
    int flage2 = 0;
    int index;
    q=initQueue();//creat queue

    printf("Enter code for TEAM 1: ");
    scanf("%s", &code1);


    printf("Enter code for TEAM 2: ");
    scanf("%s", &code2);


    struct TEAM *team1 = NULL;
    struct TEAM *team2 = NULL;

// Find the team structures for the given codes
    while (p->next != NULL)
    {
        if (strcmp(p->code, code1) == 0)
        {
            team1 = p;
        }
        else

        if (strcmp(p->code, code2) == 0)
        {
            team2 = p;
        }
        else

        p = p->next;
    }

// Read the player names  from the file
    while (fgets(line, 1000, IN) != NULL)
    {
        if (line[0] == '*')
        {
            // Extract the team code from the line
            sscanf(line, "*%s", code);
        }
        else
        {
            // Extract the player name from the line
            token = strtok(line, "*-");
            sscanf(token, "%*d-%[^\n]", name);
            index = atoi(token);

            // Insert the player into the correct team
            if (strcmp(code, code1) == 0)
            {
                if (index <= 11)
                {
                    insert_player(team1, name, index);
                }
                else
                {
                    enqueue(q, name);
                }
            }
            else if (strcmp(code, code2) == 0)
            {
                if (index <= 11)
                {
                    insert_player(team2, name, index);
                }
                else
                {
                    enqueue(q, name);
                }
            }
        }

    }

}
int insert_player(struct TEAM *team, char *name, int k)
{
    // Allocate memory for the new node
    struct PLAYER1 *new_node = (struct PLAYER1*)malloc(sizeof(struct PLAYER1));

    // Check if memory allocation was successful
    if (new_node == NULL)
    {
        return 0;
    }

    // Assign values to the fields of the new node
    strcpy(new_node->nameP1, name);
    new_node->index = k;

    // Insert the new node at the head of the list
    new_node->next = team->player1;
    team->player1 = new_node;

    return 1;
}

void printTeams(struct TEAM *head)
{
    struct TEAM *p = head->next; // Skip the dummy node at the head of the list

    while (p != NULL)
    {
        printf("Name: %s\n", p->name);
        printf("Code: %s\n", p->code);
        printf("No. wins: %d\n", p->No_wins);
        printf("No. draws: %d\n", p->No_draws);
        printf("No. loses: %d\n", p->No_loses);
        printf("Goals difference: %d\n", p->Goals_difference);
        printf("Point: %d\n", p->point);
printf("*************************\n");
        p = p->next;
    }
}

void printPlayers(struct PLAYER1 *head)
{
    struct PLAYER1 *p = head;

    while (p != NULL)
    {
        printf("Player name: %s\n", p->nameP1);
        printf("Player index: %d\n", p->index);

        p = p->next;
    }

    return; // Stop the code when printPlayers is called
}

void redCard(struct TEAM*p)
{

    struct PLAYER1 *new_node = (struct PLAYER1*)malloc(sizeof(struct PLAYER1));
    if(p==NULL)
    {
        return;
    }
    if(p->player1==NULL)
    {
        printf(" there no player\n");
        return;
    }
    printf(" enter the player name \n");
    char name[50];
    scanf("%s",&name);
    deleten(p->player1,name);

}
// change player between elmentery  and spare

void changPlayer(struct TEAM*p,struct Queue*Q)
{

    struct PLAYER1 *new_node = (struct PLAYER1*)malloc(sizeof(struct PLAYER1));
    Q=initQueue();
    if(p==NULL||Q==NULL)
    {
        return;
    }
    if(p->player1==NULL)
    {
        printf(" there no player\n");
        return;
    }

    printf(" enter the player name\n");
    char name[50];
    scanf("%s",&name);
    deleten(p,name);
    char *nameq;
    nameq= dequeue(Q);
    enqueue(name);
    insert_player(p,name,p->player1->index);


}
//*********************************queue function***********************************************
struct Queue* initQueue()
{
    struct Queue* q = malloc(sizeof(struct Queue));
    if (q == NULL)
    {
        printf("Error allocating memory for queue\n");
        exit(1);
    }
    q->front = QUEUE_SIZE-1;
    q->rear =QUEUE_SIZE-1 ;
    q->count = 0;
    return q;
}

//check if the queue is full
int isFull(Queue* q)
{
    return q->count == QUEUE_SIZE;
}
//check if the queue is empty
int isEmpty(Queue* q)
{
    return q->count == 0;
}
// insert in queue
void enqueue(Queue* q, char* value)
{
    if (isFull(q))
    {
        printf("Queue is full\n");
        return;
    }

    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->array[q->rear] = value;
    q->count++;
    printf(" the %s is insert\n",value);
}

// find the first elmente enter the queue
char* getFront(struct Queue* q)
{
    if (q->count == 0)
    {
        return NULL;
    }
    return q->array[q->front];
}

//delete the first elmente enter the queue

char* dequeue(struct Queue* q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return 0;
    }
    char* value = q->array[q->front];

    q->front = (q->front + 1) %QUEUE_SIZE;
    q->count--;
    return value;
}
// print players info in file
void writeoutp(struct  TEAM*ptr)
{
    FILE *out;
    out = fopen("playersInfo.txt","w");
    while ((ptr != NULL))
    {
        fprintf(out," code Team:%s\n",ptr->code);

        fprintf(out,"  %s  \n",ptr->player1->nameP1 );
        ptr=ptr->next;
    }
    fclose(out);
}
// function to print spare palyers info
void displayqueue(struct Queue* p)
{
    if (p->rear==-1)
        printf(" queue empty\n ");
    else
    {
        int i;
        printf(" Player spare name for Team %s :\n",p->code);
        for (int i=p->front; i<=p-> rear; i++)
        {
            printf(" %s \n",p->array[i]);
        }
    }
    printf("\n");


}
