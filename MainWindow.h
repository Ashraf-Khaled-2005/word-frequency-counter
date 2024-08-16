#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets/QMainWindow>
#include <map>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QListView>
#include <QFileDialog>
#include <QStringListModel>
#include <QStringList>
#include <QSizePolicy>
#include <QCompleter>
#include <QAbstractItemView>
#include <TextProcessor.h>
class MainWindow : public QMainWindow
    
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private slots:
    void processTextButtonClicked();
    void openFileDialog();
    void searchTextChanged();
    void feedingTheModel();
    void updateFrequency(const QString& searchText);
    void showGlobalFrequencies();
    void modify();
private:
    QLabel* frequencyLabel;
    TextProcessor proccess;
    QString FilePath;
    QStringList list;
    QStringListModel* model;
    QListView* searchListView;
    QVBoxLayout* mainLayout;
    QLabel* searchLabel;
    QHBoxLayout* searchBarLayout;
    QLineEdit* searchBar;
    QGroupBox* paragraphBox;
    QVBoxLayout* paragraphBoxLayout;
    QTextEdit* paragraphTextEdit;
    QHBoxLayout* buttonsLayout;
    QPushButton* processTextButton;
    QPushButton* uploadTextButton;
    QPushButton* modifyTextButton;
    QPushButton* showGlobalFreq;
    QPushButton* saveButton;
    QHBoxLayout* filterLayout;
    QLineEdit* filterBar;
    QLabel* filterLabel;
    QGroupBox* filterBox;
    QWidget* centralWidget;
   
};

#endif