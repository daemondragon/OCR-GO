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
    GtkWidget * box_img;
  
	
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
    box_img = gtk_vbox_new(FALSE,0);
    MenuBar = gtk_menu_bar_new();
    Menu = gtk_menu_new();

    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);

    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,NULL);
    g_signal_connect(G_OBJECT(MenuItems), "activate",
                         G_CALLBACK(create_file_selection),
                         NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);



    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE,NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);

    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE,NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);

    MenuItems = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,NULL);
    g_signal_connect(G_OBJECT(MenuItems), "activate",
                             G_CALLBACK(on_quitter_btn),(GtkWidget*) Window);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);
    MenuItems = gtk_menu_item_new_with_label("Fichier");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItems), Menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), MenuItems);

    /*second sub menu */

   Menu = gtk_menu_new();


   MenuItems = gtk_menu_item_new_with_label("Create net");
   g_signal_connect(G_OBJECT(MenuItems),"activate",G_CALLBACK(create_neuronal_network),
	(GtkWidget *) Window);
   gtk_menu_shell_append(GTK_MENU_SHELL(Menu),MenuItems);
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
    /* Insertion of boutons */
    gtk_table_attach(GTK_TABLE(Table), Button[0],
      9,10 ,9,10,GTK_EXPAND | GTK_FILL, GTK_EXPAND,0, 0);

    gtk_table_attach_defaults(GTK_TABLE(Table),VboxMenu,0,2,0,10);
    gtk_table_attach_defaults(GTK_TABLE(Table),box_img,3,7,3,7);
    g_signal_connect(G_OBJECT(Button[0]),"clicked",
                              G_CALLBACK(on_quitter_btn),(GtkWidget*) Window);



    gtk_widget_show_all(Window);


    gtk_main();

    return EXIT_SUCCESS;
}

