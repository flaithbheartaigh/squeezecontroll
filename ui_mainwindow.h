/*
    Copyright (C) 2010 Michael Rahr

    This file is part of SqueezeRemote.

    SqueezeRemote is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    SqueezeRemote is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SqueezeRemote.  If not, see <http://www.gnu.org/licenses/>.
*/


/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri 19. Mar 13:25:25 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>
#include <kineticlist.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QFrame *frame_2;
    QPushButton *play_2;
    QPushButton *skib_b_2;
    QPushButton *skib_f_2;
    QLineEdit *track_2;
    QLabel *label_7;
    QPushButton *Settings;
    kineticList *myList;
    QFrame *frame_5;
    QWidget *page_2;
    QLineEdit *lineEdit;
    QLabel *label_8;
    QPushButton *search;
    QPushButton *play_3;
    QPushButton *Add;
    QListWidget *album;
    QListWidget *contributor;
    QListWidget *trackliste;
    QLabel *label;
    QLabel *label_17;
    QLabel *label_18;
    QWidget *page_3;
    QLabel *label_6;
    QFrame *frame;
    QPushButton *play;
    QPushButton *skib_b;
    QPushButton *skib_f;
    QSlider *power;
    QLabel *pixture;
    QLineEdit *track_4;
    kineticList *ListTrack;
    QFrame *frame_6;
    QWidget *page_4;
    QLabel *label_9;
    QFrame *frame_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_8;
    QGroupBox *Network;
    QLabel *label_3;
    QLineEdit *server_ip;
    QCheckBox *server_autoconnect;
    QLabel *label_4;
    QLineEdit *server_port;
    QLabel *label_5;
    QLineEdit *server_port_2;
    QLabel *isConnected;
    QGroupBox *SqueezeCenter;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_7;
    QLabel *squ1;
    QLabel *squ2;
    QLabel *squ3;
    QLabel *squ4;
    QFrame *frame_4;
    QRadioButton *radioButton_8;
    QFrame *sync;
    QLabel *label_2;
    QLabel *sync_label;
    QProgressBar *progressBar;
    QGroupBox *ControlBox;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(360, 640);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, -1, 360, 641));
        stackedWidget->setAutoFillBackground(false);
        stackedWidget->setStyleSheet(QString::fromUtf8("\n"
"QWidget{\n"
"background-color: rgb(44, 44, 44);\n"
"}\n"
""));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        stackedWidget->setFrameShadow(QFrame::Sunken);
        stackedWidget->setLineWidth(2);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setAutoFillBackground(false);
        page->setStyleSheet(QString::fromUtf8("QToolButton:pressed{ \n"
"border-top: 1px transparent;\n"
"border-bottom: 1px transparent;\n"
"border-right: 1px transparent;\n"
"border-left: 1px transparent;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QToolButton{\n"
"background-color: rgb(5, 5, 5);\n"
"border-top: 3px transparent;\n"
"border-bottom:3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent; \n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QToolButton#back{\n"
"border-image: url(:/icon/agt_back-32.png) 3 3 3 3;\n"
"\n"
"}\n"
"\n"
"QToolButton#back:pressed{ \n"
"border-image: url(:/icon//agt_back-32.png) 3 3 3 5;\n"
"}\n"
"\n"
"QToolButton#forward{\n"
"border-image: url(:/icon/agt_forward-32.png) 3 3 3 3;\n"
"\n"
"}\n"
"\n"
"QToolButton#forward:pressed{ \n"
"border-image: url(:/icon//agt_forward-32.png) 3 3 3 5;\n"
"}\n"
"\n"
"QPushButton#Settings{\n"
"border-top: 1px transparent;\n"
"border-bottom: 1px transparent;\n"
"border-right: 1px transparent;\n"
"border-left: 3px transparent;\n"
""
                        "background-color: rgba(255, 255, 255, 0);\n"
"\n"
"border-image: url(:/icon/Settings-32.png) 2 2 2 2;\n"
"}\n"
"\n"
"QPushButton#Settings:pressed{ \n"
"border-top: 3px transparent;\n"
"border-bottom: 3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;\n"
"border-image: url(:/icon/Settings-32.png) 1 1 1 1;\n"
"}\n"
"\n"
"\n"
"\n"
"QLineEdit{\n"
"color: rgb(230, 224, 255);\n"
"font: 8pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(5, 5,5);\n"
"border-style:inset; \n"
" border-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"\n"
"}\n"
"QFrame{\n"
"background-color: qlineargradient(spread:pad, x1:0.517, y1:0.852318, x2:0.522727, y2:0.068, stop:0.170455 rgba(0, 0, 0, 255), stop:0.789773 rgba(50, 50, 50, 252));\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"border-style:inset; \n"
" border-top: 0px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
""
                        " border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"padding: 0 8px; \n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"QListWidget{\n"
"	color: rgb(255,255, 255);\n"
"\n"
"}\n"
"\n"
"QLabel{\n"
"	color: rgb(0, 0, 255);\n"
"\n"
"   border-top: 1px solid gray; \n"
"  border-right: 1px solid gray; \n"
"   border-radius: 10px; \n"
"   padding: 0 8px; \n"
"    background-color: rgb(255, 255, 255);\n"
"	background-color: rgb(7, 7, 7);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
""));
        frame_2 = new QFrame(page);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(-10, 540, 381, 111));
        frame_2->setStyleSheet(QString::fromUtf8("QPushButton:pressed{ \n"
"border-top: 1px transparent;\n"
"border-bottom: 1px transparent;\n"
"border-right: 1px transparent;\n"
"border-left: 1px transparent;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QPushButton{\n"
"background-color: rgb(5, 5, 5);\n"
"border-top: 3px transparent;\n"
"border-bottom:3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent; \n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"\n"
"QPushButton#play_2{\n"
"border-image: url(:/icon/Albums.jpg) 3 3 3 3;\n"
"}\n"
"\n"
"QPushButton#play_2:pressed{ \n"
"border-image: url(:/icon/album_sel.jpg) 3 3 3 3;\n"
"\n"
"}\n"
"\n"
"QPushButton#skib_b_2{\n"
"border-image: url(:/icon/artist.jpg) 3 3 2 3;\n"
"}\n"
"\n"
"QPushButton#skib_b_2:pressed{ \n"
"border-image: url(:/icon/artist_sel.jpg) 3 3 2 3;\n"
"		background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.0852273 rgba(255, 255, 255, 151), stop:0.227273 rgba(255, 255, 255, 225), stop:0.505682 r"
                        "gba(255, 255, 255, 200), stop:0.693182 rgba(255, 255, 255, 135), stop:0.840909 rgba(252, 252, 252, 105), stop:1 rgba(255, 255, 255, 2));\n"
"}\n"
"\n"
"QPushButton#skib_f_2{\n"
"border-image: url(:/icon/playlist.jpg) 3 3 2 3;\n"
"}\n"
"\n"
"QPushButton#skib_f_2:pressed{ \n"
"border-image: url(:/icon/playlist_sel.jpg) 3 3 2 3;\n"
"		background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.0852273 rgba(255, 255, 255, 151), stop:0.227273 rgba(255, 255, 255, 225), stop:0.505682 rgba(255, 255, 255, 200), stop:0.693182 rgba(255, 255, 255, 135), stop:0.840909 rgba(252, 252, 252, 105), stop:1 rgba(255, 255, 255, 2));\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
""));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        play_2 = new QPushButton(frame_2);
        play_2->setObjectName(QString::fromUtf8("play_2"));
        play_2->setGeometry(QRect(140, 20, 96, 74));
        play_2->setFocusPolicy(Qt::NoFocus);
        play_2->setAutoDefault(true);
        play_2->setDefault(true);
        skib_b_2 = new QPushButton(frame_2);
        skib_b_2->setObjectName(QString::fromUtf8("skib_b_2"));
        skib_b_2->setGeometry(QRect(20, 20, 96, 74));
        skib_b_2->setFocusPolicy(Qt::NoFocus);
        skib_b_2->setAutoDefault(true);
        skib_b_2->setDefault(true);
        skib_f_2 = new QPushButton(frame_2);
        skib_f_2->setObjectName(QString::fromUtf8("skib_f_2"));
        skib_f_2->setGeometry(QRect(260, 20, 96, 74));
        skib_f_2->setFocusPolicy(Qt::NoFocus);
        skib_f_2->setAutoDefault(true);
        skib_f_2->setDefault(true);
        track_2 = new QLineEdit(frame_2);
        track_2->setObjectName(QString::fromUtf8("track_2"));
        track_2->setGeometry(QRect(120, 0, 141, 21));
        track_2->setCursor(QCursor(Qt::BlankCursor));
        track_2->setMouseTracking(false);
        track_2->setFocusPolicy(Qt::NoFocus);
        track_2->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgba(0, 0, 0, 0);\n"
