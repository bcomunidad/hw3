#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
    if(head == nullptr) {                  // head is empty
        smaller = nullptr;
        larger = nullptr;
        return;
    }
    Node* trav = head->next;
    if(head->val <= pivot) {               // val is less than or equal to pivot
        if(larger == head) {
            larger = nullptr;
        }
        smaller = head;
        head = nullptr;
        llpivot(trav, smaller->next, larger, pivot);
    }
    else if(head->val > pivot) {            // val is greater than pivot
        if(smaller == head) {
            smaller = nullptr;
        }
        larger = head;
        head = nullptr;
        llpivot(trav, smaller, larger->next, pivot);
    }
}

