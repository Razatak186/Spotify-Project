#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include "appcontroller.h"
#include "artistcontroller.h"
#include <QWidget>
#include<QListWidget>
#include<addalbumdialog.h>
#include<playbackmanager.h>

inline const QString LIGHT_STYLE = R"(


QSlider#positionSlider {
    height: 6px;
    border-radius: 3px;
}
QSlider#positionSlider::groove:horizontal {
    height: 6px;
    background: rgba(255, 255, 255, 0.2);
    border-radius: 3px;
}
QSlider#positionSlider::handle:horizontal {
    background: #1DB954;
    width: 14px;
    height: 14px;
    margin: -5px 0;
    border-radius: 7px;
}
QSlider#positionSlider::handle:horizontal:hover {
    background: #1ed760;
}
QSlider#positionSlider::sub-page:horizontal {
    background: #1DB954;
    border-radius: 3px;
}

QSlider#volumeSlider {
    height: 5px;
    border-radius: 2px;
}
QSlider#volumeSlider::groove:horizontal {
    height: 5px;
    background: rgba(255, 255, 255, 0.2);
    border-radius: 2px;
}
QSlider#volumeSlider::handle:horizontal {
    background: white;
    width: 12px;
    height: 12px;
    margin: -4px 0;
    border-radius: 6px;
}
QSlider#volumeSlider::handle:horizontal:hover {
    background: #1DB954;
}
QSlider#volumeSlider::sub-page:horizontal {
    background: white;
    border-radius: 2px;
}

QLabel#nowPlayingLabel {
    font-size: 14px;
    font-weight: bold;
    color: white;
    padding: 5px;
}
QLabel#nowPlayingLabel:disabled {
    color: rgba(255, 255, 255, 0.4);
}

QLabel#timeLabel {
    font-size: 12px;
    color: rgba(255, 255, 255, 0.6);
    min-width: 80px;
}

QLabel#volumeLabel {
    font-size: 16px;
    color: white;
    min-width: 30px;
}

QPushButton#playButton {
    background-color: #1DB954;
    color: white;
    border: 2px solid #1DB954;
    border-radius: 20px;
    padding: 8px 20px;
    font-weight: bold;
    font-size: 13px;
    min-width: 80px;
}
QPushButton#playButton:hover {
    background-color: #1ed760;
    border: 2px solid #1ed760;
}
QPushButton#playButton:pressed {
    background-color: #1aa34a;
}
QPushButton#playButton:disabled {
    background-color: rgba(29, 185, 84, 0.3);
    color: rgba(255, 255, 255, 0.4);
}

QPushButton#prevButton, QPushButton#nextButton {
    background-color: rgba(255, 255, 255, 0.1);
    color: white;
    border: 2px solid rgba(255, 255, 255, 0.2);
    border-radius: 20px;
    padding: 8px 16px;
    font-size: 16px;
    min-width: 50px;
}
QPushButton#prevButton:hover, QPushButton#nextButton:hover {
    background-color: rgba(255, 255, 255, 0.2);
    border: 2px solid rgba(255, 255, 255, 0.4);
}
QPushButton#prevButton:pressed, QPushButton#nextButton:pressed {
    background-color: rgba(255, 255, 255, 0.05);
}
QPushButton#prevButton:disabled, QPushButton#nextButton:disabled {
    background-color: rgba(255, 255, 255, 0.05);
    color: rgba(255, 255, 255, 0.3);
}




QLabel#profilePhotoLabel {
    background-color: rgba(255, 255, 255, 0.2);
    border: 2px solid rgba(255, 255, 255, 0.6);
    border-radius: 25px;
    color: white;
    font-size: 22px;
}

QWidget#ArtistWindow {
    background-color: qlineargradient(
        x1: 0, y1: 0, x2: 1, y2: 1,
        stop: 0 #1DB954,
        stop: 1 #191414
    );
}

QLabel#welcomeLabel {
    font-size: 20px;
    font-weight: bold;
    color: white;
    padding: 5px;
}

