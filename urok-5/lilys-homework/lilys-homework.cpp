#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int binary_search(int *array, int n, int x) {
    int l = 0, u = n, m;
    while (u - l > 1) {
        m = (l + u) / 2;
        if (array[m] <= x) l = m;
        else u = m;
    }
    return l;
}

int count_swaps(int *array, int n) {
    // for(int i = 0; i < n; ++i) cout << array[i] << ' '; cout << endl;
    int* ordered = new int[n];
    for (int i = 0; i < n; ++i) ordered[i] = array[i];
    sort(ordered, ordered+n);
    int *reduced = new int[n];
    int *idx_in_reduced = new int[n];
    for (int i = 0; i < n; ++i) {
        reduced[i] = binary_search(ordered, n, array[i]);
        idx_in_reduced[reduced[i]] = i;
    }
    // for(int i = 0; i < n; ++i) cout << reduced[i] << ' '; cout << endl;
    // for(int i = 0; i < n; ++i) cout << idx_in_reduced[i] << ' '; cout << endl;
    
    int swaps = 0;
    for (int i = 0; i < n; ++i) {
        int j = idx_in_reduced[i];
        if (i == j) continue;
        // cout << "swap " << i << ' ' << j << endl;
        swap (idx_in_reduced[reduced[i]], idx_in_reduced[reduced[j]]);
        swap (reduced[i], reduced[j]);
        // for(int i = 0; i < n; ++i) cout << reduced[i] << ' '; cout << endl;
        ++swaps;
    }
    
    return swaps;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;
    int *array = new int[n];
    for (int i = 0; i < n; ++i) cin >> array[i];
    
    int swaps1 = count_swaps(array, n);
    for (int i = 0; 2 * i < n; ++i) swap(array[i], array[n - i - 1]);
    // cout << "------\n";
    int swaps2 = count_swaps(array, n);
    
    cout << min(swaps1, swaps2) << endl;
    return 0;
}

