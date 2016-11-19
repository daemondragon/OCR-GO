#include "options.h"

void on_quitter_btn(GtkWidget* widget, gpointer data)
{
    GtkWidget *Question;

    /* Creation of the box message*/
    /* Type : Question -> GTK_MESSAGE_QUESTION */
    /* Boutons : 1 YES, 1 NO -> GTK_BUTTONS_YES_NO */
    Question = gtk_message_dialog_new (GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Are you sure you want\n to leave this program?");

    /* Display and dialog part to know what the user want to do*/
    switch(gtk_dialog_run(GTK_DIALOG(Question)))
    {
        case GTK_RESPONSE_YES:
            /* OUI -> We leave the application*/
            gtk_widget_destroy(widget);
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NO:
            /* NON -> We destroy the box message */
            gtk_widget_destroy(Question);
            break;
    }
}

