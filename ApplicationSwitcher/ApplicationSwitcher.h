#pragma once

#include <QMainWindow>
#include <QProcess>

#include "ui_ApplicationSwitcher.h"

class SettingWidgetManager;

class ApplicationSwitcher : public QMainWindow
{
    Q_OBJECT

public:
    ApplicationSwitcher(QWidget *parent = Q_NULLPTR);
    virtual ~ApplicationSwitcher();

private slots:
    void launchProcess(/*const QString& procName*/);
    void appStateChanged(QProcess::ProcessState newState);

private:
    void regenerateGameList();

    Ui::ApplicationSwitcherClass m_ui;

    SettingWidgetManager* m_settingManager;

    QProcess* m_curProcess;
};
