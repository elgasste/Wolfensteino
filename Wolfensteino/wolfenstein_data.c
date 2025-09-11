#include "wolfenstein.h"

internal void Map_LoadLinedef( Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY, u16 color );
internal void Map_LoadLineseg( Lineseg_t* lineseg, Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY );

void Map_Load( Map_t* map )
{
   map->sectorCount = 6;

   /*************************** SECTORS ***************************/

   // outer sector (blue)
   map->sectors[0].linedefCount = 15;
   Map_LoadLinedef( &map->sectors[0].linedefs[0], 40, 0, 300, 0, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[1], 300, 0, 300, 140.0f + ( 20.0f / 3.0f ), COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[2], 300, 140.0f + ( 20.0f / 3.0f ), 260, 130.0f + ( 10.0f / 3.0f ), COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[3], 260, 130.0f + ( 10.0f / 3.0f ), 260, 180, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[4], 260, 180, 300, 200, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[5], 300, 200, 300, 250, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[6], 300, 250, 260, 290, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[7], 260, 290, 90, 290, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[8], 90, 290, 90, 230, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[9], 90, 230, 70, 210, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[10], 70, 210, 60, 210, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[11], 60, 210, 60, 290, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[12], 60, 290, 0, 290, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[13], 0, 290, 0, 40, COLOR_BLUE );
   Map_LoadLinedef( &map->sectors[0].linedefs[14], 0, 40, 40, 0, COLOR_BLUE );

   // inner sector 1 (red)
   map->sectors[1].linedefCount = 12;
   Map_LoadLinedef( &map->sectors[1].linedefs[0], 110, 60, 100, 60, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[1], 100, 60, 100, 80, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[2], 100, 80, 50, 80, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[3], 50, 80, 20, 110, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[4], 20, 110, 30, 120, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[5], 30, 120, 60, 90, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[6], 60, 90, 85, 90, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[7], 85, 90, 85, 130, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[8], 85, 130, 95, 130, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[9], 95, 130, 95, 90, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[10], 95, 90, 110, 90, COLOR_RED );
   Map_LoadLinedef( &map->sectors[1].linedefs[11], 110, 90, 110, 60, COLOR_RED );

   // inner sector 2 (green)
   map->sectors[2].linedefCount = 4;
   Map_LoadLinedef( &map->sectors[2].linedefs[0], 230, 60, 170, 60, COLOR_GREEN );
   Map_LoadLinedef( &map->sectors[2].linedefs[1], 170, 60, 170, 70, COLOR_GREEN );
   Map_LoadLinedef( &map->sectors[2].linedefs[2], 170, 70, 230, 70, COLOR_GREEN );
   Map_LoadLinedef( &map->sectors[2].linedefs[3], 230, 70, 230, 60, COLOR_GREEN );

   // inner sector 3 (magenta)
   map->sectors[3].linedefCount = 4;
   Map_LoadLinedef( &map->sectors[3].linedefs[0], 260, 20, 250, 30, COLOR_MAGENTA );
   Map_LoadLinedef( &map->sectors[3].linedefs[1], 250, 30, 260, 40, COLOR_MAGENTA );
   Map_LoadLinedef( &map->sectors[3].linedefs[2], 260, 40, 270, 30, COLOR_MAGENTA );
   Map_LoadLinedef( &map->sectors[3].linedefs[3], 270, 30, 260, 20, COLOR_MAGENTA );

   // inner sector 4 (yellow)
   map->sectors[4].linedefCount = 5;
   Map_LoadLinedef( &map->sectors[4].linedefs[0], 220, 120, 190, 130, COLOR_YELLOW );
   Map_LoadLinedef( &map->sectors[4].linedefs[1], 190, 130, 190, 140, COLOR_YELLOW );
   Map_LoadLinedef( &map->sectors[4].linedefs[2], 190, 140, 250, 160, COLOR_YELLOW );
   Map_LoadLinedef( &map->sectors[4].linedefs[3], 250, 160, 250, 130, COLOR_YELLOW );
   Map_LoadLinedef( &map->sectors[4].linedefs[4], 250, 130, 220, 120, COLOR_YELLOW );

   // inner sector 5 (cyan)
   map->sectors[5].linedefCount = 8;
   Map_LoadLinedef( &map->sectors[5].linedefs[0], 175, 185, 165, 185, COLOR_CYAN );
   Map_LoadLinedef( &map->sectors[5].linedefs[1], 165, 185, 155, 195, COLOR_CYAN );
   Map_LoadLinedef( &map->sectors[5].linedefs[2], 155, 195, 155, 205, COLOR_CYAN );
   Map_LoadLinedef( &map->sectors[5].linedefs[3], 155, 205, 165, 215, COLOR_CYAN );
   Map_LoadLinedef( &map->sectors[5].linedefs[4], 165, 215, 175, 215, COLOR_CYAN );
   Map_LoadLinedef( &map->sectors[5].linedefs[5], 175, 215, 185, 205, COLOR_CYAN );
   Map_LoadLinedef( &map->sectors[5].linedefs[6], 185, 205, 185, 195, COLOR_CYAN );
   Map_LoadLinedef( &map->sectors[5].linedefs[7], 185, 195, 175, 185, COLOR_CYAN );

   /*************************** SUBSECTORS ***************************/
   
   map->subsectorCount = 30;

   map->subsectors[0].linesegCount = 4;
   Map_LoadLineseg( &map->subsectors[0].linesegs[0], &map->sectors[1].linedefs[5], 30, 120, 60, 90 );
   Map_LoadLineseg( &map->subsectors[0].linesegs[1], &map->sectors[0].linedefs[11], 60, 210, 60, 290 );
   Map_LoadLineseg( &map->subsectors[0].linesegs[2], &map->sectors[0].linedefs[12], 60, 290, 0, 290 );
   Map_LoadLineseg( &map->subsectors[0].linesegs[3], &map->sectors[0].linedefs[13], 0, 290, 0, 150 );

   map->subsectors[1].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[1].linesegs[0], &map->sectors[1].linedefs[4], 20, 110, 30, 120 );
   Map_LoadLineseg( &map->subsectors[1].linesegs[1], &map->sectors[0].linedefs[13], 0, 150, 0, 90 );

   map->subsectors[2].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[2].linesegs[0], &map->sectors[1].linedefs[3], 40, 90, 20, 110 );

   map->subsectors[3].linesegCount = 3;
   Map_LoadLineseg( &map->subsectors[3].linesegs[0], &map->sectors[1].linedefs[6], 60, 90, 85, 90 );
   Map_LoadLineseg( &map->subsectors[3].linesegs[1], &map->sectors[1].linedefs[7], 85, 90, 85, 130 );
   Map_LoadLineseg( &map->subsectors[3].linesegs[2], &map->sectors[0].linedefs[10], 70, 210, 60, 210 );

   map->subsectors[4].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[4].linesegs[0], &map->sectors[0].linedefs[9], 85, 225, 70, 210 );

   map->subsectors[5].linesegCount = 4;
   Map_LoadLineseg( &map->subsectors[5].linesegs[0], &map->sectors[1].linedefs[8], 85, 130, 95, 130 );
   Map_LoadLineseg( &map->subsectors[5].linesegs[1], &map->sectors[5].linedefs[2], 155, 195, 155, 205 );
   Map_LoadLineseg( &map->subsectors[5].linesegs[2], &map->sectors[0].linedefs[7], 155, 290, 150, 290 );
   Map_LoadLineseg( &map->subsectors[5].linesegs[3], &map->sectors[0].linedefs[9], 90, 230, 85, 225 );

   map->subsectors[6].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[6].linesegs[0], &map->sectors[0].linedefs[7], 150, 290, 90, 290 );
   Map_LoadLineseg( &map->subsectors[6].linesegs[1], &map->sectors[0].linedefs[8], 90, 290, 90, 230 );

   map->subsectors[7].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[7].linesegs[0], &map->sectors[1].linedefs[9], 95, 130, 95, 90 );
   Map_LoadLineseg( &map->subsectors[7].linesegs[1], &map->sectors[1].linedefs[10], 95, 90, 110, 90 );

   map->subsectors[8].linesegCount = 4;
   Map_LoadLineseg( &map->subsectors[8].linesegs[0], &map->sectors[0].linedefs[13], 0, 90, 0, 40 );
   Map_LoadLineseg( &map->subsectors[8].linesegs[1], &map->sectors[0].linedefs[14], 0, 40, 40, 0 );
   Map_LoadLineseg( &map->subsectors[8].linesegs[2], &map->sectors[0].linedefs[0], 40, 0, 100, 0 );
   Map_LoadLineseg( &map->subsectors[8].linesegs[3], &map->sectors[1].linedefs[3], 50, 80, 40, 90 );

   map->subsectors[9].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[9].linesegs[0], &map->sectors[1].linedefs[1], 100, 60, 100, 80 );
   Map_LoadLineseg( &map->subsectors[9].linesegs[1], &map->sectors[1].linedefs[2], 100, 80, 50, 80 );

   map->subsectors[10].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[10].linesegs[0], &map->sectors[0].linedefs[0], 100, 0, 155, 0 );
   Map_LoadLineseg( &map->subsectors[10].linesegs[1], &map->sectors[1].linedefs[0], 110, 60, 100, 60 );

   map->subsectors[11].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[11].linesegs[0], &map->sectors[1].linedefs[11], 110, 90, 110, 60 );

   map->subsectors[12].linesegCount = 4;
   Map_LoadLineseg( &map->subsectors[12].linesegs[0], &map->sectors[4].linedefs[2], 190, 140, 250, 160 );
   Map_LoadLineseg( &map->subsectors[12].linesegs[1], &map->sectors[0].linedefs[3], 260, 160.0f + ( 10.0f / 3.0f ), 260, 180 );
   Map_LoadLineseg( &map->subsectors[12].linesegs[2], &map->sectors[0].linedefs[7], 260, 290, 185, 290 );
   Map_LoadLineseg( &map->subsectors[12].linesegs[3], &map->sectors[5].linedefs[6], 185, 205, 185, 195 );

   map->subsectors[13].linesegCount = 3;
   Map_LoadLineseg( &map->subsectors[13].linesegs[0], &map->sectors[0].linedefs[4], 260, 180, 300, 200 );
   Map_LoadLineseg( &map->subsectors[13].linesegs[1], &map->sectors[0].linedefs[5], 300, 200, 300, 250 );
   Map_LoadLineseg( &map->subsectors[13].linesegs[2], &map->sectors[0].linedefs[6], 300, 250, 260, 290 );

   map->subsectors[14].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[14].linesegs[0], &map->sectors[5].linedefs[7], 185, 195, 175, 185 );

   map->subsectors[15].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[15].linesegs[0], &map->sectors[5].linedefs[0], 175, 185, 165, 185 );

   map->subsectors[16].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[16].linesegs[0], &map->sectors[5].linedefs[1], 165, 185, 155, 195 );

   map->subsectors[17].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[17].linesegs[0], &map->sectors[5].linedefs[3], 155, 205, 165, 215 );
   Map_LoadLineseg( &map->subsectors[17].linesegs[1], &map->sectors[0].linedefs[7], 185, 290, 155, 290 );

   map->subsectors[18].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[18].linesegs[0], &map->sectors[5].linedefs[4], 165, 215, 175, 215 );

   map->subsectors[19].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[19].linesegs[0], &map->sectors[5].linedefs[5], 175, 215, 185, 205 );

   map->subsectors[20].linesegCount = 4;
   Map_LoadLineseg( &map->subsectors[20].linesegs[0], &map->sectors[0].linedefs[1], 300, 0, 300, 140.0f + ( 20.0f / 3.0f ) );
   Map_LoadLineseg( &map->subsectors[20].linesegs[1], &map->sectors[0].linedefs[2], 300, 140.0f + ( 20.0f / 3.0f ), 260, 130.0f + ( 10.0f / 3.0f ) );
   Map_LoadLineseg( &map->subsectors[20].linesegs[2], &map->sectors[4].linedefs[4], 250, 130, 230, 120.0f + ( 10.0f / 3.0f ) );
   Map_LoadLineseg( &map->subsectors[20].linesegs[3], &map->sectors[3].linedefs[2], 260, 40, 270, 30 );

   map->subsectors[21].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[21].linesegs[0], &map->sectors[0].linedefs[3], 260, 130.0f + ( 10.0f / 3.0f ), 260, 160.0f + ( 10.0f / 3.0f ) );
   Map_LoadLineseg( &map->subsectors[21].linesegs[1], &map->sectors[4].linedefs[3], 250, 160, 250, 130 );

   map->subsectors[22].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[22].linesegs[0], &map->sectors[3].linedefs[1], 250, 30, 260, 40 );
   Map_LoadLineseg( &map->subsectors[22].linesegs[1], &map->sectors[2].linedefs[3], 230, 70, 230, 60 );

   map->subsectors[23].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[23].linesegs[0], &map->sectors[0].linedefs[0], 230, 0, 280, 0 );
   Map_LoadLineseg( &map->subsectors[23].linesegs[1], &map->sectors[3].linedefs[0], 260, 20, 250, 30 );

   map->subsectors[24].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[24].linesegs[0], &map->sectors[0].linedefs[0], 280, 0, 300, 0 );
   Map_LoadLineseg( &map->subsectors[24].linesegs[1], &map->sectors[3].linedefs[3], 270, 30, 260, 20 );

   map->subsectors[25].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[25].linesegs[0], &map->sectors[2].linedefs[2], 170, 70, 230, 70 );
   Map_LoadLineseg( &map->subsectors[25].linesegs[1], &map->sectors[4].linedefs[4], 230, 120.0f + ( 10.0f / 3.0f ), 220, 120 );

   map->subsectors[26].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[26].linesegs[0], &map->sectors[4].linedefs[1], 190, 130, 190, 140 );

   map->subsectors[27].linesegCount = 1;
   Map_LoadLineseg( &map->subsectors[27].linesegs[0], &map->sectors[4].linedefs[0], 220, 120, 190, 130 );

   map->subsectors[28].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[28].linesegs[0], &map->sectors[0].linedefs[0], 155, 0, 170, 0 );
   Map_LoadLineseg( &map->subsectors[28].linesegs[1], &map->sectors[2].linedefs[1], 170, 60, 170, 70 );

   map->subsectors[29].linesegCount = 2;
   Map_LoadLineseg( &map->subsectors[29].linesegs[0], &map->sectors[0].linedefs[0], 170, 0, 230, 0 );
   Map_LoadLineseg( &map->subsectors[29].linesegs[1], &map->sectors[2].linedefs[0], 230, 60, 170, 60 );
}

internal void Map_LoadLinedef( Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY, u16 color )
{
   linedef->start.x = startX;
   linedef->start.y = startY;
   linedef->end.x = endX;
   linedef->end.y = endY;
   linedef->color = color;
}

internal void Map_LoadLineseg( Lineseg_t* lineseg, Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY )
{
   lineseg->linedef = linedef;
   lineseg->start.x = startX;
   lineseg->start.y = startY;
   lineseg->end.x = endX;
   lineseg->end.y = endY;
}
