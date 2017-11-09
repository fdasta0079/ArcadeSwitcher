#include "ApplicationSwitcher.h"

#include <QPushButton>
#include <QDir>
#include <QSettings>
#include <QtGamepad\qgamepad.h>

#include "SettingWidgetManager.h"
#include "SettingWidget.h" //TODO: Circular/bad include?

ApplicationSwitcher::ApplicationSwitcher(QWidget *parent)
    : QMainWindow(parent),
    m_curProcess(nullptr)
{
    m_ui.setupUi(this);
    qRegisterMetaTypeStreamOperators<GameInfoList>("GameInfoList");

    m_settingManager = new SettingWidgetManager(this);
    m_settingManager->setWindowModality(Qt::WindowModality::WindowModal);
    connect(m_ui.tmpEditSettingsButton, &QPushButton::clicked, m_settingManager, &QWidget::show);
    connect(m_settingManager, &QDialog::finished, this, &ApplicationSwitcher::regenerateGameList);

    m_curProcess = new QProcess(this);

    connect(m_curProcess, &QProcess::stateChanged, this, &ApplicationSwitcher::appStateChanged);
    
    readSettings();

    /*
    Todo List:
    - Fancy selection window with nice grafixxxx.
    - Saving of settings.
    - Process status checking (need to disable running another thing if we're running something, for instance.)
    - USB controls, with interruption on a button.
    */
}

ApplicationSwitcher::~ApplicationSwitcher()
{
    if (m_curProcess) {
        m_curProcess->terminate();
        m_curProcess->deleteLater();
    }

    if (m_settingManager) {
        m_settingManager->deleteLater();
    }

    QLayoutItem* item;
    while (item = m_ui.launchButtonLayout->takeAt(0)) {
        if (item->widget()) {
            delete item;
        }
    }
}

void ApplicationSwitcher::writeSettings()
{
    QSettings settings (QSettings::IniFormat, QSettings::UserScope, "Bonus Round", "Arcade Switcher");

    settings.setValue("GameList", QVariant::fromValue(m_settingManager->getGameList()));
    settings.sync();
}

void ApplicationSwitcher::readSettings()
{
    QSettings settings (QSettings::IniFormat, QSettings::UserScope, "Bonus Round", "Arcade Switcher");

    m_settingManager->setGameList(settings.value("GameList").value<GameInfoList>());
    regenerateGameList();
}

void ApplicationSwitcher::launchProcess()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if (!button) {
        return;
    }

    if (m_curProcess->state() == QProcess::NotRunning) {
        //Slash direction matters!
        QString path = QDir::fromNativeSeparators(button->property("Path").toString());

        if (path.isEmpty()) {
            return; //TODO: Bad game error msg.
        }

        QStringList args; //We'll probably need to import the args from the settings screen, but that's for when we get cool.

        m_curProcess->setProgram(path);
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

void ApplicationSwitcher::regenerateGameList()
{
    QLayoutItem* item;
    while (item = m_ui.launchButtonLayout->takeAt(0)) {
        if (item->widget()) {
            delete item->widget();
        }
    }

    GameInfoList gameList = m_settingManager->getGameList();

    for (auto game : gameList) {
        QPushButton* gameButton = new QPushButton();
        gameButton->setProperty("Path", game.path);
        gameButton->setText("Launch " + game.name);
        gameButton->setToolTip(game.path);
        m_ui.launchButtonLayout->addWidget(gameButton);
        connect(gameButton, &QPushButton::clicked, this, &ApplicationSwitcher::launchProcess);
    }

    writeSettings();
}