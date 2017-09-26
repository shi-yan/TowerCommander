package com.AnimalCrackers.TowerCommanderTest;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

import com.AnimalCrackers.TowerCommanderTest.R;
import com.AnimalCrackers.TowerCommanderTest.R.layout;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.view.Window;
import android.view.WindowManager;

public class SplashScreen extends Activity
{
	

	// ===========================================================
	// Fields
	// ===========================================================
	
	private final int SPLASH_DISPLAY_LENGHT = 5000;

	// ===========================================================
	// "Constructors"
	// ===========================================================

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle icicle) 
	{
		super.onCreate(icicle);
		requestWindowFeature(Window.FEATURE_NO_TITLE);  
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN); 
        
        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
      
        

        if(dm.widthPixels<800 || dm.heightPixels<480)
        {
        	   AlertDialog alertDialog;
               alertDialog = new AlertDialog.Builder(this).create();
               alertDialog.setTitle("Low Resolution Error:");
               alertDialog.setMessage("This game is designed for large screens with at least 800x480 resolution. A low resolution version is planned for the future.");
               alertDialog.setButton2("Yes", new DialogInterface.OnClickListener()
               {
            	   @Override
            	   public void onClick(DialogInterface dialog, int which) 
            	   {               
            		   finish();
            	   }
            	   });
               alertDialog.show();
        }
        else
        {             
        	setContentView(R.layout.splashscreen);
		
		
		
        	/* New Handler to start the Menu-Activity 
        	 * and close this Splash-Screen after some seconds.*/
        	new Handler().postDelayed(new Runnable(){
			public void run()
			{
				/* Create an Intent that will start the Menu-Activity. */
				Intent mainIntent = new Intent(SplashScreen.this,MainActivity.class);
				SplashScreen.this.startActivity(mainIntent);
				SplashScreen.this.finish();
			}
		}, SPLASH_DISPLAY_LENGHT);
		}
	}

}
