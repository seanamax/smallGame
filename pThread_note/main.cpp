#include "common.h"
#include "mytest.hpp"

using std::cout;
using std::cin;
using std::endl;




int main(void)
{

    auto pThread = new learn_thread;
    
    pThread->run();
    return 0;
}


