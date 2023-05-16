#include "antd_button.h"

const char *ANTD_BUTTON_CSS = "\
.ant-button {\
    padding: 4px 15px;\
    font-size: 14px;\
    font-weight: 500;\
    background: #f7f7f7;\
    border: 1px solid #d9d9d9;\
    border-radius: 4px;\
    color: rgba(0, 0, 0, 0.65);\
    transition: all 0.3s;\
}\
.ant-button:hover {\
    background: #e6e6e6;\
    border: #d9d9d9;\
}\
.primary {\
    background: #1890ff;\
    border: #1890ff;\
    color: #fff;\
}\
.primary:hover {\
    background: #40a9ff;\
    border: #40a9ff;\
}\
.link {\
    background: transparent;\
    border: transparent;\
    color: #1677ff;\
    box-shadow: none;\
}\
.link:hover {\
    background: transparent;\
    border: transparent;\
    color: #69b1ff;\
}\
";

    AntdButton::AntdButton(AntdButtonOption *option)
{
    GtkWidget *antd_button = gtk_button_new_with_label(option->label);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, ANTD_BUTTON_CSS, -1, NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(antd_button);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context, "ant-button");
    gtk_style_context_add_class(context, option->type);

    m_widget = antd_button;
}

GtkWidget *AntdButton::getWidget()
{
    return m_widget;
}
