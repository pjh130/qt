#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_file_clicked();

    void on_pushButton_files_clicked();

    void on_pushButton_dir_clicked();

    void on_pushButton_file_extract_clicked();

    void on_pushButton_files_extract_clicked();

    void on_pushButton_dir_extract_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
