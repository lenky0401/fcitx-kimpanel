/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  lenky gao    lenky0401@gmail.com/gaoqunkai@ubuntukylin.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MAIN_CONTROLLER_H__
#define __MAIN_CONTROLLER_H__

#include <QObject>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QTimer>
#include "main_model.h"
#include "system_tray_menu.h"
#include "kimpanelagent.h"
#include "toplevel.h"
#include "skin/skinbase.h"

//必须与FcitxCandidateLayoutHint的定义一致
enum CandidateLayout {
    CLH_NotSet,
    CLH_Vertical,
    CLH_Horizontal
};

class MainController : public QObject
{
    Q_OBJECT

public:
    static MainController* self();
    virtual ~MainController();
    void init();

private:
    explicit MainController();
    static MainController *mSelf;

private:
    TopLevel *mTopLevel;
    MainModel *mModel;
    PanelAgent *mAgent;
    SkinBase *mSkinBase;
    QDeclarativeView *mView;
    QUrl mUrl;
    QTimer *mTimer;
    QSystemTrayIcon *mSystemTray;
    SystemTrayMenu *mTrayMenu;
    bool mIsHorizontal;
    QString mSkinType;

public:
    void setSkinBase(SkinBase *skinBase);
    QString getSkinType();
    void setSkinType(QString skinType);

public slots:
    void updateProperty(const KimpanelProperty &prop);
    void updatePreeditText(const QString inputString, 
        QList<TextAttribute> attributes);

    void updateLookupTable(const KimpanelLookupTable &lookup_table);
    void updateLookupTableFull(const KimpanelLookupTable &lookup_table,
        int cursor, int layout);

    void updateSpotLocation(int x, int y);
    void updateSpotRect(int x, int y, int w, int h);
    void showPreedit(bool to_show);
    void showAux(bool to_show);
    void updateAux(const QString &text, const QList<TextAttribute> &attr);
    void showLookupTable(bool to_show);
    void updateLookupTableCursor(int pos);
    void updatePreeditCaret(int pos);

public:
    Q_INVOKABLE void getPrevPage();
    Q_INVOKABLE void getNextPage();
    Q_INVOKABLE void selectCandidate(int index);
};

#endif // __MAIN_CONTROLLER_H__
