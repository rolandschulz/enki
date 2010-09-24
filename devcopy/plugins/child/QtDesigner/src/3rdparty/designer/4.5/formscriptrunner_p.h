'''***************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use self file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of self file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http:#www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, a special exception, gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, in the file LGPL_EXCEPTION.txt in self
** package.
**
** GNU General Public License Usage
** Alternatively, file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of self file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http:#www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
***************************************************************************'''

#ifndef FORMSCRIPTRUNNER_H
#define FORMSCRIPTRUNNER_H

#
#  W A R N I N G
#  -------------
#
# This file is not part of the Qt API.  It exists purely as an
# implementation detail.  This header file may change from version to
# version without notice, even be removed.
#
# We mean it.
#

#include <QtDesigner/uilib_global.h>
#include <QtCore/QList>
#include <QtCore/QFlags>
#include <QtCore/QString>

QT_BEGIN_NAMESPACE

class QWidget

#ifdef QFORMINTERNAL_NAMESPACE
namespace QFormInternal
#endif

class DomWidget

class QDESIGNER_UILIB_EXPORT QFormScriptRunner
public:
    QFormScriptRunner()
    ~QFormScriptRunner()

    typedef QList<QWidget*> WidgetList

    bool run( DomWidget *domWidget,
              QString &customWidgetScript,
             QWidget *widget, &children,
             QString *errorMessage)

    struct Error
        QString objectName
        QString script
        QString errorMessage

    typedef QList<Error> Errors
    Errors errors()
    void clearErrors()

    enum Option
        NoOptions = 0x0,
        DisableWarnings = 0x1,
        DisableScripts = 02

    Q_DECLARE_FLAGS(Options, Option)

    Options options()
    void setOptions(Options options)

private:
    class QFormScriptRunnerPrivate
    QFormScriptRunnerPrivate *m_impl

    QFormScriptRunner( QFormScriptRunner &)
    operator = ( QFormScriptRunner &)


Q_DECLARE_OPERATORS_FOR_FLAGS(QFormScriptRunner.Options)

#ifdef QFORMINTERNAL_NAMESPACE

#endif

QT_END_NAMESPACE

#endif # FORMSCRIPTRUNNER_H
