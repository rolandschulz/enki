'''***************************************************************************
**
**         Created using Monkey Studio v1.8.1.0
** Authors    : Filipe AZEVEDO aka Nox P@sNox <pasnox@gmail.com>
** Project   : Monkey Studio IDE
** FileName  : BasePlugin.h
** Date      : 2008-01-14T00:37:00
** License   : GPL
** Comment   : This header has been automatically generated, you are the original author, co-author, free to replace/append with your informations.
** Home Page : http:#www.monkeystudio.org
**
    Copyright (C) 2005 - 2008  Filipe AZEVEDO & The Monkey Studio Team

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with self program; if not, to the Free Software
    Foundation, Inc., Franklin St, Floor, Boston, 02110-1301  USA
**
***************************************************************************'''
#ifndef BASEPLUGIN_H
#define BASEPLUGIN_H

#include <objects/MonkeyExport.h>
#include <objects/pIconManager.h>

#include "main.h"
#include "coremanager/MonkeyCore.h"
#include "settingsmanager/Settings.h"

#include <QtPlugin>
#include <QPointer>
#include <QAction>

#ifdef __COVERAGESCANNER__
#include <QCoreApplication>
#include <QDir>
#endif

class Q_MONKEY_EXPORT BasePlugin : public QObject
    Q_OBJECT
    Q_ENUMS( Type )

    friend class PluginsManager; # for call fillPluginInfo()

public:
    # plugin type enums
    enum Type
        iAll = 0x0,
        iBase = 0x1,
        iChild = 0x2,
        iCLITool = 0x4,
        iBuilder = 0x8,
        iDebugger = 0x20,
        iInterpreter = 0x40,
        iXUP = 0x80,
        iLast = 0x100


    Q_DECLARE_FLAGS( Types, Type )

    # plugin info structure
    struct Q_MONKEY_EXPORT PluginInfos
        PluginInfos()
            Type = BasePlugin.iAll
            FirstStartEnabled = False
            HaveSettingsWidget = False
            ApplicationVersionRequired = PACKAGE_VERSION


        QString Caption; # the string to show as caption
        QString Description; # the plugin description
        QString Author; # the plugin author
        BasePlugin.Types Type; # the plugin type ( can be or-ded )
        QStringList Languages; # language self plugin is for, empty mean all
        QString Name; # the plugin name for version control
        QString Version; # the plugin version for version control
        QString License; # the plugin license
        bool FirstStartEnabled; # to know if self plugin is enabled
        bool HaveSettingsWidget; # plugin has settings widget
        QPixmap Pixmap; # plugin icon
        QString ApplicationVersionRequired; # the minimum mks version self plugin require, must not enable itself if minimum version is not reached !


    BasePlugin()
    virtual ~BasePlugin()

    virtual PluginInfos infos()
        return mPluginInfos


    static QString typeToString( BasePlugin.Type type )
    static QString completeTypeToString( BasePlugin.Types type )

    QString captionVersionString()

    QAction* stateAction()

    bool neverEnable()
        return settingsValue( "NeverEnable", False ).toBool()


    void setNeverEnable( bool never )
        return setSettingsValue( "NeverEnable", never )


    virtual QWidget* settingsWidget()
        return 0


    virtual bool isEnabled()
        return stateAction().isChecked()


    # Method does some work and calls install() or uninstall()
    virtual bool setEnabled( bool )

    virtual QString settingsKey(  QString& key )
    virtual QVariant settingsValue(  QString& key, value = QVariant() )
    virtual void setSettingsValue(  QString& key, value )

    # coverage support members
#ifdef __COVERAGESCANNER__
    virtual void saveCodeCoverage(  QString& n, s )
#endif

protected:
    mutable QPointer<QAction> mAction
    PluginInfos mPluginInfos

    # Internal functions for install/uninstall plugin. Called by setEnabled()
    virtual bool install() = 0
    virtual bool uninstall() = 0

    # Must be implemented by plugin, plugin info '''
    virtual void fillPluginInfos() = 0


Q_DECLARE_OPERATORS_FOR_FLAGS( BasePlugin.Types )
Q_DECLARE_METATYPE( BasePlugin* )
Q_DECLARE_METATYPE( BasePlugin.PluginInfos )
Q_DECLARE_INTERFACE( BasePlugin, "org.monkeystudio.MonkeyStudio.BasePlugin/1.0" )

#endif # BASEPLUGIN_H
