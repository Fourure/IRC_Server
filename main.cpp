#include <QtGui/QApplication>
#include "serveur.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Serveur w;
    w.show();
    
    return a.exec();
}
