#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

const long long INF = 4e18; // A large value for infinity

// Struct to represent a campsite point
struct Point {
    int x, y;
    int type; // 0 for reserved, 1 for free
    int id;   // Original index for free campsites
};

// A standard segment tree for range maximum queries
std::vector<long long> seg_tree;
int tree_size;

void update(int idx, long long val, int node, int start, int end) {
    if (start == end) {
        seg_tree[node] = std::max(seg_tree[node], val);
        return;
    }
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid) {
        update(idx, val, 2 * node, start, mid);
    } else {
        update(idx, val, 2 * node + 1, mid + 1, end);
    }
    seg_tree[node] = std::max(seg_tree[2 * node], seg_tree[2 * node + 1]);
}

long long query(int l, int r, int node, int start, int end) {
    if (r < start || end < l || l > r) {
        return -INF;
    }
    if (l <= start && end <= r) {
        return seg_tree[node];
    }
    int mid = (start + end) / 2;
    long long p1 = query(l, r, 2 * node, start, mid);
    long long p2 = query(l, r, 2 * node + 1, mid + 1, end);
    return std::max(p1, p2);
}

// The main sweep-line logic, parameterized for all 4 cases
void run_sweep(std::vector<Point>& all_points, std::vector<long long>& results, 
               const std::map<int, int>& y_map, int x_sign, int y_sign) {
    
    // Sort points based on the sweep direction (controlled by x_sign)
    std::sort(all_points.begin(), all_points.end(), [&](const Point& a, const Point& b) {
        if (a.x * x_sign != b.x * x_sign) {
            return a.x * x_sign < b.x * x_sign;
        }
        return a.type < b.type; // Process reserved sites first
    });

    // Initialize segment tree for this run
    seg_tree.assign(4 * tree_size, -INF);

    for (const auto& p : all_points) {
        int comp_y = y_map.at(p.y);
        if (p.type == 0) { // Reserved site
            long long val = (long long)p.x * x_sign + (long long)p.y * y_sign;
            update(comp_y, val, 1, 1, tree_size);
        } else { // Free site
            long long max_val;
            if (y_sign == 1) { // Querying y <= y_f
                max_val = query(1, comp_y, 1, 1, tree_size);
            } else { // Querying y > y_f
                max_val = query(comp_y, tree_size, 1, 1, tree_size);
            }

            if (max_val != -INF) {
                long long current_dist = ((long long)p.x * x_sign + (long long)p.y * y_sign) - max_val;
                results[p.id] = std::min(results[p.id], current_dist);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    std::vector<Point> all_points;
    std::vector<int> y_coords;

    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        all_points.push_back({x, y, 0, -1});
        y_coords.push_back(y);
    }
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        all_points.push_back({x, y, 1, i});
        y_coords.push_back(y);
    }

    // Coordinate Compression
    std::sort(y_coords.begin(), y_coords.end());
    y_coords.erase(std::unique(y_coords.begin(), y_coords.end()), y_coords.end());
    std::map<int, int> y_map;
    tree_size = y_coords.size();
    for (int i = 0; i < tree_size; ++i) {
        y_map[y_coords[i]] = i + 1;
    }

    std::vector<long long> results(m, INF);

    // Run the sweep-line for all 4 cases
    run_sweep(all_points, results, y_map, 1, 1);    // x_r <= x_f, y_r <= y_f
    run_sweep(all_points, results, y_map, 1, -1);   // x_r <= x_f, y_r > y_f
    run_sweep(all_points, results, y_map, -1, 1);   // x_r > x_f, y_r <= y_f
    run_sweep(all_points, results, y_map, -1, -1);  // x_r > x_f, y_r > y_f

    for (int i = 0; i < m; ++i) {
        std::cout << results[i] << (i == m - 1 ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}
