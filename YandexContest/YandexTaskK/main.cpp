#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct block {
    int64_t index;
    int64_t len;
    bool free;
};

list<block> blocks;
unordered_map<int64_t , list<block>::iterator> block_indexes;
unordered_map<int64_t , int64_t> requests;
vector<int64_t> priorities;
unordered_set<int64_t> added;
unordered_map<int64_t, int64_t> ix_to_prior;

bool cmp(int64_t b, int64_t a) {
    if (block_indexes.find(a) != block_indexes.end() && block_indexes.find(b) != block_indexes.end()) {

        auto a_block = block_indexes[a];
        auto b_block = block_indexes[b];

        if (a_block->free && b_block->free) {
            return (a_block->len != b_block->len) ? a_block->len > b_block->len :
                   a_block->index < b_block->index;
        } else return a_block->free;
    } else {
        return block_indexes.find(a) != block_indexes.end();
    }
}

//void prt(string s) {
//    cerr << s << endl;
//    for (int64_t i: priorities) cerr << i << " ";
//    cerr << endl;
//}

int64_t parent(int64_t i) {
    return (i - 1) / 2;
}

int64_t left(int64_t i) {
    return 2 * i + 1;
}

int64_t right(int64_t i) {
    return 2 * i + 2;
}

void ix_swap(int64_t a, int64_t b) {
    int64_t k = ix_to_prior[a];
    ix_to_prior[a] = ix_to_prior[b];
    ix_to_prior[b] = k;
}

void sift_up(int64_t i) {
    while (i > 0 && cmp(priorities[parent(i)], priorities[i])) {
        swap(priorities[i], priorities[parent(i)]);
        ix_swap(priorities[i], priorities[parent(i)]);
        i = parent(i);
    }
}

void sift_down(int64_t i) {
    int64_t size = priorities.size();
    while (left(i) < size) {
        int64_t j = (right(i) < size && cmp(priorities[left(i)], priorities[right(i)])) ? right(i) : left(i);
        if (cmp(priorities[j], priorities[i])) break;
        swap(priorities[i], priorities[j]);
        ix_swap(priorities[i], priorities[j]);
        i = j;
    }
}

void normalize(int64_t ix) {
    int64_t i = ix_to_prior[ix];
    if (i > 0 && cmp(priorities[parent(i)], priorities[i])) sift_up(i);
    else sift_down(i);
}

void heapify() {
    for (int64_t i = priorities.size() / 2 - 1; i >= 0; --i) sift_down(i);
}

int main() {
    int64_t n, m;
    cin >> n >> m;

    blocks.push_back({1, n, true});
    block_indexes[1] = blocks.begin();

    priorities.push_back(1);
    priorities.push_back(2);
    added.insert(1);
    added.insert(2);
    ix_to_prior[1] = 0;
    ix_to_prior[2] = 1;

    for (int i = 0; i < m; i++) {
        int e;
        cin >> e;

        //heapify();
        if (e > 0) {
            int64_t ix = priorities[0];
            auto b = block_indexes[ix];
            if (!b->free || b->len < e) cout << -1 << endl;
            else {
                if (b->len == e) {
                    b->free = false;
                    normalize(b->index);
                }
                else {
                    int64_t b_len = b->len;
                    b->len = e;
                    b->free = false;

                    normalize(b->index);

                    blocks.insert(++b, {ix + e, b_len - e, true});
                    block_indexes[ix + e] = --b;
                    if (added.find(ix + e) == added.end()) {
                        priorities.push_back(ix + e);
                        added.insert(ix + e);
                        ix_to_prior[ix + e] = priorities.size() - 1;
                    }

                    normalize(ix + e);
                }
                requests[i + 1] = ix;
                cout << ix << endl;
            }
        } else {
            int64_t ix = requests[-e];
            if (ix == 0) continue;
            requests.erase(-e);

            auto b = block_indexes[ix];
            bool prev = (b != blocks.begin());
            bool next = (b != --blocks.end());

            b->free = true;

            normalize(b->index);

            if (next) {
                auto next_block = ++b;
                --b;
                if (next_block->free) {
                    b->len += next_block->len;

                    normalize(b->index);

                    block_indexes.erase(next_block->index);
                    blocks.erase(next_block);

                    normalize(next_block->index);
                }
            }

            if (prev) {
                auto prev_block = --b;
                ++b;
                if (prev_block->free) {
                    prev_block->len += b->len;

                    normalize(prev_block->index);

                    block_indexes.erase(b->index);
                    blocks.erase(b);

                    normalize(b->index);
                }
            }
        }
    }

    return 0;
}

