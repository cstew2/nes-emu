#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QScrollArea>
#include <QFileDialog> 
#include <QString>

#include "emu/gui.hxx"

extern "C" {
#include "sim/asm.h"
#include "sim/code.h"
#include "sim/hex.h"
#include "emu/main.h"
}
	
gui::gui(void)
{
	//main Window
	main_window = new QWidget();
	main_window->setWindowTitle(QString::fromUtf8("cnes"));
	main_window->setFixedSize(256,240);

	//Menu setup
	menu_bar = new QMenuBar(main_window);
	
	file = new QMenu(QString::fromUtf8("File"), main_window);

	open_action = new QAction(QString::fromUtf8("Open"), this);
	file->addAction(open_action);
	QObject::connect(open_action, SIGNAL(triggered()), this, SLOT(open_file()));
	
	file_info_window = new QWidget();
	file_info_window->setWindowTitle(QString::fromUtf8("File Info"));
	file->addAction(QString::fromUtf8("File Info"), file_info_window, SLOT(show()));
	
	file->addAction(QString::fromUtf8("Quit"), main_window, SLOT(close()));
	menu_bar->addMenu(file);
	
	
	prog = new QMenu(QString::fromUtf8("Prog"));
	//Hex Window
	hex_window = new QWidget();
	hex_window->resize(256,240);
	prog->addAction(QString("Hex"), hex_window, SLOT(show()));

	//Code Window
	code_window = new QWidget();
	code_window->resize(256,240);
	prog->addAction(QString("Code"), code_window, SLOT(show()));

	//Register Window
        registers_window = new QWidget();
	registers_window->resize(256,240);
	prog->addAction(QString("Registers"), registers_window, SLOT(show()));
	register_values = new QTableWidget(2, 14, registers_window);
		
	//Ram Window
	ram_window = new QWidget();
	ram_window->resize(256,240);
	prog->addAction(QString("RAM"), ram_window, SLOT(show()));
	
	menu_bar->addMenu(prog);
}

gui::~gui(void)
{
        
}

void gui::start_emu(void)
{
	start_nes(rom_file);
}

void gui::open_file()
{
	QString path = QFileDialog::getOpenFileName(main_window,
						    QString::fromUtf8("Choose a File"),
						    QString::fromUtf8(""),
						    QString::fromUtf8("Nes Roms (*.nes)"));
	if(path != "") {
		rom_file = path.toLatin1().data();
		start_emu();
	}
	else {
		printf("No file selected");
	}
	
}

void start_gui()
{
	//fake variables for qt to start
	int argc = 1;
	char prog_name[] = "cnes";
	char *argv[] = {prog_name};
	QApplication app(argc, argv);

	gui *main_gui = new gui();
	
	//start GUI
	main_gui->main_window->show();
	app.exec();
}