QPushButton#darkModeButton {
    background-color: rgba(0, 0, 0, 0.3);
    color: white;
    border: 2px solid rgba(255, 255, 255, 0.5);
    border-radius: 18px;
    padding: 8px 20px;
    font-weight: bold;
    font-size: 12px;
}
QPushButton#darkModeButton:hover {
    background-color: rgba(0, 0, 0, 0.45);
    border: 2px solid white;
}
QPushButton#darkModeButton:pressed {
    background-color: rgba(0, 0, 0, 0.55);
}

QPushButton#logoutButton {
    background-color: rgba(231, 76, 60, 0.85);
    color: white;
    border: 2px solid rgba(255, 255, 255, 0.4);
    border-radius: 18px;
    padding: 8px 20px;
    font-weight: bold;
    font-size: 12px;
}
QPushButton#logoutButton:hover {
    background-color: rgba(231, 76, 60, 1.0);
    border: 2px solid white;
}
QPushButton#logoutButton:pressed {
    background-color: rgba(192, 57, 43, 1.0);
}

QTabWidget::pane {
    background-color: rgba(255, 255, 255, 0.08);
    border: 1px solid rgba(255, 255, 255, 0.25);
    border-radius: 14px;
    top: -1px;
}
QTabBar::tab {
    background-color: rgba(255, 255, 255, 0.15);
    color: rgba(255, 255, 255, 0.75);
    padding: 10px 28px;
    border-top-left-radius: 12px;
    border-top-right-radius: 12px;
    font-weight: bold;
    margin-right: 3px;
}
QTabBar::tab:selected {
    background-color: rgba(29, 185, 84, 0.9);
    color: white;
}
QTabBar::tab:hover {
    background-color: rgba(255, 255, 255, 0.25);
}
QTabBar::tab:selected:hover {
    background-color: rgba(29, 185, 84, 1.0);
}

QListWidget, QListView {
    background: rgba(255, 255, 255, 0.08);
    border: 1px solid rgba(255, 255, 255, 0.2);
    border-radius: 16px;
    padding: 12px;
    font-size: 14px;
    outline: none;
}
QListWidget::item {
    color: white;
    padding: 14px 20px;
    margin: 4px 6px;
    border-radius: 12px;
    background: rgba(255, 255, 255, 0.05);
    border: 1px solid rgba(255, 255, 255, 0.08);
}
QListWidget::item:selected {
    background: rgba(29, 185, 84, 0.45);
    border: 1px solid rgba(29, 185, 84, 0.7);
    color: white;
}
QListWidget::item:hover {
    background: rgba(255, 255, 255, 0.15);
    border: 1px solid rgba(255, 255, 255, 0.25);
}
QListWidget::item:selected:hover {
    background: rgba(29, 185, 84, 0.6);
    border: 1px solid #1DB954;
}

QPushButton#addButton {
    background-color: rgba(29, 185, 84, 0.9);
    color: white;
    border: 2px solid rgba(255, 255, 255, 0.4);
    border-radius: 18px;
    padding: 12px 28px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#addButton:hover {
    background-color: rgba(46, 219, 106, 1.0);
    border: 2px solid white;
}
QPushButton#addButton:pressed {
    background-color: rgba(21, 138, 62, 1.0);
}

QPushButton#editButton {
    background-color: rgba(243, 156, 18, 0.9);
    color: white;
    border: 2px solid rgba(255, 255, 255, 0.4);
    border-radius: 18px;
    padding: 12px 28px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#editButton:hover {
    background-color: rgba(245, 176, 65, 1.0);
    border: 2px solid white;
}
QPushButton#editButton:pressed {
    background-color: rgba(214, 137, 16, 1.0);
}

QPushButton#deleteButton {
    background-color: rgba(231, 76, 60, 0.9);
    color: white;
    border: 2px solid rgba(255, 255, 255, 0.4);
    border-radius: 18px;
    padding: 12px 28px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#deleteButton:hover {
    background-color: rgba(236, 112, 99, 1.0);
    border: 2px solid white;
}
QPushButton#deleteButton:pressed {
    background-color: rgba(192, 57, 43, 1.0);
}

QLineEdit#searchEdit {
    background-color: rgba(255, 255, 255, 0.9);
    border: 2px solid rgba(255, 255, 255, 0.3);
    border-radius: 18px;
    padding: 8px 16px;
    font-size: 13px;
    color: #2c3e50;
}
QLineEdit#searchEdit:focus {
    border: 2px solid #1DB954;
}
QLineEdit#searchEdit::placeholder {
    color: #95a5a6;
}

