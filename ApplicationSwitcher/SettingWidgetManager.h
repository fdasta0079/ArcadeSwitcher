#pragma once

#include <QDialog>
#include "ui_settingWidgetManager.h"

class SettingWidget;

struct GameInfo
{
    QString name;
    QString path;
    QString description;
};

inline QDataStream &operator << (QDataStream &out, const GameInfo& gameInfo)
{
    out << gameInfo.name;
    out << gameInfo.path;
    out << gameInfo.description;

    return out;
}

inline QDataStream &operator >> (QDataStream &in, GameInfo& gameInfo)
{
    in >> gameInfo.name;
    in >> gameInfo.path;
    in >> gameInfo.description;

    return in;
}

typedef QList<GameInfo> GameInfoList;

Q_DECLARE_METATYPE(GameInfoList);

inline QDataStream &operator << (QDataStream &out, const GameInfoList& gameInfoList)
{
    int count = gameInfoList.size();
    out << count;

    for (auto gameInfo : gameInfoList) {
        out << gameInfo;
    }

    return out;
}

inline QDataStream &operator >> (QDataStream &in, GameInfoList& gameInfoList)
{
    int count = 0;
    in >> count;

    for (int i = 0; i < count; ++i) {
        GameInfo gameInfo;
        in >> gameInfo;

        gameInfoList.push_back(gameInfo);
    }

    return in;
}

class SettingWidgetManager : public QDialog
{
    Q_OBJECT

public:
    SettingWidgetManager(QWidget* parent = nullptr, Qt::WindowFlags flags = 0);
    virtual ~SettingWidgetManager();

    const GameInfoList getGameList();
    void setGameList(const GameInfoList&);

private:
    Ui::settingWidgetManager m_ui;

    QList<SettingWidget*> m_settingWidgetList;

    void createNewGameEntryPrivate(const GameInfo&);

private slots:
    void createNewGameEntry();
    void deleteGameEntry();
};

