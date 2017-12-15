/*
 *   Insert Node at a given position in a linked list 
 *   head can be NULL 
 *   First element in the linked list is at position 0
 *   Node is defined as 
 *   struct Node
 *   {
 *   	 int data;
 *     struct Node *next;
 *   }
 **/

Node* InsertNth(Node *head, int data, int position)
{
    Node *to_add = new Node;
    to_add -> data = data;
    if (position == 0) { to_add -> next = head; head = to_add; }
    else {
        Node *it = head;
        for(; position > 1; --position) it = it->next;
        to_add->next = it -> next;
        it->next = to_add;
    }
    return head;
}

