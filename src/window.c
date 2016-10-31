#include "window.h"

int run_window(int argc, char **argv)
{
    GtkWidget *Window;
    GtkWidget *Table;
    GtkWidget *Button[1];
    GtkWidget * VboxMenu;
    GtkWidget * MenuBar;
    GtkWidget * Menu;
    GtkWidget * MenuItems;
    GtkWidget * img;

    gtk_init(&argc, &argv);
    /* creation of the window and initialisation of size and place
    of the window */
    Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(Window),5);
    gtk_window_set_default_size(GTK_WINDOW(Window), 800, 600);
    gtk_window_set_title(GTK_WINDOW(Window),"OCR GO ");
    g_signal_connect(G_OBJECT(Window), "destroy",
                                            G_CALLBACK(gtk_main_quit), NULL);

    /* Creation and insertion of the 10 & 10 table in the window */
    Table=gtk_table_new(10,10,TRUE);
    gtk_container_add(GTK_CONTAINER(Window), GTK_WIDGET(Table));

     Button[0] = gtk_button_new_from_stock(GTK_STOCK_QUIT);


    /*Creation of the Menu Box and his different parameter */
    VboxMenu = gtk_vbox_new(FALSE, 0);
    img = gtk_vbox_new(FALSE,0);
    MenuBar = gtk_menu_bar_new();
    Menu = gtk_menu_new();

    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);

    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,NULL);
    g_signal_connect(G_OBJECT(MenuItems), "activate",
                         G_CALLBACK(creer_file_selection),
                         (GtkWidget*) Window);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);



    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE,NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);

    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE,NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);

    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,NULL);
    g_signal_connect(G_OBJECT(MenuItems), "activate",
                             G_CALLBACK(on_quitter_btn),(GtkWidget*) Window);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);
    /* ETAPE 4 */
    MenuItems = gtk_menu_item_new_with_label("Fichier");
    /* ETAPE 5 */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItems), Menu);
    /* ETAPE 6 */
    gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), MenuItems);

    /*second sub menu */

   Menu = gtk_menu_new();

   MenuItems = gtk_menu_item_new_with_label("XOR test");
   g_signal_connect(G_OBJECT(MenuItems),"activate",G_CALLBACK(test_xor),NULL);
   gtk_menu_shell_append(GTK_MENU_SHELL(Menu),MenuItems);

   MenuItems = gtk_menu_item_new_with_label("Filter test");
   g_signal_connect(G_OBJECT(MenuItems),"activate",
                                        G_CALLBACK(test_filter),NULL);
   gtk_menu_shell_append(GTK_MENU_SHELL(Menu),MenuItems);

   MenuItems = gtk_menu_item_new_with_label("Cut test");
   g_signal_connect(G_OBJECT(MenuItems),"activate",G_CALLBACK(cut_test),NULL);
   gtk_menu_shell_append(GTK_MENU_SHELL(Menu),MenuItems);


   MenuItems = gtk_menu_item_new_with_label("Test");
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItems),Menu);
   gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar),MenuItems);

    gtk_box_pack_start(GTK_BOX(VboxMenu), MenuBar, FALSE,FALSE,0);
    /* Insertion des boutons */
    gtk_table_attach(GTK_TABLE(Table), Button[0],
      9,10 ,9,10,GTK_EXPAND | GTK_FILL, GTK_EXPAND,0, 0);

    gtk_table_attach_defaults(GTK_TABLE(Table),VboxMenu,0,2,0,10);
    gtk_table_attach_defaults(GTK_TABLE(Table),img,3,7,3,7);
    g_signal_connect(G_OBJECT(Button[0]),"clicked",
                              G_CALLBACK(on_quitter_btn),(GtkWidget*) Window);



    gtk_widget_show_all(Window);


    gtk_main();

    return EXIT_SUCCESS;
}

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
void creer_file_selection()
{
    GtkWidget *selection;

    selection = gtk_file_selection_new( g_locale_to_utf8(
                                  "Sélect a file ", -1, NULL, NULL, NULL) );
    gtk_widget_show(selection);

    //We stop the utilisation of others window during the file selection.
    gtk_window_set_modal(GTK_WINDOW(selection), TRUE);

    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button),
     "clicked", G_CALLBACK(recuperer_chemin), selection );

    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)
                                                            ->cancel_button),
      "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}

void recuperer_chemin(GtkWidget *bouton,GtkWidget *file_selection)
{


  const gchar *chemin;
  chemin =gtk_file_selection_get_filename(GTK_FILE_SELECTION(file_selection));


  bouton = gtk_message_dialog_new(GTK_WINDOW(file_selection),
  GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,
  "file selected : \n%s", chemin);
  gtk_dialog_run(GTK_DIALOG(bouton));
  gtk_widget_destroy(bouton);
  gtk_widget_destroy(file_selection);


}
void test_xor()
{
	show_xor();
}
void cut_test()
{
     show_cutting();
}
void test_filter()
{
     test_filters();
}
