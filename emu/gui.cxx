#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QString>

#include "emu/gui.hxx"

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
	QAction *gui_open_file;
	file->addAction(QString::fromUtf8("Open"));
	file->addAction(QString::fromUtf8("File Info"));
	menu_bar->addMenu(file);
	
	QMenu *prog = new QMenu(QString::fromUtf8("Prog"));
	QWidget hex_window;
	prog->addAction(QString::fromUtf8("Hex"), &hex_window, SLOT(show()));
	
	QWidget code_window;
	prog->addAction(QString::fromUtf8("Code"), &code_window, SLOT(show()));
	
	QWidget registers_window;
	prog->addAction(QString::fromUtf8("Registers"), &registers_window, SLOT(show()));
	
	QWidget ram_window;
	prog->addAction(QString::fromUtf8("RAM"), &ram_window, SLOT(show()));
	menu_bar->addMenu(prog);
	
	window.show();
	app.exec();
	return 0;
}
