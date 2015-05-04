#include <iostream>
#include <queue>
#include <utility>

using namespace std;

void PrePrimes(int m, int n, int k) {
    if (m + n <= k) {
        cout << m << ' ' << n << endl;
        PrePrimes(2*m - n, m, k);
        PrePrimes(2*m + n, m, k);
        PrePrimes(m + 2*n, n, k);
    }
    return;
}

void PostPrimes(int m, int n, int k) {
    if (m + n <= k) {
        PostPrimes(2*m - n, m, k);
        PostPrimes(2*m + n, m, k);
        PostPrimes(m + 2*n, n, k);
        cout << m << ' ' << n << endl;
    }
    return;
}

void dumpStack(priority_queue<pair<int, int>>& entryStack) {
    if (entryStack.empty()) return;
    pair<int, int> values = make_pair(get<0>(entryStack.top()), get<1>(entryStack.top()));
    entryStack.pop();
    dumpStack(entryStack);
    cout << get<0>(values) << ' ' << get<1>(values) << endl;
    return;
}

void SortedPrimes(int k) {
    static priority_queue<pair<int, int>> entryStack;
    queue<pair<int,int>> currStack;
    queue<pair<int,int>> tempQueue;
    pair<int, int> entry;
    pair<int, int> entry2;
    
    entry = make_pair(2, 1);
    entryStack.push(entry);
    currStack.push(entry);
    entry = make_pair(3, 1);
    entryStack.push(entry);
    currStack.push(entry);
    
    while(!entryStack.empty()) {
        dumpStack(entryStack); // This empties the stack
        while(!currStack.empty()) {
            if (2 * get<0>(currStack.front()) - get<1>(currStack.front()) + get<0>(currStack.front()) <= k) {
                entry = make_pair(2 * get<0>(currStack.front()) - get<1>(currStack.front()), get<0>(currStack.front())); // 2m + n, m
                entryStack.push(entry);
                tempQueue.push(entry);
            }
            if (2 * get<0>(currStack.front()) + get<1>(currStack.front()) + get<0>(currStack.front()) <= k) {
                entry = make_pair(2 * get<0>(currStack.front()) + get<1>(currStack.front()), get<0>(currStack.front()));
                entryStack.push(entry);
                tempQueue.push(entry);
            }
            if (get<0>(currStack.front()) + 2 * get<1>(currStack.front()) + get<1>(currStack.front()) <= k) {
                entry = make_pair(get<0>(currStack.front()) + 2 * get<1>(currStack.front()), get<1>(currStack.front()));
                entryStack.push(entry);
                tempQueue.push(entry);
            }
            currStack.pop();
        }
        
        while(!tempQueue.empty()) {
            currStack.push(tempQueue.front());
            tempQueue.pop();
        }
    }
    //store valid pairs for later?
    return;
}