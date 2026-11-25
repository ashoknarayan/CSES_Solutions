#include <iostream>
#include <numeric>   // For C++17 std::gcd
#include <algorithm> // For std::min, std::max
#include <utility>   // For std::swap

// Use long long for all calculations to prevent integer overflow
using ll = long long;

// Custom gcd function for broader C++ version compatibility
ll custom_gcd(ll a, ll b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

// Function to calculate lcm using gcd, preventing overflow
ll custom_lcm(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    if (a == 1) return b;
    if (b == 1) return a;
    return (a / custom_gcd(a, b)) * b;
}

// Counts numbers x in [0, limit] where x % mod == rem
ll count_rem(ll limit, ll mod, ll rem) {
    if (rem > limit) {
        return 0;
    }
    return (limit - rem) / mod + 1;
}

void solve() {
    ll n, m;
    std::cin >> n >> m;

    ll N = n - 1;
    ll M = m - 1;

    // Part 1: Steps calculation
    ll steps = 2 * custom_lcm(N, M);

    // Part 2: Visited cells calculation using O(1) formulas
    ll d = custom_gcd(N, M);
    ll g = 2 * d;

    // O(1) calculation for C_eq = Count(i = j mod g)
    ll C_eq = 0;
    {
        ll qN = N / g, rN = N % g;
        ll qM = M / g, rM = M % g;
        
        ll p1 = std::min(rN, rM), p2 = std::max(rN, rM);
        
        C_eq += (p1 + 1) * (qN + 1) * (qM + 1);
        if (p2 > p1) {
            C_eq += (p2 - p1) * (rN < rM ? qN * (qM + 1) : (qN + 1) * qM);
        }
        if (g - 1 > p2) {
            C_eq += (g - 1 - p2) * qN * qM;
        }
    }
    
    // O(1) calculation for C_neg = Count(i + j = 0 mod g)
    ll C_neg = 0;
    {
        ll qN = N / g, rN = N % g;
        ll qM = M / g, rM = M % g;
        
        // k=0 term
        C_neg += count_rem(N, g, 0) * count_rem(M, g, 0);

        // Sum over k in [1, g-1]
        ll p1 = rN;
        ll p2 = g - rM;

        if (g > 1) {
            if (p1 < p2 - 1) { // three intervals
                C_neg += p1 * (qN + 1) * qM;
                C_neg += (p2 - 1 - p1) * qN * qM;
                C_neg += (g - p2) * qN * (qM + 1);
            } else { // two intervals
                C_neg += (p2 - 1) * (qN + 1) * qM;
                C_neg += (p1 - p2 + 1) * (qN + 1) * (qM + 1);
                if (g - 1 > p1) {
                    C_neg += (g - 1 - p1) * qN * (qM + 1);
                }
            }
        }
    }

    // O(1) calculation for C_int = Count(both conditions are true)
    ll C_int = 0;
    {
        ll num_multiples_of_d = (M / d) + 1;
        ll count_j_rem_0 = (num_multiples_of_d + 1) / 2;
        ll count_j_rem_d = num_multiples_of_d / 2;
        C_int = count_j_rem_0 * count_rem(N, g, 0) + count_j_rem_d * count_rem(N, g, d);
    }
    
    ll visited_cells = C_eq + C_neg - C_int;

    std::cout << steps << " " << visited_cells << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
