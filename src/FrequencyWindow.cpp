#include "FrequencyWindow.h"
#include "TextProcessor.h"
#include "Reader.h"
FrequencyWindow::FrequencyWindow(QWidget* parent) : QMainWindow(parent)
{
	setWindowTitle("Frequencies");
	mainLayout = new QVBoxLayout;


	centralWidget = new QWidget(this);
	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);
	

}

void FrequencyWindow::setTable(QTableWidget* t) {
	this->freqListView = t;
	mainLayout->addWidget(freqListView);
}