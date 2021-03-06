#include "LOS.h"

#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////
/* Adapted from the code displayed at RogueBasin's "Bresenham's Line
 * Algorithm" article, this function checks for an unobstructed line
 * of sight between two locations using Bresenham's line algorithm to
 * draw a line from one point to the other. Returns true if there is
 * line of sight, false if there is no line of sight. */
bool los(int los_x_1, int los_y_1, int los_x_2, int
         los_y_2, WorldMap * map) {
   int delta_x, delta_y, move_x, move_y, error;
 
   /* Calculate deltas. */
   delta_x = abs (los_x_2 - los_x_1) << 1;
   delta_y = abs (los_y_2 - los_y_1) << 1;
 
   /* Calculate signs. */
   move_x = los_x_2 >= los_x_1 ? 1 : -1;
   move_y = los_y_2 >= los_y_1 ? 1 : -1;
 
   /* There is an automatic line of sight, of course, between a
    * location and the same location or directly adjacent
    * locations. */
   if (abs (los_x_2 - los_x_1) < 2 && abs (los_y_2 - los_y_1) < 2) {
      /* Return. */
      return true;
   }
 
   /* "Draw" the line, checking for obstructions. */
   if (delta_x >= delta_y) {
      /* Calculate the error factor, which may go below zero. */
      error = delta_y - (delta_x >> 1);
 
      /* Search the line. */
      while (los_x_1 != los_x_2) {
         /* Check for an obstruction. If the obstruction can be "moved
          * around", it isn't really an obstruction. */
	 MapTile * t = map->GetMapTile(los_x_1, los_y_1);
         if (t != nullptr) {
	   if(t->symbol == '#')
            /* Return. */
            return false;
         }
         else {
	    //We have a map leak!
	   return false;
	 }
 
         /* Update values. */
         if (error > 0) {
            if (error || (move_x > 0)) {
               los_y_1 += move_y;
               error -= delta_x;
            }
         }
         los_x_1 += move_x;
         error += delta_y;
      }
   }
   else {
      /* Calculate the error factor, which may go below zero. */
      error = delta_x - (delta_y >> 1);
 
      /* Search the line. */
      while (los_y_1 != los_y_2) {
         /* Check for an obstruction. If the obstruction can be "moved
          * around", it isn't really an obstruction. */
         MapTile * t = map->GetMapTile(los_x_1, los_y_1);
         if (t != nullptr) {
	   if(t->symbol == '#')
            /* Return. */
            return false;
         }
         else {
	    //We have a map leak!
	   return false;
	 }
 
         /* Update values. */
         if (error > 0) {
            if (error || (move_y > 0)) {
               los_x_1 += move_x;
               error -= delta_y;
            }
         }
         los_y_1 += move_y;
         error += delta_x;
      }
   }
 
   /* Return. */
   return true;
}