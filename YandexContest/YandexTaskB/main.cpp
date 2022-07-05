#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool trap(char animal, char trap) {
    return animal != trap && tolower(animal) == tolower(trap);
}

bool is_animal(char c) {
    return c > "Z"[0];
}

void possible(const string& ans) {
    cout << "Possible" << endl << ans;
}

void impossible() {
    cout << "Impossible";
}

int main() {
    string line;
    getline(cin, line);

    size_t string_length = line.length();

    int* ans = new int[string_length / 2];

    stack<char> letters;
    stack<int> animals;
    stack<int> traps;

    int animal_counter = 0;
    int trap_counter = 0;

    for (char c: line) {
        letters.push(c);
        if (is_animal(c)) {
            animal_counter++;
            animals.push(animal_counter);
        } else {
            trap_counter++;
            traps.push(trap_counter);
        }

        if (letters.size() < 2) continue;

        char c1 = letters.top();
        letters.pop();
        char c2 = letters.top();
        letters.pop();
        if (trap(c1, c2)) {
            ans[traps.top() - 1] = animals.top();
            animals.pop();
            traps.pop();
        } else {
            letters.push(c2);
            letters.push(c1);
        }
    }

    if (letters.empty()) {
        string res;
        for (int i = 0; i < string_length / 2; i++) {
            res += to_string(ans[i]) + " ";
        }
        possible(res);
    } else impossible();

    return 0;
}
