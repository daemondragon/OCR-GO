#include "window.h"
#include "show_xor.h"
#include "testing_cut.h"
#include "filters.h"

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
void create_file_selection()
{
    GtkWidget *selection;

    selection = gtk_file_selection_new( g_locale_to_utf8(
                                  "Sélect a file ", -1, NULL, NULL, NULL) );
    gtk_widget_show(selection);

    //We stop the utilisation of others window during the file selection.
    gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
     
    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button),
     "clicked", G_CALLBACK(get_way), selection );

    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)
                                                            ->cancel_button),
      "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}
//i do the same one but with a change in the callback fonction the time i find out how 
//to make it shorter
void create_ner_selection()
{

	GtkWidget * neur_select;
	
	neur_select = gtk_file_selection_new( g_locale_to_utf8(
				"Select the neuronal network to load",-1,
				 NULL,NULL,NULL));
	gtk_widget_show(neur_select);

	gtk_window_set_modal(GTK_WINDOW(neur_select),TRUE);
	
	g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(neur_select)->ok_button),
			"clicked",G_CALLBACK(load_neural),neur_select);
	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(neur_select)->cancel_button),
				"clicked",G_CALLBACK(gtk_widget_destroy),neur_select);
}


void get_way(GtkWidget *bouton,GtkWidget *file_selection)
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
void load_neural(GtkWidget *bout,GtkWidget* neural_selected)
{
	
	 char * way;
	way =(char*) gtk_file_selection_get_filename(GTK_FILE_SELECTION(neural_selected));
	load_neural_network(way);
	gtk_widget_destroy(neural_selected);
	
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
//fonctions for neuronal network 
void create_neuronal_network(GtkWidget * Dialbox,GtkWidget * window)
{
	//variable declaration
	GtkWidget *Entry;
	GtkWidget * entr;
	GtkWidget * number_neur;
	const gchar*  n1;
	const gchar* n2;
	uint32_t  couche;
	uint32_t*  neur_per_couche;
	int launch = 1;
	int b = 1;
	Dialbox = gtk_dialog_new_with_buttons("Neuronal network creation",
			GTK_WINDOW(window),
			GTK_DIALOG_MODAL,
			GTK_STOCK_OK,GTK_RESPONSE_OK,
			GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
			NULL);
	
	//creation text zone to write in
	Entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(Entry),"Enter number of layer");
	//add the entry into our dialog box
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Dialbox)->vbox),Entry,TRUE,FALSE,0);
	
	number_neur = gtk_dialog_new_with_buttons("Neuronal network creation",
			GTK_WINDOW(window),
			GTK_DIALOG_MODAL,
			GTK_STOCK_OK,GTK_RESPONSE_OK,
			GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
			NULL);
	
	//showing dialog elements
	gtk_widget_show_all(GTK_DIALOG(Dialbox)->vbox);
	
	// we launch the dialbox and the user validate or not 
    	switch (gtk_dialog_run(GTK_DIALOG(Dialbox)))
    	{
        	/* L utilisateur valide */
        	case GTK_RESPONSE_OK:
			b = 0;
			n1 =  gtk_entry_get_text(GTK_ENTRY(Entry));
			couche = (unsigned int)n1;		 
            		break;
        	/* L utilisateur annule */
        	case GTK_RESPONSE_CANCEL:
        	case GTK_RESPONSE_NONE:
        		default:
            		     	break;
    	}
 
    /* Destruction de la boite de dialogue */
    gtk_widget_destroy(Dialbox);
    if (b==0)
	{	//Second dialog box for the neur_couche number.
		number_neur = gtk_dialog_new_with_buttons("Neuronal network creation",
                        GTK_WINDOW(window),
                        GTK_DIALOG_MODAL,
                        GTK_STOCK_OK,GTK_RESPONSE_OK,
                        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                        NULL);
		entr = gtk_entry_new();
		gtk_entry_set_text(GTK_ENTRY(entr),"Enter neuronal couche number");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(number_neur)->vbox),entr,TRUE,FALSE,0);
		
		gtk_widget_show_all(GTK_DIALOG(number_neur)->vbox);
		switch (gtk_dialog_run(GTK_DIALOG(number_neur)))
        {
                /* L utilisateur valide */
                case GTK_RESPONSE_OK:
                        n2 = gtk_entry_get_text(GTK_ENTRY(entr));
			neur_per_couche = (unsigned int*)n2;
			launch=0;
                        break;
                /* L utilisateur annule */
                case GTK_RESPONSE_CANCEL:
                case GTK_RESPONSE_NONE:
                        default:
                                  break;
        }
	
    /* Destruction de la boite de dialogue */
    gtk_widget_destroy(number_neur);

	}
	if(launch==0)
	{

		create_neural_network(couche,neur_per_couche);
		
	}
}

 
