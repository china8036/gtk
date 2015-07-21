#include <gtk/gtk.h>
#include <stdio.h>
#include "snake.h"

typedef struct arg{
  int argc;
  char **argv;
} args,*pargs;

void thread(void)
{
int i;
 while(1){
	printf("one is i:%d\n", i);
	usleep(1000000);
    i++;
 }
}
void thread1(void){
int i;
while(1){
printf("two is :%d\n",i);
i++;
usleep(100000);
}
}

void drawGTK(pargs ar){
    GtkApplication *app;
    int status,yes=1;
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), ar->argc, ar->argv);
    g_object_unref (app);
}

int
main (int    argc,
      char **argv)
{   
    GtkApplication *app;
    int status,yes=1;
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), NULL, NULL);
    g_object_unref (app);

    //pthread_t id,id1;
    //int i,ret;
    //args *ar={argc, argv};
    //drawGTK(ar);
    //ret=pthread_create(&id,NULL,(void *) thread,NULL);
    //ret=pthread_create(&id1,NULL,(void *) drawGTK, ar);
    //if(ret!=0){
	//	printf ("Create pthread error!\n");
	//	exit (1);
	//}
    //pthread_join(id,NULL);
    //pthread_join(id1,NULL);


}
