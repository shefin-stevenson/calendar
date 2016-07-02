/* examples for linked list operations.
void display_list(ROOT *r): traverse the list and print out the data field.
void display_list(ROOT r) : same as above with different parameter.

int insert_at_head(ROOT *r, DATA *d): return -1 if fail.
int insert_at_tail(ROOT *r, DATA *d): return -1 if fail.
int insert_at_position(ROOT *r, DATA *d):
	assuming the linked list's data field is sorted in the decreasing
	order, insert a new node into the list such that this order is 
	preserved.

void delete_node (ROOT *r, DATA d):   
	delete the first occurance of d from the list if the recurrsive 
	call at the end of the function is not used; otherwise, delete 
	all the occurance of d. (Say the comments inside this function
	for details.)
*/


#include <stdio.h>
#include <stdlib.h>

#define NEW(x) (x*)malloc(sizeof(x))

typedef int DATA;

typedef struct node
{ void * data;
  struct node * next;
} NODE;

typedef struct
{ long num;
  NODE * head;
  NODE * tail;
}ROOT;

void display1(NODE n)
{ printf("By display1: %d\n", *(int *)(n.data));
}

void display2(void *data)
{ printf("By display2: %d\n", *(DATA *)(data));
}

NODE * make_node (void *data)
{ NODE * temp;
  temp = NEW(NODE);
  if (temp != NULL)
  { temp->data = data;
    temp->next = NULL;
  }
  return temp;
}

ROOT * make_root (void)
{ ROOT * temp;
  temp = NEW(ROOT);
  if (temp != NULL)
  { temp->num = 0;
    temp->head = NULL;
    temp->tail = NULL;
  }
  return temp;
}

// this is also an example of traversing the linked link
void display_list(ROOT *r)
{ NODE * temp;

  if (r != NULL)	// this is safer than (r.num != 0), why?
			// if r==NULL, there will be a segmentation fault
			// 	when you try to use r.num
  { temp = r->head;
    do 
    { printf("%3d ", *(DATA *)(temp->data));
      temp = temp->next;
    } while (temp != NULL);
  }
  printf("\n");
}

/* 
// another way to do this by passing the ROOT, instead of a pointer
// however, it is better to pass by reference (i.e., use a pointer)
void display_list(ROOT r)
{ NODE * temp;

  if (&r != NULL)	
  { temp = r.head;
    do
    { printf("%3d ", *(DATA *)(temp->data));
      temp = temp->next;
    } while (temp != NULL);
  }
  printf("\n");
}
*/

int insert_at_head(ROOT *r, DATA *d)
{ NODE * temp;
  temp = make_node(d);
 
  if (temp == NULL) return -1;	// fail, cannot create new NODE

  if (r == NULL) 
  { r = make_root();
    if (r == NULL) return -1;	// fail, cannot create ROOT
  }
     
  (r->num)++;
  temp->next = r->head;
  r->head = temp;

  if (r->num == 1)		// if previously the list is empty
    r->tail = temp;
 
  return 0;
}

// inserting at tail is very similar to the above inserting at head
int insert_at_tail(ROOT *r, DATA *d)
{ NODE * temp;
  temp = make_node(d);

  if (temp == NULL) return -1;  // fail, cannot create new NODE

  if (r == NULL)
  { r = make_root();
    if (r == NULL) return -1;   // fail, cannot create ROOT
  }
    
  (r->num)++;

  if (r->num == 1)              // if previously the list is empty
    r->head = r->tail = temp;

  else 
  { r->tail->next = temp;
    r->tail = temp;
  }
 
  return 0;
}

// this is a combination of searching and insertion
int insert_at_position(ROOT *r, DATA *d)
{ NODE * temp, *this;
  temp = make_node(d);

  if (temp == NULL) return -1;  // fail, cannot create new NODE

  if (r == NULL)
  { r = make_root();
    if (r == NULL) return -1;   // fail, cannot create ROOT
  }
   
  this = r->head;
  if (*(DATA *)(this->data) <= *(DATA *)(temp->data)) // insert at head
    insert_at_head(r, temp->data);

  else
  { while (this->next != NULL && 
	*(DATA *)(this->next->data) > *(DATA *)(temp->data))
      this = this->next;
// we compare d with this->next->data rather then this->data because
// if this->next->data becomes smaller than d, we want to insert d in
// front of this->next. "this" can be treated as the previous of this->next,
// if we compare d directly with this->data, we cannot retrieve the previous
// of "this".

    if (this->next == NULL)     // update tail if insert at tail
    { r->tail = temp;
      this->next = temp;
      (r->num)++;
    }
    else
    { temp->next = this->next;
      this->next = temp;
      (r->num)++;
    }
  }
  return 0;
}

void delete_node (ROOT *r, DATA d)
{ NODE * temp;

  printf("\ndeleting %3d ... \n", d);

  if (r == NULL)		// empty list 
  { printf("No Match!\n"); 
    return;
  }

  temp = r->head;		// delete at head, special case 
  if (*(DATA *)(temp->data) == d)
  { r->head = temp->next;
    (r->num)--;
    printf("Delete %3d at head.\n", d);
  } 

  else 
  { while(temp->next != NULL && *(DATA *)(temp->next->data) != d) 
      temp = temp->next;
// same reason as above in insert_at_position for using temp->next->data

    if (temp->next == NULL )	// reach the tail of the list
    { if (*(DATA *)(temp->data) == d)
      { r->tail = temp;
        (r->num)--;
	printf("Delete %3d at tail.\n", d);
      }
      else 
        {printf("No Match!\n"); return;}
    } 
    else 	// find match: (*(DATA *)(temp->next->data) == d)
		// the order of this if-else is important, because that
		// (*(DATA *)(temp->next->data) == d) will give you a
		// segmentation fault if temp->next == NULL.
    { temp->next = temp->next->next;
      (r->num)--;
      printf("Delete %3d in the middle.\n", d);
    }
  }

// the following recursive call is try to delete all the occurance of DATA
// 	d from the list. In this example, we have 12 appears twice and both
//	of them will be deleted if this recursive call is used.
// you may want to comment all the printf() statements in this function if
//	we uncomment this revursive call. That gives you a clean look of the
//	linked list after deletion.
//  delete_node(r, d);
} 
 
int main(void)
{ ROOT *root;	// a pointer to ROOT type
  DATA *data, *data2;	// a pointer points to type DATA (int)
  DATA d, d2;
  int i;

  root = make_root(); // see what happend when this line is deleted.

  for (i=0; i<5; i++)
  { data = NEW(DATA);
    d = 10 + i;
    *data = d;
    insert_at_head(root, data);
    printf("inserting %3d at the head: ", d);
    display_list(root);
  } 

  for (i=0; i<5; i++)
  { data = NEW(DATA);
    d = 9 - 2*i;
    *data = d;
    insert_at_tail(root, data);
    printf("inserting %3d at the tail: ", d);
    display_list(root);
  }

  for (i=0; i<4; i++)
  { data = NEW(DATA);
    d = 20 - 8*i;
    *data = d;
    insert_at_position(root, data);
    printf("inserting %3d at position: ", d);
    display_list(root);
  }
  
/* you can write testing code segment to test the delete function
*/

  return 0;
}

     
