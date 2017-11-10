#pragma once

#include <QWidget>
#include "ui_settingWidget.h"

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    SettingWidget(QWidget* parent, Qt::WindowFlags flags = 0);
    virtual ~SettingWidget();

    const QString getGameName();
    const QString getGamePath();
    const QString getGameDescription();
    const QString getGameImage();

    void setGameName(const QString&);
    void setGamePath(const QString&);
    void setGameDescription(const QString&);
    void setGameImage(const QString&);

signals:
    void deletePressed();

private slots:
    void browseForGame();
    void browseForImage();

private:
    Ui::settingWidget m_ui;
};