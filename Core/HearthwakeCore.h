#pragma once
#include <cstdint>
#include <limits>
#include <map>
#include <string>
#include <vector>

namespace hearthwake {
enum class Outcome { Applied, Invalid, Capacity, Conflict, SessionFull };
struct Request { std::uint64_t id; std::string item; int delta; };
class Inventory {
public:
    explicit Inventory(int capacity, std::size_t requestLimit = 4096) : capacity_(capacity), requestLimit_(requestLimit) {}
    Outcome apply(const Request& request) {
        if (request.id == 0 || request.item.empty() || request.item.size() > 64 || request.delta == 0) return Outcome::Invalid;
        const auto seen = requests_.find(request.id);
        if (seen != requests_.end()) {
            return seen->second.request.item == request.item && seen->second.request.delta == request.delta ? seen->second.result : Outcome::Conflict;
        }
        if (requests_.size() >= requestLimit_) return Outcome::SessionFull;
        Outcome result = Outcome::Applied;
        const auto item = items_.find(request.item);
        const int current = item == items_.end() ? 0 : item->second;
        const std::int64_t next = static_cast<std::int64_t>(current) + request.delta;
        const std::int64_t newTotal = static_cast<std::int64_t>(total_) + request.delta;
        if (next < 0 || next > std::numeric_limits<int>::max()) result = Outcome::Invalid;
        else if (newTotal > capacity_ || capacity_ < 0) result = Outcome::Capacity;
        if (result == Outcome::Applied) {
            if (next == 0) items_.erase(request.item); else items_[request.item] = static_cast<int>(next);
            total_ = static_cast<int>(newTotal);
        }
        // Failed intents are also remembered: retries never change their outcome.
        requests_.emplace(request.id, Recorded{request, result}); return result;
    }
    int count(const std::string& item) const { const auto found = items_.find(item); return found == items_.end() ? 0 : found->second; }
    int total() const { return total_; }
private:
    struct Recorded { Request request; Outcome result; };
    int capacity_; int total_ = 0; std::size_t requestLimit_;
    std::map<std::string, int> items_;
    std::map<std::uint64_t, Recorded> requests_;
};
}
