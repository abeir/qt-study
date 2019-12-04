#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void newFile();

    void open();

    void save();

    void saveAs();

    void exit();

    void copy();

    void cut();

    void paste();

    void undo();

    void redo();

    void selectFont();

private:
    Ui::Notepad *ui;
    QString currentFile;
};
#endif // NOTEPAD_H
