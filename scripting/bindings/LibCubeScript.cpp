//
// Created by ztk on 2021-06-09.
//

#include "LibCubeScript.h"
namespace scripting {

    void LibCubeScript::initialize() {
        cubescript::std_init_all(cubescript_state);
    }

    void LibCubeScript::deinitialize() {

    }

    bool LibCubeScript::do_run_file(cubescript::state &s, const char* filename) {
        std::ostringstream buf;
        std::ifstream input (filename);
        buf << input.rdbuf();

        s.compile(std::string_view{buf.str().c_str(), std::size_t(buf.str().size())}, filename).call(s);
        return true;
    }

    void LibCubeScript::bind_var(const char * varname, float *var, bool readonly) {
        cubescript_state.new_var(varname, *var, readonly);
        cubescript_state.set_var_ptr(varname, var);
    }

    void LibCubeScript::bind_var(const char *varname, int *var, bool readonly) {
        cubescript_state.new_var(varname, *var, readonly);
        cubescript_state.set_var_ptr(varname, var);
    }
    void LibCubeScript::bind_var(const char *varname, std::string_view *var, bool readonly) {
        cubescript_state.new_var(varname, *var, readonly);
        cubescript_state.set_var_ptr(varname, var);
    }

    LibCubeScript::LibCubeScript() {
        initialize();
    }

    LibCubeScript::~LibCubeScript() {
        deinitialize();
    }




}