#include "SettingWidget.h"

#include <QFileDialog>

SettingWidget::SettingWidget(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    m_ui.setupUi(this);

    connect(m_ui.deleteButton, &QPushButton::clicked, this, &SettingWidget::deletePressed);
    connect(m_ui.browseButton, &QPushButton::clicked, this, &SettingWidget::browseForGame);
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

void SettingWidget::setGameName(const QString& name)
{
    m_ui.nameEdit->setText(name);
}

void SettingWidget::setGamePath(const QString& path)
{
    m_ui.pathEdit->setText(path);
}

void SettingWidget::setGameDescription(const QString& description)
{
    //TODO: set description.
}

void SettingWidget::browseForGame()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select Executable"), "",
        tr("Applications (*.exe);;All Files (*)"));

    m_ui.pathEdit->setText(fileName);
}