#include "SettingWidget.h"

SettingWidget::SettingWidget(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    m_ui.setupUi(this);

    connect(m_ui.deleteButton, &QPushButton::clicked, this, &SettingWidget::deletePressed);
}

SettingWidget::~SettingWidget() {}

const QString SettingWidget::getGameName()
{
    return m_ui.nameEdit->text();
}

const QString SettingWidget::getGamePath()
{
    return m_ui.pathEdit->text();
}

const QString SettingWidget::getGameDescription()
{
    return "";
    //TODO: Return description.
}