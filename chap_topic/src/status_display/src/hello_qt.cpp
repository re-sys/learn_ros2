#include <QApplication>
#include <QLabel>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel label("Hello Qt!");
    QString message = QString::fromStdString("Hello Qt!");
    label.setText(message);
    label.show();
    return app.exec();
};