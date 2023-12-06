#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include "mapper.h"

static void on_activate (GtkApplication *app) {
    // Create a new window
    GtkWidget *window = gtk_application_window_new (app);

    // Set the default size of the window to 500x300
    gtk_window_set_resizable((GtkWindow*)window, FALSE);
    gtk_window_set_default_size((GtkWindow*)(window), 800, 200);

    // Create a vertical box to organize elements
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_set_homogeneous((GtkBox*)box, FALSE);

    //create label
    GtkWidget *label = gtk_label_new("Enter enbf expression :");
    gtk_label_set_xalign((GtkLabel*)label, 0);
    gtk_widget_set_margin_start(label, 30);

    // create input box 
    GtkWidget *prompt = gtk_entry_new();
    gtk_widget_set_size_request(prompt, 300, 40);
    gtk_widget_set_margin_start(prompt, 30);
    gtk_widget_set_margin_end(prompt, 30);

    // Create a new button
    GtkWidget *button = gtk_button_new_with_label ("Submit");
    gtk_button_set_has_frame((GtkButton*)button, TRUE);
    gtk_widget_set_margin_start(button, 300);
    gtk_widget_set_margin_end(button, 300);

    // When the button is clicked, close the window passed as an argument
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_close), window);

    // Pack the text view and button into the vertical box
    gtk_box_append((GtkBox*)box, label);
    gtk_box_append((GtkBox*)box, prompt);
    gtk_box_append((GtkBox*)box, button);

    // Set the box as the child of the window
    gtk_window_set_child(GTK_WINDOW(window), box);

    gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char *argv[]) {
  // Create a new application
  GtkApplication *app = gtk_application_new ("com.example.GtkApplication",
                                             G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}
