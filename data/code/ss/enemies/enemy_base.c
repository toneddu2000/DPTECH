/*
  	DPTECH - scratch game framework for Darkplaces Engine http://icculus.org/twilight/darkplaces
  	Written in 2014 by toneddu2000 (email: a DOT latronico AT gmail DOT com)
  	Contributors: Spike, ChristianIce
  	To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. 
  	This software is distributed without any warranty.
 	You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

float Enemy_IsPlayerFacingFront()
{
	local vector	vec;
	local float		dot;
	
	makevectors (self.angles);
	vec = normalize (player.origin - self.origin);
	dot = vec * v_forward;
	
	if ( dot > 0.3)
	{
		return TRUE;
	}
	return FALSE;
}

void Enemy_CheckStepAmplitude()
{ 
	local vector distplayer,distenemy;
	local float fightdist;

	//distance check
	distplayer = player.origin;
	distenemy = self.origin;
	fightdist = vlen (distplayer - distenemy);
	//different animation status based on distance
	if (fightdist <= 80){
		enemyBase.stepAmplitude = 0;
		enemyBase.animationStatus = 0; //idling
	}
	else if (fightdist > 80 && fightdist < 200){ 
		enemyBase.stepAmplitude = 4;
		enemyBase.animationStatus = 1; //walking
	}
	else { 
		enemyBase.stepAmplitude = 8;
		enemyBase.animationStatus = 2; //running
	}
}

void Enemy_MovingTowardPlayer()
{ 
	local float isfront;

	isfront = Enemy_IsPlayerFacingFront();
	if(self.health > 1){
		self.goalentity = player;
		self.nextthink = time + 0.04;
		movetogoal(enemyBase.stepAmplitude);
		/*
		if(isfront){
			//here aim logic
		}
		*/
		
	}
}

// all these sent values MUST have corresponding read values in CSQC (CSQC_Ent_Update() in main.c )
float Enemy_SendEntityToCSQC()
{
	WriteByte(MSG_ENTITY, ENT_CSENEMY);
	WriteByte(MSG_ENTITY, enemyBase.frame);	//FIXME NEED COMPRESSION
	WriteByte(MSG_ENTITY, enemyBase.movetype);
	WriteByte(MSG_ENTITY, enemyBase.solid);
	WriteString(MSG_ENTITY,enemyBase.model);
	WriteByte(MSG_ENTITY, enemyBase.modelindex);
	WriteByte(MSG_ENTITY, enemyBase.skeletonindex);
	WriteByte(MSG_ENTITY, enemyBase.PersID);
	WriteShort(MSG_ENTITY, enemyBase.angles_x);
	WriteShort(MSG_ENTITY, enemyBase.angles_y);
	WriteShort(MSG_ENTITY, enemyBase.angles_z);
	WriteCoord(MSG_ENTITY, enemyBase.origin_x);
	WriteCoord(MSG_ENTITY, enemyBase.origin_y);
	WriteCoord(MSG_ENTITY, enemyBase.origin_z);
	WriteShort(MSG_ENTITY, enemyBase.velocity_x);
	WriteShort(MSG_ENTITY, enemyBase.velocity_y);
	WriteShort(MSG_ENTITY, enemyBase.velocity_z);
	WriteByte(MSG_ENTITY, enemyBase.animationStatus);
	WriteByte(MSG_ENTITY, enemyBase.stepAmplitude);
	return TRUE;
}

void Enemy_SearchingPlayer()
{
	
	Enemy_CheckStepAmplitude();
	//csqc send
	self.SendFlags |= 1;	//vital!It updates the entity in csqc and tells the engine to refresh it!
	//moving toward player
	Enemy_MovingTowardPlayer();
}

void Enemy_Think()
{ 
	self.think = Enemy_SearchingPlayer;
	self.nextthink = time + 0.04;
}

/* Put an entity in Radiant named enemy_base */
void enemy_base()
{
	local entity tempent;
	tempent = spawn(); 
	enemyBase = self; //vital! Otherwise the model is not loaded.And order matters!
	enemyBase.movetype = MOVETYPE_STEP;
	enemyBase.solid = SOLID_SLIDEBOX;
	enemyBase.angles = tempent.angles; //vital otherwise enemy doesn't search player all the time!
	precache_model(MODEL_ENEMY);
	setmodel (enemyBase, MODEL_ENEMY);
	enemyBase.health = 200;
	enemyBase.classname = "enemy_base";
	setsize (enemyBase, VEC_HULL_MIN, VEC_HULL_MAX);
	Enemy_Think();
	enemyBase.flags = FL_MONSTER;
	enemyBase.fixangle = TRUE;		// turn this way immediately
	enemyBase.SendEntity = Enemy_SendEntityToCSQC; //vital!
}
