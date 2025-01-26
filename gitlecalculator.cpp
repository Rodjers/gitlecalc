#include "gitlecalculator.h"
#include "./ui_gitlecalculator.h"
#include "libcalc.h"

GitleCalculator::GitleCalculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GitleCalculator)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("Gitle Calculator"));
    ui->calcInput->setFocus();
}

GitleCalculator::~GitleCalculator()
{
    delete ui;
}

void GitleCalculator::on_buttonDot_clicked()
{
    ui->calcInput->insert(".");
}


void GitleCalculator::on_buttonZero_clicked()
{
    ui->calcInput->insert("0");
}


void GitleCalculator::on_buttonOne_clicked()
{
    ui->calcInput->insert("1");
}


void GitleCalculator::on_buttonTwo_clicked()
{
    ui->calcInput->insert("2");
}


void GitleCalculator::on_buttonThree_clicked()
{
    ui->calcInput->insert("3");
}


void GitleCalculator::on_buttonFour_clicked()
{
    ui->calcInput->insert("4");
}


void GitleCalculator::on_buttonFive_clicked()
{
    ui->calcInput->insert("5");
}


void GitleCalculator::on_buttonSix_clicked()
{
    ui->calcInput->insert("6");
}


void GitleCalculator::on_buttonSeven_clicked()
{
    ui->calcInput->insert("7");
}


void GitleCalculator::on_buttonEight_clicked()
{
    ui->calcInput->insert("8");
}


void GitleCalculator::on_buttonNine_clicked()
{
    ui->calcInput->insert("9");
}

void GitleCalculator::on_buttonPlus_clicked()
{
    ui->calcInput->insert("+");
}

void GitleCalculator::on_buttonMinus_clicked()
{
    ui->calcInput->insert("-");
}


void GitleCalculator::on_buttonMultiply_clicked()
{
    ui->calcInput->insert("*");
}


void GitleCalculator::on_buttonDivide_clicked()
{
    ui->calcInput->insert("/");
}


void GitleCalculator::on_buttonLeftParenthesis_clicked()
{
    ui->calcInput->insert("(");
}


void GitleCalculator::on_buttonRightParenthesis_clicked()
{
    ui->calcInput->insert(")");
}


void GitleCalculator::on_buttonAllClear_clicked()
{
    ui->calcInput->clear();
    ui->calcInput->setFocus();
}


void GitleCalculator::on_Backspace_clicked()
{
    ui->calcInput->backspace();
}


void GitleCalculator::on_buttonEquals_clicked()
{
    ui->calcInput->setText(QString::fromStdString(libcalc::evaluate(ui->calcInput->text().toStdString())));
}


void GitleCalculator::on_calcInput_returnPressed()
{
    ui->calcInput->setText(QString::fromStdString(libcalc::evaluate(ui->calcInput->text().toStdString())));
}

