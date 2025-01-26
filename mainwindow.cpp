#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "libcalc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonDot_clicked()
{
    ui->calcInput->insert(".");
}


void MainWindow::on_buttonZero_clicked()
{
    ui->calcInput->insert("0");
}


void MainWindow::on_buttonOne_clicked()
{
    ui->calcInput->insert("1");
}


void MainWindow::on_buttonTwo_clicked()
{
    ui->calcInput->insert("2");
}


void MainWindow::on_buttonThree_clicked()
{
    ui->calcInput->insert("3");
}


void MainWindow::on_buttonFour_clicked()
{
    ui->calcInput->insert("4");
}


void MainWindow::on_buttonFive_clicked()
{
    ui->calcInput->insert("5");
}


void MainWindow::on_buttonSix_clicked()
{
    ui->calcInput->insert("6");
}


void MainWindow::on_buttonSeven_clicked()
{
    ui->calcInput->insert("7");
}


void MainWindow::on_buttonEight_clicked()
{
    ui->calcInput->insert("8");
}


void MainWindow::on_buttonNine_clicked()
{
    ui->calcInput->insert("9");
}

void MainWindow::on_buttonPlus_clicked()
{
    ui->calcInput->insert("+");
}

void MainWindow::on_buttonMinus_clicked()
{
    ui->calcInput->insert("-");
}


void MainWindow::on_buttonMultiply_clicked()
{
    ui->calcInput->insert("*");
}


void MainWindow::on_buttonDivide_clicked()
{
    ui->calcInput->insert("/");
}


void MainWindow::on_buttonLeftParenthesis_clicked()
{
    ui->calcInput->insert("(");
}


void MainWindow::on_buttonRightParenthesis_clicked()
{
    ui->calcInput->insert(")");
}


void MainWindow::on_buttonAllClear_clicked()
{
    ui->calcInput->clear();
}


void MainWindow::on_Backspace_clicked()
{
    ui->calcInput->backspace();
}


void MainWindow::on_buttonEquals_clicked()
{
    ui->calcInput->setText(QString::fromStdString(libcalc::evaluate(ui->calcInput->text().toStdString())));
}


void MainWindow::on_calcInput_returnPressed()
{
    ui->calcInput->setText(QString::fromStdString(libcalc::evaluate(ui->calcInput->text().toStdString())));
}

