#ifndef ANTD_BUTTON_H
#define ANTD_BUTTON_H

#include <gtk/gtk.h>

extern const char *ANTD_BUTTON_CSS;

struct AntdButtonOption
{
  gchar *type;
  gchar *label;
};

class AntdButton
{
public:
  AntdButton(AntdButtonOption *option);
  GtkWidget *getWidget();

private:
  GtkWidget *m_widget;
};

#endif // ANTD_BUTTON_H
