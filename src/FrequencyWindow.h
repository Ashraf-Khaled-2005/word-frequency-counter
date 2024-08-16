#pragma once
#ifndef FREQUENCYWINDOW_H
#define FREQUENCYWINDOW_H
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QListView>
#include <QFileDialog>
class FrequencyWindow : public QMainWindow

{
    Q_OBJECT
public:
    FrequencyWindow(QWidget* parent = nullptr);
    void setTable(QTableWidget* t);
private slots:
    
private:
    QDialog dialog;
    QVBoxLayout* freqLayout;
    QTableWidget* freqListView;
    QVBoxLayout* mainLayout;
    QWidget* centralWidget;

};

#endif