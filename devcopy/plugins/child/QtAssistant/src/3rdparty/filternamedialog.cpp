'''***************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Assistant of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use self file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** self package.
**
** GNU Lesser General Public License Usage
** Alternatively, file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of self file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http:#www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, a special exception, gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, in the file LGPL_EXCEPTION.txt in self package.
**
** If you have questions regarding the use of self file, contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
***************************************************************************'''

#include <QtGui/QPushButton>

#include "filternamedialog.h"

QT_BEGIN_NAMESPACE

FilterNameDialog.FilterNameDialog(QWidget *parent)
        : QDialog(parent)
    m_ui.setupUi(self)
    connect(m_ui.buttonBox.button(QDialogButtonBox.Ok),
            SIGNAL(clicked()), self, SLOT(accept()))
    connect(m_ui.buttonBox.button(QDialogButtonBox.Cancel),
            SIGNAL(clicked()), self, SLOT(reject()))
    connect(m_ui.lineEdit, SIGNAL(textChanged(QString)),
            self, SLOT(updateOkButton()))
    m_ui.buttonBox.button(QDialogButtonBox.Ok).setDisabled(True)



def filterName(self):
    return m_ui.lineEdit.text()


def updateOkButton(self):
    m_ui.buttonBox.button(QDialogButtonBox.Ok)
    .setDisabled(m_ui.lineEdit.text().isEmpty())


QT_END_NAMESPACE
