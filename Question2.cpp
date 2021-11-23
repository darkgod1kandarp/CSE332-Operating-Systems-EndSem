
// calling library 
#include<bits/stdc++.h>
using namespace std;
 

int size;

// Map used as hash map to store the value in (key -value format)
map<int, int> mapping;
 
//declaring vecctor globally
vector<pair<int, int>> vect1[10000];
 

 
void Buddy(int s)
{
     
    // Maximum number of powers of 2 possible
    int n = ceil(log(s) / log(2));
     
    size = n + 1;
    for(int i = 0; i <= n; i++)
        vect1[i].clear();
 
    // Initially whole block of specified
    // size is available
    vect1[n].push_back(make_pair(0, s - 1));
}
 
void allocate(int s)
{
     
    // Calculate index in free list
    // to search for block if available
    int x = ceil(log(s) / log(2));
     
    // Block available
    if (vect1[x].size() > 0)
    {
        pair<int, int> temp = vect1[x][0];
 
        // Remove block from free list
        vect1[x].erase(vect1[x].begin());
         
        cout << "Memory from " << temp.first
             << " to " << temp.second
             << " allocated" << "\n";
 
        // Map starting address with
        // size to make deallocating easy
        mapping[temp.first] = temp.second -
                         temp.first + 1;
    }
    else
    {
        int i;
         
        // If not, search for a larger block
        for(i = x + 1; i < size; i++)
        {
             
            // Find block size greater
            // than request
            if (vect1[i].size() != 0)
                break;
        }
 
        // If no such block is found
        // i.e., no memory block available
        if (i == size)
        {
            cout << "Sorry, failed to allocate memory\n";
        }
         
        // If found
        else
        {
            pair<int, int> temp;
            temp = vect1[i][0];
 
            // Remove first block to split
            // it into halves
            vect1[i].erase(vect1[i].begin());
            i--;
             
            for(;i >= x; i--)
            {
                 
                // Divide block into two halves
                pair<int, int> pair1, pair2;
                pair1 = make_pair(temp.first,
                                  temp.first +
                                 (temp.second -
                                  temp.first) / 2);
                pair2 = make_pair(temp.first +
                                 (temp.second -
                                  temp.first + 1) / 2,
                                  temp.second);
                                  
                vect1[i].push_back(pair1);
 
                // Push them in free list
                vect1[i].push_back(pair2);
                temp = vect1[i][0];
 
                // Remove first free block to
                // further split
                vect1[i].erase(vect1[i].begin());
            }
             
            cout << "Memory from " << temp.first
                 << " to " << temp.second
                 << " allocate" << "\n";
                  
            mapping[temp.first] = temp.second -
                             temp.first + 1;
        }
    }
}
 
void deallocate(int id)
{
     
    // If no such starting address available
    if(mapping.find(id) == mapping.end())
    {
        cout << "Sorry, invalid free request\n";
        return;
    }
     
    // Size of block to be searched
    int n = ceil(log(mapping[id]) / log(2));
     
    int i, buddyNumber, buddyAddress;
 
    // Add the block in free list
    vect1[n].push_back(make_pair(id,
                               id + pow(2, n) - 1));
    cout << "Memory block from " << id
         << " to "<< id + pow(2, n) - 1
         << " freed\n";
 
    // Calculate buddy number
    buddyNumber = id / mapping[id];
 
    if (buddyNumber % 2 != 0)
        buddyAddress = id - pow(2, n);
    else
        buddyAddress = id + pow(2, n);
         
    // Search in free list to find it's buddy
    for(i = 0; i < vect1[n].size(); i++)
    {
         
        // If buddy found and is also free
        if (vect1[n][i].first == buddyAddress)
        {
             
            // Now merge the buddies to make
            // them one large free memory block
            if (buddyNumber % 2 == 0)
            {
                vect1[n + 1].push_back(make_pair(id,
                   id + 2 * (pow(2, n) - 1)));
                    
                cout << "Coalescing of blocks starting at "
                     << id << " and " << buddyAddress
                     << " was done" << "\n";
            }
            else
            {
                vect1[n + 1].push_back(make_pair(
                    buddyAddress, buddyAddress +
                    2 * (pow(2, n))));
                     
                cout << "Coalescing of blocks starting at "
                     << buddyAddress << " and "
                     << id << " was done" << "\n";
            }
            vect1[n].erase(vect1[n].begin() + i);
            vect1[n].erase(vect1[n].begin() +
            vect1[n].size() - 1);
            break;
        }
    }
 
    // Remove the key existence from map
    mapping.erase(id);
}
 
// main component
int main()
{
     
    
    Buddy(128);
    allocate(16);
    allocate(16);
    allocate(16);
    allocate(16);
    deallocate(0);
    deallocate(9);
    deallocate(32);
    deallocate(16);
 
    return 0;
}
 