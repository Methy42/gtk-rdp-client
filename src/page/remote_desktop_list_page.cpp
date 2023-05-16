#include "remote_desktop_list_page.h"

// 在这里实现 RemoteDesktopListPage 类的方法

const char *REMOTE_DESKTOP_LIST_PAGE_CSS = "\
.remote-desktop-list-page {\
    padding: 15px;\
}\
.remote-desktop-list-page .tool-button-container {\
    margin-bottom: 15px;\
}\
.remote-desktop-list-page .antd-card-cover {\
    background: #000000;\
}\
";

RemoteDesktopListPage::RemoteDesktopListPage()
{
    // 这里放置远程桌面列表页面的构造逻辑
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, REMOTE_DESKTOP_LIST_PAGE_CSS, -1, NULL);
    GtkStyleContext *page_context = gtk_widget_get_style_context(vbox);
    gtk_style_context_add_provider(page_context, GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(page_context, "remote-desktop-list-page");

    // 创建页面上方的按钮工具栏
    GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(button_box), GTK_BUTTONBOX_START);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, false, false, 0);
    GtkStyleContext *tool_button_container = gtk_widget_get_style_context(button_box);
    gtk_style_context_add_provider(tool_button_container, GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(tool_button_container, "tool-button-container");

    // 添加远程桌面按钮到按钮工具栏
    struct AntdButtonOption *option = new AntdButtonOption;
    option->type = g_strdup("primary");
    option->label = g_strdup("添加远程桌面");
    GtkWidget *add_button = AntdButton(option).getWidget();
    gtk_box_pack_start(GTK_BOX(button_box), add_button, false, false, 0);

    // 远程桌面列表
    GtkWidget *listbox = gtk_flow_box_new();
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(
        GTK_SCROLLED_WINDOW(scrolled_window),
        GTK_POLICY_AUTOMATIC,
        GTK_POLICY_AUTOMATIC
    );
    gtk_container_add(GTK_CONTAINER(scrolled_window), listbox);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, true, true, 0);

    m_widget = vbox;
    m_listbox = listbox;
    m_add_button = add_button;
    m_css_provider = provider;

    // 加载远程桌面数据到列表中
    loadData();

    g_signal_connect(G_OBJECT(m_add_button), "clicked", G_CALLBACK(on_add_button_clicked), this);
}

GtkWidget *RemoteDesktopListPage::getWidget()
{
    // 返回远程桌面列表页面的gtk小部件
    return m_widget;
}

void RemoteDesktopListPage::setModal(RemoteDesktopModal *modal)
{
    m_modal = modal;
}

void RemoteDesktopListPage::loadData()
{
    std::vector<Desktop> desktops = DesktopORM::getInstance().getDesktops();

    int i = 0;
    for (auto &desktop : desktops)
    {
        // 创建桌面卡片
        AntdCard desktop_card = AntdCard(new AntdCardOption{
            g_strdup("assets/images/windows.png"),
            g_strdup(desktop.getName().c_str()),
            g_strdup(desktop.getIP().c_str())
        });

        // 创建桌面卡片的操作按钮
        AntdButton connect_button = AntdButton(new AntdButtonOption{g_strdup("link"), g_strdup("连接")});
        AntdButton edit_button = AntdButton(new AntdButtonOption{g_strdup("link"), g_strdup("编辑")});

        // 添加桌面卡片的操作按钮
        desktop_card.addAction(connect_button.getWidget());
        desktop_card.addAction(edit_button.getWidget());

        // 绑定操作按钮的点击事件
        g_signal_connect(connect_button.getWidget(), "clicked", G_CALLBACK(on_desktop_clicked), reinterpret_cast<gpointer>(&desktop));

        // 绑定页面样式到桌面卡片
        GtkStyleContext *desktop_card_cover_container_context = gtk_widget_get_style_context(desktop_card.getCoverContainer());
        gtk_style_context_add_provider(
            desktop_card_cover_container_context,
            GTK_STYLE_PROVIDER(m_css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_USER
        );

        // 将操作按钮添加到列表组件
        gtk_container_add(GTK_CONTAINER(m_listbox), desktop_card.getWidget());

        i++;
    }
}

void RemoteDesktopListPage::on_desktop_clicked(gpointer data)
{
    Desktop *desktop = reinterpret_cast<Desktop *>(data);
    RDPService::getInstance().createRDPConnection();
}

void RemoteDesktopListPage::connectRemoteDesktopSelectedSignal(std::function<void(const std::string &, const std::string &)> callback)
{
    // 连接远程桌面列表页面的远程桌面被选中信号
    // g_signal_connect_swapped(G_OBJECT(m_listbox), "row-activated", G_CALLBACK(callback), NULL);
}

void RemoteDesktopListPage::connectRemoteDesktopConnectSignal(std::function<void(const std::string &, const std::string &)> callback)
{
    // 连接远程桌面列表页面的远程桌面连接信号
    // g_signal_connect_swapped(G_OBJECT(settings_button), "clicked", G_CALLBACK(callback), NULL);
}
