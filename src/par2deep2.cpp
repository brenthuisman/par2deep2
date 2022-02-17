#include "par2deep2.h"
// #include <filesystem>

Opts::Opts(int argc, char *argv[], std::string lastdir)
{
//     op.add<popl::Switch>("h", "help", "produce help message");
    op.add<popl::Value<std::string>>("d", "directory", "Path to protect (default is current directory).", lastdir, &dirname);
    op.add<popl::Value<std::string>>("e", "excludes", "Optionally excludes directories. 'root' can be used to exclude files in the root -directory. Comma separated, no spaces.", "", &ext_exludes);
    op.add<popl::Value<std::string>>("x", "ext_excludes", "Optionally excludes file extensions. Comma separated, no spaces.", "", &ext_exludes);

	op.add<popl::Switch>("q", "quiet", "Don't asks questions, go with all defaults, including repairing and deleting files (default off).", &quiet);
	op.add<popl::Switch>("o", "overwrite", "Overwrite existing par2 files (default off).", &overwrite);
	op.add<popl::Switch>("n", "no_verify", "Do not verify existing files (default off).", &no_verify);
	op.add<popl::Switch>("k", "keep_orphan", "Keep orphaned par2 files (default off).", &keep_orphan);
	op.add<popl::Switch>("c", "clean_backup", "Remove backups created by par2 (.1,.2 and so on) from your file tree (default off).", &clean_backup);


    //unify ini and args
    op.parse(argc, argv);
    op.parse(lastdir+"/par2deep.ini");

// 	std::cout<<overwrite<<std::endl;
};

void Opts::update(std::string dirname){
    op.parse(dirname);
}


par2deep2::par2deep2(int argc, char *argv[], std::string lastdir)
    : opts{argc, argv, lastdir}
{
};
