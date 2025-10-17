#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot)
{
  //base case, nothing left to split
  if(head == nullptr){
    smaller = nullptr;
    larger = nullptr;
    return;
  }

  //save current node and detach from the rest
  Node* current = head;
  Node* rest = head->next;
  current->next = nullptr; //seperate node
  head = nullptr;

  //split rest
  llpivot(rest, smaller, larger, pivot);

  //save current node in the right list
  if(current->val <= pivot){
    current->next = smaller;
    smaller = current;
  } else {
    current->next = larger;
    larger = current;
  }
}