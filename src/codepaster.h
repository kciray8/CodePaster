/****************************************************************************
**
** CodePaster is program to simple and quick copy/paste snippets of code and organize it
** Copyright (C) 2013 Yaroslaw Baranow(aka KciRay).
** Contact: Yaroslaw Baranow (kciray8@gmail.com)
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
*****************************************************************************/

#ifndef CODEPASTER_H
#define CODEPASTER_H

#include <QMainWindow>
#include <QtCore>
#include <QSystemTrayIcon>
#include <QSettings>

#include <contrib/utils/uglobalhotkeys.h>

class CodePaster : public QWidget {
    Q_OBJECT
    enum {COPY, PASTE};
    QSystemTrayIcon m_tray;
    UGlobalHotkeys Hotkeys;
    QTimer autoSaveTimer;
    QString m_basePath;
    
    QSettings m_settings;
public:
    CodePaster();
    ~CodePaster();

    void saveStrInFile(QString &str, QString filePatch);
    void saveInFile(QString filePatch);
    void load();
public slots:
    void exit();
    void save();
private slots:
    void onHotkeyActivated(size_t id);
    void onAddSnippet();
    void onSearch();
    void autoSave();
};

#endif // CODEPASTER_H
