#include "wolfenstein.h"

internal void Map_LoadLinedef( Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY, u16 color );
internal void Map_LoadLineseg( Lineseg_t* lineseg, Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY );
internal void Map_LoadBspNode( BspNode_t* node, Bool_t isLeaf, Linedef_t* linedef, Subsector_t* subsector, BspNode_t* parent, BspNode_t* leftChild, BspNode_t* rightChild );

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

   /*************************** BSP TREE ***************************/

   map->bspTree.nodeCount = 59;

   // C5 (this is the root node)
   Map_LoadBspNode( &map->bspTree.nodes[0], False, &map->sectors[5].linedefs[2], 0, 0, &map->bspTree.nodes[24], &map->bspTree.nodes[1] );

   // G1
   Map_LoadBspNode( &map->bspTree.nodes[1], False, &map->sectors[1].linedefs[6], 0, &map->bspTree.nodes[0], &map->bspTree.nodes[17], &map->bspTree.nodes[2] );

   // H1
   Map_LoadBspNode( &map->bspTree.nodes[2], False, &map->sectors[1].linedefs[7], 0, &map->bspTree.nodes[1], &map->bspTree.nodes[12], &map->bspTree.nodes[3] );

   // L0
   Map_LoadBspNode( &map->bspTree.nodes[3], False, &map->sectors[0].linedefs[11], 0, &map->bspTree.nodes[2], &map->bspTree.nodes[9], &map->bspTree.nodes[4] );

   // F1
   Map_LoadBspNode( &map->bspTree.nodes[4], False, &map->sectors[1].linedefs[5], 0, &map->bspTree.nodes[3], &map->bspTree.nodes[6], &map->bspTree.nodes[5] );

   // 1
   Map_LoadBspNode( &map->bspTree.nodes[5], True, 0, &map->subsectors[0], &map->bspTree.nodes[4], 0, 0 );

   // E1
   Map_LoadBspNode( &map->bspTree.nodes[6], False, &map->sectors[1].linedefs[4], 0, &map->bspTree.nodes[4], &map->bspTree.nodes[8], &map->bspTree.nodes[7] );

   // 2
   Map_LoadBspNode( &map->bspTree.nodes[7], True, 0, &map->subsectors[1], &map->bspTree.nodes[6], 0, 0 );

   // 3
   Map_LoadBspNode( &map->bspTree.nodes[8], True, 0, &map->subsectors[2], &map->bspTree.nodes[6], 0, 0 );

   // K0
   Map_LoadBspNode( &map->bspTree.nodes[9], False, &map->sectors[0].linedefs[10], 0, &map->bspTree.nodes[3], &map->bspTree.nodes[11], &map->bspTree.nodes[10] );

   // 4
   Map_LoadBspNode( &map->bspTree.nodes[10], True, 0, &map->subsectors[3], &map->bspTree.nodes[9], 0, 0 );

   // 5
   Map_LoadBspNode( &map->bspTree.nodes[11], True, 0, &map->subsectors[4], &map->bspTree.nodes[9], 0, 0 );

   // I1
   Map_LoadBspNode( &map->bspTree.nodes[12], False, &map->sectors[1].linedefs[8], 0, &map->bspTree.nodes[2], &map->bspTree.nodes[16], &map->bspTree.nodes[13] );

   // J0
   Map_LoadBspNode( &map->bspTree.nodes[13], False, &map->sectors[0].linedefs[9], 0, &map->bspTree.nodes[12], &map->bspTree.nodes[15], &map->bspTree.nodes[14] );

   // 6
   Map_LoadBspNode( &map->bspTree.nodes[14], True, 0, &map->subsectors[5], &map->bspTree.nodes[13], 0, 0 );

   // 7
   Map_LoadBspNode( &map->bspTree.nodes[15], True, 0, &map->subsectors[6], &map->bspTree.nodes[13], 0, 0 );

   // 8
   Map_LoadBspNode( &map->bspTree.nodes[16], True, 0, &map->subsectors[7], &map->bspTree.nodes[12], 0, 0 );

   // B1
   Map_LoadBspNode( &map->bspTree.nodes[17], False, &map->sectors[1].linedefs[1], 0, &map->bspTree.nodes[1], &map->bspTree.nodes[21], &map->bspTree.nodes[18] );

   // D1
   Map_LoadBspNode( &map->bspTree.nodes[18], False, &map->sectors[1].linedefs[3], 0, &map->bspTree.nodes[17], &map->bspTree.nodes[20], &map->bspTree.nodes[19] );

   // 9
   Map_LoadBspNode( &map->bspTree.nodes[19], True, 0, &map->subsectors[8], &map->bspTree.nodes[18], 0, 0 );

   // 10
   Map_LoadBspNode( &map->bspTree.nodes[20], True, 0, &map->subsectors[9], &map->bspTree.nodes[18], 0, 0 );

   // A1
   Map_LoadBspNode( &map->bspTree.nodes[21], False, &map->sectors[1].linedefs[0], 0, &map->bspTree.nodes[17], &map->bspTree.nodes[23], &map->bspTree.nodes[22] );

   // 11
   Map_LoadBspNode( &map->bspTree.nodes[22], True, 0, &map->subsectors[10], &map->bspTree.nodes[21], 0, 0 );

   // 12
   Map_LoadBspNode( &map->bspTree.nodes[23], True, 0, &map->subsectors[11], &map->bspTree.nodes[21], 0, 0 );

   // C4
   Map_LoadBspNode( &map->bspTree.nodes[24], False, &map->sectors[4].linedefs[2], 0, &map->bspTree.nodes[0], &map->bspTree.nodes[40], &map->bspTree.nodes[25] );

   // G5
   Map_LoadBspNode( &map->bspTree.nodes[25], False, &map->sectors[5].linedefs[6], 0, &map->bspTree.nodes[24], &map->bspTree.nodes[29], &map->bspTree.nodes[26] );

   // D0
   Map_LoadBspNode( &map->bspTree.nodes[26], False, &map->sectors[0].linedefs[3], 0, &map->bspTree.nodes[25], &map->bspTree.nodes[28], &map->bspTree.nodes[27] );

   // 13
   Map_LoadBspNode( &map->bspTree.nodes[27], True, 0, &map->subsectors[12], &map->bspTree.nodes[26], 0, 0 );

   // 14
   Map_LoadBspNode( &map->bspTree.nodes[28], True, 0, &map->subsectors[13], &map->bspTree.nodes[26], 0, 0 );

   // H5
   Map_LoadBspNode( &map->bspTree.nodes[29], False, &map->sectors[5].linedefs[7], 0, &map->bspTree.nodes[25], &map->bspTree.nodes[31], &map->bspTree.nodes[30] );

   // 15
   Map_LoadBspNode( &map->bspTree.nodes[30], True, 0, &map->subsectors[14], &map->bspTree.nodes[29], 0, 0 );

   // A5
   Map_LoadBspNode( &map->bspTree.nodes[31], False, &map->sectors[5].linedefs[0], 0, &map->bspTree.nodes[29], &map->bspTree.nodes[33], &map->bspTree.nodes[32] );

   // 16
   Map_LoadBspNode( &map->bspTree.nodes[32], True, 0, &map->subsectors[15], &map->bspTree.nodes[31], 0, 0 );

   // B5
   Map_LoadBspNode( &map->bspTree.nodes[33], False, &map->sectors[5].linedefs[1], 0, &map->bspTree.nodes[31], &map->bspTree.nodes[35], &map->bspTree.nodes[34] );

   // 17
   Map_LoadBspNode( &map->bspTree.nodes[34], True, 0, &map->subsectors[16], &map->bspTree.nodes[33], 0, 0 );

   // D5
   Map_LoadBspNode( &map->bspTree.nodes[35], False, &map->sectors[5].linedefs[3], 0, &map->bspTree.nodes[33], &map->bspTree.nodes[37], &map->bspTree.nodes[36] );

   // 18
   Map_LoadBspNode( &map->bspTree.nodes[36], True, 0, &map->subsectors[17], &map->bspTree.nodes[35], 0, 0 );

   // E5
   Map_LoadBspNode( &map->bspTree.nodes[37], False, &map->sectors[5].linedefs[4], 0, &map->bspTree.nodes[35], &map->bspTree.nodes[39], &map->bspTree.nodes[38] );

   // 19
   Map_LoadBspNode( &map->bspTree.nodes[38], True, 0, &map->subsectors[18], &map->bspTree.nodes[37], 0, 0 );

   // 20
   Map_LoadBspNode( &map->bspTree.nodes[39], True, 0, &map->subsectors[19], &map->bspTree.nodes[37], 0, 0 );

   // D2
   Map_LoadBspNode( &map->bspTree.nodes[40], False, &map->sectors[2].linedefs[3], 0, &map->bspTree.nodes[24], &map->bspTree.nodes[50], &map->bspTree.nodes[41] );

   // C3
   Map_LoadBspNode( &map->bspTree.nodes[41], False, &map->sectors[3].linedefs[2], 0, &map->bspTree.nodes[40], &map->bspTree.nodes[45], &map->bspTree.nodes[42] );

   // C0
   Map_LoadBspNode( &map->bspTree.nodes[42], False, &map->sectors[0].linedefs[2], 0, &map->bspTree.nodes[41], &map->bspTree.nodes[44], &map->bspTree.nodes[43] );

   // 21
   Map_LoadBspNode( &map->bspTree.nodes[43], True, 0, &map->subsectors[20], &map->bspTree.nodes[42], 0, 0 );

   // 22
   Map_LoadBspNode( &map->bspTree.nodes[44], True, 0, &map->subsectors[21], &map->bspTree.nodes[42], 0, 0 );

   // B3
   Map_LoadBspNode( &map->bspTree.nodes[45], False, &map->sectors[3].linedefs[1], 0, &map->bspTree.nodes[41], &map->bspTree.nodes[47], &map->bspTree.nodes[46] );

   // 23
   Map_LoadBspNode( &map->bspTree.nodes[46], True, 0, &map->subsectors[22], &map->bspTree.nodes[45], 0, 0 );

   // A3
   Map_LoadBspNode( &map->bspTree.nodes[47], False, &map->sectors[3].linedefs[0], 0, &map->bspTree.nodes[45], &map->bspTree.nodes[49], &map->bspTree.nodes[48] );

   // 24
   Map_LoadBspNode( &map->bspTree.nodes[48], True, 0, &map->subsectors[23], &map->bspTree.nodes[47], 0, 0 );

   // 25
   Map_LoadBspNode( &map->bspTree.nodes[49], True, 0, &map->subsectors[24], &map->bspTree.nodes[47], 0, 0 );

   // C2
   Map_LoadBspNode( &map->bspTree.nodes[50], False, &map->sectors[2].linedefs[2], 0, &map->bspTree.nodes[40], &map->bspTree.nodes[56], &map->bspTree.nodes[51] );

   // E4
   Map_LoadBspNode( &map->bspTree.nodes[51], False, &map->sectors[4].linedefs[4], 0, &map->bspTree.nodes[50], &map->bspTree.nodes[53], &map->bspTree.nodes[52] );

   // 26
   Map_LoadBspNode( &map->bspTree.nodes[52], True, 0, &map->subsectors[25], &map->bspTree.nodes[51], 0, 0 );

   // B4
   Map_LoadBspNode( &map->bspTree.nodes[53], False, &map->sectors[4].linedefs[1], 0, &map->bspTree.nodes[51], &map->bspTree.nodes[55], &map->bspTree.nodes[54] );

   // 27
   Map_LoadBspNode( &map->bspTree.nodes[54], True, 0, &map->subsectors[26], &map->bspTree.nodes[53], 0, 0 );

   // 28
   Map_LoadBspNode( &map->bspTree.nodes[55], True, 0, &map->subsectors[27], &map->bspTree.nodes[53], 0, 0 );

   // B2
   Map_LoadBspNode( &map->bspTree.nodes[56], False, &map->sectors[2].linedefs[1], 0, &map->bspTree.nodes[50], &map->bspTree.nodes[58], &map->bspTree.nodes[57] );

   // 29
   Map_LoadBspNode( &map->bspTree.nodes[57], True, 0, &map->subsectors[28], &map->bspTree.nodes[56], 0, 0 );

   // 30
   Map_LoadBspNode( &map->bspTree.nodes[58], True, 0, &map->subsectors[29], &map->bspTree.nodes[56], 0, 0 );
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

internal void Map_LoadBspNode( BspNode_t* node, Bool_t isLeaf, Linedef_t* linedef, Subsector_t* subsector, BspNode_t* parent, BspNode_t* leftChild, BspNode_t* rightChild )
{
   node->isLeaf = isLeaf;
   node->linedef = linedef;
   node->subsector = subsector;
   node->parent = parent;
   node->leftChild = leftChild;
   node->rightChild = rightChild;
}
