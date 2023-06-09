#ifndef REMOTE_DESKTOP_MODAL_H
#define REMOTE_DESKTOP_MODAL_H

#include <string>

#include <gtk/gtk.h>
#include <glib.h>

#include "desktop.h"
#include "desktop_orm.h"
#include "antd_input.h"
#include "antd_form.h"

extern const char *REMOTE_DESKTOP_MODAL_CSS;

class RemoteDesktopModal {
public:
    RemoteDesktopModal();

    GtkWidget* getWidget();

    void saveData();

    void open();

    void close();

    void setConnectionInfo(std::string address, std::string username, std::string password);

    static void saveDataCallback(GtkButton* button, gpointer user_data);

    static void closeCallback(GtkButton* button, gpointer user_data);

private:
    GtkWidget* m_widget;
    AntdInput* m_name_input;
    AntdInput* m_ip_input;
    GtkWidget* m_port_input;
    AntdInput* m_username_input;
    AntdInput* m_password_input;
    AntdInput* m_domain_input;
    GtkWidget* m_auto_login_checkbutton;
};

#endif //REMOTE_DESKTOP_MODAL_H
