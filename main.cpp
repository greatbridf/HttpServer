#include "Application.h"

int main()
{
    signal(SIGPIPE, SIG_IGN);
    greatbridf::Application app;
    return app.run();
}
