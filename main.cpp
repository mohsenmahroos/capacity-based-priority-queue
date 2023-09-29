#include "pque.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <queue>
#include <random>
#include <stdexcept>

using namespace std;
using namespace chrono;

template<class item_type>
inline auto& operator<<(ostream& stream, const vector<item_type>& object) {
    if (not object.empty())
        stream << object.front();
    for (int size = object.size(), i = 1; i < size; i++)
        stream << ' ' << object[i];
    return stream; }

inline int functional_test() {
    const int capacity = 15, min_key = 1, max_key = 9;
	priority_que<int> q(capacity);
	random_device device;
	mt19937 random(device());
	uniform_int_distribution<int> uniform(min_key,max_key);
	cout << "pushed:";
	for (int i = 0; i < capacity; i++) {
        const auto key = uniform(random);
        q.push(key);
        cout << ' ' << key; }
	for (cout << endl << "container:" << endl; !q.empty(); q.pop())
        cout << q() << endl;
    return 0; }

template<class container>
inline auto run(container& q, int input[], int capacity, int output[]) {
	using clock = high_resolution_clock;
    const double scale = 1e-3;
    const auto start_time = clock::now();
    int count = 0;
    for (int i = 0; i < capacity; i++)
        q.push(input[i]);
    for (; !q.empty(); q.pop())
        output[count++] = q.top();
    if (count != capacity)
        throw 0;
    const auto duration = duration_cast<milliseconds>(clock::now()-start_time);
    return scale*duration.count(); }

inline int performance_test() {
    const int capacity = 2e5, number_of_tests = 2e2;
    const string error[] = {"size","value"};
    priority_queue<int> std;
    priority_que<int> imp(capacity);
    random_device device;
	mt19937 random(device());
    auto input      = new int[capacity];
    auto std_output = new int[capacity];
    auto imp_output = new int[capacity];
    double std_time = 0, imp_time = 0;
    try {
        for (int tests = 0; tests < number_of_tests; tests++) {
            cout << '.', cout.flush();
            for (int i = 0; i < capacity; i++)
                input[i] = random();
            std_time += run(std,input,capacity,std_output),
            imp_time += run(imp,input,capacity,imp_output);
            for (int i = 0; i < capacity; i++)
                if (imp_output[i] != std_output[i])
                    throw 1; } }
    catch (int type) {
        cout << "invalid output data " << error[type] << endl;
        return 1; }
    cout << fixed << setprecision(2) << endl;
    cout << "time(std) = " << std_time << " sec." << endl;
    cout << "time(imp) = " << imp_time << " sec." << endl;
    cout << "performance improvement = " << 100.0*(std_time-imp_time)/std_time << '%';
    return 0; }

int main() { return performance_test(); }
