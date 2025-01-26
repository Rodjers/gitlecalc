#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonZero_clicked();

    void on_buttonDot_clicked();

    void on_buttonEquals_clicked();

    void on_buttonPlus_clicked();

    void on_buttonOne_clicked();

    void on_buttonTwo_clicked();

    void on_buttonThree_clicked();

    void on_buttonFour_clicked();

    void on_buttonFive_clicked();

    void on_buttonSix_clicked();

    void on_buttonSeven_clicked();

    void on_buttonEight_clicked();

    void on_buttonNine_clicked();

    void on_buttonMinus_clicked();

    void on_buttonMultiply_clicked();

    void on_buttonDivide_clicked();

    void on_buttonRightParenthesis_clicked();

    void on_buttonLeftParenthesis_clicked();

    void on_buttonAllClear_clicked();

    void on_Backspace_clicked();

    void on_calcInput_returnPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
