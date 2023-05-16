#include <iostream>

#include "antd_card.h"

const char *ANTD_CARD_CSS = "\
.antd-card {\
    background: #fff;\
    border-radius: 2px;\
    box-shadow: 0 1px 2px rgba(0, 0, 0, 0.1);\
}\
.antd-card-cover {\
    background: #f7f7f7;\
    background-size: cover;\
    background-position: center;\
}\
.antd-card-cover img {\
}\
.antd-card-body {\
    padding: 15px;\
}\
.antd-card-body .antd-card-title {\
    margin-bottom: 10px;\
    font-size: 16px;\
    font-weight: 500;\
    color: rgba(0, 0, 0, 0.85);\
}\
.antd-card-body .antd-card-description {\
    font-size: 14px;\
    color: rgba(0, 0, 0, 0.65);\
}\
.antd-card-actions {\
    padding: 10px 15px;\
    border-top: 1px solid #f0f0f0;\
}\
.antd-card-actions > * {\
    margin-left: 8px;\
}\
.antd-card-actions > *:first-child {\
    margin-left: 0;\
}\
.antd-card-actions > *:last-child {\
    margin-right: 0;\
}\
";

AntdCard::AntdCard(AntdCardOption *option)
{
    GtkWidget *antd_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkCssProvider *antd_card_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(antd_card_provider, ANTD_CARD_CSS, -1, NULL);
    GtkStyleContext *antd_card_context = gtk_widget_get_style_context(antd_card);
    gtk_style_context_add_provider(antd_card_context, GTK_STYLE_PROVIDER(antd_card_provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(antd_card_context, "antd-card");

    // 封面
    GtkWidget *cover = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkStyleContext *cover_context = gtk_widget_get_style_context(cover);
    gtk_style_context_add_provider(cover_context, GTK_STYLE_PROVIDER(antd_card_provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(cover_context, "antd-card-cover");
    gtk_box_pack_start(GTK_BOX(antd_card), cover, false, false, 0);

    GtkWidget *cover_image = gtk_image_new_from_file(option->cover_image_path);
    gtk_box_pack_start(GTK_BOX(cover), cover_image, false, false, 0);

    // 内容
    GtkWidget *body = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkStyleContext *body_context = gtk_widget_get_style_context(body);
    gtk_style_context_add_provider(body_context, GTK_STYLE_PROVIDER(antd_card_provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(body_context, "antd-card-body");
    gtk_box_pack_start(GTK_BOX(antd_card), body, true, true, 0);

    GtkWidget *title = gtk_label_new(option->title);
    GtkStyleContext *title_context = gtk_widget_get_style_context(title);
    gtk_style_context_add_provider(title_context, GTK_STYLE_PROVIDER(antd_card_provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(title_context, "antd-card-title");
    gtk_box_pack_start(GTK_BOX(body), title, false, false, 0);

    GtkWidget *description = gtk_label_new(option->description);
    GtkStyleContext *description_context = gtk_widget_get_style_context(description);
    gtk_style_context_add_provider(description_context, GTK_STYLE_PROVIDER(antd_card_provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(description_context, "antd-card-description");
    gtk_box_pack_start(GTK_BOX(body), description, false, false, 0);

    GtkWidget *actions_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkStyleContext *actions_container_context = gtk_widget_get_style_context(actions_container);
    gtk_style_context_add_provider(actions_container_context, GTK_STYLE_PROVIDER(antd_card_provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(actions_container_context, "antd-card-actions");
    gtk_box_pack_start(GTK_BOX(antd_card), actions_container, false, false, 0);

    m_widget = antd_card;
    m_actions_container = actions_container;
    m_cover_container = cover;
}

GtkWidget *AntdCard::getWidget()
{
    return m_widget;
}

GtkWidget *AntdCard::getCoverContainer()
{
    return m_cover_container;
}

void AntdCard::addAction(GtkWidget *action)
{
    gtk_box_pack_start(GTK_BOX(m_actions_container), action, false, false, 0);
}
