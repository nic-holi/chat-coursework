#include "log.h"
#include "ui_log.h"
using namespace std;

Log::Log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);
    setWindowTitle("Chat");
}

Log::~Log()
{
    delete ui;
}

//Accept the signal to jump to the chat window
void Log::receiveToLogin() {
    this->show();
}

// Click the login button
void Log::on_log_loginButton_clicked() {
    this->hide();
    string userId = ui->log_userId->text().toStdString();
    string password = ui->log_password->text().toStdString();

    // Handling login results
    string message = conn_login(userId, password);
    if(message.compare("pass") == 0) {
        emit showMainwindow();
    }
    else {
        this->show();
        QMessageBox::information(NULL, tr("Error "), tr(message.c_str()));
    }
}

// Click the register button
void Log::on_log_registerButton_clicked() {
    this->hide();
    emit showRegwindow();
}
