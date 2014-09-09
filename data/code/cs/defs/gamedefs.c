/*
  	DPTECH - scratch game framework for Darkplaces Engine http://icculus.org/twilight/darkplaces
  	Written in 2014 by toneddu2000 (email: a DOT latronico AT gmail DOT com)
  	Contributors: Spike, ChristianIce
  	To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. 
  	This software is distributed without any warranty.
 	You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

.float enttype,PersID,oldbodyangle_y,bodyangle_y,animation;

vector CSQC_VIEW;
.vector wish_ang,old_wish_ang;

//COSTANTS
// input events
float INPUT_KEYDOWN   = 0;
float INPUT_KEYUP     = 1;
float INPUT_MOUSEMOVE = 2;

// CSQC builtins
void ()									R_ClearScene = #300;
void (float mask)						R_AddEntities = #301;
void (entity e)							R_AddEntity = #302;
float (float property, ...)				R_SetView = #303;
void ()									R_RenderScene = #304;
void (vector org, float radius, vector rgb)	R_AddDynamicLight = #305;
void ()									R_CalcRefDef = #306;

//for EnemyFacingPlayer
.float		ideal_yaw;
.float		idealpitch;

//for View
vector 		CSQC_VIEW;

//for Player
.float oldbodyangle_y;
.float bodyangle_y;
.float animation;
.float status; // 0 = standing, 1 = walking/running, 2 = walking/running backwards, 3 = jumping, 4 not on ground.
.float legsframe;
.float turn_angle_y;
.float sidestep_time;
.float legs_nextfr_time;
.float torso_nextfr_time;
.float totframes_up;
.float totframes_dw;
.float nexframe_up;
.float nexframe_dw;

//for Input
float KEY_BACKSPACE;