"color:rgb(221, 221, 221);\n"
"font: 6pt \"MS Shell Dlg 2\";\n"
"border: 0"));
        track_2->setEchoMode(QLineEdit::Normal);
        track_2->setAlignment(Qt::AlignCenter);
        track_2->setReadOnly(true);
        label_7 = new QLabel(page);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(2, 3, 358, 110));
        label_7->setLayoutDirection(Qt::LeftToRight);
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 210);\n"
"font: 5pt \"MS Shell Dlg 2\";\n"
"color:rgb(221, 221, 221);\n"
""));
        label_7->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        Settings = new QPushButton(page);
        Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->setGeometry(QRect(420, 10, 31, 32));
        myList = new kineticList(page);
        myList->setObjectName(QString::fromUtf8("myList"));
        myList->setGeometry(QRect(5, 123, 350, 400));
        myList->setStyleSheet(QString::fromUtf8("background-color: rgb(91, 81, 111);"));
        frame_5 = new QFrame(page);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(0, 120, 358, 411));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        stackedWidget->addWidget(page);
        frame_2->raise();
        label_7->raise();
        Settings->raise();
        frame_5->raise();
        myList->raise();
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setStyleSheet(QString::fromUtf8("QToolButton:pressed{ \n"
"border-top: 1px transparent;\n"
"border-bottom: 1px transparent;\n"
"border-right: 1px transparent;\n"
"border-left: 1px transparent;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QToolButton{\n"
"background-color: rgb(5, 5, 5);\n"
"border-top: 3px transparent;\n"
"border-bottom:3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent; \n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QToolButton#back_2{\n"
"border-image: url(:/icon/agt_back-32.png) 3 3 3 3;\n"
"\n"
"}\n"
"\n"
"QToolButton#back_2:pressed{ \n"
"border-image: url(:/icon//agt_back-32.png) 3 3 3 5;\n"
"}\n"
"\n"
"QToolButton#forward_2{\n"
"border-image: url(:/icon/agt_forward-32.png) 3 3 3 3;\n"
"\n"
"}\n"
"\n"
"QToolButton#forward_2:pressed{ \n"
"border-image: url(:/icon//agt_forward-32.png) 3 3 3 5;\n"
"}\n"
"\n"
"\n"
"QLineEdit{\n"
"color: rgb(230, 224, 255);\n"
"font: 8pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(5, 5,5);\n"
"border-style:inset; \n"
" border-t"
                        "op: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"\n"
"}\n"
"QFrame{\n"
"background-color: rgb(5, 5,5);\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"border-style:inset; \n"
" border-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"padding: 0 8px; \n"
"\n"
"}\n"
"\n"
"QLabel{\n"
"	color: rgb(0, 0, 255);\n"
"\n"
"   border-top: 1px solid gray; \n"
"  border-right: 1px solid gray; \n"
"   border-radius: 10px; \n"
"   padding: 0 8px; \n"
"    background-color: rgb(255, 255, 255);\n"
"	background-color: rgb(7, 7, 7);\n"
"}\n"
"\n"
""));
        lineEdit = new QLineEdit(page_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(2, 120, 358, 41));
        label_8 = new QLabel(page_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(2, 3, 358, 110));
        label_8->setLayoutDirection(Qt::LeftToRight);
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 210);\n"
"font: 5pt \"MS Shell Dlg 2\";\n"
"color:rgb(221, 221, 221);\n"
"\n"
""));
        label_8->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        label_8->setIndent(0);
        search = new QPushButton(page_2);
        search->setObjectName(QString::fromUtf8("search"));
        search->setGeometry(QRect(100, 590, 151, 41));
        search->setFocusPolicy(Qt::NoFocus);
        play_3 = new QPushButton(page_2);
        play_3->setObjectName(QString::fromUtf8("play_3"));
        play_3->setGeometry(QRect(0, 590, 91, 41));
        play_3->setFocusPolicy(Qt::NoFocus);
        Add = new QPushButton(page_2);
        Add->setObjectName(QString::fromUtf8("Add"));
        Add->setGeometry(QRect(260, 590, 101, 41));
        Add->setFocusPolicy(Qt::NoFocus);
        album = new QListWidget(page_2);
        album->setObjectName(QString::fromUtf8("album"));
        album->setGeometry(QRect(2, 190, 358, 111));
        album->setStyleSheet(QString::fromUtf8("color: rgb(211, 211, 211);\n"
"font: 5pt \"MS Shell Dlg 2\";"));
        album->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        contributor = new QListWidget(page_2);
        contributor->setObjectName(QString::fromUtf8("contributor"));
        contributor->setGeometry(QRect(2, 330, 358, 111));
        contributor->setStyleSheet(QString::fromUtf8("color:rgb(220, 220, 220);\n"
"font: 5pt \"MS Shell Dlg 2\";"));
        contributor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        trackliste = new QListWidget(page_2);
        trackliste->setObjectName(QString::fromUtf8("trackliste"));
        trackliste->setGeometry(QRect(2, 470, 358, 111));
        trackliste->setStyleSheet(QString::fromUtf8("color: rgb(214, 214, 214);\n"
"font: 5pt \"MS Shell Dlg 2\";"));
        trackliste->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label = new QLabel(page_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 168, 131, 20));
        label->setStyleSheet(QString::fromUtf8("font: 5pt \"MS Shell Dlg 2\";"));
        label_17 = new QLabel(page_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 308, 131, 20));
        label_17->setStyleSheet(QString::fromUtf8("font: 5pt \"MS Shell Dlg 2\";"));
        label_18 = new QLabel(page_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 448, 131, 20));
        label_18->setStyleSheet(QString::fromUtf8("font: 5pt \"MS Shell Dlg 2\";"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setStyleSheet(QString::fromUtf8("\n"
"QToolButton:pressed{ \n"
"border-top: 1px transparent;\n"
"border-bottom: 1px transparent;\n"
"border-right: 1px transparent;\n"
"border-left: 1px transparent;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QToolButton{\n"
"background-color: rgb(5, 5, 5);\n"
"border-top: 3px transparent;\n"
"border-bottom:3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent; \n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QToolButton#back_3{\n"
"border-image: url(:/icon/agt_back-32.png) 3 3 3 3;\n"
"\n"
"}\n"
"\n"
"QToolButton#back_3:pressed{ \n"
"border-image: url(:/icon//agt_back-32.png) 3 3 3 5;\n"
"}\n"
"\n"
"QToolButton#forward_3{\n"
"border-image: url(:/icon/agt_forward-32.png) 3 3 3 3;\n"
"\n"
"}\n"
"\n"
"QToolButton#forward_3:pressed{ \n"
"border-image: url(:/icon//agt_forward-32.png) 3 3 3 5;\n"
"}\n"
"\n"
"\n"
"QLineEdit{\n"
"color: rgb(230, 224, 255);\n"
"font: 8pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(5, 5,5);\n"
"border-style:inset; \n"
" bor"
                        "der-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"\n"
"}\n"
"QFrame{\n"
"background-color: qlineargradient(spread:pad, x1:0.517, y1:0.852318, x2:0.522727, y2:0.068, stop:0.170455 rgba(0, 0, 0, 255), stop:0.789773 rgba(50, 50, 50, 252));\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"border-style:inset; \n"
" border-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"padding: 0 8px; \n"
"\n"
"}\n"
"\n"
"QFrame#frame{\n"
" border-top: 0px solid gray; \n"
"}\n"
"QListWidget{\n"
"	color: rgb(255,255, 255);\n"
"\n"
"}\n"
"\n"
"QLabel{\n"
"	color: rgb(0, 0, 255);\n"
"\n"
"   border-top: 1px solid gray; \n"
"  border-right: 1px solid gray; \n"
"   border-radius: 10px; \n"
"   padding: 0 8px; \n"
"    background-color: rgb(255, 255, 255);\n"
"	background-color: rgb(7, 7, 7);\n"
"}\n"
"\n"
"QProgressBar{\n"
"	c"
                        "olor: rgb(0, 0, 255);\n"
"\n"
"   border-top: 1px solid gray; \n"
"  border-right: 1px solid gray; \n"
"   border-radius: 7px; \n"
"\n"
"   padding: 0 3px; \n"
"    background-color: rgb(255, 255, 255);\n"
"	background-color: rgb(7, 7, 7);\n"
"}\n"
"\n"
"QProgressBar::chunk { \n"
"	background-color: qlineargradient(spread:reflect, x1:0.516864, y1:0.516, x2:0.505318, y2:0.04, stop:0.00568182 rgba(0, 61, 255, 255), stop:0.806818 rgba(66, 66, 66, 214));\n"
"width: 1px; \n"
"}\n"
"\n"
"\n"
"QSlider::groove:horizontal { \n"
"background-color: rgb(44, 44, 44);\n"
"position: absolute; /* absolutely position 4px from the left and right of the widget. setting margins on the widget should work too... */\n"
"height: 15px;\n"
"width: 300px;\n"
"margin: 0 8 0 0;\n"
"\n"
"\n"
" } \n"
"\n"
"QSlider::handle:horizontal {\n"
"\n"
"	background-image: url(:/icon/bullet_silver_50.png);\n"
"\n"
"width: 30px;\n"
"height: 10px;\n"
" margin: -8 -5; /* handle is placed by default on the contents rect of the groove. Expand outside the g"
                        "roove */ \n"
"} \n"
"\n"
"QSlider::add-page:horizontal {\n"
" background: white;\n"
"   border-top: 1px solid gray; \n"
"  border-right: 1px solid gray; \n"
"   border-radius: 4px; \n"
"   padding: 0 0px; \n"
"  \n"
"	background-color: rgb(0, 0, 0);\n"
"\n"
"} \n"
"\n"
"QSlider::sub-page:horizontal {\n"
"   border-top: 1px solid gray; \n"
"  border-right: 1px solid gray; \n"
"   border-radius: 4px; \n"
"   padding: 0 8px; \n"
" \n"
"	background-color: qlineargradient(spread:reflect, x1:0.516864, y1:0.516, x2:0.505318, y2:0.04, stop:0.00568182 rgba(0, 61, 255, 255), stop:0.806818 rgba(66, 66, 66, 214));\n"
"	\n"
"\n"
"}\n"
""));
        label_6 = new QLabel(page_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(2, 3, 358, 110));
        label_6->setLayoutDirection(Qt::LeftToRight);
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 210);\n"
"font: 5pt \"MS Shell Dlg 2\";\n"
"color:rgb(221, 221, 221);\n"
"padding: 0px;"));
        label_6->setScaledContents(true);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6->setMargin(0);
        label_6->setIndent(100);
        frame = new QFrame(page_3);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(-3, 510, 371, 141));
        frame->setStyleSheet(QString::fromUtf8("QPushButton:pressed{ \n"
"background-color: rgb(0, 0, 0,0);\n"
"border-top: 3px transparent;\n"
"border-bottom: 5px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;\n"
"}\n"
"\n"
"QPushButton{\n"
" \n"
"	background-color: rgb(0, 0, 0,0);\n"
"border-top: 3px transparent;\n"
"border-bottom: 5px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent; \n"
"}\n"
"\n"
"\n"
"QPushButton#play{\n"
"border-image: url(:/icon/play.png);\n"
"\n"
"}\n"
"\n"
"QPushButton#play:pressed{ \n"
"border-image: url(:/icon/play.png) 3 3 2 3;\n"
"		background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.0852273 rgba(255, 255, 255, 151), stop:0.227273 rgba(255, 255, 255, 225), stop:0.505682 rgba(255, 255, 255, 200), stop:0.693182 rgba(255, 255, 255, 135), stop:0.840909 rgba(252, 252, 252, 105), stop:1 rgba(255, 255, 255, 2));\n"
"}\n"
"\n"
"QPushButton#skib_b{\n"
"border-image: url(:/icon/previous.png) 3 3 1 3;\n"
"}\n"
"\n"
"QPushButton"
                        "#skib_b:pressed{ \n"
"border-image: url(:/icon/previous.png) 3 3 2 3;\n"
"		background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.0852273 rgba(255, 255, 255, 151), stop:0.227273 rgba(255, 255, 255, 225), stop:0.505682 rgba(255, 255, 255, 200), stop:0.693182 rgba(255, 255, 255, 135), stop:0.840909 rgba(252, 252, 252, 105), stop:1 rgba(255, 255, 255, 2));\n"
"}\n"
"\n"
"QPushButton#skib_f{\n"
"border-image: url(:/icon/next.png) 3 3 2 3;\n"
"}\n"
"\n"
"QPushButton#skib_f:pressed{ \n"
"border-image: url(:/icon/next.png) 3 3 2 3;\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.0852273 rgba(255, 255, 255, 151), stop:0.227273 rgba(255, 255, 255, 255), stop:0.505682 rgba(255, 255, 255, 237), stop:0.693182 rgba(255, 255, 255, 185), stop:0.840909 rgba(252, 252, 252, 105), stop:1 rgba(255, 255, 255, 5));\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton#repeat{\n"
"border-image: url(:/icon/Gnome-Media-Playlist-Repeat-32) 3 3 2 3;\n"
"}\n"
""
                        "\n"
"QPushButton#repeat:pressed{ \n"
"border-image: url(:/icon/Gnome-Media-Playlist-Repeat-32g) 3 3 2 3;\n"
"}\n"
"\n"
"QPushButton#shuffel{\n"
"border-image: url(:/icon/Gnome-Media-Playlist-Shuffle-32) 3 3 2 3;\n"
"}\n"
"\n"
"QPushButton#shuffel:pressed{ \n"
"border-image: url(:/icon/Gnome-Media-Playlist-Shuffle-32) 3 3 2 3;\n"
"}\n"
"\n"
"QPushButton#pause{\n"
"border-image: url(:/icon/PauseNormalBlue) 3 3 2 3;\n"
"}\n"
"\n"
"QPushButton#pause:pressed{ \n"
"border-image: url(:/icon/PausePressedBlue) 3 3 2 3;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        play = new QPushButton(frame);
        play->setObjectName(QString::fromUtf8("play"));
        play->setGeometry(QRect(150, 0, 80, 80));
        play->setFocusPolicy(Qt::NoFocus);
        skib_b = new QPushButton(frame);
        skib_b->setObjectName(QString::fromUtf8("skib_b"));
        skib_b->setGeometry(QRect(10, 0, 80, 80));
        skib_b->setFocusPolicy(Qt::NoFocus);
        skib_f = new QPushButton(frame);
        skib_f->setObjectName(QString::fromUtf8("skib_f"));
        skib_f->setGeometry(QRect(280, 0, 80, 80));
        skib_f->setFocusPolicy(Qt::NoFocus);
        power = new QSlider(frame);
        power->setObjectName(QString::fromUtf8("power"));
        power->setGeometry(QRect(20, 80, 321, 41));
        power->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        power->setSliderPosition(50);
        power->setOrientation(Qt::Horizontal);
        pixture = new QLabel(page_3);
        pixture->setObjectName(QString::fromUtf8("pixture"));
        pixture->setGeometry(QRect(12, 10, 90, 90));
        pixture->setStyleSheet(QString::fromUtf8("QLabel{\n"
"\n"
"   border: 0px solid gray; \n"
"\n"
"   border-radius: 5px; \n"
"\n"
"\n"
"}"));
        pixture->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pixture->setMargin(-10);
        pixture->setIndent(10);
        pixture->setOpenExternalLinks(true);
        pixture->setTextInteractionFlags(Qt::NoTextInteraction);
        track_4 = new QLineEdit(page_3);
        track_4->setObjectName(QString::fromUtf8("track_4"));
        track_4->setGeometry(QRect(100, 500, 141, 23));
        track_4->setCursor(QCursor(Qt::BlankCursor));
        track_4->setMouseTracking(false);
        track_4->setFocusPolicy(Qt::NoFocus);
        track_4->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgba(0, 0, 0, 5);\n"
"color:rgb(221, 221, 221);\n"
"font: 6pt \"MS Shell Dlg 2\";\n"
"border: 0"));
        track_4->setEchoMode(QLineEdit::Normal);
        track_4->setAlignment(Qt::AlignCenter);
        track_4->setReadOnly(true);
        ListTrack = new kineticList(page_3);
        ListTrack->setObjectName(QString::fromUtf8("ListTrack"));
        ListTrack->setGeometry(QRect(5, 122, 352, 375));
        frame_6 = new QFrame(page_3);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(2, 120, 358, 381));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        stackedWidget->addWidget(page_3);
        label_6->raise();
        frame->raise();
        pixture->raise();
        track_4->raise();
        frame_6->raise();
        ListTrack->raise();
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setStyleSheet(QString::fromUtf8("QToolButton:pressed{ \n"
"border-top: 1px transparent;\n"
"border-bottom: 1px transparent;\n"
"border-right: 1px transparent;\n"
"border-left: 1px transparent;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QToolButton{\n"
"background-color: rgb(5, 5, 5);\n"
"border-top: 3px transparent;\n"
"border-bottom:3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent; \n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QToolButton#back_4{\n"
"border-image: url(:/icon/agt_back-32.png) 3 3 3 3;\n"
"\n"
"}\n"
"\n"
"QToolButton#back_4:pressed{ \n"
"border-image: url(:/icon//agt_back-32.png) 3 3 3 5;\n"
"}\n"
"\n"
"QToolButton#forward_4{\n"
"border-image: url(:/icon/agt_forward-32.png) 3 3 3 3;\n"
"\n"
"}\n"
"\n"
"QToolButton#forward_4:pressed{ \n"
"border-image: url(:/icon//agt_forward-32.png) 3 3 3 5;\n"
"}\n"
"\n"
"\n"
"\n"
"QLineEdit{\n"
"color: rgb(230, 224, 255);\n"
"font: 8pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(5, 5,5);\n"
"border-style:inset; \n"
" bor"
                        "der-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"\n"
"}\n"
"QFrame{\n"
"background-color: qlineargradient(spread:pad, x1:0.517, y1:0.852318, x2:0.522727, y2:0.068, stop:0.170455 rgba(0, 0, 0, 255), stop:0.789773 rgba(50, 50, 50, 252));\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"border-style:inset; \n"
" border-top: 0px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"padding: 0 8px; \n"
"\n"
"}\n"
"\n"
"QGroupBox{\n"
"background-color: qlineargradient(spread:pad, x1:0.517, y1:0.852318, x2:0.522727, y2:0.068, stop:0.170455 rgba(0, 0, 0, 255), stop:0.789773 rgba(50, 50, 50, 252));\n"
"font: 8pt \"MS Shell Dlg 2\";\n"
"border-style:inset; \n"
" border-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
""
                        "padding: 0 2px; \n"
"}\n"
"\n"
"QLabel{\n"
"	color: rgb(0, 0, 255);\n"
"\n"
"   border-top: 1px solid gray; \n"
"  border-right: 1px solid gray; \n"
"   border-radius: 10px; \n"
"   padding: 0 8px; \n"
"    background-color: rgb(255, 255, 255);\n"
"	background-color: rgb(7, 7, 7);\n"
"}\n"
"\n"
"QPushButton{\n"
"font: 18pt \"MS Shell Dlg 2\";\n"
"background-color: qlineargradient(spread:pad, x1:0.483, y1:0.00568182, x2:0.5, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-style:inset; \n"
" border-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed{ \n"
"	background-color: qlineargradient(spread:pad, x1:0.494, y1:1, x2:0.523, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-style:inset; \n"
" border-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid "
                        "white;  \n"
"border-radius: 10px; \n"
"\n"
"}"));
        label_9 = new QLabel(page_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(2, 3, 358, 110));
        label_9->setLayoutDirection(Qt::LeftToRight);
        label_9->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 210);\n"
