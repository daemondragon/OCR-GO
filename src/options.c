#include "window.h"
#include "show_xor.h"
#include "filters.h"
#include "testing_cut.h"
#include "rotation.h"
#include "image_to_matrix.h"
#include "img2txt.h"
#include "testing_img2txt.h"
#include "save_load_network.h"
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
void open_butt(GtkWidget * dialog, gpointer user_data)
{
	const gchar * image_name;
	static GtkWidget * image;
	struct window_s * wind;
	wind = (window_t*)user_data;
	GtkWidget * box_img;
	struct box_s * box;
	box = wind->box;
	dialog = gtk_file_chooser_dialog_new("Open a file",NULL,
			GTK_FILE_CHOOSER_ACTION_OPEN,
			GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
			GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,
			NULL);
	box_img = box->main_box;
	
	
	switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_ACCEPT:
			
			image_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			if(image)
			{
                                gtk_image_set_from_file(GTK_IMAGE(image),image_name);
				wind->image_name = image_name;
			}
			else
			{
			
			
				image= gtk_image_new_from_file(image_name);
				gtk_box_pack_end(GTK_BOX(box_img),image,TRUE,FALSE,0);
				wind->image_name = image_name;
				gtk_widget_show(image);
			}
			break;
		case GTK_RESPONSE_CANCEL:
		default:
				break; 
	}
	gtk_widget_destroy(dialog);

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

void save_neural_net(GtkWidget * dialog, gpointer data)
{

	struct window_s * window;
	window = (window_t *)data;
	
	char * net_name;
	dialog = gtk_file_chooser_dialog_new("Save neural network", NULL,	
				GTK_FILE_CHOOSER_ACTION_SAVE,
				GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
				GTK_STOCK_SAVE,GTK_RESPONSE_ACCEPT,
				NULL);
	switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_ACCEPT:
				net_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
				save_neural_network(window->net,net_name);
				break;
		case GTK_RESPONSE_CANCEL:
		default:
			break;
	}
	gtk_widget_destroy(dialog);		

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
void load_neural(GtkWidget *bouton,gpointer  data)
{
	
	char * way;
	struct window_s * wind;
	wind = (window_t*) data;
	bouton = gtk_file_chooser_dialog_new("Choose neural network to load",NULL,
				GTK_FILE_CHOOSER_ACTION_OPEN,
				GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
				GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,
				NULL);
	switch(gtk_dialog_run(GTK_DIALOG(bouton)))
	{
		case GTK_RESPONSE_ACCEPT:
			way = (char*)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(bouton));
			wind->net = load_neural_network(way);
			break;
		case GTK_RESPONSE_CANCEL:
		default:
			break;
	}				     
	gtk_widget_destroy(bouton);
}
//fonctions for neuronal network 
void create_neuronal_network(GtkWidget * Dialbox,gpointer data)
{
	struct window_s * wind;
	wind = (window_t*) data;
	GtkWidget * window;
	window = wind->main_window;
	//variable declaration
	GtkWidget *Entry;
	GtkWidget * entr;
	GtkWidget * number_neur;
	uint32_t  couche;
	uint32_t * neur_per_couche;
	char* n1;//represent user enter value
	char *n2;
	
	//create_neural_network(couche,neur_per_couche);

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
        	//L utilisateur valide 
        	case GTK_RESPONSE_OK:
			b = 0;
			n1 =(char*)  gtk_entry_get_text(GTK_ENTRY(Entry));
			couche= (uint32_t)strtoul(n1,NULL,0);
			 printf("couche = %d \n",couche);
					 
            		break;
        	// L utilisateur annule 
        	case GTK_RESPONSE_CANCEL:
        	case GTK_RESPONSE_NONE:
        		default:
            		     	break;
    	}
 
    // Destruction de la boite de dialogue 
    gtk_widget_destroy(Dialbox);
     
    if (b==0)
	{
		neur_per_couche = malloc(sizeof(uint32_t) * couche);	
		
		for(uint32_t i = 0; i<couche;i++)
		{
			//Second dialog box for the neur_couche number.
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
                		// L utilisateur valide 
                		case GTK_RESPONSE_OK:
                        		n2 =(char*) gtk_entry_get_text(GTK_ENTRY(entr));
					neur_per_couche[i]=(uint32_t)strtoul(n2,NULL,0);
					printf("nb_neurone = %d \n", neur_per_couche[i]);
					launch=0;
                        		break;
                		// L utilisateur annule 
                		case GTK_RESPONSE_CANCEL:
                		case GTK_RESPONSE_NONE:
                        	default:
					 launch =42;
                                 	 break;
        		}
	
    			// Destruction de la boite de dialogue 
   			 gtk_widget_destroy(number_neur);
		}
	}
	
	if(launch==0)
	{

		wind->net=create_neural_network(couche,neur_per_couche);
		
	}
}
void rotation_bout(const char * image_name, gpointer data)
{
	struct window_s * window;
	window = (window_t *)data;
	GtkWidget * wind = window->main_window;
	struct box_s * box;
	box = window->box;
	GtkWidget * box_img;
	box_img = box->main_box;
	gtk_widget_destroy(box_img);
	GtkWidget * image;
	GtkWidget * box2;
	image_name = window->image_name;
	box = create_box();
	box2 = box->main_box;
	int width,height;
        double * matrix_end;
        double * matrix = file_to_matrix_grey(image_name,
                &matrix_end,&width,&height);
        binarize_simple(matrix,matrix_end);
        double * matrix2 = autorotate(matrix,&width,&height);
        image = image_from_matrix(matrix2,width,height);
	gtk_box_pack_end(GTK_BOX(box2),image,TRUE,FALSE,0);
	gtk_table_attach_defaults(GTK_TABLE(window->Table),box2,0,5,2,9);
	window->box->main_box=box2;
	gtk_widget_show_all(wind);
		
			
}
void binarize_op(const char* image,gpointer data)
{
	struct window_s * window;
	window = (window_t *)data;
	struct box_s * box;
	box = window->box;
	GtkWidget * box_img;
	box_img = box->main_box;
	GtkWidget * img;
	img = box->image;
	gtk_widget_hide(box_img);
	GtkWidget * img2;
	image = window->image_name;
	img2 = file_to_image_bin(image);
	gtk_image_set_from_image(GTK_IMAGE(img),img2,0);
	gtk_widget_show(img);
}
void get_result(GtkWidget * text,gpointer data)
{
 	test_save();	
	struct text_s * test;
	test = (text_t*)data;
	text = test->text_view;
	GtkTextBuffer *buffer;
    	GtkTextIter start;
    	GtkTextIter end;
    	FILE *fichier;
    	const gchar *chemin;
    	gchar lecture[1024];
     
    	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
     
    	chemin = "./image_test/test_cut.txt";
    	fichier = fopen(chemin,"rt");
     
	gtk_text_buffer_get_start_iter(buffer,&start);
    	gtk_text_buffer_get_end_iter(buffer,&end);
   	gtk_text_buffer_delete(buffer, &start, &end);
     
    	while(fgets(lecture, 1024, fichier))
    	{
        	gtk_text_buffer_get_end_iter(buffer,&end);
        	gtk_text_buffer_insert(buffer, &end, g_locale_to_utf8
		(lecture, -1, NULL, NULL, NULL), -1);
    	}
     
    	fclose(fichier);
	

}
