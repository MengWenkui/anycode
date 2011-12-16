#include <iostream>
#include <fstream>
#include "index.pb.h"

using namespace std;

int main()
{
    ofstream output("index.txt", ios::out | ios::trunc | ios::binary);
    for(int i = 0; i < 4; i++) {
       index_msg_t idx;
       idx.set_flag(i);
       idx.set_magic(i);
       idx.set_key(i);
       idx.set_offset(i);
       idx.set_size(i);
       idx.SerializeToOstream(&output);
    }
    output.close();

    ifstream input("index.txt", ios::in | ios::binary);
//    for(int i = 0; i < 10; i++) {
       index_msg_t idx;
       idx.ParseFromIstream(&input);
       cout << idx.offset() << endl;
//    }
    input.close();

    return 0;
}
