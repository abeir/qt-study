#include "notepad.h"
#include "ui_notepad.h"

#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QTextStream>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    connect(ui->actionNew, &QAction::triggered, this, &Notepad::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::open);
    connect(ui->actionSave, &QAction::triggered, this, &Notepad::save);
    connect(ui->actionSaveAs, &QAction::triggered, this, &Notepad::saveAs);
    connect(ui->actionExit, &QAction::triggered, this, &Notepad::exit);
    connect(ui->actionCopy, &QAction::triggered, this, &Notepad::copy);
    connect(ui->actionCut, &QAction::triggered, this, &Notepad::cut);
    connect(ui->actionPaste, &QAction::triggered, this, &Notepad::paste);
    connect(ui->actionUndo, &QAction::triggered, this, &Notepad::undo);
    connect(ui->actionRedo, &QAction::triggered, this, &Notepad::redo);
    connect(ui->actionFont, &QAction::triggered, this, &Notepad::selectFont);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::newFile()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件");
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "不能打开: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::save()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "保存");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "不能保存: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "另存为...");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "不能保存: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::exit()
{
    QCoreApplication::quit();
}

void Notepad::copy()
{
    ui->textEdit->copy();
}

void Notepad::cut()
{
    ui->textEdit->cut();
}

void Notepad::paste()
{
    ui->textEdit->paste();
}

void Notepad::undo()
{
     ui->textEdit->undo();
}

void Notepad::redo()
{
    ui->textEdit->redo();
}

void Notepad::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

