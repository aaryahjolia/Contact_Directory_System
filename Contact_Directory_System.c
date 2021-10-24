/*
CONTACT MANAGEMENT SYSTEM

DS USED : CIRCULAR DOUBLY LINKED LIST

COPYRIGHT : AARYA AHJOLIA
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Creating Struct for Linked List 
struct node{
    int fav;
    char name[40];
    char number[20];
    struct node*next;
    struct node*prev;
};
//Creating temp string and int variables to take input for inserting, deleting, searching,etc.
char temp[40];
char temp_number[20];
struct node*head=NULL;
int te;

//Declaring sort function
void sort();
// void capital_name();

//Creating Insert Function
void insert(){
    struct node* new_node=(struct node*)malloc(sizeof(struct node));
    printf("Enter Person Name:\n");
    while((getchar())!='\n');
    scanf("%[^\n]%*c",temp);
    phone_no:
    printf("Enter 10 Digit Phone Number:\n");
    scanf("%[^\n]%*c",temp_number);
    if(strlen(temp_number)!=10){
        printf("Please Enter 10 digit Number !\n");
        goto phone_no;
    }

    printf("Add this contact to Favourite List ?\n");
    int choice;
    printf("1. Yes\n2. No\nEnter choice : ");
    scanf("%d",&choice);
    if(choice==1){
        new_node->fav=1;
    }
    else{
        new_node->fav=0;
    }

    //Copying input string to node's string variable
    strcpy(new_node->name,temp);
    strcpy(new_node->number,temp_number);
    //Joining new node to the linked list
    if(head==NULL){
        new_node->next=new_node->prev=new_node;
        head=new_node;
        return;
    }
    struct node*last=head->prev;
    new_node->prev=last;
    last->next=new_node;
    new_node->next=head;
    head->prev=new_node;
    sort();
}

/*void capital_name(){
    struct node*ptr=head;
    if(ptr!=NULL){
        do{
            for(int i=0;i<strlen(ptr->name);i++){
                if(i==0 && (ptr->name[i]>=97 && ptr->name[i]<=122)){
                    ptr->name[i]=ptr->name[i]-32;
                }
                if(ptr->name[i]==' ' && (ptr->name[i+1]>=97 && ptr->name[i+1]<=122)){
                    ptr->name[i+1]=ptr->name[i+1]-32;
                }
            }
            ptr=ptr->next;
        }while(ptr!=head);
    }
}*/

//Creating Sort function that interchanges all values of a node according to ascending name
void sort(){
    struct node*ptr=head;
    if(ptr!=NULL){
        do{
            struct node*ptr2=ptr->next;
            if(ptr2!=NULL){
                while(ptr2!=ptr){
                    if(strcmp(ptr->name,ptr2->name)<0){
                        char temp[100];
                        strcpy(temp,ptr->name);
                        strcpy(ptr->name,ptr2->name);
                        strcpy(ptr2->name,temp);

                        char temp_n[20];
                        strcpy(temp_n,ptr->number);
                        strcpy(ptr->number,ptr2->number);
                        strcpy(ptr2->number,temp_n);

                        int fav_temp;
                        fav_temp=ptr->fav;
                        ptr->fav=ptr2->fav;
                        ptr2->fav=fav_temp;
                    }
                    ptr2=ptr2->next;
                }
            }
            ptr=ptr->next;
        }while(ptr!=head);
    }
}

//Creating Delete Function
void Delete_element(){
    if(head==NULL){
        printf("No Contact is there to delete!\n");
        return;
    }
    printf("Enter Full Person Name to delete : (Name you entered when adding contact) \n");
    while((getchar())!='\n');
    scanf("%[^\n]%*c",temp);
    printf("\n");
    struct node*ptr=head;
    //Checking if name is there or not and deleting
    do{
        if(ptr->next==ptr && strcmp(ptr->name,temp)==0){
            printf("One Contact deleted! Contact List is Empty Now!\n");
            head=NULL;
            free(ptr);
            return;
        }
        else if(strcmp(ptr->name,temp)==0){
            struct node*prev=ptr->prev;
            struct node*next=ptr->next;
            prev->next=next;
            next->prev=prev;
            head=next;
            free(ptr);
            printf("Contact deleted!\n");
            return;
        }
        ptr=ptr->next;
    }while(ptr!=head);
    printf("No Contact Profile is there!\n");
}

