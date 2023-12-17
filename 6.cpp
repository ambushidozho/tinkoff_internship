#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> lazy;
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        }
        else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update(int node, int start, int end, int left, int right, int x) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start > right || end < left) {
            return;
        }

        if (start >= left && end <= right) {
            tree[node] += x;
            if (start != end) {
                lazy[2 * node] += x;
                lazy[2 * node + 1] += x;
            }
            return;
        }

        int mid = (start + end) / 2;
        update(2 * node, start, mid, left, right, x);
        update(2 * node + 1, mid + 1, end, left, right, x);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int left, int right) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start > right || end < left) {
            return numeric_limits<int>::min();  // Возвращаем минимальное значение для операции поиска максимума
        }

        if (start >= left && end <= right) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int leftMax = query(2 * node, start, mid, left, right);
        int rightMax = query(2 * node + 1, mid + 1, end, left, right);

        return max(leftMax, rightMax);
    }

    void getLeaves(int node, int start, int end, vector<int>& leaves) {
        if (start == end) {
            leaves.push_back(tree[node]);
        }
        else {
            int mid = (start + end) / 2;
            getLeaves(2 * node, start, mid, leaves);
            getLeaves(2 * node + 1, mid + 1, end, leaves);
        }
    }


public:
    SegmentTree(vector<int>& arr) {
        int n = arr.size();
        tree.resize(4 * n, numeric_limits<int>::min());  // Инициализация минимальными значениями
        lazy.resize(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    vector<int> getAllLeaves() {
        vector<int> leaves;
        getLeaves(1, 0, tree.size() / 4 - 1, leaves);
        return leaves;
    }

    void update(int left, int right, int x) {
        update(1, 0, tree.size() / 4 - 1, left, right, x);
    }

    int query(int left, int right) {
        return query(1, 0, tree.size() / 4 - 1, left, right);
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegmentTree segmentTree(arr);

    for (int i = 0; i < q; ++i) {
        char sign;
        cin >> sign;

        if (sign == '+') {
            int l, r, x;
            cin >> l >> r >> x;
            segmentTree.update(l - 1, r - 1, x);
        }
        else {
            int l, r, k, b;
            cin >> l >> r >> k >> b;
            vector<int> answer;

            answer = segmentTree.getAllLeaves();

            for (int i = l; i <= r; ++i)
            {
                answer[i - 1] = std::min(answer[i - 1], k * i + b);
            }

            SegmentTree tempTree(answer);

            cout << tempTree.query(l - 1, r - 1) << endl;
        }
    }

    return 0;
}