QPushButton#searchButton {
    background-color: rgba(29, 185, 84, 0.85);
    color: white;
    border: 2px solid rgba(29, 185, 84, 0.85);
    border-radius: 18px;
    padding: 8px 20px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#searchButton:hover {
    background-color: rgba(29, 185, 84, 1.0);
}
QPushButton#searchButton:pressed {
    background-color: rgba(21, 138, 62, 1.0);
}

QComboBox {
    background-color: rgba(255, 255, 255, 0.9);
    border: 2px solid rgba(255, 255, 255, 0.3);
    border-radius: 18px;
    padding: 6px 14px;
    font-size: 13px;
    color: #2c3e50;
    min-width: 80px;
}
QComboBox:hover {
    border: 2px solid #1DB954;
}
QComboBox::drop-down {
    border: none;
    padding-right: 10px;
}
QComboBox::down-arrow {
    image: none;
    border-left: 5px solid transparent;
    border-right: 5px solid transparent;
    border-top: 5px solid #2c3e50;
    margin-right: 5px;
}
QComboBox QAbstractItemView {
    background-color: white;
    border: 2px solid #1DB954;
    border-radius: 12px;
    padding: 5px;
    selection-background-color: #1DB954;
    selection-color: white;
}

QPushButton#editProfileButton {
    background-color: rgba(52, 152, 219, 0.85);
    color: white;
    border: 2px solid rgba(52, 152, 219, 0.85);
    border-radius: 18px;
    padding: 8px 18px;
    font-weight: bold;
    font-size: 12px;
}
QPushButton#editProfileButton:hover {
    background-color: rgba(52, 152, 219, 1.0);
}
QPushButton#editProfileButton:pressed {
    background-color: rgba(41, 128, 185, 1.0);
}

QPushButton#deleteProfileButton {
    background-color: rgba(231, 76, 60, 0.8);
    color: white;
    border: 2px solid rgba(231, 76, 60, 0.5);
    border-radius: 18px;
    padding: 8px 18px;
    font-weight: bold;
    font-size: 12px;
}
QPushButton#deleteProfileButton:hover {
    background-color: rgba(231, 76, 60, 1.0);
    border: 2px solid #e74c3c;
}
QPushButton#deleteProfileButton:pressed {
    background-color: rgba(192, 57, 43, 1.0);
}



)";

inline const QString DARK_STYLE= R"(

QLabel#profilePhotoLabel {
    background-color: rgba(255, 255, 255, 0.08);
    border: 2px solid rgba(29, 185, 84, 0.5);
    border-radius: 25px;
    color: #d4edda;
    font-size: 22px;
}


QLineEdit#searchEdit {
    background-color: rgba(255, 255, 255, 0.12);
    border: 2px solid rgba(255, 255, 255, 0.15);
    border-radius: 18px;
    padding: 8px 16px;
    font-size: 13px;
    color: #e0e0e0;
}
QLineEdit#searchEdit:focus {
    border: 2px solid #1DB954;
}
QLineEdit#searchEdit::placeholder {
    color: #888;
}

QPushButton#searchButton {
    background-color: rgba(29, 185, 84, 0.6);
    color: white;
    border: 2px solid rgba(29, 185, 84, 0.6);
    border-radius: 18px;
    padding: 8px 20px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#searchButton:hover {
    background-color: rgba(29, 185, 84, 0.85);
}

QComboBox {
    background-color: rgba(255, 255, 255, 0.08);
    border: 2px solid rgba(255, 255, 255, 0.12);
    border-radius: 18px;
    padding: 6px 14px;
    font-size: 13px;
    color: #d0d0d0;
    min-width: 80px;
}
QComboBox:hover {
    border: 2px solid #1DB954;
}
QComboBox::down-arrow {
    border-top: 5px solid #d0d0d0;
}
QComboBox QAbstractItemView {
    background-color: #2d2d44;
    border: 2px solid #1DB954;
    border-radius: 12px;
    padding: 5px;
    selection-background-color: #1DB954;
    selection-color: white;
    color: #d0d0d0;
}

