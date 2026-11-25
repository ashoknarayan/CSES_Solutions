#include <bits/stdc++.h>
using namespace std;

// BeginCodeSnip{FenwickTree}
struct FenwickTree {
	int size;
	vector<int> tree;

	FenwickTree(int n) : size(n), tree(n + 1, 0) {}

	// Adds delta to the element at index i (1-based)
	void add(int i, int delta) {
		while (i <= size) {
			tree[i] += delta;
			i += i & -i;
		}
	}

	// Returns the sum of elements from 1 to i
	int query(int i) {
		int sum = 0;
		while (i > 0) {
			sum += tree[i];
			i -= i & -i;
		}
		return sum;
	}
};
// EndCodeSnip

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	// Store elements as {value, original_index}
	vector<pair<int, int>> elements(n);
	for (int i = 0; i < n; i++) {
		cin >> elements[i].first;
		elements[i].second = i + 1; // 1-based indexing 
	}

	// Sort in descending order to process largest elements first
	sort(elements.rbegin(), elements.rend());

	FenwickTree ft(n);
	long long total_swaps = 0;

	for (int i = 0; i < n; i++) {
		int current_pos = elements[i].second;

		// Calculate how many larger elements are already to the left
		int left_cost = ft.query(current_pos - 1);
		
		// Calculate how many larger elements are already to the right
		// 'i' is the total count of elements processed so far
		int right_cost = i - left_cost;

		// Greedily choose the side with fewer swaps
		total_swaps += min(left_cost, right_cost);

		// Mark this position as occupied (Point Update)
		ft.add(current_pos, 1);
	}

	cout << total_swaps << endl;

	return 0;
}
