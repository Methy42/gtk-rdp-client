#ifndef REMOTE_DESKTOP_VIEW_PAGE_H
#define REMOTE_DESKTOP_VIEW_PAGE_H

#include <gtk/gtk.h>

#include <functional>
#include <string>

class RemoteDesktopViewPage {
public:
    RemoteDesktopViewPage();

    GtkWidget* getWidget();

    void connectRemoteDesktop();

    void connectBackButtonClickedSignal(std::function<void()> callback);

    void connectConnectButtonClickedSignal(std::function<void(const std::string&, const std::string&)> callback);

    void setTitle(const std::string& title);

    void setAddress(const std::string& address);

    void setPort(const std::string& port);

    void setUserName(const std::string& userName);

    void setPassword(const std::string& password);

    std::string getTitle();

    std::string getAddress();

    std::string getPort();

    std::string getUserName();

    std::string getPassword();

private:
    GtkWidget* m_widget;
    GtkWidget* m_title_label;
    GtkWidget* m_address_entry;
    GtkWidget* m_port_entry;
    GtkWidget* m_username_entry;
    GtkWidget* m_password_entry;
    GtkWidget* m_connect_button;
};

#endif //REMOTE_DESKTOP_VIEW_PAGE_H