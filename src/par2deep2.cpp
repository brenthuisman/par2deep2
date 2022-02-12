#include "par2deep2.h"
// #include <filesystem>

Opts::Opts(int argc, char *argv[], std::string lastdir)
{
    op.add<popl::Switch>("h", "help", "produce help message");
//  op.add<popl::Value<std::string>>("s", "long", "description", "default value");
    op.add<popl::Value<std::string>>("d", "directory", "Path to protect (default is current directory).", lastdir, &dirname);

    //unify ini and args
    op.parse(argc, argv);
    op.parse(lastdir+"/par2deep.ini");
};

void Opts::update(std::string dirname){
    op.parse(dirname);
}


par2deep2::par2deep2(int argc, char *argv[], std::string lastdir)
    : opts{argc, argv, lastdir}
{
};
