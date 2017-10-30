#include "ApplicationSwitcher.h"

#include <QPushButton>
#include <QtGamepad\qgamepad.h>

ApplicationSwitcher::ApplicationSwitcher(QWidget *parent)
	: QMainWindow(parent),
	m_curProcess(nullptr)
{
	m_ui.setupUi(this);

	connect(m_ui.testBroforceButton, &QPushButton::clicked, this, &ApplicationSwitcher::launchProcess);
	connect(m_ui.testSamuraiGunnButton, &QPushButton::clicked, this, &ApplicationSwitcher::launchProcess);

	m_curProcess = new QProcess(this);

	connect(m_curProcess, &QProcess::stateChanged, this, &ApplicationSwitcher::appStateChanged);
	
	/*
	Todo List:
	- Settings window allowing for specifying arbitrary games and their arguments.
	- Fancy selection window with nice grafixxxx.
	- Saving of settings.
	- Process status checking (need to disable running another thing if we're running something, for instance.)
	- USB controls, with interruption on a button.
	- Put this all up on Github.
	*/
}

ApplicationSwitcher::~ApplicationSwitcher()
{
	if (m_curProcess) {
		m_curProcess->terminate();
		m_curProcess->deleteLater();
	}
}

void ApplicationSwitcher::launchProcess()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());

	if (!button) {
		return;
	}

	if (m_curProcess->state() == QProcess::NotRunning) {
		//Doing this based on the button text is gross, but this is temporary anyway.
		//Slash direction matters!
		QString testPath;
		if (button->text().contains("Broforce", Qt::CaseInsensitive)) {
			testPath = "D:/Programs/Steam/steamapps/common/Broforce/Broforce_beta.exe";
		} else if (button->text().contains("Samurai Gunn", Qt::CaseInsensitive)) {
			testPath = "D:/Programs/Steam/steamapps/common/Samurai Gunn/SamuraiGunn.exe";
		}

		QStringList args; //We'll probably need to import the args from the settings screen, but that's for when we get cool.

		m_curProcess->setProgram(testPath);
		m_curProcess->setArguments(args);

		m_curProcess->start();

	} else {
		//This means that control has returned to the UI and another game launched without the first closing.
		//What to do here? Try to terminate the old game and circle back? Throw up an assert?
		//Decisions need to be made.
		m_curProcess->kill();
		//TODO: Call attendant error message.
	}
}

void ApplicationSwitcher::appStateChanged(QProcess::ProcessState newState)
{
	if (newState == QProcess::NotRunning) {
		m_ui.launcherBox->setEnabled(true);
	} else {
		m_ui.launcherBox->setEnabled(false);
	}
}
