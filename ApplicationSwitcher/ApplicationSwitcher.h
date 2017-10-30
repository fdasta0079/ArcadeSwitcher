#pragma once

#include <QtWidgets/QMainWindow>
#include <QProcess>

#include "ui_ApplicationSwitcher.h"

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
	Ui::ApplicationSwitcherClass m_ui;

	QProcess* m_curProcess;
};
