//
// Created by ztk on 2021-06-11.
//

#ifndef SAUERKRAUT_STATE_H
#define SAUERKRAUT_STATE_H


namespace kraut::engine {

    enum {
        NOT_INITING = 0,
        INIT_GAME,
        INIT_LOAD,
        INIT_RESET
    };

    class State {

    public:
        int initing = INIT_RESET;
        unsigned int numcpus = 1;


    };
}

#endif //SAUERKRAUT_STATE_H
