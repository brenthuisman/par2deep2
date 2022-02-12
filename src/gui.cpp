#include "gui.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDir>

#include <iostream>
#include <QGroupBox>
#include <QFileDialog>
#include <QLineEdit>

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
    QObject::connect(pickdir_txt, &QLineEdit::textChanged, this, [=](QString text){
        //todo check is text is existing dir
        new_window(topbar_frame(0), start_options_frame(text.toStdString()), start_actions_frame());
    });

    auto basicset_layout = new QHBoxLayout();
    basicset_layout->addWidget(pickdir_btn,0);
    basicset_layout->addWidget(pickdir_txt,1);
    basicset->setLayout(basicset_layout);


	auto subframe = new QWidget();
    auto l = new QVBoxLayout();
    l->addWidget(basicset);
//     l.addWidget(advset);
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
