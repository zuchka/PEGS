#include <dos.h>
#include <graphics.h>
#define ROW 7
#define COLUMN 7
#define xC_yC 2


int location [ROW][COLUMN][xC_yC] =
   {   {       {0,0},	  {0,0},  {68,253},  {68,303},	{68,353},     {0,0},	 {0,0}	 },
       {       {0,0},	  {0,0}, {118,253}, {118,303}, {118,353},     {0,0},	 {0,0}	 },
       {   {168,153}, {168,203}, {168,253}, {168,303}, {168,353}, {168,403}, {168,453}	 },
       {   {218,153}, {218,203}, {218,253}, {218,303}, {218,353}, {218,403}, {218,453}	 },
       {   {268,153}, {268,203}, {268,253}, {268,303}, {268,353}, {268,403}, {268,453}	 },
       {       {0,0},	  {0,0}, {318,253}, {318,303}, {318,353},     {0,0},	 {0,0}	 },
       {       {0,0},	  {0,0}, {368,253}, {368,303}, {368,353},     {0,0},	 {0,0}	 }   };

int outline[ ] = {220,35, 400,35, 400,135, 500,135, 500,315, 400,315, 400,415,
		  220,415, 220,315, 120,315, 120,135, 220,135, 220,35};

int border1[ ] = {420, 55, 420,135, 400,135, 400, 35, 420, 55};
int border2[ ] = {520,155, 520,335, 500,315, 500,135, 520,155};
int border3[ ] = {520,335, 420,335, 400,315, 500,315, 520,335};
int border4[ ] = {420,335, 420,435, 400,415, 400,315, 420,335};
int border5[ ] = {420,435, 240,435, 220,415, 400,415, 420,435};
int border6[ ] = {140,335, 120,315, 220,315, 220,335, 140,335};