"font: 5pt \"MS Shell Dlg 2\";\n"
"color:rgb(221, 221, 221);\n"
""));
        label_9->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        frame_3 = new QFrame(page_4);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(-10, 540, 381, 111));
        frame_3->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"\n"
"background-color: qlineargradient(spread:pad, x1:0.483, y1:0.00568182, x2:0.5, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-style:inset; \n"
" border-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed{ \n"
"	background-color: qlineargradient(spread:pad, x1:0.494, y1:1, x2:0.523, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-style:inset; \n"
" border-top: 1px solid gray; \n"
"border-right: 1px solid gray;\n"
"border-bottom: 1px solid white;\n"
" border-left: 1px solid white;  \n"
"border-radius: 10px; \n"
"\n"
"}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        pushButton_2 = new QPushButton(frame_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(270, 40, 91, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(7);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        pushButton_2->setFont(font);
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 7pt \"MS Shell Dlg 2\";"));
        pushButton_3 = new QPushButton(frame_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(130, 40, 121, 51));
        pushButton_3->setFont(font);
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 7pt \"MS Shell Dlg 2\";"));
        pushButton = new QPushButton(frame_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 40, 91, 51));
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("font: 7pt \"MS Shell Dlg 2\";"));
        pushButton_8 = new QPushButton(frame_3);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(310, -10, 51, 51));
        pushButton_8->setFocusPolicy(Qt::NoFocus);
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_8{\n"
"border-image: url(:/icon/RecordHot1.png) ;\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QPushButton#pushButton_8:pressed{\n"
"border-image: url(:/icon/RecordPressed1.png) ;\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"}"));
        Network = new QGroupBox(page_4);
        Network->setObjectName(QString::fromUtf8("Network"));
        Network->setGeometry(QRect(10, 130, 341, 35));
        Network->setMouseTracking(true);
        Network->setCheckable(true);
        Network->setChecked(false);
        label_3 = new QLabel(Network);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 320, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 7pt \"MS Shell Dlg 2\";\n"
