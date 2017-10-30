/********************************************************************************
** Form generated from reading UI file 'ApplicationSwitcher.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATIONSWITCHER_H
#define UI_APPLICATIONSWITCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApplicationSwitcherClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *launcherBox;
    QVBoxLayout *verticalLayout;
    QPushButton *testBroforceButton;
    QPushButton *testSamuraiGunnButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ApplicationSwitcherClass)
    {
        if (ApplicationSwitcherClass->objectName().isEmpty())
            ApplicationSwitcherClass->setObjectName(QStringLiteral("ApplicationSwitcherClass"));
        ApplicationSwitcherClass->resize(600, 400);
        centralWidget = new QWidget(ApplicationSwitcherClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        launcherBox = new QGroupBox(centralWidget);
        launcherBox->setObjectName(QStringLiteral("launcherBox"));
        verticalLayout = new QVBoxLayout(launcherBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        testBroforceButton = new QPushButton(launcherBox);
        testBroforceButton->setObjectName(QStringLiteral("testBroforceButton"));

        verticalLayout->addWidget(testBroforceButton);

        testSamuraiGunnButton = new QPushButton(launcherBox);
        testSamuraiGunnButton->setObjectName(QStringLiteral("testSamuraiGunnButton"));

        verticalLayout->addWidget(testSamuraiGunnButton);


        gridLayout->addWidget(launcherBox, 0, 0, 1, 1);

        ApplicationSwitcherClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ApplicationSwitcherClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        ApplicationSwitcherClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ApplicationSwitcherClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ApplicationSwitcherClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ApplicationSwitcherClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ApplicationSwitcherClass->setStatusBar(statusBar);

        retranslateUi(ApplicationSwitcherClass);

        QMetaObject::connectSlotsByName(ApplicationSwitcherClass);
    } // setupUi

    void retranslateUi(QMainWindow *ApplicationSwitcherClass)
    {
        ApplicationSwitcherClass->setWindowTitle(QApplication::translate("ApplicationSwitcherClass", "ApplicationSwitcher", Q_NULLPTR));
        launcherBox->setTitle(QApplication::translate("ApplicationSwitcherClass", "LauncherBox", Q_NULLPTR));
        testBroforceButton->setText(QApplication::translate("ApplicationSwitcherClass", "Launch Broforce", Q_NULLPTR));
        testSamuraiGunnButton->setText(QApplication::translate("ApplicationSwitcherClass", "Launch Samurai Gunn", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ApplicationSwitcherClass: public Ui_ApplicationSwitcherClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATIONSWITCHER_H
