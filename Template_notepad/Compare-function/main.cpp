#include "common.h"
#include "mytest.hpp"

using std::cout;
using std::cin;
using std::endl;




int main(void)
{

    iterator_compare <int> Compare;
    
    int v1 = 1, v2 = 2;
    
    cout << Compare(v1, v2) << endl;
    cout << Compare(v2, v1) << endl;
    cout << Compare(v1, v1) << endl;
    
    cout << Compare(1, 2) << endl;
    
    return 0;
}


