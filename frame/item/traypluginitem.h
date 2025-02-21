// SPDX-FileCopyrightText: 2011 - 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TRAYPLUGINITEM_H
#define TRAYPLUGINITEM_H

#include "pluginsitem.h"

class TrayPluginItem : public PluginsItem
{
    Q_OBJECT

public:
    TrayPluginItem(PluginsItemInterface* const pluginInter, const QString &itemKey, const QString &pluginApi, QWidget *parent = nullptr);

    inline ItemType itemType() const override {return ItemType::TrayPlugin;}

    void setSuggestIconSize(QSize size);
    void setRightSplitVisible(const bool visible);
    int trayVisibleItemCount();

Q_SIGNALS:
    void trayVisableCountChanged(const int &count) const;

private:
    bool eventFilter(QObject *watched, QEvent *e) override;

private:
    int m_trayVisableItemCount = 0;
};

#endif // TRAYPLUGINITEM_H
