/*
  	DPTECH - scratch game framework for Darkplaces Engine http://icculus.org/twilight/darkplaces
  	Written in 2014 by toneddu2000 (email: a DOT latronico AT gmail DOT com)
  	Contributors: Spike, ChristianIce
  	To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. 
  	This software is distributed without any warranty.
 	You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

//SSQC to CSQC defs
float ENT_CSPLAYER = 1;
float ENT_CSENEMY = 2;

//Entities shared (toneddu2000 test)
.entity 			entityType;
.float				stepAmplitude; //how big is the step that monster use to walk
.float				animationStatus; //byte to let csqc know if enemy is running, walking, idling, etc

//Player defs
entity				player;
.float				weaponCurrent;
.float				bCanShoot;

//Monster defs
entity 				enemyBase;
.void()				thinkAi;

// Entity Sending
.float(entity viewer) SendEntity;
.float Version;
.float SendFlags;		//vital!It tells the engine to update the entity in CSQC
float MSG_ENTITY = 5;
float CLIENT_IDs;		// Called on client connect for CSQC - USEFUL?!?
.float PersID;			// Assigned to client on client connect to later identify the client on CSQC.

// EXT_CSQC
// AddStat
void(float index, float type, ...) AddStat = #232; // third parameter is an entity field // already in dp
float AS_STRING          = 1;
float AS_FLOAT_TRUNCATED = 2;
float AS_FLOAT           = 8;

//Models defs
string MODEL_PLAYER = "models/player/player.iqm";
string MODEL_ENEMY = "models/enemies/erebus.iqm";
