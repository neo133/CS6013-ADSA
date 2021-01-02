/* Assignment 2 ADSA */
/* Dynamic 2-SUM */

#include <bits/stdc++.h> 
using namespace std; 

// linked list defined
class node {

public: 
    int data; 
    node* next; 
}; 

//insert values in a sorted fashion
void sortedInsert(node** head_ref, node* new_node){ 

    node* current; 
    // Special case for the head end 
    if (*head_ref == NULL 
        || (*head_ref)->data 
            >= new_node->data) { 
        new_node->next = *head_ref; 
        *head_ref = new_node; 
    } 
    else{ 
        current = *head_ref; 
        while (current->next != NULL && current->next->data < new_node->data) { 
            current = current->next; 
        } 
        new_node->next = current->next; 
        current->next = new_node; 
    } 
} 

// new node to add in linked list
node* newNode(int new_data){ 
    /* allocate node */
    node* new_node = new node(); 

    /* put in the data */
    new_node->data = new_data; 
    new_node->next = NULL; 

    return new_node; 
} 

// delete node function to delete a value
void deleteNode(node** head_ref, int key){ 
      
    // Store head node 
    node* temp = *head_ref; 
    node* prev = NULL; 
      
    // If head node key needs to be deleted
    if (temp != NULL && temp->data == key){ 
        *head_ref = temp->next; // Changed head 
        delete temp;            // free old head 
        return; 
    } 
  
    // Else Search for the key to be deleted,  
    while (temp != NULL && temp->data != key){ 
        prev = temp; 
        temp = temp->next; 
    } 
  
    // If key was not present in linked list 
    if (temp == NULL) 
        return; 
  
    // Unlink the node from linked list 
    prev->next = temp->next; 
  
    // Free memory 
    delete temp; 
} 

// length of the Linked List 
int findlength(node* head){

    node* curr = head; 
    int cnt = 0; 
    while (curr != NULL) { 
        cnt++; 
        curr = curr->next; 
    } 
    return cnt; 
} 
// binary search to find the upper bound of y
int upper_bound(int arr[], int l, int r, int x){ 

    if (r >= l){ 
       int mid = l + (r - l) / 2; 
        if (arr[mid] ==x ){
            return mid+1;
         }
        if (arr[mid] > x){
            return upper_bound(arr, l, mid - 1, x);   
        }
        return upper_bound(arr, mid + 1, r, x); 
    } 
    return max(r,l);
}
//binary search to find the lower bound of y
int lower_bound(int arr[], int l, int r, int x){

    if (r >= l){ 
       int mid = l + (r - l) / 2; 
        if (arr[mid] ==x ){
            return mid-1;
         }
        if (arr[mid] > x){
            return lower_bound(arr, l, mid - 1, x);   
        }
        return lower_bound(arr, mid + 1, r, x); 
    } 
    return min(r,l); 
}

// Query function as stated in the question
void aquery(int arr[],int arr1[],int ind1,int ind2,int a,int b){

        int cnt=0;
    // finds the lower and upper bound of y=t-x using binary search for the given a,b bound
        for(int i=0; i<ind1-1;i++){
            int lower=lower_bound(arr, i+1,ind1-1,a-arr[i]);
            int upper=upper_bound(arr, i+1,ind1-1,b-arr[i]);
            cnt=cnt+upper-lower-1;
        }
    //this loop takes care of the duplicate entries and adds the duplicate elements
        for(int i=0; i<ind2;i++){
            int temp1=arr[arr1[i]]+arr[arr1[i]];
            if(temp1>=a && temp1<=b ){
                cnt++;
            }
        }

        cout<<cnt<<endl;
    
}

// Driver program
int main(){ 

    string chaar;
    int n,d,cnt,i,a,b;
    node* head = NULL; 
    while(1){
        cin>>chaar;
        if (chaar=="I"){
            cin>>n;
            node* new_node = newNode(n); 
            sortedInsert(&head, new_node);
        }
        else if (chaar == "D"){
            cin>>n;
            deleteNode(&head, n);
        }
        else if (chaar == "Q"){
            cin>>a>>b;
            int len = findlength(head); 
          
            // Create an array of the 
            // required length 
            int arr[len]; //array to store linked list distinct keys
            int arr1[len]; //array to store the indexes of the repeated keys
            int index = 0,index1=0,old_index=0; 
            node* curr = head; 
            if(curr==NULL){
                cout<<0<<endl;                
            }
            else{
            // linked list to array with duplicates taken care of
            int duplicate=curr->data+100;
                for (int i =0;i<len;i++){
               
                if(duplicate!=curr->data){ 
                    arr[index++] = curr->data; //copies the distinct linked list keys into the array
                    duplicate=curr->data;
                    curr = curr->next; 
                } 
                else if(old_index!=index){
                    arr1[index1++]=index-1; //this copies the index of the duplicate elements in the first array
                    old_index=index; 
                    curr = curr->next; 
                }
                else{
                    curr = curr->next; 
                }
            }
                      
            aquery(arr,arr1,index,index1,a,b);}
        }
        else if (chaar=="E"){
            break;
        }
    }

    return 0; 
}
