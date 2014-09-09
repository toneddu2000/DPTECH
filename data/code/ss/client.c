/*
  	DPTECH - scratch game framework for Darkplaces Engine http://icculus.org/twilight/darkplaces
  	Written in 2014 by toneddu2000 (email: a DOT latronico AT gmail DOT com)
  	Contributors: Spike, ChristianIce
  	To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. 
  	This software is distributed without any warranty.
 	You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

entity Player_FindStartPoint()
{
	local entity spot;
	
	spot = find(world,classname,"info_player_start");
	if(!spot){
		error ("PutClientInServer: no starting point on level");
	}
	return spot;
}

void Player_TouchEnemy()
{
	if (other.classname =="enemy_base"){
		enemyBase.health -= 2; 
	}
}

//Built-in functions start - DO NOT REMOVE THEM!
void ClientKill()
{
	
}

void ClientConnect()
{
		
}

void ClientDisconnect()
{
	
}

void PlayerPreThink()
{
	
}

void PlayerPostThink()
{
	self.Version = self.Version + 1; //vital!!Otherwise player won't land on the ground!!
}

// all these sent values MUST have corresponding read values in CSQC (CSQC_Ent_Update() in main.c )
float Player_SendEntityToCSQC()
{
	WriteByte(MSG_ENTITY, ENT_CSPLAYER);
	WriteByte(MSG_ENTITY, player.frame);	//FIXME NEED COMPRESSION
	//WriteByte(MSG_ENTITY, player.movetype); -- not used, uncomment and delete this if needed
	//WriteByte(MSG_ENTITY, player.solid); -- not used, uncomment and delete this if needed
	//WriteString(MSG_ENTITY,player.model);	-- not used, uncomment and delete this if needed
	//WriteByte(MSG_ENTITY, player.skeletonindex); -- DON'T SEND IT - it will break code driven animation
	WriteByte(MSG_ENTITY, player.modelindex);
	WriteByte(MSG_ENTITY, player.PersID);
	WriteShort(MSG_ENTITY, player.angles_x);
	WriteShort(MSG_ENTITY, player.angles_y);
	WriteShort(MSG_ENTITY, player.angles_z);
	WriteCoord(MSG_ENTITY, player.origin_x);
	WriteCoord(MSG_ENTITY, player.origin_y);
	WriteCoord(MSG_ENTITY, player.origin_z);
	WriteShort(MSG_ENTITY, player.velocity_x);
	WriteShort(MSG_ENTITY, player.velocity_y);
	WriteShort(MSG_ENTITY, player.velocity_z);
	return TRUE;
}

void PutClientInServer()
{
	local				entity	playerspwn;
	
	playerspwn = 		Player_FindStartPoint();
	player = self;		//now use player as global player entity
	player.classname = "player";
	player.health = 100;
	player.takedamage = DAMAGE_AIM;
	player.solid = SOLID_SLIDEBOX;
	player.movetype = MOVETYPE_WALK;
	player.origin = playerspwn.origin;
	player.angles = playerspwn.angles;
	player.fixangle = TRUE;		// turn this way immediately
	precache_model(MODEL_PLAYER);
	setmodel (player, MODEL_PLAYER); 
	setsize (player, VEC_HULL_MIN, VEC_HULL_MAX);
	player.flags = FL_CLIENT;
	player.touch = Player_TouchEnemy;
	player.SendEntity = Player_SendEntityToCSQC;//VITAL!
	self.Version = self.Version + 1;//Is this needed?
}
//Built-in functions end

void info_player_start()
{
	//vital!Otherwise Player's spawn point is not found!
}
