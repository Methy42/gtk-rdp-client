#include "antd_input.h"

const char *ANTD_INPUT_CSS = "\
    .antd-input {\
        border: #d9d9d9;\
        background: #ffffff;\
        border-radius: 6px;\
    }\
    .antd-input:focus {\
        border-color: #4096ff;\
        box-shadow: 0 0 0 2px rgba(24, 144, 255, 0.2);\
    }\
";

AntdInput::AntdInput(AntdInputOption* option)
{
    m_widget = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(m_widget), option->placeholder);
    gtk_entry_set_text(GTK_ENTRY(m_widget), option->value);

    m_css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(m_css_provider, ANTD_INPUT_CSS, -1, NULL);
    gtk_style_context_add_provider(gtk_widget_get_style_context(m_widget), GTK_STYLE_PROVIDER(m_css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(gtk_widget_get_style_context(m_widget), "antd-input");
}

GtkWidget* AntdInput::getWidget()
{
    return m_widget;
}