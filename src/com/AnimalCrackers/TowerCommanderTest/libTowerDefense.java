package com.AnimalCrackers.TowerCommanderTest;


public class libTowerDefense 
{
	     static {        
	         System.loadLibrary("towerdefense");
	     }
	 
	    /** 
	     * @param width the current view width           
	     * @param height the current view height 
	     */
	     public static native void init(int width, int height,String filename,AndroidTextureLoader t,SoundManager s,MainActivity ma);
	     public static native boolean step(); 
	     public static native void cleanup();     
		public static native void touchBegin(int count, float x0, float y0, float x1,	float y1) ;
		public static native void touchEnd(int count, float x0, float y0, float x1,	float y1) ;
		public static native void touchMove(int count, float x0, float y0, float x1,float y1) ;
		  
		public static native void doubleTap(int count,float x0,float y0);        

		public static native void updateScene();
		public static native void animate();
		
		public static native void onBack(); 
	
}
