#include <cstdlib>
#include "application.hpp"



int main(int argc, char *argv[])
{
    srand(time(0));

    MyApp app;

    app.init(argc, argv);
    app.run();
    
    return 0;
};
