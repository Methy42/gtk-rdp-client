#include "antd_form_item.h"

const char *ANTD_FORM_ITEM_CSS = "\
.antd-form-item {\
\
}\
.antd-form-item .antd-content {\
\
}\
.antd-form-item .antd-explain {\
\
}\
.antd-form-item .antd-content .antd-label {\
}\
.antd-form-item .antd-content .antd-control {\
}\
";

AntdFormItem::AntdFormItem(AntdFormItemOption *option)
{
    m_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *content = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    m_explain = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    m_label = gtk_label_new(option->label);
    GtkWidget* 
    m_control = option->control;
    m_validator = option->validator;

    gtk_container_add(GTK_CONTAINER(content), m_label);
    gtk_container_add(GTK_CONTAINER(content), m_control);
    gtk_container_add(GTK_CONTAINER(m_widget), content);
    gtk_container_add(GTK_CONTAINER(m_widget), m_explain);

    GtkStyleContext *context = gtk_widget_get_style_context(m_widget);
    GtkStyleContext *content_context = gtk_widget_get_style_context(content);
    GtkStyleContext *explain_context = gtk_widget_get_style_context(m_explain);
    GtkStyleContext *label_context = gtk_widget_get_style_context(m_label);
    GtkStyleContext *control_context = gtk_widget_get_style_context(m_control);

    m_css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(m_css_provider, ANTD_FORM_ITEM_CSS, -1, NULL);

    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(m_css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_provider(content_context, GTK_STYLE_PROVIDER(m_css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_provider(explain_context, GTK_STYLE_PROVIDER(m_css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_provider(label_context, GTK_STYLE_PROVIDER(m_css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_provider(control_context, GTK_STYLE_PROVIDER(m_css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_style_context_add_class(context, "antd-form-item");
    gtk_style_context_add_class(content_context, "antd-content");
    gtk_style_context_add_class(explain_context, "antd-explain");
    gtk_style_context_add_class(label_context, "antd-label");
    gtk_style_context_add_class(control_context, "antd-control");
}

bool AntdFormItem::validate()
{
    if (m_validator == NULL)
        return true;

    gchar *validate_result = m_validator(m_control);
    if (validate_result != NULL)
    {
        GtkStyleContext *context = gtk_widget_get_style_context(m_widget);
        gtk_style_context_add_class(context, "antd-validate-filed");

        GtkWidget *validate_result_text = gtk_label_new(validate_result);
        gtk_container_add(GTK_CONTAINER(m_explain), validate_result_text);
        GtkStyleContext *validate_result_text_context = gtk_widget_get_style_context(validate_result_text);
        gtk_style_context_add_provider(validate_result_text_context, GTK_STYLE_PROVIDER(m_css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_style_context_add_class(validate_result_text_context, "antd-explain-text");
        return false;
    }
    else
    {
        GtkStyleContext *context = gtk_widget_get_style_context(m_widget);
        gtk_style_context_remove_class(context, "antd-validate-filed");

        gtk_container_remove(GTK_CONTAINER(m_explain), gtk_bin_get_child(GTK_BIN(m_explain)));
        return true;
    }
}

void AntdFormItem::set_label_width(gint width)
{
    gtk_label_set_width_chars(GTK_LABEL(m_label), width);
}

void AntdFormItem::set_margin_bottom(gint margin_bottom)
{
    gtk_widget_set_margin_bottom(m_widget, margin_bottom);
}

AntdFormItem *AntdFormItem::create_without_validator(AntdFormItemWithoutValidatorOption *option)
{
    AntdFormItemOption *fullOption = new AntdFormItemOption();
    fullOption->label = option->label;
    fullOption->control = option->control;
    fullOption->validator = NULL;
    return new AntdFormItem(fullOption);
}

GtkWidget *AntdFormItem::get_widget() {
    return m_widget;
}

GtkWidget *AntdFormItem::get_label_widget() {
    return m_label;
}

GtkWidget *AntdFormItem::get_control_widget() {
    return m_control;
}

ValidatorFunc *AntdFormItem::get_validator() {
    return m_validator;
}