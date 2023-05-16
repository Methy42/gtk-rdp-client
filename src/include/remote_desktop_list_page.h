#ifndef REMOTE_DESKTOP_LIST_PAGE_H
#define REMOTE_DESKTOP_LIST_PAGE_H

#include <functional>
#include <string>

#include <gtk/gtk.h>

#include "remote_desktop_modal.h"
#include "desktop_orm.h"
#include "rdp_service.h"
#include "antd_button.h"
#include "antd_card.h"

extern const char *REMOTE_DESKTOP_LIST_PAGE_CSS;

class RemoteDesktopListPage {
public:
    RemoteDesktopListPage();

    GtkWidget* getWidget();

    void loadData();

    void connectRemoteDesktopSelectedSignal(std::function<void(const std::string&, const std::string&)> callback);

    void connectRemoteDesktopConnectSignal(std::function<void(const std::string&, const std::string&)> callback);

    void setModal(RemoteDesktopModal* modal);

private:
    GtkWidget* m_widget;
    GtkWidget* m_add_button;
    GtkWidget* m_listbox;
    GtkCssProvider* m_css_provider;
    RemoteDesktopModal* m_modal; // 远程桌面模态框

    static void on_add_button_clicked(GtkButton* button, gpointer user_data) {
        RemoteDesktopListPage* self = reinterpret_cast<RemoteDesktopListPage*>(user_data);
        self->m_modal->open();
    }

    static void on_desktop_clicked(gpointer data);
};

#endif //REMOTE_DESKTOP_LIST_PAGE_H