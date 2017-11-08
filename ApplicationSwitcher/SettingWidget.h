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

signals:
    void deletePressed();

private:
    Ui::settingWidget m_ui;
};