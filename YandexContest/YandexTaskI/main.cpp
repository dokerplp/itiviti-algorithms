#include <iostream>
#include <vector>
#include <list>
#include <set>

#define INF 500005

struct car {
    uint32_t index;
    uint32_t next;
};

std::vector<uint32_t> q;
std::vector<std::list<uint32_t>> cars;

auto cmp = [](const car& a, const car& b) { return a.next > b.next;};
std::set<car, decltype(cmp)> on_floor(cmp);


int main() {
    uint32_t n, k, p;
    std::cin >> n >> k >> p;

    q.reserve(p);
    cars.resize(n + 1);

    for (int i = 0; i < p; i++) {
        uint32_t c;
        std::cin >> c;
        q.push_back(c);
        cars[c].push_back(i);
    }

    uint32_t actions = 0;
    for (uint32_t c: q) {
        car e = {c, cars[c].front()};
        cars[c].pop_front();

        uint32_t ix = cars[c].empty() ? INF : cars[c].front();

        auto car = on_floor.end();
        if ((car = on_floor.find(e)) != on_floor.end()) {
            auto new_car = *car;
            new_car.next = ix;
            on_floor.erase(car);
            on_floor.insert(new_car);
            continue;
        }

        actions++;

        if (on_floor.size() == k) on_floor.erase(on_floor.begin());

        on_floor.insert({c, ix});
    }

    std::cout << actions;

}
