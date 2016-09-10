#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QScrollArea>
#include <QString>

#include "emu/gui.hxx"
#include "sim/asm.h"
#include "sim/code.h"
#include "sim/hex.h"

int main_gui(void)
{
	int argc = 1;
	char prog_name[] = "cnes";
	char *argv[] = {prog_name};
	QApplication app(argc, argv);
	
	QWidget window;
	window.setWindowTitle(QString::fromUtf8("cnes"));
	window.setFixedSize(256,240);

	QMenuBar *menu_bar = new QMenuBar(&window);
	
	QMenu *file = new QMenu(QString::fromUtf8("File"));
	file->addAction(QString::fromUtf8("Open"));
	file->addAction(QString::fromUtf8("File Info"));
	file->addAction(QString::fromUtf8("Quit"));
	menu_bar->addMenu(file);

	QAction *gui_open_file;
	QAction *gui_file_info;
	QAction *gui_quit;
	
	QMenu *prog = new QMenu(QString::fromUtf8("Prog"));
	
	QWidget hex_window;
	hex_window.resize(256,240);
	prog->addAction(QString::fromUtf8("Hex"), &hex_window, SLOT(show()));
	QScrollArea *hex_scroll = new QScrollArea(&hex_window);
	hex_scroll->setMinimumSize(256,240);
	hex_scroll->setWidgetResizable(true);
	hex_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	
	QWidget code_window;
	code_window.resize(256,240);
	prog->addAction(QString::fromUtf8("Code"), &code_window, SLOT(show()));
	
	QWidget registers_window;
	registers_window.resize(256,240);
	prog->addAction(QString::fromUtf8("Registers"), &registers_window, SLOT(show()));
	
	QWidget ram_window;
	ram_window.resize(256,240);
	prog->addAction(QString::fromUtf8("RAM"), &ram_window, SLOT(show()));
	menu_bar->addMenu(prog);
	
	window.show();
	app.exec();
	return 0;
}
