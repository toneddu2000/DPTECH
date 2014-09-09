/*
  	DPTECH - scratch game framework for Darkplaces Engine http://icculus.org/twilight/darkplaces
  	Written in 2014 by toneddu2000 (email: a DOT latronico AT gmail DOT com)
  	Contributors: Spike, ChristianIce
  	To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. 
  	This software is distributed without any warranty.
 	You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

void Enemy_Startup(float newent)
{
	if (newent)
	{
		enemyBase.classname = "enemy_base";
		setmodelindex(self, enemyBase.modelindex);
		enemyBase.drawmask = MASK_NORMAL; // makes the entity visible
		//skeleton
		if (!self.skeletonindex){
			self.skeletonindex = skel_create(self.modelindex);
			example_skel_player_update_begin(self.modelindex,frameforname(self.modelindex,"run"),0);
		}
	}
}

void Enemy_AnimationByStatus()
{ 
	switch(self.animationStatus){ 
	case 0:
		AnimationPlayByName("shoot");
	  	AnimationPlayOnce();
	break;
	case 1:
		AnimationPlayByName("duckwalk");
		AnimationPlayLoop();
	break;
	case 2:
		AnimationPlayByName("run");
		AnimationPlayLoop();
	break;
	default:
		AnimationSlipToIdle();//exit strategy in case something went wrong with anims
	break;
  }
}

void Enemy_FacingPlayer(entity thisent)
{
	local vector distance, distancenormalized;
	distance = vectoangles (player.origin - thisent.origin); 
	makevectors (distance);
	distancenormalized = normalize (v_forward);
	thisent.angles = vectoangles(distancenormalized);  
}

void Enemy_Predraw()
{
	Enemy_AnimationByStatus();
}
