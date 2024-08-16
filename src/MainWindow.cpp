#include "MainWindow.h"
#include "TextProcessor.h"
#include "Reader.h"
#include "FrequencyWindow.h"
#include "WordFilter.h" 
MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
{
	//general Map
	/*
	Read General Map
	*/;
	setWindowTitle("Word Frequency Counter");
	mainLayout = new QVBoxLayout;
	searchBar = new QLineEdit;
	searchLabel = new QLabel("Search:");
	searchBarLayout = new QHBoxLayout;
	searchBarLayout->addWidget(searchLabel);
	searchBarLayout->addWidget(searchBar);
	mainLayout->addLayout(searchBarLayout);
	 frequencyLabel = new QLabel(this);
	mainLayout->addWidget(frequencyLabel);

	connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::updateFrequency);
	
	mainLayout->addWidget(searchListView);

	model = new QStringListModel(this); // zabat el hwar dah
	// Add your list of possible completions here
	
	//connect
	connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::searchTextChanged);

	//signal fired to slot
	paragraphBox = new QGroupBox("Paragraph");
	paragraphBoxLayout = new QVBoxLayout;
	paragraphTextEdit = new QTextEdit;
	paragraphBoxLayout->addWidget(paragraphTextEdit);
	paragraphBox->setLayout(paragraphBoxLayout);
	//paragraphTextEdit->setCompleter(completer); msh shaghala
	mainLayout->addWidget(paragraphBox);
	

	buttonsLayout = new QHBoxLayout;
	processTextButton = new QPushButton("Process Text");
	uploadTextButton = new QPushButton("Upload File");
	modifyTextButton = new QPushButton("Modify Text");
	showGlobalFreq = new QPushButton("Show Global Frequencies");
	buttonsLayout->addWidget(processTextButton);
	buttonsLayout->addWidget(uploadTextButton);
	buttonsLayout->addWidget(modifyTextButton);
	buttonsLayout->addWidget(showGlobalFreq);
	mainLayout->addLayout(buttonsLayout);

	//connections for buttons Layout
	connect(processTextButton, SIGNAL(clicked()), this, SLOT(processTextButtonClicked()));
	connect(uploadTextButton, &QPushButton::clicked, this, &MainWindow::openFileDialog);
	connect(showGlobalFreq, SIGNAL(clicked()), this, SLOT(showGlobalFrequencies()));
	connect(modifyTextButton, SIGNAL(clicked()), this, SLOT(modify()));



	filterLayout = new QHBoxLayout;
	filterBar = new QLineEdit;
	filterBox = new QGroupBox("Filter:");
	filterLayout->addWidget(filterBar);
	//filterLayout->addWidget(filterLabel);
	filterBox->setLayout(filterLayout);
	filterLayout->addWidget(filterBar);
	mainLayout->addWidget(filterBox);


	centralWidget = new QWidget(this);
	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);
	//Modify
	//ranking fel gui	
	// search
	//tries auto correct auto complete


}


void MainWindow::showGlobalFrequencies() {
	QTableWidget* freqTable = new QTableWidget;
	freqTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	vector<pair<string, int>> sortedWords = proccess.sortedGeneralWords;
	freqTable->setColumnCount(2);
	QStringList headers;
	headers << "Word" << "Global Frequency";
	freqTable->setHorizontalHeaderLabels(headers);
	freqTable->setRowCount(sortedWords.size());
	int row = 0;
	for (const auto& result : sortedWords) {
		QTableWidgetItem* wordItem = new QTableWidgetItem(QString::fromStdString(result.first));
		QTableWidgetItem* freqItem = new QTableWidgetItem(QString::number(result.second));
		freqTable->setItem(row, 0, wordItem);
		freqTable->setItem(row, 1, freqItem);
		++row;
	}
	FrequencyWindow* f = new FrequencyWindow;
	f->setTable(freqTable);
	f->show();

}
void MainWindow::processTextButtonClicked()
{

	vector<string> filterWords;
	if (!(filterBar->text().isEmpty())) {
		string filter = filterBar->text().toStdString();
		stringstream ss(filter);
		string word;
		while (getline(ss, word, ',')) {
			size_t start = word.find_first_not_of(" \t");
			size_t end = word.find_last_not_of(" \t");
			if (start != std::string::npos && end != std::string::npos) {
				word = word.substr(start, end - start + 1);
			}
			filterWords.push_back(word);
		}
	}

	TextProcessor t(paragraphTextEdit->toPlainText().toStdString(),filterWords);
	this->proccess = t;
	QTableWidget* freqTable = new QTableWidget;
	freqTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	vector<pair<string,int>> sortedWords = this->proccess.getSortedWords();
	freqTable->setColumnCount(3);
	QStringList headers;
	headers << "Word" << "Local Frequency"<<"Global Frequency";
	freqTable->setHorizontalHeaderLabels(headers);
	freqTable->setRowCount(sortedWords.size());
	int row = 0;
	for (const auto& result : sortedWords) {
		QTableWidgetItem* wordItem = new QTableWidgetItem(QString:: fromStdString(result.first));
		QTableWidgetItem* freqItem = new QTableWidgetItem(QString::number(result.second));
		QTableWidgetItem* globalItem = new QTableWidgetItem(QString::number(this->proccess.generalWords[result.first]));
		freqTable->setItem(row, 0, wordItem); 
		freqTable->setItem(row, 1, freqItem);
		freqTable->setItem(row, 2, globalItem);
		++row;
	}
	FrequencyWindow *f = new FrequencyWindow;
	// eb2a raga3hum
	feedingTheModel();
	model->setStringList(list);
	QCompleter* completer = new QCompleter(this);
	completer->setModel(model);
	searchBar->setCompleter(completer);
	f->setTable(freqTable);
	f->show();
}

