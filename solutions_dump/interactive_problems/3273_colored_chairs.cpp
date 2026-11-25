#include <iostream>
#include <string>
#include <vector> // Not strictly needed but good practice

// Function to flush output
void flush_output() {
    std::cout << std::flush;
}

int main() {
    // Optimize C++ standard streams for speed
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // Query chair 1
    char color1;
    std::cout << "? 1\n";
    flush_output();
    std::cin >> color1;

    // Query chair n
    char colorN;
    std::cout << "? " << n << "\n";
    flush_output();
    std::cin >> colorN;

    // If chairs 1 and n have the same color, report chair n (meaning n and 1 are same)
    if (color1 == colorN) {
        std::cout << "! " << n << "\n";
        flush_output();
        return 0;
    }
    int left = 1;
    int right = n;
    char current_color_left = color1;
    char current_color_right_placeholder = colorN;
    while (true) {
        if (right - left == 1) {
            std::cout << "! " << left << "\n";
            flush_output();
            return 0;
        }
        int mid = left + (right - left) / 2;
        char color_mid;
        std::cout << "? " << mid << "\n";
        flush_output();
        std::cin >> color_mid;
        if ((current_color_left == color_mid && (mid - left + 1) % 2 == 0) ||
            (current_color_left != color_mid && (mid - left + 1) % 2 == 1)) {
            right = mid;
        } else {
            left = mid;
            current_color_left = color_mid; 
        }
    }

    return 0;
}
