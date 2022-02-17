#include "gui.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDir>

#include <iostream>
#include <QGroupBox>
#include <QFileDialog>
#include <QLineEdit>
#include <QCheckBox>

pgui::pgui(int argc, char *argv[], QWidget *parent)
    : QMainWindow(parent),
    guisettings {ORGNAME, APPNAME},
    p2d {argc,argv,guisettings.value("lastdir", QDir::homePath()).toString().toStdString()}
{
	setWindowTitle(APPNAME);
	resize(800, 800);
	setWindowIcon(QIcon("../par2deep.ico"));

	restoreGeometry(guisettings.value("geometry", saveGeometry()).toByteArray());

	new_window(topbar_frame(0), start_options_frame(p2d.opts.dirname), start_actions_frame());
}

void pgui::closeEvent(QCloseEvent *event)
{
	guisettings.setValue("geometry", saveGeometry());
// 	std::cout<<p2d.opts.overwrite<<std::endl;
}

void pgui::new_window(QWidget *t,QWidget *m,QWidget *b)
{
	auto subframe = new QWidget();
	auto mainLayout = new QVBoxLayout();
	mainLayout->addWidget(t,0);
	t->setFixedHeight(100);
	mainLayout->addWidget(m,1);
	mainLayout->addWidget(b,0);
	b->setFixedHeight(100);
	subframe->setLayout(mainLayout);
	setCentralWidget(subframe);
}

QWidget* pgui::topbar_frame(int stage){
	auto subframe = new QWidget();
	auto l = new QHBoxLayout();
	l->addStretch(1);
	QStringList labels = {"Start","Proposed actions","Executing actions","Report","Further actions","Final report"};
	labels.replace(stage,"<u>"+labels.at(stage)+"</u>");
	for (auto label : labels){
		l->addWidget(new QLabel(label));
		l->insertSpacing(-1,10);
	}
	l->addStretch(1);
	subframe->setLayout(l);
	return subframe;
}


QWidget* pgui::start_options_frame(std::string chosen_dir){
    p2d.opts.update(chosen_dir);
    guisettings.setValue("lastdir", QString{}.fromStdString(chosen_dir));

    auto basicset = new QGroupBox("Basic Settings");

    auto pickdir_btn = new QPushButton("Pick directory");
    QObject::connect(pickdir_btn, &QPushButton::clicked, this, [=](){
        auto new_dirname = QFileDialog::getExistingDirectory(this,"Set directory in which to protect data",QString{}.fromStdString(chosen_dir));
        new_window(topbar_frame(0), start_options_frame(new_dirname.toStdString()), start_actions_frame());
    });

    auto pickdir_txt = new QLineEdit(QString{}.fromStdString(chosen_dir));
    QObject::connect(pickdir_txt, &QLineEdit::textChanged, this, [=](QString pickdir){
        if (QDir(pickdir).exists()){
			new_window(topbar_frame(0), start_options_frame(pickdir.toStdString()), start_actions_frame());
		}
    });

    auto basicset_layout = new QHBoxLayout();
    basicset_layout->addWidget(pickdir_btn,0);
    basicset_layout->addWidget(pickdir_txt,1);
    basicset->setLayout(basicset_layout);

	auto advset = new QGroupBox("Advanced Settings");

	auto cb1 = new QCheckBox("Overwrite all parity data");
	cb1->setChecked(p2d.opts.overwrite);
	cb1->setToolTip("Existing parity data found (*.par* files) will be removed and overwritten.");
	QObject::connect(cb1,&QCheckBox::stateChanged,this,[=](bool fldval){p2d.opts.overwrite=fldval;});

	auto cb2 = new QCheckBox("Skip verification");
	cb2->setChecked(p2d.opts.no_verify);
	cb2->setToolTip("Skips verification of files with existing parity data. Use when you just want to create parity data for newly added files.");
	QObject::connect(cb2,&QCheckBox::stateChanged,this,[=](bool fldval){p2d.opts.no_verify=fldval;});

	auto cb3 = new QCheckBox("Keep orphaned par2 files");
	cb3->setChecked(p2d.opts.keep_orphan);
	cb3->setToolTip("Do not remove unused parity files (*.par*).");
	QObject::connect(cb3,&QCheckBox::stateChanged,this,[=](bool fldval){p2d.opts.keep_orphan=fldval;});

	auto cb4 = new QCheckBox("Remove backup files");
	cb4->setChecked(p2d.opts.clean_backup);
	cb4->setToolTip("Remove backup files (*.[0-9]).");
	QObject::connect(cb4,&QCheckBox::stateChanged,this,[=](bool fldval){p2d.opts.clean_backup=fldval;});
/*
	auto ex_lb = new QLabel("Exclude directories (comma separated):");
	auto ex_fld = new QLineEdit(','.join(self.p2d.args["excludes"]));
	ex_fld->setToolTip("These sub-directories will be excluded from the analysis. Use 'root' for the root of the directory.");
	ex_fld.textChanged.connect(lambda fldval : self.p2d.args.update({"excludes":fldval.split(',')}));

	auto exex_lb = new QLabel("Exclude extensions (comma separated):");
	auto exex_fld = new QLineEdit(','.join(self.p2d.args["extexcludes"]));
	exex_fld->setToolTip("These extensions will be excluded from the analysis.");
	exex_fld.textChanged.connect(lambda fldval : self.p2d.args.update({"extexcludes":fldval.split(',')}));

	auto parpath_lb = new QLabel("Path to alternative par2(.exe) executable:");
	auto parpath_fld = new QLineEdit(self.p2d.args["par_cmd"]);
	parpath_fld->setToolTip("Leave blank for built-in library or par2 in PATH.");
	parpath_fld.textChanged.connect(lambda fldval : self.p2d.args.update({"par_cmd":fldval}));

	auto perc_sldr = new BSlider("Percentage of protection",5,100,lambda fldval : self.p2d.args.update({"percentage":fldval}),self.p2d.args["percentage"]);
	perc_sldr->setToolTip("The maximum percentage of corrupted data you will be able to recover from. Higher is safer, but uses more disk space.");*/


	auto advset_layout = new QVBoxLayout();
	advset_layout->addWidget(cb1,0);
	advset_layout->addWidget(cb2,0);
	advset_layout->addWidget(cb3,0);
	advset_layout->addWidget(cb4,0);
// 	advset_layout->addWidget(ex_lb,0);
// 	advset_layout->addWidget(ex_fld,0);
// 	advset_layout->addWidget(exex_lb,0);
// 	advset_layout->addWidget(exex_fld,0);
// 	advset_layout->addWidget(parpath_lb,0);
// 	advset_layout->addWidget(parpath_fld,0);
// 	advset_layout->addWidget(perc_sldr,0);
	advset->setLayout(advset_layout);

	auto subframe = new QWidget();
    auto l = new QVBoxLayout();
    l->addWidget(basicset);
    l->addWidget(advset);
    l->addStretch(1);
    subframe->setLayout(l);
	return subframe;
}


QWidget* pgui::start_actions_frame(){
	auto ssa_btn = new QPushButton("Check directory contents");
	//ssa_btn->clicked.connect(set_start_actions)
	
	auto subframe = new QWidget();
	auto l = new QHBoxLayout();
	l->addStretch(1);
	l->addWidget(ssa_btn);
	l->addStretch(1);
	subframe->setLayout(l);
	return subframe;
}
