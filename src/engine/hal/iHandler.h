//
// Created by ztk on 2021-06-11.
//

#ifndef SAUERKRAUT_IHANDLER_H
#define SAUERKRAUT_IHANDLER_H

class iHandler {
public:
    virtual bool init() = 0;
    virtual void deinit() = 0;
    virtual ~iHandler() = default;
};

#endif //SAUERKRAUT_IHANDLER_H
