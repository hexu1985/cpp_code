#ifndef __name_dialog_h
#define __name_dialog_h

#include <QDialog>
#include "ui_name.h"

class Name_dialog: public QDialog {
	Q_OBJECT
public:
	Name_dialog(QWidget *parent = 0);
	~Name_dialog();

public slots:
	void slot_push_ok();
	void slot_push_cancel();

private:
	Ui::Dialog ui_;
};

#endif
