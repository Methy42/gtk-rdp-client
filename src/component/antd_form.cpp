#include "antd_form.h"

const char* ANTD_FORM_CSS = "/* Your CSS here */";

AntdForm::AntdForm()
{
    m_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    m_css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(m_css_provider, ANTD_FORM_CSS, -1, NULL);
    gtk_style_context_add_provider(gtk_widget_get_style_context(m_widget), GTK_STYLE_PROVIDER(m_css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

AntdForm* AntdForm::create_with_option(AntdFormOption* option)
{
    AntdForm* ant_form = new AntdForm();
    ant_form->set_form_item_label_width(option->label_width);

    return ant_form;
}

void AntdForm::add_item(AntdFormItem* formItem)
{
    gtk_container_add(GTK_CONTAINER(m_widget), formItem->get_widget());
    form_item_list.push_back(formItem);

    if (m_form_item_label_width != 0)
    {
        formItem->set_label_width(m_form_item_label_width);
    }
}

GtkWidget* AntdForm::get_widget()
{
    return m_widget;
}

std::vector<AntdFormItem*> AntdForm::get_form_item_list()
{
    return form_item_list;
}

bool AntdForm::validate()
{
    bool isValid = true;
    
    for (int i = 0; i < form_item_list.size(); i++)
    {
        if (!form_item_list[i]->validate())
        {
            isValid = false;
        }
    }

    return isValid;
}

void AntdForm::set_form_item_label_width(gint width)
{
    m_form_item_label_width = width;
    for (int i = 0; i < form_item_list.size(); i++)
    {
        form_item_list[i]->set_label_width(width);
    }
}

void AntdForm::set_form_item_margin_bottom(gint margin_bottom)
{
    m_form_item_margin_bottom = margin_bottom;
    for (int i = 0; i < form_item_list.size(); i++)
    {
        form_item_list[i]->set_margin_bottom(margin_bottom);
    }
}