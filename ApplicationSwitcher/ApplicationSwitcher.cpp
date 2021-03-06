#include "ApplicationSwitcher.h"

#include <QPushButton>
#include <QDir>
#include <QSettings>
#include <QImageReader>
#include <QtGamepad\qgamepad.h>

#include "SettingWidgetManager.h"

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

    m_ui.descriptionEdit->setReadOnly(true);

    /*
    Todo List:
    - Fancy selection window with nice grafixxxx.
    - Process status checking (need to disable running another thing if we're running something, for instance.)
    - USB controls, with interruption on a button.
    - Figure out how to mitigate issue where steam launches and then launches the game, thus breaking our control signals. Offline mode in Steam isn't a fix.
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
        gameButton->setProperty("Image Path", game.image);
        gameButton->setProperty("Description", game.description);
        gameButton->setText("Launch " + game.name);
        gameButton->setToolTip(game.path);
        m_ui.launchButtonLayout->addWidget(gameButton);
        connect(gameButton, &QPushButton::clicked, this, &ApplicationSwitcher::launchProcess);
        gameButton->installEventFilter(this);
    }

    writeSettings();
}

bool ApplicationSwitcher::eventFilter(QObject *obj, QEvent *event)
{
    QPushButton* button = qobject_cast<QPushButton*>(obj);
    if (button) {
        if (event->type() == QEvent::Enter) {
            m_ui.descriptionEdit->setText(button->property("Description").toString());
            //TODO: Save the pixmaps as a property instead of loading the file every time.
            //There also isn't really any testing to see if the image is valid, but YOLO.
            int w = m_ui.imageLabel->width();
            int h = m_ui.imageLabel->height();
            m_ui.imageLabel->setPixmap(QPixmap(button->property("Image Path").toString()).scaled(w, h, Qt::KeepAspectRatio));
        }

        return QWidget::eventFilter(obj, event);
    }
}