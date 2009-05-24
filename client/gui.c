
#include "client.h"

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
  //printf("%s\n", new);

  send(sockfd, new, strlen(new), 0);

  gtk_entry_set_text(GTK_ENTRY((GtkWidget *)data), "");
}

void back(GtkWidget *widget, gpointer data){
  char new[MAXDISTANCE];
  const char *val = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
  sprintf(new, "b%s", val);
  send(sockfd, new, strlen(new), 0);
  gtk_entry_set_text(GTK_ENTRY((GtkWidget *)data), "");
}

void turnL(GtkWidget *widget, gpointer data){
  char new[MAXDISTANCE];
  const char *val = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
  sprintf(new, "l%s", val);
  send(sockfd, new, strlen(new), 0);
  gtk_entry_set_text(GTK_ENTRY((GtkWidget *)data), "");
}

void turnR(GtkWidget *widget, gpointer data){
  char new[MAXDISTANCE];
  const char *val = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
  sprintf(new, "r%s", val);
  send(sockfd, new, strlen(new), 0);
  gtk_entry_set_text(GTK_ENTRY((GtkWidget *)data), "");
}



void runGUI(int argc, char *argv[]){
  GtkWidget *window;
  GtkWidget *fwdButton, *bwdButton, *turnLButton, *turnRButton, *dist, *distLabel, *stopButton;
  GtkWidget *hbox1, *hbox2;
  GtkWidget *vbox1, *vbox2, *vbox3, *vbox4;

  /* Initialize the GTK+ and all of its supporting libraries. */
  gtk_init (&argc, &argv);
  /* Create a new window, give it a title and display it to the user. */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Bot Controller");
  gtk_window_set_default_size (GTK_WINDOW (window), 750, 500);

  /* Connect the main window to the destroy */
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);

  fwdButton = gtk_button_new_with_label("Forward");
  bwdButton = gtk_button_new_with_label("Back");
  turnLButton = gtk_button_new_with_label("Turn left");
  turnRButton = gtk_button_new_with_label("Turn right");
  stopButton = gtk_button_new_with_label("STOP");
  dist = gtk_entry_new();
  distLabel = gtk_label_new("Distance: ");

  g_signal_connect(G_OBJECT(fwdButton), "clicked", G_CALLBACK(forward), dist);
  g_signal_connect(G_OBJECT(bwdButton), "clicked", G_CALLBACK(back), dist);
  g_signal_connect(G_OBJECT(turnLButton), "clicked", G_CALLBACK(turnL), dist);
  g_signal_connect(G_OBJECT(turnRButton), "clicked", G_CALLBACK(turnR), dist);  
  g_signal_connect(G_OBJECT(turnRButton), "clicked", G_CALLBACK(stop), dist);  

  hbox1 = gtk_hbox_new(FALSE, 5);
  hbox2 = gtk_hbox_new(FALSE, 5);
  vbox1 = gtk_vbox_new(TRUE, 5);
  vbox2 = gtk_vbox_new(TRUE, 5);
  vbox3 = gtk_vbox_new(FALSE, 5);
  vbox4 = gtk_vbox_new(FALSE, 5);

  gtk_box_pack_start(GTK_BOX(vbox1), turnLButton, TRUE, FALSE, 10);

  gtk_box_pack_start(GTK_BOX(hbox2), distLabel, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox2), dist, FALSE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(vbox2), fwdButton, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox2), hbox2, FALSE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox2), bwdButton, TRUE, FALSE, 10);

  gtk_box_pack_start(GTK_BOX(vbox3), turnRButton, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox4), stopButton, TRUE, FALSE, 10);
  
  gtk_box_pack_start(GTK_BOX(hbox1), vbox1, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox2, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox3, TRUE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox4, TRUE, FALSE, 10);
  gtk_container_add(GTK_CONTAINER(window), hbox1);

  gtk_widget_show_all(window);
  /* Hand control over to the main loop. */
  gtk_main ();
  // return 0;

}

/*
int main (int argc, char *argv[]){
  runGUI(argc, argv);

  return 0;
}
*/
