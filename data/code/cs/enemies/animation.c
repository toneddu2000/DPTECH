/*
  	DPTECH - scratch game framework for Darkplaces Engine http://icculus.org/twilight/darkplaces
  	Written in 2014 by toneddu2000 (email: a DOT latronico AT gmail DOT com)
  	Contributors: Spike, ChristianIce
  	To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. 
  	This software is distributed without any warranty.
 	You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

void AnimationPlayLoop()
{ 
	local float duration, duration2,range,range2,timer;
	duration = frameduration(self.modelindex, self.frame );
	duration2 = frameduration(self.modelindex, self.frame2 );
	range = self.frame1time / duration;
	range2 = self.frame2time / duration2;
	timer = duration;
	timer = timer - time;
	
	self.frame1time = (range-floor(range))*duration;
	self.frame1time = time-self.frame1time;
	self.frame2time = (range2-floor(range2))*duration2;
	self.frame2time = time-self.frame2time;
}

void AnimationPlayByName(string animName)
{
	self.frame1time = time; //vital!Otherwise animation is jerky 
	self.frame =  frameforname(self.modelindex,animName);
}

void AnimationPlayOnce()
{ 
  local float duration, range,timer;
  duration = frameduration(self.modelindex, self.frame );
  range = self.frame1time / duration;
  timer = duration;
  timer = timer - time;

  self.frame1time = time - ((range-floor(range)) * (duration + frametime) );//sembra un loop ancora migliore!
}

void AnimationPlayOnce2()
{ 
  local float duration, range;
  duration = frameduration(self.modelindex, self.frame );
  range = self.frame1time / duration;

  self.frame1time = time - ((range-floor(range)) * (duration + frametime) );
}

void AnimationSlipToIdle()
{
	self.frame1time = time; //vital!Otherwise animation is jerky
	self.frame =  frameforname(self.modelindex,"idle");
	AnimationPlayLoop();
}
