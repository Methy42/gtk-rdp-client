#include <string>
#include <gtk/gtk.h>

#include "remote_desktop_list_page.h"
#include "remote_desktop_view_page.h"
#include "remote_desktop_modal.h"

int main(int argc, char *argv[]) {
    // 初始化GTK库
    gtk_init(&argc, &argv);

    // 创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // 创建一个stack容器，用于切换不同的页面
    GtkWidget *stack = gtk_stack_new();
    gtk_container_add(GTK_CONTAINER(window), stack);

    // 创建远程桌面列表页面、远程桌面连接画面页面和远程桌面连接信息模态框
    RemoteDesktopListPage remoteDesktopListPage;
    RemoteDesktopViewPage remoteDesktopViewPage;
    RemoteDesktopModal remoteDesktopModal;

    remoteDesktopListPage.setModal(&remoteDesktopModal);

    // 添加页面到stack中
    gtk_stack_add_named(GTK_STACK(stack), remoteDesktopListPage.getWidget(), "remote-desktop-list-page");
    gtk_stack_add_named(GTK_STACK(stack), remoteDesktopViewPage.getWidget(), "remote-desktop-view-page");

    // 远程桌面列表页面的回调函数，响应用户选择一个远程桌面后的事件
    auto onRemoteDesktopSelected = [&](const std::string& name, const std::string& address) {
        // 更新远程桌面连接画面的标题和地址
        remoteDesktopViewPage.setTitle(name);
        remoteDesktopViewPage.setAddress(address);

        // 切换到远程桌面连接画面页面
        gtk_stack_set_visible_child_name(GTK_STACK(stack), "remote-desktop-view-page");
    };

    // 远程桌面连接画面页面的回调函数，响应用户点击返回按钮后的事件
    auto onBackButtonClicked = [&]() {
        // 切换回远程桌面列表页面
        gtk_stack_set_visible_child_name(GTK_STACK(stack), "remote-desktop-list-page");
    };

    // 远程桌面连接画面页面的回调函数，响应用户点击连接按钮后的事件
    auto onConnectButtonClicked = [&](const std::string& username, const std::string& password) {
        // 打开远程桌面连接信息模态框
        remoteDesktopModal.open();

        // 在模态框中设置远程桌面连接信息
        remoteDesktopModal.setConnectionInfo(remoteDesktopViewPage.getAddress(), username, password);
    };

    // 将回调函数绑定到远程桌面列表页面、远程桌面连接画面页面和模态框的信号中
    remoteDesktopListPage.connectRemoteDesktopSelectedSignal(onRemoteDesktopSelected);
    remoteDesktopViewPage.connectBackButtonClickedSignal(onBackButtonClicked);
    remoteDesktopViewPage.connectConnectButtonClickedSignal(onConnectButtonClicked);

    // 显示所有小部件
    gtk_widget_show_all(window);

    // 启动GTK主循环，等待用户交互
    gtk_main();

    return 0;
}