QPushButton#editProfileButton {
    background-color: rgba(52, 152, 219, 0.5);
    color: white;
    border: 2px solid rgba(52, 152, 219, 0.5);
    border-radius: 18px;
    padding: 8px 18px;
    font-weight: bold;
    font-size: 12px;
}
QPushButton#editProfileButton:hover {
    background-color: rgba(52, 152, 219, 0.8);
}

QPushButton#deleteProfileButton {
    background-color: rgba(231, 76, 60, 0.5);
    color: white;
    border: 2px solid rgba(231, 76, 60, 0.3);
    border-radius: 18px;
    padding: 8px 18px;
    font-weight: bold;
    font-size: 12px;
}
QPushButton#deleteProfileButton:hover {
    background-color: rgba(231, 76, 60, 0.8);
    border: 2px solid #e74c3c;
}


QWidget#ArtistWindow {
    background: qlineargradient(
        x1: 0, y1: 0, x2: 1, y2: 1,
        stop: 0 #0a0f0a,
        stop: 0.4 #0d1a0d,
        stop: 0.7 #0f2410,
        stop: 1 #0d1a0d
    );
}

QLabel#welcomeLabel {
    font-size: 20px;
    font-weight: bold;
    color: #d4edda;
    padding: 5px;
}

QPushButton#darkModeButton {
    background: rgba(241, 196, 15, 0.12);
    color: #f1c40f;
    border: 2px solid rgba(241, 196, 15, 0.4);
    border-radius: 18px;
    padding: 8px 20px;
    font-weight: bold;
    font-size: 12px;
}
QPushButton#darkModeButton:hover {
    background: rgba(241, 196, 15, 0.25);
    border: 2px solid #f1c40f;
}

QPushButton#logoutButton {
    background: rgba(231, 76, 60, 0.6);
    color: white;
    border: 2px solid rgba(231, 76, 60, 0.4);
    border-radius: 18px;
    padding: 8px 20px;
    font-weight: bold;
    font-size: 12px;
}
QPushButton#logoutButton:hover {
    background: rgba(231, 76, 60, 0.9);
    border: 2px solid #e74c3c;
}

QTabWidget::pane {
    background: rgba(255, 255, 255, 0.03);
    border: 1px solid rgba(29, 185, 84, 0.2);
    border-radius: 14px;
    top: -1px;
}
QTabBar::tab {
    background: rgba(255, 255, 255, 0.04);
    color: rgba(255, 255, 255, 0.5);
    padding: 10px 28px;
    border-top-left-radius: 12px;
    border-top-right-radius: 12px;
    font-weight: bold;
    margin-right: 3px;
}
QTabBar::tab:selected {
    background: rgba(29, 185, 84, 0.7);
    color: white;
}
QTabBar::tab:hover {
    background: rgba(255, 255, 255, 0.08);
}
QTabBar::tab:selected:hover {
    background: rgba(29, 185, 84, 0.9);
}

QListWidget, QListView {
    background: rgba(255, 255, 255, 0.03);
    border: 1px solid rgba(29, 185, 84, 0.15);
    border-radius: 16px;
    padding: 12px;
    font-size: 14px;
    outline: none;
}
QListWidget::item {
    color: #c8e6c9;
    padding: 14px 20px;
    margin: 4px 6px;
    border-radius: 12px;
    background: rgba(255, 255, 255, 0.02);
    border: 1px solid rgba(29, 185, 84, 0.05);
}
QListWidget::item:selected {
    background: rgba(29, 185, 84, 0.35);
    border: 1px solid rgba(29, 185, 84, 0.5);
    color: white;
}
QListWidget::item:hover {
    background: rgba(29, 185, 84, 0.15);
    border: 1px solid rgba(29, 185, 84, 0.25);
}
QListWidget::item:selected:hover {
    background: rgba(29, 185, 84, 0.5);
    border: 1px solid #1DB954;
}

QPushButton#addButton {
    background: rgba(29, 185, 84, 0.7);
    color: white;
    border: 2px solid rgba(29, 185, 84, 0.4);
    border-radius: 18px;
    padding: 12px 28px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#addButton:hover {
    background: rgba(29, 185, 84, 0.9);
    border: 2px solid rgba(29, 185, 84, 0.8);
}