char pegs [ROW][COLUMN] =
   {   { 'b', 'b', 'p', 'p', 'p', 'b', 'b'},
       { 'b', 'b', 'p', 'p', 'p', 'b', 'b'},
       { 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
       { 'p', 'p', 'p', 'e', 'p', 'p', 'p'},
       { 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
       { 'b', 'b', 'p', 'p', 'p', 'b', 'b'},
       { 'b', 'b', 'p', 'p', 'p', 'b', 'b'}   };


   void  * buffer_hole;
   void * buffer_peg;


main()
{
   int driver, mode;
   int radius=16;
   int x, y;
   char key, key2;
   char b, e, p;
   float c, res_1, res_2;
   int bottom;


   unsigned size;

   registerbgidriver( EGAVGA_driver );
   registerbgifont( small_font );

   driver = DETECT;

   initgraph( &driver, &mode, "" );

   _BL = 0x36;
   _AX = 0x1201;
   geninterrupt(0x10);

   if(driver == VGA)
      res_1=480;
   else
      res_1=350;

   res_2=480;

   c=res_1/res_2;

   for(x=0; x<7; x++)
      for(y=0; y<7; y++)
	 location[x][y][0]=(location[x][y][0])*c;


   for(x=1; x<27; x+=2)
      outline[x]=(outline[x])*c;

   for(x=1; x<10; x+=2)
      border1[x]=(border1[x])*c;

   for(x=1; x<10; x+=2)
      border2[x]=(border2[x])*c;

   for(x=1; x<10; x+=2)
      border3[x]=(border3[x])*c;

   for(x=1; x<10; x+=2)
      border4[x]=(border4[x])*c;

   for(x=1; x<10; x+=2)
      border5[x]=(border5[x])*c;

   for(x=1; x<10; x+=2)
      border6[x]=(border6[x])*c;

   drawborder(13, &outline, 310, 240, c);
   drawborder(5, &border1, 410, 100, c);
   drawborder(5, &border2, 510, 200, c);
   drawborder(5, &border3, 420, 325, c);
   drawborder(5, &border4, 410, 385, c);
   drawborder(5, &border5, 310, 425, c);
   drawborder(5, &border6, 140, 325, c);


   for(x=0; x<7; x++)
      for(y=0; y<7; y++)
	 checkforpeg(x,y,radius);

   size = imagesize(234,49,280,95);
   buffer_peg = (void *)malloc (size);
   getimage(234,49,280,95,buffer_peg);
   buffer_hole = (void *)malloc (size);
   getimage(284,199,330,245,buffer_hole);

bottom=455*c;

setcolor(WHITE);
setfillstyle( SOLID_FILL, DARKGRAY);
floodfill( 0, 0, WHITE);

moveto( 0, bottom);
settextstyle( SMALL_FONT, HORIZ_DIR, 6);
outtext("      Arrow keys to select peg;  Enter to jump;  'X' to exit;");

   _BL = 0x36;
   _AX = 0x1200;
   geninterrupt(0x10);


   x=3;
   y=3;

   x_line(x,y,c);
   while( ((key=getch()) != 'X') && (key != 'x' ) )
      {
      if( key==0 )
	 {
	 key2 = getch();
	 switch (key2)
	    {
	    case 77:
	       if (y != 6 && location[x][y+1][0] != 0 )
		  {
		  drawpeg(x,y);
		  ++y;
		  x_line(x,y,c);
		  break;
		  }
	       else
		  break;
	    case 75:
	       if (y != 0 && location[x][y-1][0] != 0 )
		  {
		  drawpeg(x,y);
		  --y;
		  x_line(x,y,c);
		  break;
		  }
	       else
		  break;
	    case 72:
	       if (x != 0 && location[x-1][y][0] != 0 )
		  {
		  drawpeg(x,y);
		  --x;
		  x_line(x,y,c);
		  break;
		  }
	       else
		  break;
	    case 80:
	       if (x != 6 && location[x+1][y][0] != 0 )
		  {
		  drawpeg(x,y);
		  ++x;
		  x_line(x,y,c);
		  break;
		  }
	       else
		  break;
	    default:
	       break;
	    }
	}
     else if( key==13 )
	{
	key = getch();
	if(key == 0)
	   {
	   key2 = getch();
	   switch (key2)
	      {
	      case 77:
		 if (y <= 4 && pegs[x][y] == 'p' && pegs[x][y+1] == 'p' && pegs[x][y+2]== 'e' )
		    {
                    pegs[x][y] = 'e';
		    drawpeg(x,y);
		    pegs[x][++y] = 'e';
		    drawpeg(x,y);
		    pegs[x][++y] = 'p';
		    drawpeg(x,y);
		    x_line(x,y,c);
		    break;
		    }
		 else
		    break;
	      case 75:
		 if (y >= 2 && pegs[x][y] == 'p' && pegs[x][y-1] == 'p' && pegs[x][y-2] == 'e' )
		    {
                    pegs[x][y] = 'e';
		    drawpeg(x,y);
		    pegs[x][--y] = 'e';
		    drawpeg(x,y);
		    pegs[x][--y] = 'p';
		    drawpeg(x,y);
		    x_line(x,y,c);
		    break;
		    }
		 else
		    break;
	      case 72:
		 if (x >= 2 && pegs[x][y] == 'p' && pegs[x-1][y] == 'p' && pegs[x-2][y] == 'e' )
		    {
                    pegs[x][y] = 'e';
		    drawpeg(x,y);
		    pegs[--x][y] = 'e';
		    drawpeg(x,y);
		    pegs[--x][y] = 'p';
		    drawpeg(x,y);
		    x_line(x,y,c);
		    break;
		    }
		 else
		    break;
	      case 80:
		 if (x <= 4 && pegs[x][y] == 'p' && pegs[x+1][y] == 'p' && pegs[x+2][y] == 'e' )
		    {
                    pegs[x][y] = 'e';
		    drawpeg(x,y);
		    pegs[++x][y] = 'e';
		    drawpeg(x,y);
		    pegs[++x][y] = 'p';
		    drawpeg(x,y);
		    x_line(x,y,c);
		    break;
		    }
		 else
		    break;
	      default:
		 break;
		 }
	     }
	 }
     }

   closegraph();
}


draw_circle(x,y,radius,color)
{
   if(color != 0)
   {
   struct arccoordstype arcinfo;
   int adj, opp;

   setcolor( LIGHTCYAN );
   circle( location[x][y][1], location[x][y][0], radius );
   setfillstyle( INTERLEAVE_FILL, color );
   floodfill( location[x][y][1], location[x][y][0], LIGHTCYAN );
   setcolor( WHITE );
   circle( location[x][y][1], location[x][y][0], radius );
   arc( (location[x][y][1]+7), (location[x][y][0]+7), 227, 43, radius );
   getarccoords(&arcinfo);
   adj = 12;
   opp = 12;
   line(arcinfo.xend, (arcinfo.yend-1), (location[x][y][1] + adj+1), (location[x][y][0] - opp+1) );
   line(arcinfo.xstart, (arcinfo.ystart-1), (location[x][y][1] - adj+1), (location[x][y][0] + opp+1) );
   floodfill( (location[x][y][1]+adj+2), (location[x][y][0]+opp+2), WHITE );

   }
   else
   {
   setcolor( WHITE );
   circle( location[x][y][1]+7, location[x][y][0]+7, radius );
   setfillstyle( INTERLEAVE_FILL, color );
   floodfill( location[x][y][1], location[x][y][0], WHITE );
   }
}

x_line(x,y,c)
float c;
{
   char _peg;
   int x1,y1;
   x1=location[x][y][1];
   y1=location[x][y][0];
   _peg = pegs[x][y];
   if(_peg == 'e')
      {
      x1+=7;
      y1+=7;
      }
   else
      {
      }
   line( x1-8, y1-(8*c), x1+8, y1+(8*c) );
   line( x1+8, y1-(8*c), x1-8, y1+(8*c) );
}

checkforpeg(x,y,radius)
{
   char _peg;

   _peg = pegs[x][y];
	    switch (_peg)
	       {
	       case 'p': draw_circle(x,y,radius,LIGHTBLUE); break;
	       case 'e': draw_circle(x,y,radius,BLACK); break;
	       case 'b': break;
	       }
}


drawborder(num, area, x1, y1, c)
int *area;
float c;
{
   y1=y1*c;
   setcolor(WHITE);
   drawpoly(num, area);
   setfillstyle(SOLID_FILL, CYAN);
   floodfill(x1,y1,WHITE);
}

drawpeg(x,y,z)
void *z;
{

   char _peg;

   _peg = pegs[x][y];
	    switch (_peg)
	       {
	       case 'p': z = buffer_peg; break;
	       case 'e': z = buffer_hole; break;
	       }
   putimage((location[x][y][1]-19),(location[x][y][0]-19),z,COPY_PUT);
}
