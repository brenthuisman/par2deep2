#ifndef PAR2DEEP2_H
#define PAR2DEEP2_H

#include "constants.h"

#include <string>
#include <vector>
#include <popl.hpp>

class Opts {
public:
    std::string dirname;
    std::vector<std::string> excludes;
    std::vector<std::string> ext_exludes;
    unsigned int percentage;
    bool quiet;
    bool overwrite;
    bool noverify;
    bool keep_orphan;
    bool clean_backup;

    Opts(int, char *[], std::string);
    void update(std::string dirname);
private:
    popl::OptionParser op {std::string{APPNAME}+" options"};
};

class par2deep2
{
public:
	par2deep2(int, char *[], std::string);
	~par2deep2() = default;

    Opts opts;

private:

};

#endif // PAR2DEEP2_H
