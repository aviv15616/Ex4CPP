// Demo.cpp
// anksilae@gmail.com

#include <iostream>
#include "MyContainer.hpp"

using namespace std;
using namespace containers;

int main() {
    // --------- Part 1: int -----------
    MyContainer<int> cont;

    cout << "Adding elements..." << endl;
    cont.add(7);
    cont.add(15);
    cont.add(6);
    cont.add(1);
    cont.add(2);
    cout << "Container after add: " << cont << endl;

    cout << "\nRemoving element 15..." << endl;
    cont.remove(15);
    cout << "Container after removal: " << cont << endl;

    cout << "\nTrying to remove non-existent element 100:" << endl;
    try {
        cont.remove(100);
    } catch (const exception& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    // --------- Part 2: Exception for modification during iteration -----------
    cout << "\n--- Demonstrating exception: modified during iteration ---" << endl;
    try {
        for (auto it = cont.Ascending().begin(); it != cont.Ascending().end(); ++it) {
            cout << *it << " ";
            cont.add(999); //modifying the container during iteration
        }
    } catch (const exception& e) {
        cout << "\nCaught exception during iteration: " << e.what() << endl;
    }

    // --------- Part 3: Demonstrate all 6 iterators -----------

    MyContainer<int> asc_result;
    for (auto val : cont.Ascending()) asc_result.add(val);
    cout << "\nAscendingOrder: " << asc_result << endl;

    MyContainer<int> desc_result;
    for (auto val : cont.Descending()) desc_result.add(val);
    cout << "DescendingOrder: " << desc_result << endl;

    MyContainer<int> cross_result;
    for (auto val : cont.SideCross()) cross_result.add(val);
    cout << "SideCrossOrder: " << cross_result << endl;

    MyContainer<int> mid_result;
    for (auto val : cont.MiddleOut()) mid_result.add(val);
    cout << "MiddleOutOrder: " << mid_result << endl;

    MyContainer<int> norm_result;
    for (auto val : cont.Normal()) norm_result.add(val);
    cout << "NormalOrder: " << norm_result << endl;

    MyContainer<int> rev_result;
    for (auto val : cont.Reverse()) rev_result.add(val);
    cout << "ReverseOrder: " << rev_result << endl;

    // --------- Part 4: Demonstration with std::string -----------

    cout << "\n--- String container example ---" << endl;
    MyContainer<string> strCont;
    strCont.add("banana");
    strCont.add("apple");
    strCont.add("cherry");

    cout << "Original string container: " << strCont << endl;

    MyContainer<string> normalStr;
    for (auto val : strCont.Normal()) normalStr.add(val);
    cout << "NormalOrder (string): " << normalStr << endl;

    MyContainer<string> reverseStr;
    for (auto val : strCont.Reverse()) reverseStr.add(val);
    cout << "ReverseOrder (string): " << reverseStr << endl;

    return 0;
}
