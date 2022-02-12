#ifndef PAR2DEEP2_H
#define PAR2DEEP2_H

#include "constants.h"

#include <string>
#include <vector>
#include <QStringList>

struct Opts {
    std::string dirname;
    bool quiet;
    bool overwrite;
    bool noverify;
    bool keep_orphan;
    bool clean_backup;
    std::vector<std::string> excludes;
    std::vector<std::string> ext_exludes;
};

Opts configargparse(const QStringList &);

class par2deep2
{
public:
	par2deep2(Opts);
	~par2deep2() = default;

	std::string test;

private:

};

#endif // PAR2DEEP2_H
