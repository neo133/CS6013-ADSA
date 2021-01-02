//EE19MTECH01008:- Question2

#include <iostream>
using namespace std; 

int inv_merge(int array[], int first, int last){

    int mid = (first+last)/2;
    int x = first;
    int y = mid+1;
    int t = last-first+1;
    int f[t], i1=0;
    int inv = 0, i;

    while (x <= mid && y <= last) {
        if (array[x] <= array[y]) {
                f[i1++] = array[x++];
        } else {
                f[i1++] = array[y++];
                inv += mid - x + 1;
        }
    }

    while (x <= mid)
        f[i1++] = array[x++];

    while (y <= last) 
        f[i1++] = array[y++];

    for (i=0 ; i<last-first+1 ; i++)
        array[i+first] = f[i];      

    return inv;
}

int inv_count(int array[], int a, int b){

    int x, y, z, mid;
    if (a >= b) 
        return 0;
    mid = (a+b)/2;
    
    x = inv_count(array, a, mid);
    y = inv_count(array, mid+1, b);
    z = inv_merge(array, a, b);

    return x+y+z;
}

int main()
{   
    int n,inv;
    cin>>n;
    int a[n];
    for (int i =0;i<n;i++){
        cin>>a[i];
      }
    inv = inv_count(a, 0, n-1);
    cout << inv << endl;          
    return 0;   
}