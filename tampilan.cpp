#include "tampilan.h"
#include "ui_tampilan.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QRadioButton>
#include <QAbstractButton>
#include <QStringList>

tampilan::tampilan(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tampilan)
{
    QFile kontak("kontak.txt");
    if(!kontak.open(QIODevice::ReadWrite)){
        QMessageBox::information(0,"info",kontak.errorString());
        QTextStream out(&kontak);
    }
    QTextStream in(&kontak);

    ui->setupUi(this);
    setFixedSize(this->geometry().width(),this->geometry().height());
    ui->dataViewer->setText(in.readAll());
    kontak.close();
}

tampilan::~tampilan()
{
    delete ui;
}

/* I.S. : Field telah terisi semua atau sebagian
 * F.S. : Mengisikan nilai pada field ke text file jika memenuhi syarat*/

void tampilan::on_simpanButton_clicked()
{
    //Mengambil data pada pinEdit & nameEdit
    QString pinData, nameData;
    pinData = ui->pinEdit->text();
    nameData = ui->nameEdit->text();

    //Mengakses file kontak.txt
    QFile kontak("kontak.txt");

    //Validasi pengisian field
    if (pinData.isEmpty()||nameData.isEmpty()) {
             QMessageBox::information(this, tr("Isi PIN dan Nama"),
                     "Tidak boleh kosong, harus diisi semua field.!");
    }else{
    if(!kontak.open(QIODevice::ReadWrite)){
        QMessageBox::information(0,"info",kontak.errorString());
    }

    QTextStream update(&kontak);

    //Mencari end of file dari kontak.txt
    QString line;
    do{
        line = update.readLine();
    }while(!line.isNull());

    //Menambah data pada kontak.txt
    update <<"#"<< pinData;
    update <<"#"<< nameData;

    //Mengecek Radio Button dan menambahkannya pada file kontak.txt
    if(ui->radioMale->isChecked()==true){
        update <<"#M";
    }else if(ui->radioFemale->isChecked()==true){
        update <<"#F";
    }
    update <<"\n";

    //Menutup file kontak.txt
    kontak.close();
    }

    //Mengembalikan nilai default field
    ui->pinEdit->clear();
    ui->nameEdit->clear();
    ui->radioMale->setChecked(true);

    //memuat ulang file kontak.txt
    kontak.open(QIODevice::ReadOnly);
    QTextStream in(&kontak);
    ui->dataViewer->setText(in.readAll());
    kontak.close();
}

/* I.S. : Field telah terisi semua atau sebagian
 * F.S. : Mengembalikan nilai field pada kondisi clear*/

void tampilan::on_resetButton_clicked()
{
    ui->pinEdit->clear();
    ui->nameEdit->clear();
    ui->radioMale->setChecked(true);
    ui->keywordEdit->clear();
}

void tampilan::on_cariButton_clicked()
{
    //Mengakses file kontak.txt
    QFile kontak("kontak.txt");
    QString keywordCari;
    keywordCari = ui->keywordEdit->text();
    kontak.open(QIODevice::ReadOnly|QIODevice::Text);

    bool ketemu = false;

    //Validasi mencari pin atau nama
    QString line,comboBox;
    comboBox = ui->comboCari->currentText();

    if(keywordCari.isEmpty()){
        QMessageBox::information(this,tr("Peringatan"),
                                 "Masukkan kata kunci terlebih dahulu.");
    }

    else{
    //Memuat file kontak
    QTextStream cariTeks(&kontak);
        do{ line = cariTeks.readLine();
            QStringList parts = line.split("#",QString::KeepEmptyParts);
            if(parts.length() == 4 ){
                QString pinData, nameData, genderData;
                pinData = parts[1];
                nameData = parts[2];
                genderData = parts[3];

                //Validasi combo box
                if(comboBox=="PIN"){

                //Jika combo box berisi nilai "PIN"
                    if(pinData == keywordCari){
                        ketemu = true;
                        QMessageBox::information(this,tr("Ketemu"),
                                             "#"+pinData+"#"+nameData+"#"+genderData);
                    }
                }

                //Jika combo box berisi nilai "Nama"
                else{
                    if(nameData == keywordCari){
                        ketemu = true;
                        QMessageBox::information(this,tr("Ketemu"),
                                                 "#"+pinData+"#"+nameData+"#"+genderData);
                    }
                }
            }
        }while(!line.isNull()&&ketemu==false);
    if(ketemu==false && comboBox=="PIN"){
        QMessageBox::information(this,tr("Peringatan"),
                                 "PIN yang anda cari tidak ada.");
    }
    else if(ketemu==false && comboBox=="Name"){
        QMessageBox::information(this,tr("Peringatan"),
                                 "Nama yang anda cari tidak ada.");
    }
    }
    kontak.close();
    ui->keywordEdit->clear();
}
