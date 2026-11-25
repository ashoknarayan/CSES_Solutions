#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

// Function to calculate cross product of two vectors AB and AC
int crossProduct(pair<int, int> A, pair<int, int> B, pair<int, int> C)
{
    int ABx = B.first - A.first; // x component of vector AB
    int ABy = B.second - A.second; // y component of vector AB
    int ACx = C.first - A.first; // x component of vector AC
    int ACy = C.second - A.second; // y component of vector AC
    return ABx * ACy - ABy * ACx; // Cross product of AB and AC
}

// Function to compare two points
bool comparePoints(const pair<int, int>& a, const pair<int, int>& b)
{
    return (a.first == b.first) ? (a.second < b.second) : (a.first < b.first);
}

// Function to check if point C lies between points A and B
bool isMidPoint(pair<int, int> A, pair<int, int> B, pair<int, int> C)
{
    vector<pair<int, int>> points = {A, B, C};
    sort(points.begin(), points.end(), comparePoints);
    return (points[1] == C); // C should be the middle point
}

// Function to get the sign of a number
int sign(int x)
{
    return (x > 0) - (x < 0);
}

// Function to check if line segments AB and CD intersect
bool doIntersect(pair<int, int> A, pair<int, int> B, pair<int, int> C, pair<int, int> D)
{
    int cross1 = crossProduct(A, B, C);
    int cross2 = crossProduct(A, B, D);
    int cross3 = crossProduct(C, D, A);
    int cross4 = crossProduct(C, D, B);

    // Check for collinearity and whether points lie on the segment
    if (cross1 == 0 && isMidPoint(A, B, C)) return true;
    if (cross2 == 0 && isMidPoint(A, B, D)) return true;
    if (cross3 == 0 && isMidPoint(C, D, A)) return true;
    if (cross4 == 0 && isMidPoint(C, D, B)) return true;

    // General case: check if the segments straddle each other
    return (sign(cross1) != sign(cross2)) && (sign(cross3) != sign(cross4));
}

void solve()
{
    // Input the coordinates of the points
    pair<int, int> A, B, C, D;
    cin >> A.first >> A.second >> B.first >> B.second >> C.first >> C.second >> D.first >> D.second;

    // Check if the line segments intersect
    cout << (doIntersect(A, B, C, D) ? "YES" : "NO") << endl;
    return;
}

signed main()
{
    int testCases;
    cin >> testCases;
    while (testCases--) solve(); // Process each test case
    return 0;
}
