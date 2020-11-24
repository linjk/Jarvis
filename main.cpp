//
// Created by linjk on 2020/9/27.
//

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

void printUsage();

int main(int argc, char* argv[]) {
    if (2 == argc) {
        int selection;
        istringstream params(argv[1]);
        if (!(params >> selection)) {
            cerr << "Invalid input selection 「" << argv[1] << "」" << endl;
            printUsage();
        }

        switch (selection) {
            case 1:
                testing::InitGoogleTest();
                return RUN_ALL_TESTS();
            case 2:
                cout << "N/A." << endl;
                break;
            default:
                printUsage();
                break;
        }
    }
    printUsage();
    return 0;
}

void printUsage() {
    cout << "-----------------------------------" << endl;
    cout << "Usage:" << endl;
    cout << "1. Run gTest." << endl;
    cout << "-----------------------------------" << endl;
}
