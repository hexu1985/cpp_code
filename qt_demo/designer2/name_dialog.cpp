#include "name_dialog.h"
#include <QMessageBox>

Name_dialog::Name_dialog(QWidget *parent):
	QDialog(parent)
{
	ui_.setupUi(this);
	ui_.lineEdit->setText("Hexu");
	connect(ui_.pushButton_OK, SIGNAL(clicked()), this, SLOT(slot_push_ok()));
	connect(ui_.pushButton_Cancel, SIGNAL(clicked()), this, SLOT(slot_push_cancel()));
}

Name_dialog::~Name_dialog() {}

void Name_dialog::slot_push_ok()
{
	QString str = tr("Hi, ");
	str += ui_.lineEdit->text();
	QMessageBox::information(this, "pushed OK button", str);
}

void Name_dialog::slot_push_cancel()
{
	QString str = tr("Bye, ");
	str += ui_.lineEdit->text();
	QMessageBox::information(this, "pushed Cancel button", str);
}