"color: rgb(0, 0, 255);"));
        server_ip = new QLineEdit(Network);
        server_ip->setObjectName(QString::fromUtf8("server_ip"));
        server_ip->setGeometry(QRect(10, 80, 320, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Serif"));
        font1.setPointSize(7);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        server_ip->setFont(font1);
        server_ip->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(27, 27, 27);\n"
"font: 7pt \"MS Serif\";"));
        server_autoconnect = new QCheckBox(Network);
        server_autoconnect->setObjectName(QString::fromUtf8("server_autoconnect"));
        server_autoconnect->setGeometry(QRect(10, 280, 320, 21));
        server_autoconnect->setStyleSheet(QString::fromUtf8("font: 7pt \"MS Shell Dlg 2\";\n"
"color: rgb(255, 255, 255);"));
        server_autoconnect->setIconSize(QSize(25, 25));
        label_4 = new QLabel(Network);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 120, 320, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 7pt \"MS Shell Dlg 2\";\n"
"color: rgb(0, 0, 255);"));
        server_port = new QLineEdit(Network);
        server_port->setObjectName(QString::fromUtf8("server_port"));
        server_port->setGeometry(QRect(10, 160, 320, 31));
        server_port->setFont(font1);
        server_port->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(27, 27, 27);\n"
"font: 7pt \"MS Serif\";"));
        label_5 = new QLabel(Network);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 200, 320, 31));
        label_5->setStyleSheet(QString::fromUtf8("font: 7pt \"MS Shell Dlg 2\";\n"
"color: rgb(0, 0, 255);"));
        server_port_2 = new QLineEdit(Network);
        server_port_2->setObjectName(QString::fromUtf8("server_port_2"));
        server_port_2->setGeometry(QRect(10, 240, 320, 31));
        server_port_2->setFont(font1);
        server_port_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(27, 27, 27);\n"
