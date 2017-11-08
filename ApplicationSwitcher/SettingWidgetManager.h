#pragma once

#include <QDialog>
#include "ui_settingWidgetManager.h"

class SettingWidget;

class SettingWidgetManager : public QDialog
{
    Q_OBJECT

public:
    SettingWidgetManager(QWidget* parent = nullptr, Qt::WindowFlags flags = 0);
    virtual ~SettingWidgetManager();

    const QList<SettingWidget*> getSettingWidgetList() { return m_settingWidgetList; }

private:
    Ui::settingWidgetManager m_ui;

    QList<SettingWidget*> m_settingWidgetList;

private slots:
    void createNewGameEntry();
    void deleteGameEntry();

};