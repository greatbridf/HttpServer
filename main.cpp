#include "Application.h"
#include <Utils/Foundation/LifeManagement/ArgumentParser.hpp>
#include <Utils/Foundation/LifeManagement/Daemon.hpp>

int run(int argn, const char** argv)
{
    greatbridf::Application app(argn, argv);
    return app.run();
}

int main(int argn, const char** argv)
{
    std::ios::sync_with_stdio(false);

    auto args = greatbridf::ArgumentParser(argn, argv);
    auto daemon = greatbridf::Daemon("HttpParser");

    if (!args.hasOption("-d"))
        return run(argn, argv);

    auto op = std::move(args.getOption("-d"));
    if (op.empty())
        return greatbridf::Daemon::pError(greatbridf::ExitCode::BadArgs);
    if (op == "stop")
        return greatbridf::Daemon::pError(daemon.stop(daemon.check()));
    if (op == "start")
        return greatbridf::Daemon::pError(daemon.start(run, argn, argv));
}