QPushButton#editButton {
    background: rgba(243, 156, 18, 0.6);
    color: white;
    border: 2px solid rgba(243, 156, 18, 0.3);
    border-radius: 18px;
    padding: 12px 28px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#editButton:hover {
    background: rgba(243, 156, 18, 0.85);
    border: 2px solid rgba(243, 156, 18, 0.7);
}

QPushButton#deleteButton {
    background: rgba(231, 76, 60, 0.6);
    color: white;
    border: 2px solid rgba(231, 76, 60, 0.3);
    border-radius: 18px;
    padding: 12px 28px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#deleteButton:hover {
    background: rgba(231, 76, 60, 0.85);
    border: 2px solid rgba(231, 76, 60, 0.7);


QSlider#positionSlider {
    height: 6px;
    border-radius: 3px;
}
QSlider#positionSlider::groove:horizontal {
    height: 6px;
    background: rgba(255, 255, 255, 0.1);
    border-radius: 3px;
}
QSlider#positionSlider::handle:horizontal {
    background: #1DB954;
    width: 14px;
    height: 14px;
    margin: -5px 0;
    border-radius: 7px;
}
QSlider#positionSlider::handle:horizontal:hover {
    background: #1ed760;
}
QSlider#positionSlider::sub-page:horizontal {
    background: #1DB954;
    border-radius: 3px;
}

QSlider#volumeSlider {
    height: 5px;
    border-radius: 2px;
}
QSlider#volumeSlider::groove:horizontal {
    height: 5px;
    background: rgba(255, 255, 255, 0.1);
    border-radius: 2px;
}
QSlider#volumeSlider::handle:horizontal {
    background: #d4edda;
    width: 12px;
    height: 12px;
    margin: -4px 0;
    border-radius: 6px;
}
QSlider#volumeSlider::handle:horizontal:hover {
    background: #1DB954;
}
QSlider#volumeSlider::sub-page:horizontal {
    background: #d4edda;
    border-radius: 2px;
}

QLabel#nowPlayingLabel {
    font-size: 14px;
    font-weight: bold;
    color: #d4edda;
    padding: 5px;
}
QLabel#nowPlayingLabel:disabled {
    color: rgba(212, 237, 218, 0.4);
}

QLabel#timeLabel {
    font-size: 12px;
    color: rgba(255, 255, 255, 0.5);
    min-width: 80px;
}

QLabel#volumeLabel {
    font-size: 16px;
    color: #d4edda;
    min-width: 30px;
}

QPushButton#playButton {
    background-color: rgba(29, 185, 84, 0.8);
    color: white;
    border: 2px solid rgba(29, 185, 84, 0.4);
    border-radius: 20px;
    padding: 8px 20px;
    font-weight: bold;
    font-size: 13px;
    min-width: 80px;
}
QPushButton#playButton:hover {
    background-color: rgba(29, 185, 84, 1.0);
    border: 2px solid #1DB954;
}
QPushButton#playButton:disabled {
    background-color: rgba(29, 185, 84, 0.2);
    color: rgba(255, 255, 255, 0.3);
}

QPushButton#prevButton, QPushButton#nextButton {
    background-color: rgba(255, 255, 255, 0.05);
    color: rgba(255, 255, 255, 0.7);
    border: 2px solid rgba(255, 255, 255, 0.1);
    border-radius: 20px;
    padding: 8px 16px;
    font-size: 16px;
    min-width: 50px;
}
QPushButton#prevButton:hover, QPushButton#nextButton:hover {
    background-color: rgba(255, 255, 255, 0.12);
    border: 2px solid rgba(255, 255, 255, 0.25);
}
QPushButton#prevButton:disabled, QPushButton#nextButton:disabled {
    background-color: rgba(255, 255, 255, 0.03);
    color: rgba(255, 255, 255, 0.2);
}
}

/* ============= Player Section (Dark) ============= */

