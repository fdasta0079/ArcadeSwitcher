#include "SettingWidget.h"

#include <QFileDialog>

SettingWidget::SettingWidget(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    m_ui.setupUi(this);

    connect(m_ui.deleteButton, &QPushButton::clicked, this, &SettingWidget::deletePressed);
    connect(m_ui.browseGameButton, &QPushButton::clicked, this, &SettingWidget::browseForGame);
    connect(m_ui.browseImageButton, &QPushButton::clicked, this, &SettingWidget::browseForImage);
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
    //TODO: Return rich text (requires slight rewrite of stream operators).
    return m_ui.descriptionEdit->toPlainText();
}

const QString SettingWidget::getGameImage()
{
    return m_ui.imageEdit->text();
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
    m_ui.descriptionEdit->setText(description);
}

void SettingWidget::setGameImage(const QString& image)
{
    m_ui.imageEdit->setText(image);
}

void SettingWidget::browseForGame()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select Executable"), "",
        tr("Applications (*.exe);;All Files (*)"));

    m_ui.pathEdit->setText(fileName);
}

void SettingWidget::browseForImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select Image"), "",
        tr("Image Files (*.png *.jpg *.bmp);;All Files (*)"));

    m_ui.imageEdit->setText(fileName);
}