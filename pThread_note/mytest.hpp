//
//  mytest.hpp
//  test
//
//  Created by Chris on 16/8/14.
//  Copyright © 2016年 Chris. All rights reserved.
//

#ifndef mytest_hpp
#define mytest_hpp

#include "common.h"

enum objLockEnum
{
    Free = 0,
    Locked
};

class learn_thread
{
public:
    static unsigned int objLock;
    
    static size_t winner;
    
    const static unsigned int LIMIT_NUM = 3;
    
    const static unsigned int LIMIT_SLEEP_TIME = 2;
    
    size_t timer;
    
    pthread_t * players;
    
    learn_thread() {
        
        players = new pthread_t [ LIMIT_NUM ];
        
        if(!players) {
            fprintf(stderr, "Cann't new %d thread in run class\n", LIMIT_NUM);
        }
        
        assert(players);
        
    }
    
    ~learn_thread() {
        delete [] players;
    }
    
    void run() {
    
        for(size_t i=0; i < LIMIT_NUM; ++ i) {
            int ret = pthread_create(players+i, NULL, playerRun, (void *)&i);
            
            if(ret) {
                
                fprintf(stderr, "Cann't create process thread\n");
                pthread_exit(NULL);
                assert(0);
                
            }
            
            sleep(1);
        }
        
        
        sleep(100);
        
        printf("Now judging the Winner is No.%zu\n", winner);
        
        pthread_exit(NULL);
    }
    
    static void * playerRun(void * __player) {
        
        size_t player = *((size_t *)__player);
        
        printf("No.%zu player already run!\n", player);
        
        sleep(player);
        
        printf("No.%zu player running instance for %zu in path\n", player, player);
        
        
        for(size_t i=0; i < LIMIT_SLEEP_TIME; ++ i) {
            
            sleep(LIMIT_SLEEP_TIME);
            
            printf("No.%zu player running instance for %zu in path\n",
                   player, player + i * LIMIT_SLEEP_TIME);
            
        }
        
        if(objLock == Free) {
            
            objLock = Locked;
            winner = player;
            
        }
        
        return NULL;
    }

    
};


unsigned int learn_thread::objLock = Free;
size_t learn_thread::winner = 0;

#endif /* mytest_hpp */
