"""Status bar shows shows current line, column, save state, EOL and indent mode
"""

import os.path

from PyQt4 import uic

from PyQt4.QtCore import QSize, Qt
from PyQt4.QtGui import QDialog, QFrame, QIcon, QLabel, QMenu, QPixmap, QStatusBar, QToolBar, QToolButton

import mks.monkeycore

"""AK: Idea of _EolIndicatorAndSwitcher, and icons for it was taken from juffed
"""

class _EolIndicatorAndSwitcher(QToolButton):
    """This widget is visible on Status Bar as EOL type icon.
    It draws menu with EOL choise and switches EOL
    """
    _ICON_FOR_MODE = {r'\r\n'   : "winEol.png",
                      r'\r'     : "macEol.png",
                      r'\n'     : "unixEol.png"}
    
    def __init__(self, parent):
        QToolButton.__init__(self, parent)
        self.setEnabled(False)
        self.setToolTip(self.tr("Line endings. Click for convert"))
        self.setIconSize(QSize(16, 16))  # FIXME hlamer: it doesn't work for my Ubuntu, why???
        self.setPopupMode(QToolButton.InstantPopup)
        
        menu = QMenu(self)  # menu filled on popup. Performance optimisation for quicker start up
        self.setMenu(menu)
        menu.aboutToShow.connect(self._onMenuAboutToShow)
        menu.triggered.connect(self._onEolActionTriggered)
        
        mks.monkeycore.workspace().currentDocumentChanged.connect(self._onCurrentDocumentChanged)
    
    def _onCurrentDocumentChanged(self, oldDocument, currentDocument):
        if currentDocument is not None:
            self._setEolMode( currentDocument.eolMode() )
        else:
            self._setEolMode(None)
    
    def _onMenuAboutToShow(self):
        document = mks.monkeycore.workspace().currentDocument()
        if document is not None:
            currentMode = document.eolMode()
            self._updateEolMenu(currentMode)

    def _updateEolMenu(self, currentMode):
        """Generate EOL menu
        """
        self.menu().clear()
        
        def addAction(text, eolMode):
            action = self.menu().addAction(QIcon(':/mksicons/' + self._ICON_FOR_MODE[eolMode]), text)
            action.setData(eolMode)
            if eolMode == currentMode:
                action.setCheckable(True)
                action.setChecked(True)
            return action

        addAction(self.tr("CR+LF: Windows"), r'\r\n')
        addAction(self.tr("CR: Mac OS (but not Mac OS X)"), r'\r')
        addAction(self.tr("LF: Unix"), r'\n')

    def _onEolActionTriggered(self, action):
        newEol = str(action.data().toString())
        editor = mks.monkeycore.workspace().currentDocument()
        editor.setEolMode(newEol)
        self._setEolMode(editor.eolMode())

    def _setEolMode(self, mode):
        if mode is not None:
            self.setIcon(QIcon(':/mksicons/' + self._ICON_FOR_MODE[mode]))
            self.setEnabled(True)
        else:
            self.setEnabled(False)

class _IndentationDialog(QDialog):
    """Indentation dialog appears, if indentation label on the status bar clicked
    """
    def __init__(self, parent, document):
        QDialog.__init__(self, parent)
        self._document = document
        
        uic.loadUi(os.path.join(mks.monkeycore.dataFilesPath(), 'IndentationDialog.ui'), self)        
        
        self._widthSlider.setValue(document.indentWidth())
        self._updateWidthLabel()
        self._widthSlider.valueChanged.connect(self._onWidthChanged)
        
        if document.indentUseTabs():
            self._tabsRadio.setChecked(True)
        else:
            self._spacesRadio.setChecked(True)
        self._tabsRadio.toggled.connect(self._onTabsToggled)        
        
        self._convertButton.clicked.connect(self._onConvertClicked)
    
    def _updateWidthLabel(self):
        template = unicode(self.tr("Width: %d"))
        self._widthLabel.setText(template % self._document.indentWidth())
        
    def _onWidthChanged(self, value):
        self._document.setIndentWidth(value)
        self._updateWidthLabel()
    
    def _onConvertClicked(self):
        pass
    
    def _onTabsToggled(self, toggled):
        self._document.setIndentUseTabs(toggled)

