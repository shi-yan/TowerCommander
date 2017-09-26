package com.AnimalCrackers.TowerCommanderTest;

import com.AnimalCrackers.TowerCommanderTest.R;
import com.AnimalCrackers.TowerCommanderTest.R.id;
import com.AnimalCrackers.TowerCommanderTest.R.layout;
import com.AnimalCrackers.TowerCommanderTest.R.raw;
import com.flurry.android.FlurryAgent;
//import com.google.android.apps.analytics.GoogleAnalyticsTracker;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.app.Dialog;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

public class MainActivity extends Activity {
    /** Called when the activity is first created. */
	
	MediaPlayer  mMediaPlayer ;
	GLView view=null;
	private Handler mHandler;  
	private Dialog helpDialog;
	class SplashMusicOnCompletionCallback implements android.media.MediaPlayer.OnCompletionListener
	{

		@Override
		public void onCompletion(MediaPlayer mp) {
			// TODO Auto-generated method stub
			mMediaPlayer.release();
			mMediaPlayer=null;
		}
	}
	
	public void popupHelpDialog()
	{
		
		
		 mHandler.post(new Runnable(){  
             @Override  
             public void run() {  
            	    //set up dialog
                 


               //  dialog.setOnKeyListener(onKeyListener)
                 

                 helpDialog.show();
             }  
          });  
    
		
	}
	
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);  
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN); 
    

	   
        AndroidTextureLoader.am=getAssets();
        SoundManager.init(this);
        installResources(); 
         helpDialog = new Dialog(this);
    	 helpDialog.setContentView(R.layout.helpdialog);
    	 helpDialog.setTitle("Tower Commander Help");
    	 helpDialog.setCancelable(true);
    
    	 mHandler=new Handler();
        
        setContentView(view=new GLView(this,getApplication()));
   
    }
    
    @Override
    public void onStart()
    {
       super.onStart();
       FlurryAgent.onStartSession(this, "5TET2V6YESH72X55NV1W");
       mMediaPlayer = MediaPlayer.create(this, R.raw.splash);
       mMediaPlayer.setOnCompletionListener(new SplashMusicOnCompletionCallback());
   	 	mMediaPlayer.start();
    }
    
    private void installResources()
    {
    	
    	
    //	(new File("/sdcard/TowerCommander/groundTile")).mkdirs();
    	(new File("/sdcard/TowerCommander")).mkdirs();

    	
    	
    	String [] resources=
    	{
    			"exportedmap.map",
    			"exportedmap2.map",
    			"exportedmap3.map",
    			"level1.lev",
    			"level2.lev",
    			"level3.lev",
    	
    	};
    	
    	TextView loadingText=(TextView) findViewById(R.id.loading_text);
    	
    	int k=0;
    	
    	for(String s : resources)
    	{
    		
    		saveAssetFileToSdcard(s);
    		//loadingText.setText((int)((float)k++/(float)resources.length*100.0f)+"%");
    	} 
    	
    	
    	
    }
    
    private boolean saveAssetFileToSdcard(String filename)
    {
    	
    	String path="/sdcard/TowerCommander/";  
    	/*if((new File(path+filename)).exists())
    	{
    		return true;
    	}*/
    	
    	
    	byte[] buffer=null; 
    	
    	try 
    	{
     
    	InputStream fIn =getAssets().open(filename);   
    	int size=0;  
    	  
    	 
    		size = fIn.available();  
    		buffer = new byte[size];  
    		fIn.read(buffer);  
    		fIn.close(); 
    	} 
    	catch (IOException e) 
    	{  
    		// TODO Auto-generated catch block  
    		return false;  
    	}  
    	
    	FileOutputStream save;  
    	try 
    	{  
    		save = new FileOutputStream(path+filename);  
    	 	save.write(buffer);  
    	 	save.flush();  
    	 	save.close();  
    	} 
    	catch (FileNotFoundException e) 
    	{  
    		// TODO Auto-generated catch block  
    		return false;  
    	} 
    	catch (IOException e) 
    	{  
    		// TODO Auto-generated catch block  
    		return false;  
    	}  
    	return true;
    }
    
    @Override
    public void onStop()
    {
       super.onStop();
       FlurryAgent.onEndSession(this);
     //  tracker.stop();
       // your code
       
       
       android.os.Process.killProcess(android.os.Process.myPid()); 
       
    }
    
    @Override 
    protected void onPause()
    {
        super.onStop();
        FlurryAgent.onEndSession(this);
        android.os.Process.killProcess(android.os.Process.myPid()); 
    	
    } 
    
    @Override
    protected void onDestroy() 
    {
      super.onDestroy();
      
      if(mMediaPlayer!=null)
      { 
    	  mMediaPlayer.stop();
    	  mMediaPlayer.release();
      
    	  mMediaPlayer=null;
      }// Stop the tracker when it is no longer needed.
      
      SoundManager.release();
    }
    
    @Override
    public boolean onKeyUp (int keyCode, KeyEvent event)
    {
    	
    	if(event.getKeyCode()==KeyEvent.KEYCODE_MENU)
    	{
    		popupHelpDialog();
    		return true;
    		
    	}
    	return super.onKeyUp(keyCode, event);
    }
    
    @Override 
    public void onBackPressed() 
    {
        final Runnable event = new Runnable() 
        {
            public void run()
            { 
            	if(NativeLock.isAvailable)
            	{
            		NativeLock.isAvailable=false;
               		libTowerDefense.onBack();
            	
            		NativeLock.isAvailable=true;
            	}
         
            }
        };
 
  
        
        view.queueEvent( event );

    }
    
}