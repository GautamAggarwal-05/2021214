#include "BigInteger.h"


struct BigInteger initialize(char *s) {
    struct BigInteger num;
    //num.sign = 1;
    num.head = NULL;
    num.length = 0;
    int i = 0;

    while (s[i] != '\0') {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = s[i] - '0';  // Convert character to integer
        newNode->next = num.head;  // put  next pointer
        num.head = newNode;          // Update head pointer
        num.length++;
        i++;
    }

    return num;
}


void reverse(struct BigInteger* num) {
    struct node* forward = NULL;
    struct node* curr = num->head;
    struct node* prev = NULL;
    while (curr != NULL) {
        forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    num->head = prev;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct node *first = a.head;
    struct node *second = b.head;

   
    struct BigInteger result;
    result.head = NULL;
    result.length = 0;

   

        struct node *currentA = a.head;
        struct node *currentB = b.head;
        struct node *prev = NULL;
        int borrow = 0;

        while (currentA != NULL || currentB != NULL)
        {

            int diff = borrow + (currentA ? currentA->data : 0) - (currentB ? currentB->data : 0);

            if (currentA)
            {
                currentA = currentA->next;
            }
            if (currentB)
            {
                currentB = currentB->next;
            }

            if (diff < 0)
            {
                diff += 10;
                borrow = -1;
            }
            else
            {
                borrow = 0;
            }

            struct node *newNode = (struct node *)malloc(sizeof(struct node));
            newNode->data = diff;
            newNode->next = NULL;

            if (prev == NULL)
            {
                result.head = newNode;
            }
            else
            {
                prev->next = newNode;
            }

            prev = newNode;
            result.length++;
        }

        // Remove leading zeros
        reverse(&result);
        while (result.head->next != NULL && result.head->data == 0)
        {
            struct node *temp = result.head;
            result.head = result.head->next;
            free(temp);
            result.length--;
        }
    
    reverse(&result);
    return result;
}



struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    result.head = NULL;
    result.length = 0;

        struct node* A = a.head;
        struct node* B = b.head;
        struct node* prev = NULL;
        int carry = 0;

        while (A != NULL || B != NULL || carry) {
            int sum;
            if (A != NULL && B != NULL) {
                 sum = carry + A->data + B->data;
                } 
                else if (A != NULL) {
                          sum = carry + A->data;
                    } 
                    else if (B != NULL) {
                      sum = carry + B->data;
                    }
                    else {
                          sum = carry;
                    }
            if (A) {
                A = A->next;
            }
            if (B) {
                B = B->next;
            }

            struct node* newNode = (struct node*)malloc(sizeof(struct node));
            newNode->data = sum % 10;
            newNode->next = NULL;

            if (prev == NULL) {
                result.head=newNode;
            } 
            else {
                prev->next=newNode;
            }
            prev=newNode;
            carry=sum / 10;
            result.length++;
        }
    return result;
}

//MULTIPLY


// Function to insert  Node at the end of LL

struct node* createnode(int data)
{
	struct node* new =(struct node*)malloc(sizeof(struct node));
	new->data = data;
	new->next = NULL;
	return new;
}

void insert(Node** head, int val) {
     Node* new = createnode(val);
    if (*head == NULL) {
        *head = new;
         return ;
    }
     Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
}

// Function to reverse the linked list and return its length
int rev(struct node** head)
{
	 Node* prev = NULL;
	 Node* forward;
	 Node* curr = *head;
	int len=0;
	while (curr!=NULL) {
		len++;
		forward=curr->next;
		curr->next=prev;
		prev=curr;
		curr=forward;
	}
	*head=prev;
	return len;
}
// Function to make an empty linked list of given size to store the result 
Node* newlist(int size)
{
	 Node* head = NULL;
	while (size--)
	{
		insert(&head,0);
	}
	return head;
}

// MULTIPLY LOGIC
 Node* multiply( Node* first, Node* second ,int n,int m,int k)
{
	
	 Node* result = newlist(m + n + 1);
	 Node *ptr2 = second,*resptr1 = result, *resptr2, *ptr1;

	// multiply each Node of second list with first
	while (ptr2) {

		int carry = 0;
		
		resptr2 = resptr1;
		ptr1 = first;
		while (ptr1) {
			int mul = ptr1->data * ptr2->data+ carry;
			resptr2->data += mul % 10;
			carry = mul / 10 + resptr2->data / 10;
			resptr2->data = resptr2->data % 10;

			ptr1 = ptr1->next;
			resptr2 = resptr2->next;
		}
		
		if (carry > 0) {
			resptr2->data += carry;
		}
		resptr1 = resptr1->next;
		ptr2 = ptr2->next;
	}
	 rev(&result);
	while (result->data == 0) {
		struct node* temp = result;
		result = result->next;
		free(temp);
	}
    rev(&result);
	return result;
}

struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    struct node * first=a.head;
    struct node *second=b.head;
    int k=0;
    struct BigInteger result;
    result.head=multiply(first,second,a.length,b.length,k);
    return result;
}

//Divide Logic 
int getLength(Node* Node)
{
    int len = 0;
    while (Node != NULL) {
        Node = Node->next;
        len++;
    }
    return len;
}

int compare(struct node * n1,struct node * n2)
{
    rev(&n1);
    rev(&n2);
	int l1=getLength(n1);
	int l2=getLength(n2);
	if(l1>l2)
		return 1;
	else if(l2>l1)
	{
		return -1;
	}
	else{
		struct node *itr1=n1,*itr2=n2;
		while(itr1!=NULL)
		{
			if(itr1->data>itr2->data)
			{
				return 1;
			}
			else if(itr1->data<itr2->data)
			{
				return -1;
			}
			itr1=itr1->next;
			itr2=itr2->next;
		}
        rev(&n1);
        rev(&n2);
		return 0;
	}
}

struct BigInteger div1(struct BigInteger a,struct BigInteger b)
{
   struct BigInteger res=b;
   struct BigInteger c;
   c.head=createnode(0);
   struct BigInteger adder ;
   adder.head=createnode(1) ;
  if(compare(a.head,b.head)==-1)
  {
      return c;
  }
  if(compare(a.head,b.head)==0)
  {
    return adder;
  }

  while(compare(res.head,a.head)!=1)
  {
    
      c=add(c,adder);
      res=add(res,b);
  }
  return c;
           
}

struct BigInteger mod(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger res=b;
   struct BigInteger c;
   c.head=createnode(0);
   struct BigInteger adder ;
   adder.head=createnode(1) ;
  if(compare(a.head,b.head)==-1)
  {
      return c;
  }
  if(compare(a.head,b.head)==0)
  {
    return adder;
  }

  while(compare(res.head,a.head)!=1)
  {
    
      c=add(c,adder);
      res=add(res,b);
  }
  return sub(b,res);
}

//Function to print result
void display(struct BigInteger num) {
   
    reverse(&num);
    struct node *ptr = num.head;
    while (ptr!= NULL) 
    {
        printf("%d", ptr->data);
        ptr= ptr->next;
    }
    printf("\n");
}
