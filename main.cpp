#include "mainwindow.hpp"

#include <QApplication>

#include "smartupsserialclient.hpp"

int main(int argc, char *argv[])
{
    QString a = "#uD43132135138129uM43229234239224uA43110112114108uI43253264271280lD43103100097106lM43177172168182lA43090092081085lI43196188208204e44200155090oI43230240220225oD13115oJ13100oM13208s441HMLLq44202050710p443020180300600k4410TLNr443000060180300E443336168ON OFF\r\n";
    SmartUpsSerialClient c;
    c.getVariables(a);
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}
