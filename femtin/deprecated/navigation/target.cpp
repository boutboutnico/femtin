/*****************************************************************************
 * INCLUDE
 *****************************************************************************/
#include "target.h"
/*****************************************************************************
 * NAMESPACE
 *****************************************************************************/
using namespace motor;

/*****************************************************************************
 * GLOBALE VARIABLE
 *****************************************************************************/

/*****************************************************************************
 * PUBLIC IMPLEMENTATION
 *****************************************************************************/
Target::Target()
{
	target_distance = 0.0;
	heading_error_rad = 0.0;
}

ST_traj Target::computeToXY(ST_pos& st_pos, float x_target, float y_target)
{
	float x = x_target - st_pos.x;
	float y = y_target - st_pos.y;
	float target_bearing_rad = 0.0;

	target_distance = sqrt((x * x) + (y * y));

	/* no divide-by-zero allowed! */
	if (x > 0.00001) target_bearing_rad = HALF_PI - atan(y / x);
	else if (x < -0.00001) target_bearing_rad = -HALF_PI - atan(y / x);

	heading_error_rad = target_bearing_rad - (st_pos.theta_deg);    // * RAD_TO_DEG);

	if (heading_error_rad > PI) heading_error_rad -= TWO_PI;
	else if (heading_error_rad < -PI) heading_error_rad += TWO_PI;

	ST_traj st_traj = { target_distance, heading_error_rad };
	return st_traj;
}
/*****************************************************************************
 * PRIVATE IMPLEMENTATION
 *****************************************************************************/

/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
