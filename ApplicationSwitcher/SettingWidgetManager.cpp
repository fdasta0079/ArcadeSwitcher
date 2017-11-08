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
            settingWidget->deleteLater();
        }
    }
}

void SettingWidgetManager::createNewGameEntry()
{
    SettingWidget* settingWidget = new SettingWidget(this);

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