# Enki. A text editor for programmers


## Why new code editor?
vim and emacs are really grate editors. 2 the best in the history. But original vi was created at 1976, emacs was started at mid-1970s. Time goes, world changes. A lot of new cool technologies has been invented.

Currently some programmers **spend a lot of time to learn and configure vim or emacs**. Than become fans of one of the editors and try to argue, that favorite editor is very intuitive, user friendly and it is absolutelly impossible to create better interface.

Other people **move from one ugly GUI IDE to another**, and finally understand, that all it is even worse, than vi and emacs. Some people never understand.

Vim and Emacs are powerful, extensible and hacker friendly. But not usable. Modern IDEs are beginner friendly, but often slow, force you to use your mouse and do not allow a hacker to work as productivelly as possible.

I'm absolutelly sure, that it is possible to **join all the best in one project**. I really can't understand why the open source comunity hasn't done it yet. **Where are heros of the new generation?**

I'm going to create next Unix text editor. Of course, such revolution can't be done by one man, but only by the comunity. **Your bug reports, suggestions, patches... are welcome!**

## Enki principles

* Intuitive and clear interface. Works out of the box. You don't have to read a lot of docs
* Hacker friendly. Minimize your mouse usage and work quicker.
* Minimalistic interface. Screen is used for code, not for bells and whistles.
* Powerful. Smart.
* Extensible. Missing feature or language support? Don't create a new IDE, create a plugin

## Features
 * Syntax highlighting for more than 30 languages
 * Bookmarks
 * Powerful search and replace functionality for files and directories.
 * File browser (File system tree)
 * Locator. File open dialog with bash-like Tab completion and globs support. Even better, than bash.
 * Autocompletion, based on document contents
 * Hightly configurable
 * [MIT Scheme REPL integration](https://github.com/hlamer/enki/wiki/Scheme-support)

<table frame="void">
    <tr>
        <td width="25%">
            <a href="http://hlamer.github.com/enki/screenshots/main-ui.png">
                <img src="http://hlamer.github.com/enki/screenshots/preview/main-ui.png" width="100%" height="100%"/>
            </a>
            UI
        </td>
        <td width="25%">
            <a href="http://hlamer.github.com/enki/screenshots/minimal.png">
                <img src="http://hlamer.github.com/enki/screenshots/preview/minimal.png" width="100%" height="100%"/>
            </a>
            Minimalistic UI
        </td>
        <td width="25%">
            <a href="http://hlamer.github.com/enki/screenshots/search.png">
                <img src="http://hlamer.github.com/enki/screenshots/preview/search.png" width="100%" height="100%"/>
            </a>
            Search
        </td>
        <td width="25%">
            <a href="http://hlamer.github.com/enki/screenshots/search-replace.png">
                <img src="http://hlamer.github.com/enki/screenshots/preview/search-replace.png" width="100%" height="100%"/>
            </a>
            Good bye sed
        </td>
    </tr>
</table>

enki is **crossplatform**, but, currently has been tested only on Linux. Team will be appreciate you, if you shared your experience about other platforms.

The project is licensed under **GNU GPL v2** license

## Download and install

#### Ubuntu

Supported versions are 10.04 - 11.10. For other, see Debian instructions.

    sudo add-apt-repository ppa:monkeystudio/ppa
    sudo apt-get update
    sudo apt-get install enki
    

#### Debian (and based on it)


1. Download **enki{latest version}~ppa1_all.deb** package from [Monkey Studio PPA](https://launchpad.net/~monkeystudio/+archive/ppa/+packages)
2. Install the package with

`sudo dpkg --install enki*.deb`

#### Source package

See [source installation instructions](https://github.com/hlamer/enki/wiki/source-installation-instructions)

## Documentation and support


* [Documentation](https://github.com/hlamer/enki/wiki/User-manual)
* [Discussion and support Google group](http://groups.google.com/group/enki)
* IRC room `#enki` on `irc.freenode.net`. [Web interface](http://hlamer.github.com/enki/irc.html). We never kick our users!


## Report bug

There are 3 ways to report a bug:

* Fork the repository and fix it
* Fill an [issue](https://github.com/hlamer/enki/issues)
* Send bug report to enki-bugs@googlegroups.com

## Hacking

Documentation for developers is [here](http://hlamer.github.com/enki/api)


## Authors

* **Andrei Kopats** ported core and some plugins to Python, reworked it and released the result as *enki*
* **Filipe Azevedo**, **Andrei Kopats** (aka **hlamer**) and [Monkey Studio v2 team](http://monkeystudio.org/team) developed *Monkey Studio v2*
* **Filipe Azevedo** (aka **P@sNox**) and [Monkey Studio v1 team](http://monkeystudio.org/node/17) developed *Monkey Studio v1*

See [The Team](https://github.com/hlamer/enki/wiki/Team)


Use enki-editor@googlegroups.com or hlamer@tut.by as contact email.

<a href="https://sourceforge.net/donate/index.php?group_id=163493" target="_blank"> <img src="https://images-ssl.sourceforge.net/images/project-support.jpg"/></a>