class _IndentIndicatorAndSwitcher(QToolButton):
    """This widget is visible on Status Bar as indent type label
    It draws menu with indent choise and switches indent
    """
    
    def __init__(self, parent):
        QToolButton.__init__(self, parent)
        self.setEnabled(False)
        
        self.setToolTip(self.tr("Indentation mode. Click to change"))
        
        self.clicked.connect(self._onClicked)
        mks.monkeycore.workspace().currentDocumentChanged.connect(self._onCurrentDocumentChanged)
        
    
    def _onCurrentDocumentChanged(self, oldDocument, currentDocument):
        if currentDocument is not None:
            self._setIndentMode( currentDocument.indentWidth(), currentDocument.indentUseTabs() )
        else:
            self._clearIndentMode()
    
    def _onClicked(self):
        document = mks.monkeycore.workspace().currentDocument()
        if document is not None:
            dialog = _IndentationDialog(self, document)
            dialog.exec_()
            self._setIndentMode(document.indentWidth(), document.indentUseTabs())
    
    def _setIndentMode(self, width, useTabs):
        if useTabs:
            self.setText(self.tr("Tabs"))
        else:
            self.setText(self.tr("%s spaces" % width))
        self.setEnabled(True)
    
    def _clearIndentMode(self):
        self.setEnabled(False)

class StatusBar(QStatusBar):
    """Class implementes statusbar. Bar shows current line, column, save state, EOL and indent mode
    """

    def __init__(self, parent):
        QStatusBar.__init__(self, parent)
        # create labels
        
        def createLabel(tip):
            label = QLabel(self)
            label.setToolTip(tip)
            label.setMargin( 2 )
            label.setFrameStyle( QFrame.NoFrame )
            label.setAttribute( Qt.WA_MacSmallSize )
            self.addPermanentWidget( label )
            return label
        
        self._cursorPos = createLabel(self.tr("Cursor position"))
        self._modified = createLabel(self.tr("Modification state of file"))

        bar = QToolBar(self)        
        # EOL indicator and switcher
        bar.addWidget(_EolIndicatorAndSwitcher(self))
        # Indentation indicator and switcher
        bar.addWidget(_IndentIndicatorAndSwitcher(bar))
        
        self.addPermanentWidget(bar)
        
        createLabel(self.tr("Line")).setText("Line:")
        self._line = createLabel(self.tr("Line"))
        createLabel(self.tr("Column")).setText("Column:")
        self._col = createLabel(self.tr("Column"))
        
        # Avoid flickering, when line length of a number changes
        self._line.setMinimumWidth(30)
        self._line.setMargin(0)
        self._col.setMinimumWidth(30)
        self._line.setMargin(0)
        
        # force remove statusbar label frame
        self.setStyleSheet( "QStatusBar.item { border: 0px; }" )
        
        # connections
        self.messageChanged.connect(self.setMessage)
        
        mks.monkeycore.workspace().currentDocumentChanged.connect(self._onCurrentDocumentChanged)

    def _onCurrentDocumentChanged(self, oldDocument, currentDocument):
        # Update connections
        if oldDocument is not None:
            oldDocument.cursorPositionChanged.disconnect(self._setCursorPosition)
            oldDocument.modifiedChanged.disconnect(self._setModified)
        if currentDocument is not None:
            currentDocument.cursorPositionChanged.connect(self._setCursorPosition)
            currentDocument.modifiedChanged.connect(self._setModified)
        
        # Update info
        if currentDocument is not None:
            self._setModified( currentDocument.isModified() )
            #self.setIndentMode( currentDocument.indentUseTabs())
            self._setCursorPosition( *currentDocument.cursorPosition())
        else:
            self._setModified(False)
            #self.setIndentMode( document.indentsUseTabs())
            self._setCursorPosition(-1, -1)

    def setMessage(self, message ):
        self.showMessage( message )
        self.setToolTip( message )

    def _setModified(self, modified):
        icon = QIcon( ":/mksicons/save.png" )
        if modified:
            pixmap = icon.pixmap(16, 16, QIcon.Normal)
        else:
            pixmap = icon.pixmap(16, 16, QIcon.Disabled)
        self._modified.setPixmap(pixmap)
    
    def setIndentMode(self, mode ):
        self._indent.setText(mode)

    def _setCursorPosition(self, line, col):
        if line != -1 and col != -1:
            self._line.setText(str(line))
            self._col.setText(str(col))
        else:
            self._line.setText('-')
            self._col.setText('-')