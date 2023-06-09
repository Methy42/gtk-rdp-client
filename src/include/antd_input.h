#ifndef ANTD_INPUT_H
#define ANTD_INPUT_H

#include <gtk/gtk.h>

extern const char *ANTD_INPUT_CSS;


struct AntdInputOption
{
    gchar* placeholder;
    gchar* value;
    gint width;
};

class AntdInput
{
public:
    AntdInput(AntdInputOption* option);
    GtkWidget* getWidget();

private:
    GtkWidget* m_widget;
    GtkCssProvider* m_css_provider;
};

#endif // ANTD_INPUT_H