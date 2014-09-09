/*
  	DPTECH - scratch game framework for Darkplaces Engine http://icculus.org/twilight/darkplaces
  	Written in 2014 by toneddu2000 (email: a DOT latronico AT gmail DOT com)
  	Contributors: Spike, ChristianIce
  	To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. 
  	This software is distributed without any warranty.
 	You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

void View_ThirdPerson ()
{
	local float dist, dist2;
	local vector view, add_h;

	dist = 50;

	view = input_angles;
	view_x = view_x * (-1);

	makevectors (view);

	view = '0 0 0';
	view_z = input_angles_x * 0.1;

	traceline(player.origin + '0 0 40' + v_right*(dist/6), player.origin + '0 0 40' + view - v_forward*dist - v_up*(input_angles_x/6) + v_right*(dist/3), TRUE, self);

	dist2 = vlen(trace_endpos - (player.origin + '0 0 40' + v_right*(dist/6))) ;
	add_h_z = 35 + (dist2 * 2 * (input_angles_x * 0.01));

	traceline(player.origin + '0 0 40' + v_right*(dist/6), player.origin + add_h + view - v_forward*dist2 - v_up*(input_angles_x/6) + v_right*(dist/3), TRUE, self);

	CSQC_VIEW = trace_endpos;
	CSQC_VIEW = CSQC_VIEW + v_forward*4;
}

void View_UpdateEveryFrame()
{
	local entity ent;

	ent = nextent(world);
	while (ent)
	{
		if (ent.classname == "player")
		{
			if (player.PersID == CLIENT_IDs)	// YOURSELF
			{
				View_ThirdPerson ();
			}
			player.predraw = Player_AnimationBlendCyclesIQM;
		}
		else if (ent.classname == "enemy_base")
		{
			Enemy_FacingPlayer(ent);
			enemyBase.predraw = Enemy_Predraw;
		}
		ent = nextent(ent);
	}
}

// CSQC_UpdateView - Called every rendered frame on the client.  Useful for HUD drawing operations.
void CSQC_UpdateView(float vwidth, float vheight)
{	
	R_ClearScene();// ALWAYS Clear Current Scene First
	// Assign Standard Viewflags
	R_SetView(VF_DRAWWORLD, 1);// Draw the World (and sky) - this MUST be set to 1!
	R_SetView(VF_DRAWCROSSHAIR, 1);// Draw the Crosshair
	R_SetView(VF_DRAWENGINESBAR, 0);//Don't draw Quake status bar
	// Setup Entities to be Rendered (include all base types; normal, engine and viewmodels)
	View_UpdateEveryFrame();
	R_SetView(VF_ORIGIN, CSQC_VIEW);
	R_AddEntities(MASK_ENGINE | MASK_ENGINEVIEWMODELS | MASK_NORMAL );
	// Render the Scene
	R_RenderScene();
	GUI_HudDraw();
}
