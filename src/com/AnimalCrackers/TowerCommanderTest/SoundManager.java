package com.AnimalCrackers.TowerCommanderTest;

import com.AnimalCrackers.TowerCommanderTest.R;
import com.AnimalCrackers.TowerCommanderTest.R.raw;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;


public class SoundManager 
{
	static int SoundSize=10;
	static int [] soundEffects;
	static SoundPool theSoundPool;
	
	static void init(Context context)
	{
		theSoundPool=new SoundPool(30,AudioManager.STREAM_MUSIC, 0);
		soundEffects=new int[SoundSize];
		
		soundEffects[0]=
			theSoundPool.load(context, R.raw.button, 1);
		soundEffects[1]=theSoundPool.load(context, R.raw.machinegun, 1);
		soundEffects[2]=theSoundPool.load(context, R.raw.laser,1);
	}
	
	static void play(int soundid)
	{
		switch(soundid)
		{
		case 0:
			theSoundPool.play(soundEffects[soundid], 0.5f, 0.5f, 10, 0, 1.0f);
		case 1:
			theSoundPool.play(soundEffects[soundid], 0.1f, 0.1f, 2, 0, 1.0f);
		case 2:
			theSoundPool.play(soundEffects[soundid], 0.1f, 0.1f, 2, 0, 1.0f);
		}
	}
	
	static void release()
	{
		theSoundPool.release();
		theSoundPool=null;
	}
}
