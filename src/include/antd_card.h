#ifndef ANTD_CARD_H
#define ANTD_CARD_H

#include <gtk/gtk.h>

extern const char *ANTD_CARD_CSS;

struct AntdCardOption
{
    gchar* cover_image_path;
    gchar* title;
    gchar* description;
};

class AntdCard
{
public:
    AntdCard(AntdCardOption* option);
    GtkWidget* getWidget();
    GtkWidget* getCoverContainer();
    void addAction(GtkWidget* action);

private:
    GtkWidget* m_widget;
    GtkWidget* m_actions_container;
    GtkWidget* m_cover_container;
};

#endif // ANTD_CARD_H