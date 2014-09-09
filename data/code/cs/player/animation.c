/*
  	DPTECH - scratch game framework for Darkplaces Engine http://icculus.org/twilight/darkplaces
  	Written in 2014 by toneddu2000 (email: a DOT latronico AT gmail DOT com)
  	Contributors: Spike, ChristianIce
  	To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. 
  	This software is distributed without any warranty.
 	You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

void Player_SkeletonDisplayNumBones()
{
	local float numbones,i;
	numbones = skel_get_numbones(self.skeletonindex);
	for (i = 1;i< numbones;i++){
		print(ftos(i) ," - ", skel_get_bonename(self.skeletonindex,i)," \n");
	}
}

void Player_AnimationBlendCyclesIQM()
{
	local vector vc_vel, ang, body_ang;
	local vector ang_pelvis;
	local float fl_vel, vel_F, legsang_y, weap, diff, trans;
	//bones - IMPORTANT: Spine uses Z as rotation axes, torso instead uses Y
	local float root = skel_find_bone(self.skeletonindex, "root");
	local float pelvis = skel_find_bone(self.skeletonindex, "pelvis");
	local float spine = skel_find_bone(self.skeletonindex, "spine");
	local float torso = skel_find_bone(self.skeletonindex, "torso");
	local float head = skel_find_bone(self.skeletonindex, "head");
	local float thighright = skel_find_bone(self.skeletonindex, "legthigh_r");
	local float thighleft = skel_find_bone(self.skeletonindex, "legthigh_l");
	local float handright = skel_find_bone(self.skeletonindex, "armhand_r");
	local float handleft = skel_find_bone(self.skeletonindex, "armhand_l");
	//bone rotation vectors
	local vector ang_pelvis,ang_spine,ang_torso,ang_head;
	
	vc_vel = self.velocity;
	vc_vel_z = 0;
	fl_vel = vlen(vc_vel);
	// LEGS
	if (time > self.legs_nextfr_time)
	{	
		if (fl_vel < 6){
			// STANDING STILL
			self.frame = frameforname(self.modelindex,"idle");
		}
		else{
			//WALKING/RUNNING
			if (fl_vel < 260 ){
			//WALKING
				if(input_movevalues_x > 0){
					// WALKING FORWARD
					self.frame = frameforname(self.modelindex,"walk");					
				}
				else if(input_movevalues_x < 0){
					// WALKING BACKWARD
					self.frame = frameforname(self.modelindex,"walk");					
				}
				else if(input_movevalues_y > 0){
					// WALKING RIGHT STEP
					self.frame = frameforname(self.modelindex,"walk");					
				}
				else if(input_movevalues_y < 0){
					// WALKING LEFT STEP
					self.frame = frameforname(self.modelindex,"walk");					
				}
			}
			else{
				// RUNNING
				//SPINE	
				if(input_movevalues_x > 0){
					// RUNNING FORWARD
					self.frame = frameforname(self.modelindex,"run");					
				}
				else if(input_movevalues_x < 0){
					// RUNNING BACKWARD
					self.frame = frameforname(self.modelindex,"run");					
				}
				else if(input_movevalues_y > 0){
					// RUNNING RIGHT STEP
					self.frame = frameforname(self.modelindex,"run");					
				}
				else if(input_movevalues_y < 0){
					// RUNNING LEFT STEP
					self.frame = frameforname(self.modelindex,"run");					
				}
			}
		}
		skel_build(self.skeletonindex, self, self.modelindex, 0.3, 0, pelvis); // Fix position of the pivot on the ground.
		skel_build(self.skeletonindex, self, self.modelindex, 0.4, pelvis, thighright);
	}
	// TORSO
	if (time > self.torso_nextfr_time)
	{
		//weapon holder switch
		if (self.bCanShoot == 1) {
			// FIX ME ... export weapon in use - as a byte from ssqc
			self.frame = frameforname(self.modelindex,"shoot");
		}
		skel_build(self.skeletonindex, self, self.modelindex, 0.2, pelvis, handright); 
	}
	//SPINE	
	gettaginfo(self, torso);//captures bone
	ang_spine_z = -input_angles_x * torso; // makes the spine bend
	makevectors(ang_spine); //put the angles origin at the spine
	//should prevent spine to rotate in excess but it doesn't work	
	if(ang_spine_z < 14 || ang_spine_z > -20){
		skel_mul_bone(self.skeletonindex,spine, '0.0 0.0 0.0');//rotates spine bone
	}
	//TORSO	
	gettaginfo(self, torso);//captures bone
	ang_torso_y = -input_angles_x * torso * 0.2; // makes the torso bend according to mouse input
	makevectors(ang_torso);//put the angles origin at the torso
	//should prevent torso to rotate in excess but it doesn't work	
	if(ang_torso_y < 15 || ang_torso_y > -15){
		skel_mul_bone(self.skeletonindex,torso, '0.0 0.0 0.0');//rotates torso bone
	}
	//HEAD
	gettaginfo(self, head);//captures bone
	ang_head_y = -input_angles_x * head; // makes the head bend according to mouse input
	makevectors(ang_head);
	skel_set_bone(self.skeletonindex,head, '1.1 11.8 0.0');//rotates head bone 
}
