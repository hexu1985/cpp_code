#include <QApplication>
#include "name_dialog.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Name_dialog *dialog = new Name_dialog;
	dialog->show();
	return app.exec();
}
