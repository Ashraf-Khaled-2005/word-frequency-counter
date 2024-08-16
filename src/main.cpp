#include <QtWidgets/QApplication>
#include <QLabel>
#include <QLineEdit>
#include "MainWindow.h"
#include "Reader.h"
#include "TextProcessor.h"
using namespace std;
std::map<string, int> TextProcessor::generalWords;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Reader* r = new Reader();
    //vector<pair<string, int>>sortedWords = sortedfreq(general);
    
    TextProcessor::generalWords = r->readGeneralmap();
    MainWindow w(nullptr);
    w.show();
    return a.exec();
}