//Creating Show Function and displaying contacts
void show(){
    if(head==NULL){
        printf("Contact Directory is Empty!\n");
        return;
    }
    struct node*show_ptr=head;
    printf("\n");
    int i=1;
    printf("Displaying Contact Directory :\n");
    do{
        char tem[40];
        //Converting string's first letter to uppercase, showing, and converting back to original
        strcpy(tem,show_ptr->name);
        for(int i=0;i<strlen(show_ptr->name);i++){
            if(i==0 && (show_ptr->name[i]>=97 && show_ptr->name[i]<=122)){
                show_ptr->name[i]=show_ptr->name[i]-32;
            }
            if(show_ptr->name[i]==' ' && (show_ptr->name[i+1]>=97 && show_ptr->name[i+1]<=122)){
                show_ptr->name[i+1]=show_ptr->name[i+1]-32;
            }
        }
        printf("Name : %-15s , Phone No.: +91-%-10s\n",show_ptr->name,show_ptr->number);
        strcpy(show_ptr->name,tem);
        i++;
        show_ptr=show_ptr->next;
    }while(show_ptr!=head);
}

//Creating Search Function
void search(){
    struct node*ptr=head;
    if(ptr==NULL){
        printf("No Contact is there !\n");
        return;
    }

    printf("Enter Person Name to Search : ");
    while((getchar())!='\n');
    scanf("%[^\n]%*c",temp);

    //Searching names by matching substring so that a single char is also searched in whole string using strstr function
    int i=1;
    printf("\nFound Names :\n");
    do{
        if(strstr(ptr->name,temp)){
            char tem[40];
            strcpy(tem,ptr->name);
            for(int i=0;i<strlen(ptr->name);i++){
                if(i==0 && (ptr->name[i]>=97 && ptr->name[i]<=122)){
                    ptr->name[i]=ptr->name[i]-32;
                }
                if(ptr->name[i]==' ' && (ptr->name[i+1]>=97 && ptr->name[i+1]<=122)){
                    ptr->name[i+1]=ptr->name[i+1]-32;
                }
            }       
            printf("%d. %s\n",i,ptr->name);
            strcpy(ptr->name,tem);
            i++;
        }
        ptr=ptr->next;
    }while(ptr!=head);
    if(i==1){
        printf("No Names Found!\n");
    }
}

//Creating Update details function
void update_details(){
    struct node*ptr=head;
    if(ptr==NULL){
        printf("No contact is there to Update !\n");
        return;
    }
    printf("Enter Person Name to Update : ");
    while((getchar())!='\n');
    scanf("%[^\n]%*c",temp);

    char t[50];
    do{
        if(strstr(ptr->name,temp)){   
            printf("\nFound Name : %s\n",ptr->name);
            printf("Do you want to update this Contact ?\n1. Yes\n2. Find another contact\n");
            int choice;
            scanf("%d",&choice);
            if(choice==1){
                printf("\nWhat do you want to update?\n1. Name\n2. Phone no\n3. Add/Remove from favourites\n");
                int c;
                printf("Enter choice : ");
                scanf("%d",&c);
                //Updating Name
                if(c==1){
                    printf("Enter New Name : ");
                    while((getchar())!='\n');
                    scanf("%[^\n]%*c",t);
                    strcpy(ptr->name,t);
                    printf("Successfully Updated Name !\n");
                }
                //Updating Phone no.
                else if(c==2){
                    printf("Enter New Phone no : ");
                    while((getchar())!='\n');
                    scanf("%[^\n]%*c",t);
                    strcpy(ptr->number,t);
                    printf("Successfully Updated Phone no !\n");
                }
                //Updating Favourite list
                else if(c==3){
                    printf("\nWhat do you want to do?\n1. Add to Favourites\n2. Remove from favourites\n");
                    int choice;
                    scanf("%d",&choice);
                    if(choice==1){
                        if(ptr->fav==1)printf("It is Already Favourite !\n");
                        else{
                            ptr->fav=1;
                            printf("Added to Favourite List Successfully !\n");
                        }
                    }
                    else if(choice==2){
                        if(ptr->fav==0)printf("It is Already not there !\n");
                        else{
                            ptr->fav=1;
                            printf("Removed from Favourite List Successfully !\n");
                        }
                    }
                    else{
                        printf("Enter Valid Number !\n");
                    }
                }
            }
            else if(choice!=1 && choice!=2){
                printf("Enter correct choice!\n");
            }
        }
        ptr=ptr->next;
    }while(ptr!=head);
}

