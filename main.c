
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "item.h"

#define MAX_SCALE 12.0f            // resolution scale for the canvase
#define DISPLACEMENT_SCALE 100.0f // between tree levels
#define GEO_NODE_SPACE_RATIO 0.5f	  // the geometric decrement between levels
#define TEXT_SIZE 70
#define	NODE_RADIUS 50

typedef struct _rgb
{
    float r;
    float g;
    float b;
}rgb;

void write_eps_header(FILE * file_ptr, char * title, int width, int height)
{
    fprintf(file_ptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(file_ptr, "%%%%Title:%s\n", title);
    fprintf(file_ptr, "%%%%BoundingBox: 0 0 %d %d \n", width, height);
    fprintf(file_ptr, "%%%%EndComments\n");


    // write down all procedures
    fprintf(file_ptr, "/arrowhead {%% stack: s x1 y1, current point: x0 y0\n");
    fprintf(file_ptr, "gsave\n");
    fprintf(file_ptr, "currentpoint   %% s x1 y1 x0 y0 \n");
    fprintf(file_ptr, "4 2 roll exch  %% s x0 y0 y1 x1 \n");
    fprintf(file_ptr, "4 -1 roll exch %% s y0 y1 x0 x1 \n");
    fprintf(file_ptr, "sub 3 1 roll   %% s x1-x2 y0 y1 \n");
    fprintf(file_ptr, "sub exch       %% s y0-y1 x1-x2 \n");
    fprintf(file_ptr, "atan rotate    %% rotate over arctan((y0-y1)/(x1-x2)) \n");
    fprintf(file_ptr, "dup scale      %% scale by factor s \n");
    fprintf(file_ptr, "-7 2 rlineto 1 -2 rlineto -1 -2 rlineto \n");
    fprintf(file_ptr, "closepath fill  %% fill arrowhead \n");
    fprintf(file_ptr, "grestore \n");
    fprintf(file_ptr, "newpath \n");
    fprintf(file_ptr, "} def \n");



}


void draw_line(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, float width)
{
    fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d moveto %d %d lineto %f setlinewidth stroke\n", color.r, color.g, color.b, x1, y1, x2, y2, width );
}

void draw_square(FILE * file_ptr, rgb color,  int x1, int y1, int x2, int y2, float width)
{
    fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d moveto %d %d rlineto %d %d rlineto %d %d rlineto %d %d rlineto  closepath  %f setlinewidth stroke \n",
            color.r, color.g, color.b, x1, y1, 0, y2, y2, 0, 0, -y2, -y2, 0, width );

}

void draw_arc(FILE * file_ptr, rgb color,  int x, int y, int radius, int start_angle, int end_angle, float width)
{
    fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d %d %d %d arc closepath %f setlinewidth stroke \n", color.r, color.g, color.b, x, y, radius, start_angle, end_angle, width);

}

void draw_circle(FILE * file_ptr, rgb color,  int x, int y, int radius, float width)
{
    fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d %d 0 360 arc closepath %f setlinewidth stroke \n", color.r, color.g, color.b, x, y, radius, width);

}


void draw_link(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, int width)
{
    //fprintf(file_ptr, "\");
    fprintf(file_ptr, "%d %d translate\n", x1, y1);
    fprintf(file_ptr, "%f %f %f setrgbcolor 0 0 moveto %d %d lineto stroke\n", color.r, color.g, color.b, x2, y2 );
    fprintf(file_ptr, "newpath %d %d moveto %d 0 0 arrowhead \n", x2, y2, width);
    //fprintf(file_ptr, "grestore\n");

}

void draw_text(FILE * file_ptr, rgb color, int scale, int x, int y, char * text)
{
    fprintf(file_ptr, "/Times-Roman findfont %f %f %f setrgbcolor %d scalefont setfont newpath %d %d moveto (%s) show\n",
            color.r, color.g, color.b, scale, x, y, text);

}


void draw_array(FILE * file_ptr, int * array, int start, int end, int x, int y, int scale, rgb bgcolor, rgb fgcolor)
{
    int i;
    for(i = start ; i <= end ; i++)
    {
        draw_square(file_ptr, bgcolor,  x + (i * scale * scale) , y , (scale * scale), (scale * scale), 1);
        char str[10];
        sprintf(str, "%d", array[i-1]);
        draw_text(file_ptr, fgcolor, 20, (x + (i * scale * scale) ) + scale * scale /2 - scale, y + scale * scale /2 -scale, str);
    }
}


void draw_node(FILE * file_ptr, rgb color,  int x, int y, int radius, float width, int text_size, char * text)
{
    draw_circle(file_ptr, (rgb){0,1,0}, x, y, radius, width);
    draw_text(file_ptr, (rgb){0,0,0}, text_size, x - (text_size/4), y - (text_size/4), text);
}

void draw_tree(FILE * file_ptr, TREE node, int geo_level, float geo_tree_height, int x, int y)
{
    if(node != NULL)
    {

        TREE left = get_left(node);
        TREE right = get_right(node);

        ITEM node_item = get_item(node);


        float level_scale = DISPLACEMENT_SCALE * geo_level * geo_tree_height;


        char item[2];
        sprintf(item, "%c", get_item_sat(node_item));
        draw_node(file_ptr, (rgb){0,1,0}, x, y, NODE_RADIUS, 3, TEXT_SIZE, item);

        int lx = x - level_scale;
        int ly = y - level_scale;
        int rx = x + level_scale;
        int ry = y - level_scale;

        draw_tree(file_ptr, left, geo_level, geo_tree_height - GEO_NODE_SPACE_RATIO, lx, ly);
        draw_tree(file_ptr, right, geo_level, geo_tree_height - GEO_NODE_SPACE_RATIO, rx, ry);

        if(left)
            draw_line(file_ptr, (rgb){0,0,1}, x, y - NODE_RADIUS, lx, ly + NODE_RADIUS , 10);
        if(right)
            draw_line(file_ptr, (rgb){0,0,1}, x, y - NODE_RADIUS, rx , ry +  NODE_RADIUS , 10);
    }
}

int main()
{
    char * file_path = "out.eps";
    int width = 5200;
    int height = 5200;

    float square_scale = 6.0f;

    FILE * file_ptr = fopen(file_path, "w+");
    write_eps_header(file_ptr, "lines", width, height);


    ITEM it1 = create_item(10, 'a');
    ITEM it2 = create_item(2, 'b');
    ITEM it3 = create_item(23, 'c');
    ITEM it4 = create_item(17, 'd');
    ITEM it5 = create_item(16, 'e');
    ITEM it6 = create_item(18, 'f');
    ITEM it7 = create_item(21, 'w');
    ITEM it8 = create_item(11, 'y');
    ITEM it9 = create_item(14, 'u');
    ITEM it10 = create_item(1, 'v');


    TREE root = create_node(it1); // root

    TREE left = create_node(it2);

    TREE right = create_node(it3);

    insert(root, left, right);
    insert(left, create_node(it5), create_node(it4));
    insert(right, create_node(it8), create_node(it6));
    insert(get_left(left), create_node(it10), create_node(it7));
    insert(get_left(get_left(left)), create_node(it9), NULL);
    //insert(get_right(get_left(left)), create_node(it9), NULL);

    //print_tree(root);

    draw_tree(file_ptr, root, 1, (float)get_tree_height(root), width /2, height - 100 );

    printf("Tree height = %d \n", get_tree_height(root));

    int* path = (int*) malloc(sizeof(int) * get_tree_height(root));
    printLongestPath(root,path,0,get_tree_height(root));

    return 0;

}