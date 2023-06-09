#ifndef ANTD_FORM_ITEM_H
#define ANTD_FORM_ITEM_H

#include <gtk/gtk.h>

extern const char *ANTD_FORM_ITEM_CSS;

typedef gchar* (ValidatorFunc)(const GtkWidget *control);

struct AntdFormItemOption
{
    gchar *label;
    GtkWidget *control;
    ValidatorFunc* validator;
};

struct AntdFormItemWithoutValidatorOption
{
    gchar *label;
    GtkWidget *control;
};

class AntdFormItem
{
public:
    AntdFormItem(AntdFormItemOption* option);
    GtkWidget* get_widget();
    GtkWidget* get_label_widget();
    GtkWidget* get_control_widget();
    ValidatorFunc* get_validator();
    bool validate();
    void set_label_width(gint width);
    void set_margin_bottom(gint margin_bottom);
    static AntdFormItem* create_without_validator(AntdFormItemWithoutValidatorOption* option);

private:
    GtkWidget* m_widget;
    GtkWidget* m_label;
    GtkWidget* m_label_container;
    GtkWidget* m_control;
    GtkWidget* m_explain;
    ValidatorFunc* m_validator;
    GtkCssProvider* m_css_provider;
};

#endif // ANTD_FORM_ITEM_H