//Displaying Fav list
void fav_list(){
        if(head==NULL){
        printf("Favourite Contact Directory is Empty!\n");
        return;
    }
    struct node*show_ptr=head;
    printf("\n");
    printf("Displaying Favourite Contact Directory :\n");
    int i=1;
    do{
        if(show_ptr->fav==1){
            char tem[40];
            strcpy(tem,show_ptr->name);
            for(int i=0;i<strlen(show_ptr->name);i++){
                if(i==0 && (show_ptr->name[i]>=97 && show_ptr->name[i]<=122)){
                    show_ptr->name[i]=show_ptr->name[i]-32;
                }
                if(show_ptr->name[i]==' ' && (show_ptr->name[i+1]>=97 && show_ptr->name[i+1]<=122)){
                    show_ptr->name[i+1]=show_ptr->name[i+1]-32;
                }
            }
            printf("%d. Name : %-15s , Phone No.: +91-%-10s\n",i,show_ptr->name,show_ptr->number);
            strcpy(show_ptr->name,tem);
            i++;
        }
        show_ptr=show_ptr->next;
    }while(show_ptr!=head);
    if(i==1){
        printf("No Favourite Contact is there !\n");
    }
}

//Main Function
int main(){
    //Providing a Menu
    int choice;
        menu:
        printf("\n-----Contact Management Application-----\n");
        printf("1. Add Contact\n");
        printf("2. Remove Contact\n");
        printf("3. Show Contacts\n");
        printf("4. Search Contacts\n");
        printf("5. Update Details\n");
        printf("6. Show Favourite List\n");
        printf("7. Exit\n\n");
        printf("Enter Choice : ");
        scanf("%d",&choice);

        if (choice == 1)
            insert();

        else if (choice == 2)
            Delete_element();

        else if (choice == 3)
            show();

        else if (choice == 4)
            search();

        else if (choice == 5)
            update_details();

        else if (choice == 6)
            fav_list();
            
        else
            exit(0);

            goto menu;
    return 0;
}

/*
    OUTPUT :

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 1
Enter Person Name:
aarya ahjolia
Enter 10 Digit Phone Number:
222222222
Please Enter 10 digit Number !
Enter 10 Digit Phone Number:
2222222222
Add this contact to Favourite List ?
1. Yes
2. No
Enter choice : 2

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 1
Enter Person Name:
xyz ahjolia
Enter 10 Digit Phone Number:
3333333333
Add this contact to Favourite List ?
1. Yes
2. No
Enter choice : 2

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 1
Enter Person Name:
the begmmer human
Enter 10 Digit Phone Number:
4444444444
Add this contact to Favourite List ?
1. Yes
2. No
Enter choice : 2

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 3

Displaying Contact Directory :
Name : Aarya Ahjolia   , Phone No.: +91-2222222222
Name : The Begmmer Human , Phone No.: +91-4444444444
Name : Xyz Ahjolia     , Phone No.: +91-3333333333

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 4
Enter Person Name to Search : j

Found Names :
1. Aarya Ahjolia
2. Xyz Ahjolia

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 4
Enter Person Name to Search : the

Found Names :
1. The Begmmer Human

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 6

Displaying Favourite Contact Directory :
No Favourite Contact is there !

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 5
Enter Person Name to Update : aar

Found Name : aarya ahjolia
Do you want to update this Contact ?
1. Yes
2. Find another contact
1

What do you want to update?
1. Name
2. Phone no
3. Add/Remove from favourites
Enter choice : 3

What do you want to do?
1. Add to Favourites
2. Remove from favourites
1
Added to Favourite List Successfully !

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 5
Enter Person Name to Update : th

Found Name : the begmmer human
Do you want to update this Contact ?
1. Yes
2. Find another contact
1

What do you want to update?
1. Name
2. Phone no
3. Add/Remove from favourites
Enter choice : 3

What do you want to do?
1. Add to Favourites
2. Remove from favourites
1
Added to Favourite List Successfully !

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 6

Displaying Favourite Contact Directory :
1. Name : Aarya Ahjolia   , Phone No.: +91-2222222222
2. Name : The Begmmer Human , Phone No.: +91-4444444444

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 3

Displaying Contact Directory :
Name : Aarya Ahjolia   , Phone No.: +91-2222222222
Name : The Begmmer Human , Phone No.: +91-4444444444
Name : Xyz Ahjolia     , Phone No.: +91-3333333333

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 2
Enter Full Person Name to delete : (Name you entered when adding contact)
the begmmer human

Contact deleted!

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 2
Enter Full Person Name to delete : (Name you entered when adding contact)
xyz ahjolia

Contact deleted!

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 3

Displaying Contact Directory :
Name : Aarya Ahjolia   , Phone No.: +91-2222222222

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 6

Displaying Favourite Contact Directory :
1. Name : Aarya Ahjolia   , Phone No.: +91-2222222222

-----Contact Management Application-----
1. Add Contact
2. Remove Contact
3. Show Contacts
4. Search Contacts
5. Update Details
6. Show Favourite List
7. Exit

Enter Choice : 7
*/