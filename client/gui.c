
#include "client.h"

#define CAMERA_WIDTH 128
#define CAMERA_HEIGHT 128


GtkWidget *fRange, *lRange,*bRange, *rRange, *batt, *key;

void destroy(GtkWidget *widget, gpointer data){
  send(sockfd, "destroy", 7, 0);
  close(sockfd);
  gtk_main_quit();
}

void stop(GtkWidget *widget, gpointer data){
  send(sockfd, "stop", 4, 0);
}

void forward(GtkWidget *widget, gpointer data){
  char new[MAXDISTANCE];
  const char *val = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
  sprintf(new, "f%s", val);

  if (strlen(val) == 0)
    sprintf(new, "f1");

  send(sockfd, new, strlen(new), 0);
  gtk_entry_set_text(GTK_ENTRY((GtkWidget *)data), "");
}

void back(GtkWidget *widget, gpointer data){
  char new[MAXDISTANCE];
  const char *val = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
  sprintf(new, "b%s", val);

  if (strlen(val) == 0)
   sprintf(new, "b1");

  send(sockfd, new, strlen(new), 0);
  gtk_entry_set_text(GTK_ENTRY((GtkWidget *)data), "");
}

void turnL(GtkWidget *widget, gpointer data){
  char new[MAXDISTANCE];
  const char *val = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
  sprintf(new, "l%s", val);

  if (strlen(val) == 0)
    sprintf(new, "l90");

  send(sockfd, new, strlen(new), 0);
  gtk_entry_set_text(GTK_ENTRY((GtkWidget *)data), "");
}

void turnR(GtkWidget *widget, gpointer data){
  char new[MAXDISTANCE];
  const char *val = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
  sprintf(new, "r%s", val);

  if (strlen(val) == 0)
    sprintf(new, "r90");

  send(sockfd, new, strlen(new), 0);
  gtk_entry_set_text(GTK_ENTRY((GtkWidget *)data), "");
}

void updateSensors(){
  gtk_label_set_text((GtkLabel *) fRange, "10");
  gtk_label_set_text((GtkLabel *) bRange, "7");
  gtk_label_set_text((GtkLabel *) lRange, "5");
  gtk_label_set_text((GtkLabel *) rRange, "3");
  gtk_label_set_text((GtkLabel *) batt, "Battery: 4.6");
  gtk_label_set_text((GtkLabel *) key, "Key: 10");
}

/*
int loadImage(unsigned char *data)
{
        printf("Got image!\n");
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(data, GDK_COLORSPACE_RGB,
                                         FALSE, 8, CAMERA_WIDTH, CAMERA_HEIGHT,
                                         CAMERA_WIDTH * 3, NULL, NULL);
        gtk_image_set_from_pixbuf((GtkImage*) image, pixbuf);
        gtk_widget_queue_draw(image);
        printf("Loaded\n");
        return 0;
}
*/

void runGUI(int argc, char *argv[]){
  GtkWidget *window, *image, *newimage;
  GdkPixbuf *pixbuf;
  GtkWidget *fwdButton, *bwdButton, *turnLButton, *turnRButton, *dist, *stopButton;
  GtkWidget *hbox1, *hbox2, *hbox3, *hbox4, *hbox5;
  GtkWidget *vbox1, *vbox2, *vbox3, *vbox4, *vbox5;

  /* Initialize the GTK+ and all of its supporting libraries. */
  gtk_init (&argc, &argv);
  /* Create a new window, give it a title and display it to the user. */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Bot Controller");
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);

  /* Connect the main window to the destroy */
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);

  fwdButton = gtk_button_new_with_label("Forward");
  bwdButton = gtk_button_new_with_label("Back");
  turnLButton = gtk_button_new_with_label("Turn left");
  turnRButton = gtk_button_new_with_label("Turn right");
  stopButton = gtk_button_new_with_label("STOP");
  dist = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY((GtkWidget *)dist),12);

  
  // range data labels:
  fRange = gtk_label_new("-");
  lRange = gtk_label_new("-");
  bRange = gtk_label_new("-");
  rRange = gtk_label_new("-");
  batt = gtk_label_new("-");
  key = gtk_label_new("-");
  

  g_signal_connect(G_OBJECT(fwdButton), "clicked", G_CALLBACK(forward), dist);
  g_signal_connect(G_OBJECT(bwdButton), "clicked", G_CALLBACK(back), dist);
  g_signal_connect(G_OBJECT(turnLButton), "clicked", G_CALLBACK(turnL), dist);
  g_signal_connect(G_OBJECT(turnRButton), "clicked", G_CALLBACK(turnR), dist);  
  g_signal_connect(G_OBJECT(stopButton), "clicked", G_CALLBACK(stop), dist);  

  hbox1 = gtk_hbox_new(FALSE, 5);
  hbox2 = gtk_hbox_new(FALSE, 5);
  hbox3 = gtk_hbox_new(FALSE, 5);
  hbox4 = gtk_hbox_new(FALSE, 5);
  hbox5 = gtk_hbox_new(FALSE, 5);

  vbox1 = gtk_vbox_new(FALSE, 5);
  vbox2 = gtk_vbox_new(FALSE, 5);
  vbox3 = gtk_vbox_new(FALSE, 5);
  vbox4 = gtk_vbox_new(FALSE, 5);
  vbox5 = gtk_vbox_new(FALSE, 10);

  gtk_box_pack_start(GTK_BOX(hbox2), batt, FALSE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox2, FALSE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(hbox3), lRange, TRUE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(hbox3), turnLButton, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox3, FALSE, FALSE, 176);

  gtk_box_pack_start(GTK_BOX(vbox2), fRange, TRUE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(vbox2), fwdButton, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox2), /*hbox2*/ dist, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox2), bwdButton,TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox2), bRange, TRUE, FALSE, 20);  

  gtk_box_pack_start(GTK_BOX(hbox5), key, FALSE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(hbox4), turnRButton, TRUE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(hbox4), rRange, TRUE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(vbox3), hbox5, FALSE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(vbox3), hbox4, FALSE, FALSE, 176);

  image = gtk_image_new_from_file("bla.jpg");
  pixbuf = gtk_image_get_pixbuf((GtkImage *) image);
  newimage = gtk_image_new();
  
  gtk_box_pack_start(GTK_BOX(vbox4), newimage, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox4), stopButton, TRUE, FALSE, 5);
  
  gtk_box_pack_start(GTK_BOX(hbox1), vbox1, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox2, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox3, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox4, TRUE, TRUE, 10);
  gtk_container_add(GTK_CONTAINER(window), hbox1);

  updateSensors();

  gtk_widget_show_all(window);

  gtk_image_set_from_pixbuf((GtkImage*) newimage, pixbuf);
  gtk_widget_queue_draw(newimage);

  /* Hand control over to the main loop. */
  gtk_main ();
}

/*
int main (int argc, char *argv[]){
  runGUI(argc, argv);

  return 0;
}
*/

