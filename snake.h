#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include "sys/malloc.h"
#define R 4
#define B 400

//链表用于存储蛇的每个元素
typedef struct eBlock
{
    struct Eblock *pre;
    double x;
    double y;
    int type;//显示种类闪烁 黑点 空白
    struct Eblock *next;
} eB, *peB;

struct eDir
{
    int x;//x方向
    int y; //y方向
};

int dot_num, width, height, hw, tmp;
peB eb0 ,eb_p,eb_n,eb_tmp;

GtkWidget *window;
GtkWidget *frame;
GtkWidget *drawing_area;

peB insert_one_eB(peB p,peB n, double x, double y, int type)
{
    peB tmp = (peB)malloc(sizeof(eB));
    tmp->x = x;
    tmp->y = y;
    tmp->type= type;
    tmp->next = n;
    tmp->pre = p;
    return tmp;
}

int init_eB(void)
{
    dot_num = (int)(B*B/(R*2*2*R));//屏幕上点数
    width = height = (int)(B/(2*R));
    hw  = (int)(width/2);
    //printf("w:%d,h:%d\n", width, height);
    peB all_dot[dot_num];
    eb0 = insert_one_eB(NULL,NULL, R, R, 0);
    eb_p = eb0;
    for(int i=0; i<6; i++)
    {
        tmp = hw - 3 +i;
        eb_tmp = insert_one_eB(eb_p,NULL,(2*tmp+1)*R, (2*hw+1)*R, 1);
        eb_p->next = eb_tmp;
        eb_p = eb_tmp;
    }
    eb_p->next = eb0;
    return 0;
}

/* Surface to store current scribbles */
static cairo_surface_t *surface = NULL;

static void
clear_surface (void)
{
    cairo_t *cr;

    cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    cairo_destroy (cr);
}

/* Create a new surface of the appropriate size to store our scribbles */
static gboolean
configure_event_cb (GtkWidget         *widget,
                    GdkEventConfigure *event,
                    gpointer           data)
{
    if (surface)
        cairo_surface_destroy (surface);

    surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
              CAIRO_CONTENT_COLOR,
              gtk_widget_get_allocated_width (widget),
              gtk_widget_get_allocated_height (widget));

    /* Initialize the surface to white */
    clear_surface ();

    /* We've handled the configure event, no need for further processing. */
    return TRUE;
}

/* Redraw the screen from the surface. Note that the ::draw
 * signal receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
 */
static gboolean
draw_cb (GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data)
{
    cairo_set_source_surface (cr, surface, 0, 0);
    cairo_paint (cr);

    return FALSE;
}



/* Draw a rectangle on the surface at the given position */
static void
draw_brush (GtkWidget *widget,
            gdouble    x,
            gdouble    y)
{
    cairo_t *cr;

    /* Paint to the surface, where we store our state */
    cr = cairo_create (surface);

    cairo_rectangle (cr, x - R, y - R, 2*R, 2*R);
    cairo_fill (cr);

    cairo_destroy (cr);

    /* Now invalidate the affected region of the drawing area. */
    gtk_widget_queue_draw_area (widget, x - R, y - R, 2*R, 2*R);
}

void reDraw(GtkWidget *drawing_area)
{
    eb_n = eb0->next;
    while(eb_n != eb0)
    {
        if(eb_n->type == 1)
        {
            draw_brush(drawing_area, eb_n->x, eb_n->y);
        }
        eb_n = eb_n->next;
    }
}


static void
close_window (void)
{
    if (surface)
        cairo_surface_destroy (surface);

    gtk_main_quit ();
}

static void drawSnake(void)
{
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{


    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Drawing Area");

    g_signal_connect (window, "destroy", G_CALLBACK (close_window), NULL);

    gtk_container_set_border_width (GTK_CONTAINER (window), 8);

    frame = gtk_frame_new (NULL);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
    gtk_container_add (GTK_CONTAINER (window), frame);

    drawing_area = gtk_drawing_area_new ();
    /* set a minimum size */
    gtk_widget_set_size_request (drawing_area, B, B);

    gtk_container_add (GTK_CONTAINER (frame), drawing_area);

    /* Signals used to handle the backing surface */
    g_signal_connect (drawing_area, "draw",
                      G_CALLBACK (draw_cb), NULL);
    g_signal_connect (drawing_area,"configure-event",
                      G_CALLBACK (configure_event_cb), NULL);


    /* Ask to receive events the drawing area doesn't normally
     * subscribe to. In particular, we need to ask for the
     * button press and motion notify events that want to handle.
     */
    gtk_widget_set_events (drawing_area, gtk_widget_get_events (drawing_area)
                           | GDK_BUTTON_PRESS_MASK
                           | GDK_POINTER_MOTION_MASK);

    gtk_widget_show_all (window);
    init_eB();
    reDraw(drawing_area);
}


