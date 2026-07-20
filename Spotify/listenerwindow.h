#ifndef LISTENERWINDOW_H
#define LISTENERWINDOW_H

#include "appcontroller.h"
#include "listenercontroller.h"
#include "qlistwidget.h"
#include <QWidget>

inline const QString LIGHT_STYLES = R"(
QWidget#ListenerWindow {
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

QPushButton#removeFromPlaylistButton {
    background-color: #e67e22;
    color: white;
    border: 2px solid #ca6f1e;
    border-radius: 18px;
    padding: 10px 20px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#removeFromPlaylistButton:hover {
    background-color: #eb984e;
    border: 2px solid #e67e22;
}
QPushButton#removeFromPlaylistButton:pressed {
    background-color: #ca6f1e;
    border: 2px solid #a04000;
}
QPushButton#removeFromPlaylistButton:disabled {
    background-color: rgba(230, 126, 34, 0.3);
    color: rgba(255, 255, 255, 0.4);
    border: 2px solid rgba(230, 126, 34, 0.2);
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

QPushButton#likeButton {
    background-color: #e74c3c;
    color: white;
    border: 2px solid #c0392b;
    border-radius: 18px;
    padding: 10px 20px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#likeButton:hover {
    background-color: #ec7063;
    border: 2px solid #e74c3c;
}
QPushButton#likeButton:pressed {
    background-color: #c0392b;
    border: 2px solid #922b21;
}
QPushButton#likeButton:disabled {
    background-color: rgba(231, 76, 60, 0.3);
    color: rgba(255, 255, 255, 0.4);
    border: 2px solid rgba(231, 76, 60, 0.2);
}

QPushButton#unlikeButton {
    background-color: #34495e;
    color: white;
    border: 2px solid #2c3e50;
    border-radius: 18px;
    padding: 10px 20px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#unlikeButton:hover {
    background-color: #5d6d7e;
    border: 2px solid #34495e;
}
QPushButton#unlikeButton:pressed {
    background-color: #2c3e50;
    border: 2px solid #1a252f;
}
QPushButton#unlikeButton:disabled {
    background-color: rgba(52, 73, 94, 0.3);
    color: rgba(255, 255, 255, 0.4);
    border: 2px solid rgba(52, 73, 94, 0.2);
}

QPushButton#addToPlaylistButton {
    background-color: rgba(155, 89, 182, 0.85);
    color: white;
    border: 2px solid rgba(155, 89, 182, 0.5);
    border-radius: 18px;
    padding: 12px 28px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#addToPlaylistButton:hover {
    background-color: rgba(155, 89, 182, 1.0);
}
QPushButton#addToPlaylistButton:disabled {
    background-color: rgba(155, 89, 182, 0.3);
    color: rgba(255, 255, 255, 0.5);
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

inline const QString DARK_STYLES = R"(
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
}

QPushButton#likeButton {
    background-color: rgba(231, 76, 60, 0.7);
    color: white;
    border: 2px solid rgba(231, 76, 60, 0.4);
    border-radius: 18px;
    padding: 10px 20px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#likeButton:hover {
    background-color: rgba(231, 76, 60, 0.9);
    border: 2px solid #e74c3c;
}
QPushButton#likeButton:disabled {
    background-color: rgba(231, 76, 60, 0.2);
    color: rgba(255, 255, 255, 0.3);
    border: 2px solid rgba(231, 76, 60, 0.15);
}

QPushButton#unlikeButton {
    background-color: rgba(52, 73, 94, 0.7);
    color: white;
    border: 2px solid rgba(52, 73, 94, 0.4);
    border-radius: 18px;
    padding: 10px 20px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#unlikeButton:hover {
    background-color: rgba(52, 73, 94, 0.9);
    border: 2px solid #5d6d7e;
}
QPushButton#unlikeButton:disabled {
    background-color: rgba(52, 73, 94, 0.2);
    color: rgba(255, 255, 255, 0.3);
    border: 2px solid rgba(52, 73, 94, 0.15);
}

QPushButton#removeFromPlaylistButton {
    background-color: rgba(230, 126, 34, 0.7);
    color: white;
    border: 2px solid rgba(230, 126, 34, 0.4);
    border-radius: 18px;
    padding: 10px 20px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#removeFromPlaylistButton:hover {
    background-color: rgba(230, 126, 34, 0.9);
    border: 2px solid #e67e22;
}
QPushButton#removeFromPlaylistButton:disabled {
    background-color: rgba(230, 126, 34, 0.2);
    color: rgba(255, 255, 255, 0.3);
    border: 2px solid rgba(230, 126, 34, 0.15);
}

QPushButton#addToPlaylistButton {
    background: rgba(155, 89, 182, 0.6);
    color: white;
    border: 2px solid rgba(155, 89, 182, 0.3);
    border-radius: 18px;
    padding: 12px 28px;
    font-weight: bold;
    font-size: 13px;
}
QPushButton#addToPlaylistButton:hover {
    background: rgba(155, 89, 182, 0.85);
}
QPushButton#addToPlaylistButton:disabled {
    background: rgba(155, 89, 182, 0.2);
    color: rgba(255, 255, 255, 0.3);
}

QWidget#ListenerWindow {
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
)";

namespace Ui {
class ListenerWindow;
}

class ListenerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ListenerWindow(int listenerId ,ListenerController& controller,AppController& appController,QWidget *parent = nullptr);
    ~ListenerWindow();
private slots:
    void onAddPlaylistClicked();
    void onEditPlaylistClicked();
    void onDeletePlaylistClicked();

    void onLikeClicked();
    void onUnlikeClicked();
    void onAddToPlaylistClicked();

    void onSearchClicked();
    void onFilterTypeChanged();
    void onFilterValueChanged();

    void onTabChanged(int index);

    void onArtistClicked(QListWidgetItem* item);
    void onAlbumClicked(QListWidgetItem* item);
    void onSongClicked(QListWidgetItem* item);

    void onEditProfileClicked();
    void onDeleteProfileClicked();
    void onLogoutClicked();

    void onDarkModeClicked();

    void onPlaylistClicked(QListWidgetItem* item);
    void onRemoveFromPlaylistClicked();
    void onPlaylistSongsClicked(QListWidgetItem* item);

private:
    Ui::ListenerWindow *ui;
    ListenerController& listenerCtrl;
    AppController& appCtrl;
    int currentListenerId;
    bool isDarkMode;

    void loadPlaylists();
    void loadArtists();
    void loadAlbums(int artistId);
    void loadSongs(int albumId);
    void loadFavorites();
    void refreshAll();

    void applyTheme();
    void applyCurrentFilter();
    int getCurrentTab();
    int getSelectedItemId(QListWidget* list);
    void updateActionButtons();
};

#endif // LISTENERWINDOW_H
