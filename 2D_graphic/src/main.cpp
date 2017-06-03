#include "application.hpp"



int main(int argc, char *argv[])
{
    MyApp app;

    app.init(argc, argv);
    app.run();
    
    return 0;
};
