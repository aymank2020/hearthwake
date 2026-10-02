#include "HearthwakeCore.h"
#include <iostream>
#include <stdexcept>
static void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }
static void tests() {
    using hearthwake::Outcome;
    hearthwake::Inventory inventory(10);
    check(inventory.apply({1, "wood", 4}) == Outcome::Applied, "gather intent");
    check(inventory.apply({1, "wood", 4}) == Outcome::Applied && inventory.count("wood") == 4, "retry cannot duplicate");
    check(inventory.apply({1, "stone", 4}) == Outcome::Conflict && inventory.count("stone") == 0, "changed request ID");
    check(inventory.apply({2, "wood", -5}) == Outcome::Invalid && inventory.total() == 4, "no negative stack");
    check(inventory.apply({3, "stone", 7}) == Outcome::Capacity, "capacity rejection");
    check(inventory.apply({4, "wood", -4}) == Outcome::Applied && inventory.total() == 0, "consume stack");
    check(inventory.apply({3, "stone", 7}) == Outcome::Capacity && inventory.total() == 0, "failed retry remains failed");
    check(inventory.apply({0, "wood", 1}) == Outcome::Invalid, "request IDs are required");
    check(inventory.apply({5, "wood", 2147483647}) == Outcome::Capacity, "overflow-safe capacity");
    hearthwake::Inventory bounded(10, 1);
    check(bounded.apply({1, "wood", 1}) == Outcome::Applied && bounded.apply({2, "wood", 1}) == Outcome::SessionFull, "bounded request history");
    check(bounded.apply({1, "wood", 1}) == Outcome::Applied && bounded.total() == 1, "retry after session full");
}
int main(int argc, char** argv) {
    try {
        if (argc == 2 && std::string(argv[1]) == "--self-test") { tests(); std::cout << "Hearthwake core checks passed\n"; return 0; }
        if (argc != 1) { std::cerr << "Usage: core-demo [--self-test]\n"; return 2; }
        hearthwake::Inventory server(10);
        const hearthwake::Request gather{42, "wood", 4}; server.apply(gather); server.apply(gather);
        std::cout << "wood=" << server.count("wood") << " total=" << server.total() << " retry=deduplicated\n";
    } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
