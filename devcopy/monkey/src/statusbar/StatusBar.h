#ifndef QUEUEDSTATUSBAR_H
#define QUEUEDSTATUSBAR_H

#include <objects/MonkeyExport.h>
#include <qsciscintilla.h>

#include <QStatusBar>

class QLabel

class Q_MONKEY_EXPORT StatusBar : public QStatusBar
    Q_OBJECT

public:
    enum LabelType { ltCursorPosition, ltSaveState, ltEOLMode, ltIndentMode
    StatusBar( parent = 0 )

    QLabel* label( StatusBar.LabelType type )

protected:
    QLabel* mLabels[4]

public slots:
    void setMessage(  QString& message )
    void setModified( bool modified )
    void setEOLMode( QsciScintilla.EolMode mode ); # -1 for none
    void setIndentMode( int mode ); # -1 for none, for spaces, for tabs
    void setCursorPosition(  QPoint& pos ); # QPoint( -1, -1 ) for none


#endif # QUEUEDSTATUSBAR_H
