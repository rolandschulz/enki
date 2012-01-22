from PyQt4.QtCore import pyqtSignal, Qt, QTimer
from PyQt4.QtGui import QAction, QColor, QDockWidget, QPainter

from .pDockWidgetTitleBar import pDockWidgetTitleBar

class pDockWidget(QDockWidget):
    
    toggleViewAction_triggered = pyqtSignal()
    
    def __init__(self, *args):
        QDockWidget.__init__(self, *args)

        self._showAction = None
        self._titleBar = pDockWidgetTitleBar( self )
        self.setTitleBarWidget( self._titleBar )
        self.toggleViewAction().triggered.connect(self.toggleViewAction_triggered)

    def paintEvent(self, event ):
        QDockWidget.paintEvent(self,  event )
        
        if  self.isFloating() and style().objectName().tolower() != "Oxygen".tolower():
            rect = self.rect().adjusted( 0, 0, -1, -1 )
            
            painter = QPainter( self )
            painter.setPen( QColor( 145, 142, 142 ) )
            painter.setBrush( Qt.NoBrush )
            painter.drawRect( rect )

    def titleBar(self):
        return self._titleBar

    def showAction(self):
        if  not self._showAction :
            self._showAction = QAction(self.windowIcon(), self.windowTitle(), self)
            self._showAction.activated.connect(self.show)
            self._showAction.activated.connect(self.handleFocusProxy)

        return self._showAction


    def toggleViewAction_triggered(self, toggled ):
        if  toggled and focusProxy():
            if  self.isFloating():
                QTimer.singleShot( 0, self.handleWindowActivation )
            else:
                QTimer.singleShot( 0, self.handleFocusProxy )

    def handleWindowActivation(self):
        self.activateWindow()
        QTimer.singleShot( 0, self.handleWindowActivation )

    def handleFocusProxy(self):
        if  self.focusProxy() :
            self.focusProxy().setFocus()

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Escape and \
           event.modifiers() == Qt.NoModifier:
                self.hide()
        else:
            return QDockWidget.keyPressEvent( self, event )