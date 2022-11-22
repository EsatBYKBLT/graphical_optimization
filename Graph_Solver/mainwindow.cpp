#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

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


void MainWindow::on_actionCredits_triggered()
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("About me :)");
    msgBox.setText("Muhammet Esat BÜYÜKBULUT\n"
                   "1306191434\n"
                   "@2022");
    //msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();


}


void MainWindow::on_kisit_denklemi_ekle_clicked()
{
    Equation e;
    e.x= ui->kisit_denklemi_x->text().toDouble();
    e.y= ui->kisit_denklemi_y->text().toDouble();
    e.b= ui->kisit_denklemi_b->text().toDouble();
    if(ui->kisit_denklemi_comboBox->currentText()== "<=")
        e.bke = BKE::kucuk;
    else
        e.bke = BKE::buyuk;

    s.add_kisit_denklemi(e);


    ui->kisit_denklemi_plainTextEdit->clear();
    ui->kisit_denklemi_plainTextEdit->setPlainText(QString::fromStdString(s.get_kisitdenklemleri()));
}


void MainWindow::on_kisit_denklemi_temizle_clicked()
{
    s.kisit_denklemleri.clear();
    ui->kisit_denklemi_plainTextEdit->clear();
    ui->kisit_denklemi_plainTextEdit->setPlainText(QString::fromStdString(s.get_kisitdenklemleri()));

}


void MainWindow::on_pushButton_3_clicked()
{
    Equation e;
    e.x = ui->amac_fonksiyonu_x->text().toDouble();
    e.y = ui->amac_fonksiyonu_y->text().toDouble();
    s.set_amac_fonksiyonu(e);

    s.solve();

    ui->sonuc_lineEdit->setText(QString::fromStdString(s.get_result()));
}

