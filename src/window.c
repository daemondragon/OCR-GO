#include "window.h"

window_t* create_window()
{
    window_t* window = malloc(sizeof(window_t));
    if (!window)
        return (NULL);

    int argc = 0;
    char **argv = NULL;

    gtk_init(&argc, &argv);

    window->net = NULL;
    window->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    window->Table = gtk_table_new(10,10,TRUE);
    window->image_name = NULL;
    window->box=create_box();
    gtk_container_set_border_width(GTK_CONTAINER(window->main_window),5);
    gtk_window_set_default_size(GTK_WINDOW(window->main_window), 1024,768);
    gtk_window_set_title(GTK_WINDOW(window->main_window),"OCR GO ");
    gtk_window_set_position(GTK_WINDOW(window->main_window),GTK_WIN_POS_CENTER);
    gtk_window_maximize(GTK_WINDOW(window->main_window));
    gtk_window_set_gravity(GTK_WINDOW(window->main_window),GDK_GRAVITY_CENTER);
    g_signal_connect(G_OBJECT(window->main_window), "destroy",
                                            G_CALLBACK(gtk_main_quit), NULL);

    return (window);
}
box_t*  create_box()
{
	box_t *  box = malloc(sizeof(box_t));
	if(!box)
		return NULL;
	box->main_box = gtk_vbox_new(TRUE,0); 
	
	//box->image_name = NULL;
	return (box);

}
text_t*	create_text()
{
	text_t * text = malloc(sizeof(text_t));
	if(!text)
		return NULL;
	
	text->box = gtk_vbox_new(FALSE,5);
	text->scrollbar =gtk_scrolled_window_new(NULL,NULL);
	gtk_box_pack_start(GTK_BOX(text->box),text->scrollbar,TRUE,TRUE,5);

	text->text_view = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(text->scrollbar),text->text_view);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(text->scrollbar),
		GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	return (text);
}

void delete_window(window_t *window)
{
    if (window->net)
        delete_neural_network(window->net);

    free(window);
}

int run_window(int argc, char **argv)
{
    struct window_s * wind;
    struct box_s * box;
    struct text_s * texte;
    GtkWidget *Window;
    //GtkWidget *Table;
    GtkWidget *Button[2];
    GtkWidget * VboxMenu;
    GtkWidget * MenuBar;
    GtkWidget * Menu;
    GtkWidget * MenuItems;
    GtkWidget * box_img;
    GtkWidget * box_result;
	
    gtk_init(&argc, &argv);
    /* creation of the window and initialisation of size and place
    of the window */
    wind = create_window();
    box = wind->box;
    texte = create_text();
    Window = wind->main_window;
	//gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //gtk_container_set_border_width(GTK_CONTAINER(Window),5);
    //gtk_window_set_default_size(GTK_WINDOW(Window), 1024, 768);
    //gtk_window_set_title(GTK_WINDOW(Window),"OCR GO ");
    //g_signal_connect(G_OBJECT(Window), "destroy",
      //                                      G_CALLBACK(gtk_main_quit), NULL);

    /* Creation and insertion of the 10 & 10 table in the window */
    //Table=gtk_table_new(10,10,TRUE);
   
    gtk_container_add(GTK_CONTAINER(Window), GTK_WIDGET(wind->Table));

     Button[0] = gtk_button_new_from_stock(GTK_STOCK_QUIT);
     Button[1] = gtk_button_new_with_label("get result");

    /*Creation of the Menu Box and his different parameter */
    VboxMenu = gtk_vbox_new(FALSE, 0);
    box_img = box->main_box;
    box_result = texte->box;
    MenuBar = gtk_menu_bar_new();
    
    Menu = gtk_menu_new(); 
    
    MenuItems = gtk_image_menu_item_new_with_label("open image");
    g_signal_connect(G_OBJECT(MenuItems), "activate", 
			G_CALLBACK(open_butt),(gpointer*)wind);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);

    MenuItems = gtk_image_menu_item_new_with_label("open net");
    g_signal_connect(G_OBJECT(MenuItems), "activate",
                         G_CALLBACK(load_neural),
                         (gpointer*)wind);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);



    MenuItems = gtk_image_menu_item_new_with_label("save net");
    g_signal_connect(G_OBJECT(MenuItems),"activate",
			G_CALLBACK(save_neural_net),(gpointer*)wind);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);

    MenuItems = gtk_image_menu_item_new_with_label("create net");
    g_signal_connect(G_OBJECT(MenuItems),"activate",
			G_CALLBACK(create_neuronal_network),
				(gpointer*)wind);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);

    MenuItems = gtk_image_menu_item_new_with_label("leave program");
    g_signal_connect(G_OBJECT(MenuItems), "activate",
                             G_CALLBACK(on_quitter_btn),(GtkWidget*) Window);
    gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItems);
    MenuItems = gtk_menu_item_new_with_label("Fichier");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItems), Menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), MenuItems);

    /*second sub menu */
   //tu crées la base de ton menu
   Menu = gtk_menu_new();

   //tu commences à créer les différents éléments qui composent ton menu(les boutons)
   MenuItems = gtk_menu_item_new_with_label("Rotation");
   g_signal_connect(G_OBJECT(MenuItems),"activate",G_CALLBACK(rotation_bout),
	(gpointer *)wind);//ici cela te permet d'appeler les fonctions void qui seront lié à tes boutons grace au callback
   gtk_menu_shell_append(GTK_MENU_SHELL(Menu),MenuItems);//ici tu attache le bouton à ton menu
   MenuItems = gtk_menu_item_new_with_label("Binarize");//tu recommences pour les différentrs boutons dont tu as besoin
   g_signal_connect(G_OBJECT(MenuItems),"activate",G_CALLBACK(binarize_op),(gpointer*)wind);
   gtk_menu_shell_append(GTK_MENU_SHELL(Menu),MenuItems);

   MenuItems = gtk_menu_item_new_with_label("extract");
   gtk_menu_shell_append(GTK_MENU_SHELL(Menu),MenuItems);

   MenuItems = gtk_menu_item_new_with_label("contrast improve");
   gtk_menu_shell_append(GTK_MENU_SHELL(Menu),MenuItems);


   MenuItems = gtk_menu_item_new_with_label("Traitement image");
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItems),Menu);//ici tu set le dernier item comme le nom global de ton menu

   //et tu t'arrêtes à ce niveau la ^ la ligne du dessous et celle qui rajoute le tout à notre interface
   gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar),MenuItems);

    gtk_box_pack_start(GTK_BOX(VboxMenu), MenuBar, FALSE,FALSE,0);
    /* Insertion of boutons */
    gtk_table_attach(GTK_TABLE(wind->Table), Button[0],
      9,10 ,0,1,GTK_EXPAND | GTK_FILL, GTK_EXPAND,0, 0);

    gtk_table_attach_defaults(GTK_TABLE(wind->Table),VboxMenu,0,3,0,2);
    gtk_table_attach_defaults(GTK_TABLE(wind->Table),box_img,0,5,2,9);
    gtk_table_attach_defaults(GTK_TABLE(wind->Table),Button[1],9,10,9,10);
    gtk_table_attach_defaults(GTK_TABLE(wind->Table),box_result,6,10,2,9);

    g_signal_connect(G_OBJECT(Button[0]),"clicked",
                              G_CALLBACK(on_quitter_btn),(GtkWidget*) Window);

    g_signal_connect(G_OBJECT(Button[1]),"clicked",
				G_CALLBACK(get_result),texte);


    gtk_widget_show_all(Window);


    gtk_main();

    return EXIT_SUCCESS;
}

