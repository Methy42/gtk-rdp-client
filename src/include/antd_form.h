#ifndef ANTD_FORM_H
#define ANTD_FORM_H

#include <gtk/gtk.h>
#include <vector>
#include "antd_form_item.h"

extern const char *ANTD_FORM_CSS;

struct AntdFormOption
{
    gint label_width;
    gint item_margin_bottom;
};

class AntdForm
{
public:
    AntdForm();
    AntdForm* create_with_option(AntdFormOption* option);
    void add_item(AntdFormItem* formItem);
    GtkWidget* get_widget();
    std::vector<AntdFormItem*> get_form_item_list();
    bool validate();
    void set_form_item_label_width(gint width);
    void set_form_item_margin_bottom(gint margin_bottom);

private:
    GtkWidget* m_widget;
    GtkCssProvider* m_css_provider;
    gint m_form_item_label_width;
    gint m_form_item_margin_bottom;
    std::vector<AntdFormItem*> form_item_list;
};

#endif // ANTD_FORM_H