"font: 7pt \"MS Serif\";"));
        isConnected = new QLabel(Network);
        isConnected->setObjectName(QString::fromUtf8("isConnected"));
        isConnected->setGeometry(QRect(10, 305, 321, 31));
        isConnected->setStyleSheet(QString::fromUtf8("color: rgb(214, 220, 220);\n"
"font: 5pt \"MS Serif\";"));
        SqueezeCenter = new QGroupBox(page_4);
        SqueezeCenter->setObjectName(QString::fromUtf8("SqueezeCenter"));
        SqueezeCenter->setGeometry(QRect(10, 170, 341, 35));
        SqueezeCenter->setMouseTracking(true);
        SqueezeCenter->setStyleSheet(QString::fromUtf8("QRadioButton{\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"	color: rgb(204, 204, 204);\n"
"}"));
        SqueezeCenter->setCheckable(true);
        SqueezeCenter->setChecked(false);
        radioButton = new QRadioButton(SqueezeCenter);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(77, 40, 200, 17));
        radioButton_2 = new QRadioButton(SqueezeCenter);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(77, 80, 200, 17));
        radioButton_3 = new QRadioButton(SqueezeCenter);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(77, 120, 200, 17));
        radioButton_7 = new QRadioButton(SqueezeCenter);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));
        radioButton_7->setGeometry(QRect(77, 160, 200, 17));
        squ1 = new QLabel(SqueezeCenter);
        squ1->setObjectName(QString::fromUtf8("squ1"));
        squ1->setGeometry(QRect(10, 30, 51, 41));
        squ1->setStyleSheet(QString::fromUtf8("QLabel{\n"
"border:none;\n"
"\n"
"}"));
        squ2 = new QLabel(SqueezeCenter);
        squ2->setObjectName(QString::fromUtf8("squ2"));
        squ2->setGeometry(QRect(10, 70, 51, 41));
        squ2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"border:none;\n"
