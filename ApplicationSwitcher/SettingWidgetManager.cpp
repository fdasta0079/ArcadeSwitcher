#include "SettingWidgetManager.h"

#include "SettingWidget.h"

SettingWidgetManager::SettingWidgetManager(QWidget* parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    m_ui.setupUi(this);

    connect(m_ui.addGameButton, &QPushButton::clicked, this, &SettingWidgetManager::createNewGameEntry);
}

SettingWidgetManager::~SettingWidgetManager() 
{
    for (auto&& settingWidget : m_settingWidgetList) {
        if (settingWidget) {
            delete settingWidget;
        }
    }

    m_settingWidgetList.clear();
}

void SettingWidgetManager::setGameList(const GameInfoList& gameInfoList)
{
    for (auto&& gameInfo : gameInfoList) {
        createNewGameEntryPrivate(gameInfo);
    }
}

const GameInfoList SettingWidgetManager::getGameList()
{
    GameInfoList gameInfoList;

    for (auto&& settingWidget : m_settingWidgetList) {
        if (settingWidget) {
            GameInfo gameInfo;
            gameInfo.name = settingWidget->getGameName();
            gameInfo.path = settingWidget->getGamePath();
            gameInfo.description = settingWidget->getGameDescription();
            gameInfo.image = settingWidget->getGameImage();

            gameInfoList.append(gameInfo);
        }
    }

    return gameInfoList;
}

void SettingWidgetManager::createNewGameEntry()
{
    createNewGameEntryPrivate(GameInfo());
}

void SettingWidgetManager::createNewGameEntryPrivate(const GameInfo& gameInfo)
{
    SettingWidget* settingWidget = new SettingWidget(this);
    settingWidget->setGameName(gameInfo.name);
    settingWidget->setGamePath(gameInfo.path);
    settingWidget->setGameDescription(gameInfo.description);
    settingWidget->setGameImage(gameInfo.image);

    m_ui.settingWidgetLayout->addWidget(settingWidget);
    m_settingWidgetList.append(settingWidget);

    connect(settingWidget, &SettingWidget::deletePressed, this, &SettingWidgetManager::deleteGameEntry);
}

void SettingWidgetManager::deleteGameEntry()
{
    SettingWidget* sender = qobject_cast<SettingWidget*>(QObject::sender());

    if (!sender) {
        return;
    }

    sender->hide();
    m_ui.settingWidgetLayout->removeWidget(sender);
    m_settingWidgetList.removeAll(sender);
    sender->deleteLater();
}