#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int seq[1000001];
vector <int> digit, cnt, digits_before;

int main() {
    int n;
    cin >> n;
    int currdigit, prevdigit;
    cin >> seq[0];
    int curr_count = 1, total_count = 0;
    for (int i = 1; i < n; ++i) { // Find the digits (without repeating them) and how many times they repeat
        cin >> seq[i];
        if (seq[i] == seq[i - 1]) curr_count ++;
        else {
            digit.push_back(seq[i - 1]);
            cnt.push_back(curr_count);
            digits_before.push_back(total_count);
            total_count += curr_count;
            curr_count = 1;
        }
    }
    
    digit.push_back(seq[n - 1]);
    digits_before.push_back(total_count);
    cnt.push_back(curr_count);
    
    // Find the length of the number
    int maxlen = 0, maxbeg, maxend; // length, idx of beginning, and idx after end of largest number
    for (int i = 0; i < digit.size(); ++i) // Consider single-digit numbers first
        if (digit[i] != 0 && maxlen < cnt[i]) {
            maxlen = cnt[i];
            maxbeg = digits_before[i];
            maxend = digits_before[i] + cnt[i];
        }
    
    //Now consider multi-digit numbers
    int first_idx = 0, last_idx, k, length; // first and last idx (in 'digit') incl, k and length for current num
    while(first_idx < digit.size() - 1) { // Don't start at the end, since searching multi-digit
        if (digit[first_idx] == 0) ++first_idx;
        else { // A number can begin here; find the end
            last_idx = first_idx + 1;
            k = min(cnt[first_idx], cnt[first_idx + 1]);
            while (last_idx < digit.size() && cnt[last_idx] == k) ++last_idx;
            if (last_idx == digit.size() || cnt[last_idx] < k) --last_idx;
            length = (last_idx - first_idx + 1) * k;
            int currbeg = digits_before[first_idx] + cnt[first_idx] - k;
            
            if(length > maxlen) {
                maxlen = length;
                maxbeg = currbeg;
                maxend = currbeg + length;
            }
            else if (length == maxlen) {
                bool is_curr_bigger = false;
                for (int curri = currbeg, maxi = maxbeg; maxi < maxend; ++curri, ++maxi) {
                    if (seq[curri] < seq[maxi]) break;
                    if (seq[curri] > seq[maxi]) { is_curr_bigger = true; break; }
                }
                if (is_curr_bigger) {
                    maxbeg = currbeg;
                    maxend = currbeg + length;
                }
            }
            first_idx = last_idx;
        }
    }
    
    if (maxlen == 0) cout << 0 << endl;
    else {
        for (int i = maxbeg; i < maxend; ++i) cout << seq[i];
        cout << endl;
    }
    return 0;
}

