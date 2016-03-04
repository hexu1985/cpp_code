#ifndef STANDARDDIALOGS_H
#define STANDARDDIALOGS_H

// Qt5 header
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFrame>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

#include <QtGui>

class StandardDialogs : public QDialog
{
    Q_OBJECT
public:
    StandardDialogs( QWidget *parent=0, Qt::WindowFlags  f=0 );
    ~StandardDialogs();
public:
    QGridLayout *layout; 
    
    QPushButton *filePushButton;
    QPushButton *colorPushButton;
    QPushButton *fontPushButton;

    QLineEdit *fileLineEdit;   
    QLineEdit *fontLineEdit;	
    QFrame *colorFrame;
    
private slots:
    void slotOpenFileDlg();
    void slotOpenColorDlg();
    void slotOpenFontDlg();
};

#endif 

