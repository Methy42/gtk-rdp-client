#include "remote_desktop_modal.h"

const char *REMOTE_DESKTOP_MODAL_CSS = "\
.\
";

// 在这里实现 RemoteDesktopModal 类的方法

RemoteDesktopModal::RemoteDesktopModal()
{
    // 这里放置远程桌面连接信息模态框的构造逻辑
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "远程桌面连接信息");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), false);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    AntdForm* remote_desktop_form = new AntdForm();

    // 远程桌面名称
    m_name_input = new AntdInput(new AntdInputOption{g_strdup("请输入名称"), g_strdup(""), 40});
    AntdFormItem* name_form_item = new AntdFormItem(new AntdFormItemOption{g_strdup("名称"), m_name_input->getWidget(), NULL});

    // 远程桌面IP地址
    m_ip_input = new AntdInput(new AntdInputOption{ g_strdup("请输入IP"), g_strdup(""), 40 });
    AntdFormItem* ip_form_item = new AntdFormItem(new AntdFormItemOption{g_strdup("IP地址"), m_ip_input->getWidget(), NULL});

    // 远程桌面端口号
    GtkWidget *port_label = gtk_label_new("端口号：");
    // 创建一个整数范围的GtkAdjustment对象
    GtkAdjustment *adj = gtk_adjustment_new(0, 0, G_MAXINT, 1, 10, 0);
    // 创建一个新的GtkSpinButton对象，并使用上面创建的GtkAdjustment对象进行初始化
    m_port_input = gtk_spin_button_new(adj, 1, 0);
    // 将GtkSpinButton设置为整形数字
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(m_port_input), true);
    AntdFormItem* port_form_item = new AntdFormItem(new AntdFormItemOption{ g_strdup("端口"), m_port_input, NULL });
    
    // 远程桌面账号
    m_username_input = new AntdInput(new AntdInputOption{ g_strdup("请输入桌面账号"), g_strdup(""), 40 });
    AntdFormItem* username_form_item = new AntdFormItem(new AntdFormItemOption{g_strdup("账号"), m_username_input->getWidget(), NULL});

    // 远程桌面密码
    m_password_input = new AntdInput(new AntdInputOption{ g_strdup("请输入密码"), g_strdup(""), 40 });
    gtk_entry_set_visibility(GTK_ENTRY(m_password_input->getWidget()), false); // 将密码输入框中的内容隐藏
    AntdFormItem* password_form_item = new AntdFormItem(new AntdFormItemOption{g_strdup("密码"), m_password_input->getWidget(), NULL});

    // 远程桌面域名
    m_domain_input = new AntdInput(new AntdInputOption{ g_strdup("请输入域名"), g_strdup(""), 40 });
    AntdFormItem* domain_form_item = new AntdFormItem(new AntdFormItemOption{g_strdup("域名"), m_domain_input->getWidget(), NULL});

    // 是否自动登录
    m_auto_login_checkbutton = gtk_check_button_new_with_label("自动登录");
    AntdFormItem* auto_login_form_item = new AntdFormItem(new AntdFormItemOption{g_strdup(""), m_auto_login_checkbutton, NULL});

    remote_desktop_form->add_item(name_form_item);
    remote_desktop_form->add_item(ip_form_item);
    remote_desktop_form->add_item(port_form_item);
    remote_desktop_form->add_item(username_form_item);
    remote_desktop_form->add_item(password_form_item);
    remote_desktop_form->add_item(domain_form_item);
    remote_desktop_form->add_item(auto_login_form_item);

    gtk_container_add(GTK_CONTAINER(vbox), remote_desktop_form->get_widget());

    remote_desktop_form->set_form_item_label_width(80);
    remote_desktop_form->set_form_item_margin_bottom(10);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(hbox), true);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);

    // 确定按钮
    GtkWidget *ok_button = gtk_button_new_with_label("确定");
    g_signal_connect(G_OBJECT(ok_button), "clicked", G_CALLBACK(RemoteDesktopModal::saveDataCallback), this);
    gtk_box_pack_end(GTK_BOX(hbox), ok_button, false, false, 0);

    // 取消按钮
    GtkWidget *cancel_button = gtk_button_new_with_label("取消");
    g_signal_connect_swapped(G_OBJECT(cancel_button), "clicked", G_CALLBACK(RemoteDesktopModal::closeCallback), this);
    gtk_box_pack_end(GTK_BOX(hbox), cancel_button, false, false, 0);

    gtk_widget_set_size_request(window, 400, -1); // 设置模态框的宽度为400个像素
    m_widget = window;
}

GtkWidget *RemoteDesktopModal::getWidget()
{
    // 返回远程桌面连接信息模态框的gtk小部件
    return m_widget;
}

void RemoteDesktopModal::saveData()
{
    // 将远程桌面连接信息保存到全局位置中
    std::string name = gtk_entry_get_text(GTK_ENTRY(m_name_input->getWidget()));
    std::string ip = gtk_entry_get_text(GTK_ENTRY(m_ip_input->getWidget()));
    int port = (int)gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m_port_input));
    std::string username = gtk_entry_get_text(GTK_ENTRY(m_username_input->getWidget()));
    std::string password = gtk_entry_get_text(GTK_ENTRY(m_password_input->getWidget()));
    std::string domain = gtk_entry_get_text(GTK_ENTRY(m_domain_input->getWidget()));
    bool auto_login = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(m_auto_login_checkbutton));

    // 在这里将数据保存到全局位置中，比如使用一个单例类来保存
    Desktop desktop = Desktop(name, ip, port, username, password, domain, auto_login);
    DesktopORM::getInstance().addDesktop(desktop);
}

void RemoteDesktopModal::open()
{
    // 打开远程桌面连接信息模态框
    gtk_widget_show_all(m_widget);
}

void RemoteDesktopModal::close()
{
    // 关闭远程桌面连接信息模态框
    gtk_widget_hide(m_widget);
    delete m_name_input;
}

void RemoteDesktopModal::setConnectionInfo(std::string address, std::string username, std::string password)
{
    // 设置远程桌面连接信息
    gtk_entry_set_text(GTK_ENTRY(m_ip_input->getWidget()), address.c_str());
    gtk_entry_set_text(GTK_ENTRY(m_username_input->getWidget()), username.c_str());
    gtk_entry_set_text(GTK_ENTRY(m_password_input->getWidget()), password.c_str());
}

void RemoteDesktopModal::saveDataCallback(GtkButton *button, gpointer user_data)
{
    RemoteDesktopModal *modal = static_cast<RemoteDesktopModal *>(user_data);
    modal->saveData();
    modal->close();
}

void RemoteDesktopModal::closeCallback(GtkButton *button, gpointer user_data)
{
    RemoteDesktopModal *modal = static_cast<RemoteDesktopModal *>(user_data);
    modal->close();
}