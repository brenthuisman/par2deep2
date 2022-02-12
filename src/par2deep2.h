#ifndef PAR2DEEP2_H
#define PAR2DEEP2_H

#include "constants.h"

#include <string>
#include <vector>
#include <popl.hpp>

struct Opts {
    std::string dirname;
    std::vector<std::string> excludes;
    std::vector<std::string> ext_exludes;
    unsigned int percentage;
    bool quiet;
    bool overwrite;
    bool noverify;
    bool keep_orphan;
    bool clean_backup;
};

inline Opts configargparse(int argc, char *argv[])
{
    std::string lastdir; //uit main trekken
    Opts opts;
    popl::OptionParser op(std::string{APPNAME}+" options");
    op.add<popl::Switch>("h", "help", "produce help message");
//  op.add<popl::Value<std::string>>("s", "long", "description", "default value");
    op.add<popl::Value<std::string>>("d", "directory", "Path to protect (default is current directory).", lastdir, &opts.dirname);

    //unify ini and args
    op.parse(argc, argv);
    return opts;
};

class par2deep2
{
public:
	par2deep2(Opts);
	~par2deep2() = default;

	std::string test;

private:

};

#endif // PAR2DEEP2_H