QSlider#positionSlider {
    height: 6px;
    border-radius: 3px;
}
QSlider#positionSlider::groove:horizontal {
    height: 6px;
    background: rgba(255, 255, 255, 0.1);
    border-radius: 3px;
}
QSlider#positionSlider::handle:horizontal {
    background: #1DB954;
    width: 14px;
    height: 14px;
    margin: -5px 0;
    border-radius: 7px;
}
QSlider#positionSlider::handle:horizontal:hover {
    background: #1ed760;
}
QSlider#positionSlider::sub-page:horizontal {
    background: #1DB954;
    border-radius: 3px;
}

QSlider#volumeSlider {
    height: 5px;
    border-radius: 2px;
}
QSlider#volumeSlider::groove:horizontal {
    height: 5px;
    background: rgba(255, 255, 255, 0.1);
    border-radius: 2px;
}
QSlider#volumeSlider::handle:horizontal {
    background: #d4edda;
    width: 12px;
    height: 12px;
    margin: -4px 0;
    border-radius: 6px;
}
QSlider#volumeSlider::handle:horizontal:hover {
    background: #1DB954;
}
QSlider#volumeSlider::sub-page:horizontal {
    background: #d4edda;
    border-radius: 2px;
}

QLabel#nowPlayingLabel {
    font-size: 14px;
    font-weight: bold;
    color: #d4edda;
    padding: 5px;
}
QLabel#nowPlayingLabel:disabled {
    color: rgba(212, 237, 218, 0.4);
}

QLabel#timeLabel {
    font-size: 12px;
    color: rgba(255, 255, 255, 0.5);
    min-width: 80px;
}

QLabel#volumeLabel {
    font-size: 16px;
    color: #d4edda;
    min-width: 30px;
}

QPushButton#playButton {
    background-color: rgba(29, 185, 84, 0.8);
    color: white;
    border: 2px solid rgba(29, 185, 84, 0.4);
    border-radius: 20px;
    padding: 8px 20px;
    font-weight: bold;
    font-size: 13px;
    min-width: 80px;
}
QPushButton#playButton:hover {
    background-color: rgba(29, 185, 84, 1.0);
    border: 2px solid #1DB954;
}
QPushButton#playButton:disabled {
    background-color: rgba(29, 185, 84, 0.2);
    color: rgba(255, 255, 255, 0.3);
}

QPushButton#prevButton, QPushButton#nextButton {
    background-color: rgba(255, 255, 255, 0.05);
    color: rgba(255, 255, 255, 0.7);
    border: 2px solid rgba(255, 255, 255, 0.1);
    border-radius: 20px;
    padding: 8px 16px;
    font-size: 16px;
    min-width: 50px;
}
QPushButton#prevButton:hover, QPushButton#nextButton:hover {
    background-color: rgba(255, 255, 255, 0.12);
    border: 2px solid rgba(255, 255, 255, 0.25);
}
QPushButton#prevButton:disabled, QPushButton#nextButton:disabled {
    background-color: rgba(255, 255, 255, 0.03);
    color: rgba(255, 255, 255, 0.2);
}
)";

namespace Ui {
class ArtistWindow;
}

class ArtistWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ArtistWindow(int artistId,ArtistController& controller,AppController& appController,QWidget *parent = nullptr);
    ~ArtistWindow();
private slots :
    void onAddClicked();
    void onEditClicked();
    void onDeleteClicked();
    void onLogoutClicked();
    void onDarkModeClicked();
    void onTabChanged(int index);
    void onSearchClicked();
    void onFilterTypechanged();
    void onFilterValuechanged();
    void onEditProfileClicked();
    void onDeleteProfileClicked();
    void onPlayButtonclicked();
    void onPrevButtonclicked();
    void onNextButtonclicked();
    void onVolumechanged(int value);
    void onSongchanged(const Song& song);
    void onSongDoubleClicked(QListWidgetItem* item);
private:
    Ui::ArtistWindow *ui;
    ArtistController& artistCtrl;
    AppController& appCtrl;
    int currentArtsitId;
    bool isDarkMode;

    void loadAlbums();
    void loadSongs(int albumId);
    void loadSingles();
    void refreshAll();
    void  applyTheme();
    int getCurrentTab();
    int getSelectedItemId(QListWidget* list);
    void applyCurrentFilter();
    PlaybackManager playbackManager;

};

#endif // ARTISTWINDOW_H