void MainWindow::openFileDialog() {
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt)"));
	this->FilePath = filePath;
	if (!filePath.isEmpty()) {
		string paragraphPath = filePath.toStdString();
		paragraphTextEdit->setText(QString::fromStdString(Reader(paragraphPath).read()));
	}
	else {
		return;
	}
}
void MainWindow::searchTextChanged() {
 }

void MainWindow::feedingTheModel(){
	map<string, int> words = this->proccess.generalWords;
	for (auto it = words.begin(); it != words.end(); ++it) 
		this->list<<(QString::fromStdString(it->first));
}


void MainWindow::updateFrequency(const QString& searchText) {
	/*bool isInList = false;
	for (const QString& item : this->list) {
		if (item.contains(searchText, Qt::CaseInsensitive)) {
			isInList = true;
			break;
		}
	}*/
	if (searchText.isEmpty()) {
		frequencyLabel->clear(); // Clear the frequency label if search text is empty
		return;
	}

		frequencyLabel->setText("");
		map<string, int> localWords = this->proccess.getWords();

	
		vector<pair<string, int>> correct = proccess.searchauto(searchText.toStdString());
		vector<pair<string, int>>autocorrect = proccess.searchcorrect(searchText.toStdString());
		QString formattedText;
		

		for (const auto& t : correct) {
			
				formattedText += QString("Word: %1, Global Frequency: %2,Local Frequency: %3, Local Rank: %4, Global Rank: %5\n").arg(QString::fromStdString(t.first), QString::number(t.second), QString::number(localWords[t.first]), QString::number(this->proccess.rankkingbyfreq(t.first, false)), QString::number(this->proccess.rankkingbyfreq(t.first, true)));
			
			//formattedText += QString("\nWord: %1, Global Frequency: %2,Local Frequency: %3, Local Rank: %4, Global Rank: %5").arg(QString::fromStdString(t.first), QString::number(t.second), QString::number(localWords[t.first]), QString::number(this->proccess.rankkingbyfreq(t.first, false)), QString::number(this->proccess.rankkingbyfreq(t.first, true)));
		}
		if(formattedText.isEmpty())
		for (const auto& t : autocorrect) {
				formattedText += QString("Word: %1, Global Frequency: %2,Local Frequency: %3, Local Rank: %4, Global Rank: %5\n").arg(QString::fromStdString(t.first), QString::number(t.second), QString::number(localWords[t.first]), QString::number(this->proccess.rankkingbyfreq(t.first, false)), QString::number(this->proccess.rankkingbyfreq(t.first, true)));
			}
		

		frequencyLabel->setText(formattedText);
		return;
	

	/*auto words = this->proccess.generalWords;
	if (words.find(searchText.toStdString()) != words.end()) {
		QString formattedText = QString("Word: %1, Frequency: %2").arg(searchText, QString::number(words.at(searchText.toStdString())));
		frequencyLabel->setText(formattedText);
	}
	else {
		frequencyLabel->setText("Word not found");
	}*/
}

void MainWindow:: modify() {
	this->proccess.modify(paragraphTextEdit->toPlainText().toStdString());
	if(!FilePath.isEmpty())
	Reader(FilePath.toStdString()).write(paragraphTextEdit->toPlainText().toStdString());

}
MainWindow::~MainWindow()
{
	Reader().writeGeneralmap(TextProcessor::generalWords);
}

