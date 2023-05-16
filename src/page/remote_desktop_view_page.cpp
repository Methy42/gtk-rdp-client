#include "remote_desktop_view_page.h"

RemoteDesktopViewPage::RemoteDesktopViewPage()
{
    // 创建一个GtkBox，用于放置远程桌面连接画面页面的小部件
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // 创建一个GtkLabel，用于显示远程桌面连接画面页面的标题
    GtkWidget *title_label = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(vbox), title_label, FALSE, FALSE, 0);

    // 创建一个GtkGrid，用于放置远程桌面连接相关的参数和连接按钮
    GtkWidget *grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 10);

    // 创建并添加各种控件到GtkGrid中
    GtkWidget *address_label = gtk_label_new("Address:");
    GtkWidget *address_entry = gtk_entry_new();
    GtkWidget *port_label = gtk_label_new("Port:");
    GtkWidget *port_entry = gtk_entry_new();
    GtkWidget *username_label = gtk_label_new("Username:");
    GtkWidget *username_entry = gtk_entry_new();
    GtkWidget *password_label = gtk_label_new("Password:");
    GtkWidget *password_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), address_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), address_entry, 1, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), port_label, 4, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), port_entry, 5, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 1, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 4, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 5, 1, 1, 1);

    // 创建一个GtkButton，用于连接到远程桌面
    GtkWidget *connect_button = gtk_button_new_with_label("Connect");
    gtk_box_pack_start(GTK_BOX(vbox), connect_button, FALSE, FALSE, 10);

    // 将GtkBox作为远程桌面连接画面页面的小部件
    m_widget = vbox;

    // 保存各个控件的指针到私有变量中
    m_title_label = title_label;
    m_address_entry = address_entry;
    m_port_entry = port_entry;
    m_username_entry = username_entry;
    m_password_entry = password_entry;
    m_connect_button = connect_button;
}

GtkWidget *RemoteDesktopViewPage::getWidget()
{
    return m_widget;
}

void RemoteDesktopViewPage::connectRemoteDesktop()
{
    // 连接到远程桌面
    // 获取地址、端口、用户名和密码，并使用相应的协议连接到远程桌面
}

void RemoteDesktopViewPage::connectBackButtonClickedSignal(std::function<void()> callback)
{
    // 连接远程桌面连接画面页面的返回按钮被点击信号
    // 当用户点击返回按钮时，调用callback函数
}

void RemoteDesktopViewPage::connectConnectButtonClickedSignal(std::function<void(const std::string &, const std::string &)> callback)
{
    // 连接远程桌面连接画面页面的连接按钮被点击信号
    // 当用户点击连接按钮时，调用callback函数，并传递地址、端口、用户名和密码作为参数
}

void RemoteDesktopViewPage::setTitle(const std::string &title)
{
    // 设置远程桌面连接画面页面的标题
    gtk_label_set_text(GTK_LABEL(m_title_label), title.c_str());
}

void RemoteDesktopViewPage::setAddress(const std::string &address)
{
    // 设置远程桌面连接画面页面的地址
    gtk_entry_set_text(GTK_ENTRY(m_address_entry), address.c_str());
}

void RemoteDesktopViewPage::setPort(const std::string &port)
{
    // 设置远程桌面连接画面页面的端口
    gtk_entry_set_text(GTK_ENTRY(m_port_entry), port.c_str());
}

void RemoteDesktopViewPage::setUserName(const std::string &userName)
{
    // 设置远程桌面连接画面页面的用户名
    gtk_entry_set_text(GTK_ENTRY(m_username_entry), userName.c_str());
}

void RemoteDesktopViewPage::setPassword(const std::string &password)
{
    // 设置远程桌面连接画面页面的密码
    gtk_entry_set_text(GTK_ENTRY(m_password_entry), password.c_str());
}

std::string RemoteDesktopViewPage::getTitle()
{
    // 获取远程桌面连接画面页面的标题
    const gchar *title = gtk_label_get_text(GTK_LABEL(m_title_label));
    return std::string(title);
}

std::string RemoteDesktopViewPage::getAddress()
{
    // 获取远程桌面连接画面页面的地址
    const gchar *address = gtk_entry_get_text(GTK_ENTRY(m_address_entry));
    return std::string(address);
}

std::string RemoteDesktopViewPage::getPort()
{
    // 获取远程桌面连接画面页面的端口
    const gchar *port = gtk_entry_get_text(GTK_ENTRY(m_port_entry));
    return std::string(port);
}

std::string RemoteDesktopViewPage::getUserName()
{
    // 获取远程桌面连接画面页面的用户名
    const gchar *userName = gtk_entry_get_text(GTK_ENTRY(m_username_entry));
    return std::string(userName);
}

std::string RemoteDesktopViewPage::getPassword()
{
    // 获取远程桌面连接画面页面的密码
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(m_password_entry));
    return std::string(password);
}