"\n"
"}"));
        squ3 = new QLabel(SqueezeCenter);
        squ3->setObjectName(QString::fromUtf8("squ3"));
        squ3->setGeometry(QRect(10, 110, 51, 41));
        squ3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"border:none;\n"
"\n"
"}"));
        squ4 = new QLabel(SqueezeCenter);
        squ4->setObjectName(QString::fromUtf8("squ4"));
        squ4->setGeometry(QRect(10, 150, 51, 41));
        squ4->setStyleSheet(QString::fromUtf8("QLabel{\n"
"border:none;\n"
"\n"
"}"));
        frame_4 = new QFrame(SqueezeCenter);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(10, 259, 321, 51));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        radioButton_8 = new QRadioButton(frame_4);
        radioButton_8->setObjectName(QString::fromUtf8("radioButton_8"));
        radioButton_8->setGeometry(QRect(50, 15, 200, 20));
        sync = new QFrame(page_4);
        sync->setObjectName(QString::fromUtf8("sync"));
        sync->setEnabled(true);
        sync->setGeometry(QRect(10, 220, 341, 291));
        sync->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color: rgb(199, 199, 199);\n"
"	font: 7pt \"MS Shell Dlg 2\";\n"
"}"));
        sync->setFrameShape(QFrame::StyledPanel);
        sync->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(sync);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 10, 301, 21));
        sync_label = new QLabel(sync);
        sync_label->setObjectName(QString::fromUtf8("sync_label"));
        sync_label->setGeometry(QRect(20, 40, 301, 21));
        progressBar = new QProgressBar(sync);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(20, 250, 301, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setFormat(QString::fromUtf8(""));
        stackedWidget->addWidget(page_4);
        label_9->raise();
        frame_3->raise();
        SqueezeCenter->raise();
        sync->raise();
        Network->raise();
        ControlBox = new QGroupBox(centralWidget);
        ControlBox->setObjectName(QString::fromUtf8("ControlBox"));
        ControlBox->setGeometry(QRect(0, -200, 360, 91));
        ControlBox->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"background-color: rgba(0, 0, 0, 180);\n"
"border-style:outset; \n"
" border-top: 0px solid gray; \n"
"border-right: 0px solid gray;\n"
"border-bottom: 2px solid rgb(85, 85, 127);\n"
" border-left: 0px solid white;  \n"
"border-radius: 12px; \n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(spread:pad, x1:0.511, y1:0.0742273, x2:0.488273, y2:0.915, stop:0.170455 rgba(0, 0, 0, 255), stop:0.789773 rgba(50, 50, 50, 252));\n"
"}\n"
"\n"
"QPushButton:focus{\n"
"	background-color: qlineargradient(spread:pad, x1:0.511, y1:0.0742273, x2:0.488273, y2:0.915, stop:0.170455 rgba(0, 0, 0, 255), stop:0.789773 rgba(50, 50, 50, 252));\n"
"}"));
        pushButton_6 = new QPushButton(ControlBox);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(265, -2, 90, 90));
        pushButton_6->setFocusPolicy(Qt::StrongFocus);
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_6{\n"
"border-image: url(:/icon/setting-64.png) 3 3 3 3;\n"
"\n"
"}"));
        pushButton_7 = new QPushButton(ControlBox);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(180, -2, 90, 90));
        pushButton_7->setFocusPolicy(Qt::StrongFocus);
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_7{\n"
"border-image: url(:/icon/search-icon.png);\n"
"\n"
"}"));
        pushButton_4 = new QPushButton(ControlBox);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(5, -2, 90, 90));
        pushButton_4->setFocusPolicy(Qt::StrongFocus);
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/icon/ma-Musique-icon.png) 3 3 3 3;\n"
"\n"
"}"));
        pushButton_5 = new QPushButton(ControlBox);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(90, -2, 90, 90));
        pushButton_5->setFocusPolicy(Qt::StrongFocus);
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/icon/liste.png) ;\n"
"\n"
"}"));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        play_2->setText(QString());
        skib_b_2->setText(QString());
        skib_f_2->setText(QString());
        track_2->setText(QApplication::translate("MainWindow", "Track 0 of 15", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Album list", 0, QApplication::UnicodeUTF8));
        Settings->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "Search", 0, QApplication::UnicodeUTF8));
        search->setText(QApplication::translate("MainWindow", "Search", 0, QApplication::UnicodeUTF8));
        play_3->setText(QApplication::translate("MainWindow", "Play", 0, QApplication::UnicodeUTF8));
        Add->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Album", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "Artister", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "Tracks", 0, QApplication::UnicodeUTF8));
        label_6->setText(QString());
        play->setText(QString());
        skib_b->setText(QString());
        skib_f->setText(QString());
        pixture->setText(QString());
        track_4->setText(QApplication::translate("MainWindow", "Track 0 of 15", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Text1", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "Sync", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QString());
        Network->setTitle(QApplication::translate("MainWindow", "Network", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Server ip, is the IP addr. on the SqueezeCenter</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("MainWindow", "Server IP Address", 0, QApplication::UnicodeUTF8));
        server_ip->setInputMask(QString());
        server_ip->setText(QApplication::translate("MainWindow", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        server_autoconnect->setText(QApplication::translate("MainWindow", "Auto Connect to server on start", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_4->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">The Server port Nr. Is the server CLI (Command Line Interface), see SqueezeCenter network settings for port number.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">The Default number is 9090</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("MainWindow", "Server CLI port number", 0, QApplication::UnicodeUTF8));
        server_port->setInputMask(QApplication::translate("MainWindow", "####; ", 0, QApplication::UnicodeUTF8));
        server_port->setText(QApplication::translate("MainWindow", "9090", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_5->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">The Server port Nr. Is the server CLI (Command Line Interface), see SqueezeCenter network settings for port number.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">The Default number is 9090</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("MainWindow", "Server HTTP port number", 0, QApplication::UnicodeUTF8));
        server_port_2->setInputMask(QApplication::translate("MainWindow", "####; ", 0, QApplication::UnicodeUTF8));
        server_port_2->setText(QApplication::translate("MainWindow", "9001", 0, QApplication::UnicodeUTF8));
        isConnected->setText(QApplication::translate("MainWindow", "Connection ?", 0, QApplication::UnicodeUTF8));
        SqueezeCenter->setTitle(QApplication::translate("MainWindow", "SqueezeCenter", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("MainWindow", "SqueezeBox 1", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("MainWindow", "SqueezeBox 2", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("MainWindow", "SqueezeBox 3", 0, QApplication::UnicodeUTF8));
        radioButton_7->setText(QApplication::translate("MainWindow", "SqueezeBox 4", 0, QApplication::UnicodeUTF8));
        squ1->setText(QString());
        squ2->setText(QString());
        squ3->setText(QString());
        squ4->setText(QString());
        radioButton_8->setText(QApplication::translate("MainWindow", "Squeeze Network", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Syncing to server", 0, QApplication::UnicodeUTF8));
        sync_label->setText(QApplication::translate("MainWindow", "Albums to sync", 0, QApplication::UnicodeUTF8));
        ControlBox->setTitle(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
