//Implement In-place quick sort

#include <iostream>
using namespace std;

class node {
public:
    int value;
    node * next;
    node * previous;
    node(int i) { value = i; next = previous = nullptr; }
    node() { next = previous = nullptr; }
};

class doubly_linked_list {
public:
    node * head;
    node * tail;
    doubly_linked_list() { head = tail = nullptr; }
    void make_random_list(int m, int n); //create m nodes with value randomly in 0 ... n-1
    void print_forward();
    void print_backward();
    
    //implement the following member functions:
    
    void sort(node * p1, node * p2);
    //Range of sort is from *p1 to *p2
    //Use in-place quick sort algorithm to sort the linked list in ascending order.
    //You are only allowed to modify the pointers of nodes, but not values of nodes
    
};

void doubly_linked_list::sort(node * p1, node * p2){
    //If the node number of linked list is 1, jump out of the recurrence
    if(p1 == nullptr || p2 ==nullptr)
        return;
    if(p1 == p2)
        return;
    if(p1 == p2->next)
        return;
    
    //Let the last element is pivot
    int x  = p2->value;   // The value of pivot
    node *i = p1->previous;
    node *mark_p1 = p1;   //To record the posistion of old p1
    int flag = 0; //To judge if the position of p1 is changed
    
    for (node *j = p1; j != p2; j = j->next){
        if (j->value <= x){
            i = (i == nullptr)? p1 : i->next;
            if(i==mark_p1){
                flag++;
                mark_p1 = j;
            }
            
            //swap((i->value), (j->value));
            if(i == j){
                continue;
            }
            node * prev_i, *prev_j, *next_i, *next_j;
            prev_i = i->previous;
            prev_j = j->previous;
            next_i = i->next;
            next_j = j->next;
            if(next_i == j){
                if(prev_i != nullptr){
                    prev_i->next = j;
                    j->previous = prev_i;
                    j->next = i;
                    i->previous = j;
                    i->next = next_j;
                    if(next_j != nullptr) next_j->previous = i;
                    else tail = i;
                }
                else{
                    i->previous = j;
                    i->next = next_j;
                    j->next = i;
                    j->previous = nullptr;
                    head = j;
                    if(next_j != nullptr) next_j->previous = i;
                    else tail = i;
                }
            }
            else{
                if(prev_i != nullptr){
                    prev_i->next = j;
                    j->previous = prev_i;
                    next_i->previous = j;
                    j->next = next_i;
                    i->previous = prev_j;
                    prev_j->next = i;
                    i->next = next_j;
                    if(next_j != nullptr) next_j->previous = i;
                    else tail = i;
                }
                else{
                    i->next = next_j;
                    j->next = next_i;
                    next_i->previous = j;
                    i->previous = prev_j;
                    prev_j->next = i;
                    j->previous = nullptr;
                    head = j;
                    if(next_j != nullptr) next_j->previous = i;
                    else tail = i;
                }
            }
            node * mark_j = j;
            j = i;
            i = mark_j;
        }
    }
    
    i = (i == nullptr)? p1 : i->next;
    if(!flag) mark_p1 = p2;  //If the min node at the end of the list, put p1 on it before swap to first position
    
    //swap((i->value), (p2->value));
    node * prev_i, *prev_p2, *next_i, *next_p2;
    prev_i = i->previous;
    prev_p2 = p2->previous;
    next_i = i->next;
    next_p2 = p2->next;
    
    int test_case = 0;
    switch(test_case = i==p2?1:2){
        case 1:
            break;    //If i=p2, do nothing
        case 2:
            if(next_i == p2){
                if(prev_i != nullptr){
                    prev_i->next = p2;
                    p2->previous = prev_i;
                    p2->next = i;
                    i->previous = p2;
                    i->next = next_p2;
                    if(next_p2 != nullptr) next_p2->previous = i;
                    else tail = i;
                }
                else{
                    i->next = next_p2;
                    i->previous = p2;
                    p2->next = i;
                    p2->previous = nullptr;
                    head = p2;
                    if(next_p2 != nullptr) next_p2->previous = i;
                    else tail = i;
                }
            }
            else{
                if(prev_i != nullptr){
                    prev_i->next = p2;
                    p2->previous = prev_i;
                    next_i->previous = p2;
                    p2->next = next_i;
                    i->previous = prev_p2;
                    prev_p2->next = i;
                    i->next = next_p2;
                    if(next_p2 != nullptr) next_p2->previous = i;
                    else tail = i;
                }
                else{
                    i->next = next_p2;
                    p2->next = next_i;
                    next_i->previous = p2;
                    i->previous = prev_p2;
                    prev_p2->next = i;
                    p2->previous = nullptr;
                    head = p2;
                    if(next_p2 != nullptr) next_p2->previous = i;
                    else tail = i;
                }
            }
            break;
    }
    //put p1 to mark_p1, which marks the position of the first element
    //put p2 to the end of the current linked list
    //put i to the current pivot
    node * mark_p2 = p2;
    p2 = i;
    i = mark_p2;
    p1 = mark_p1;
    
    //Recurrently call sort()
    node * pivot = i;
    if(p1!=nullptr && p2!= nullptr && p1 != p2 && p1 != p2->next){
        sort(p1,pivot->previous);
        sort(pivot->next,p2);
    }
}

void doubly_linked_list::make_random_list(int m, int n) {
    
    for (int i = 0; i < m; i++) {
        node * p1 = new node(rand() % n);
        p1->previous = tail;
        if (tail != nullptr) tail->next = p1;
        tail = p1;
        if (head == nullptr) head = p1;
    }
}

void doubly_linked_list::print_forward() {
    cout << endl;
    node * p1 = head;
    while (p1 != nullptr) {
        cout << p1->value << " ";
        p1 = p1->next;
    }
}

void doubly_linked_list::print_backward() {
    cout << endl;
    node * p1 = tail;
    while (p1 != nullptr) {
        cout << p1->value << " ";
        p1 = p1->previous;
    }
}

int main() {
    doubly_linked_list d1;
    d1.make_random_list(50, 20);
    d1.print_forward();
    d1.print_backward();
    
    d1.sort(d1.head, d1.tail);
    d1.print_forward();
    d1.print_backward();
    
    getchar();
    getchar();
    return 0;
}

