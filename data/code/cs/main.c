/*
  	DPTECH - scratch game framework for Darkplaces Engine http://icculus.org/twilight/darkplaces
  	Written in 2014 by toneddu2000 (email: a DOT latronico AT gmail DOT com)
  	Contributors: Spike, ChristianIce
  	To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. 
  	This software is distributed without any warranty.
 	You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

// BEGIN REQUIRED CSQC FUNCTIONS
void CSQC_Init()
{
}

void CSQC_Shutdown(void)
{
}

float CSQC_ConsoleCommand(string strMessage)
{
	return 0;
}

float(float eventType, float scanCode, float unicode) CSQC_InputEvent =
{
	switch(eventType)
	{
	case INPUT_KEYDOWN:
		if (scanCode == KEY_BACKSPACE){
			player.bCanShoot = 1; //junk, it's useless for now
		}
	default:
		break;
	}

	return FALSE;
};
// END REQUIRED CSQC FUNCTIONS

// BEGIN OPTIONAL CSQC FUNCTIONS
/* CSQC_Ent_Update : Called every frame that the server has indicated an update to the SSQC / CSQC entity has occured.
 The only parameter reflects if the entity is "new" to the client, meaning it just came into the client's PVS.*/
void CSQC_Ent_Update (float isnew)
{
	self.enttype = ReadByte();
	switch(self.enttype)
	{
		//receiving Player
		case 	ENT_CSPLAYER:
			player = self;
			//read here all send values from client.c in ssqc	
			player.animation = ReadByte();
			//player.movetype = ReadByte(); -- not used, uncomment and delete this if needed
			//player.solid = ReadByte(); -- not used, uncomment and delete this if needed
			//player.model = ReadString(); -- not used, uncomment and delete this if needed
			//player.skeletonindex = ReadByte(); -- DON'T USE IT - it will break code driven animation
			player.modelindex = ReadByte();
			player.PersID = ReadByte();
			player.angles_x = ReadShort();
			player.angles_y = ReadShort();
			player.angles_z = ReadShort();
			player.origin_x = ReadCoord();
			player.origin_y = ReadCoord();
			player.origin_z = ReadCoord();
			player.velocity_x = ReadShort();
			player.velocity_y = ReadShort();
			player.velocity_z = ReadShort();

			Player_Startup(isnew); //run only once - cs/player/startup.c	
		break;
		
		//recieving Enemy		
		case 	ENT_CSENEMY:
			enemyBase = self;		
			enemyBase.animation = ReadByte();
			enemyBase.movetype = ReadByte();
			enemyBase.solid = ReadByte();
			enemyBase.model = ReadString();
			enemyBase.modelindex = ReadByte();
			enemyBase.skeletonindex = ReadByte();
			enemyBase.PersID = ReadByte();
			enemyBase.angles_x = ReadShort();
			enemyBase.angles_y = ReadShort();
			enemyBase.angles_z = ReadShort();
			enemyBase.origin_x = ReadCoord();
			enemyBase.origin_y = ReadCoord();
			enemyBase.origin_z = ReadCoord();
			enemyBase.velocity_x = ReadShort();
			enemyBase.velocity_y = ReadShort();
			enemyBase.velocity_z = ReadShort();
			enemyBase.animationStatus = ReadByte();//read what animation enemy should play
			enemyBase.stepAmplitude = ReadByte();//it will be replaced with full physics (hopefully)

			Enemy_Startup(isnew); //run only once - cs/enemy/enemy_base.c
		break;
		
	}

}

// CSQC_Ent_Remove : Called when the server requests a SSQC / CSQC entity to be removed.  Essentially call remove(self) as well.
void CSQC_Ent_Remove()
{	
	//cleanup enemy skeleton
    skel_delete(self.skeletonindex); //important! Otherwise the model appears all messed-up!
	self.skeletonindex=0;
	//engine stuff
	remove(self);
}
