#include <iostream>
#include "config/Config.h"
#include "log/LogHandler.h"
#include <cubescript/cubescript.hh>
#include <fstream>
#include <string_view>

static bool do_run_file(cubescript::state &s, std::string fname) {
    std::ostringstream buf;
    std::ifstream input (fname);
    buf << input.rdbuf();

    s.compile(std::string_view{buf.str().c_str(), std::size_t(buf.str().size())}, fname).call(s);
    return true;
}


int main(int argc, char **argv) {

    config::Config config{};

    config.parseImportantArgs(argc, argv);

    config.parseArgs(argc, argv);

    auto *logHandler = new log::LogHandler(&config);
    auto logHandlerThread = logHandler->run();

    cubescript::state cubescript_state;
    cubescript::std_init_all(cubescript_state);

    cubescript_state.new_var("test", "foo", false);
    do_run_file(cubescript_state, "test.cfg");
    std::cout << cubescript_state.lookup_value("test").force_string(cubescript_state) << "\n";



    logHandler->stop();
    if(logHandlerThread.joinable()) {
        logHandlerThread.join();
    }

    return 0;
}
