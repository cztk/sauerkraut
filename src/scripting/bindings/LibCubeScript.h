//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_CUBESCRIPT_H
#define SAUERKRAUT_CUBESCRIPT_H

#include <cubescript/cubescript.hh>
#include <fstream>
#include <sstream>

namespace scripting {


    class LibCubeScript {

    public:
        LibCubeScript();
        ~LibCubeScript();
        bool execute(const char* filename);

        void bind_var(const char *varname, float *var, bool readonly);
        void bind_var(const char *varname, int *var, bool readonly);
        void bind_var(const char *varname, std::string *var, bool readonly);
    private:
        cubescript::state cubescript_state;

        void initialize();
        void deinitialize();
    };

}
#endif //SAUERKRAUT_CUBESCRIPT_H
