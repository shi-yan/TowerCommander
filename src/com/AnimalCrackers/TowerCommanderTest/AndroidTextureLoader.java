package com.AnimalCrackers.TowerCommanderTest;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.String;
import java.util.Hashtable;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.opengles.GL10;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.opengl.GLUtils;
import android.util.Log;

public class AndroidTextureLoader 
{ 

	public static GL10 gl;
	private static Paint textPaint;
	private Hashtable<String,TextureInfo> textureIDHash;
	public static AssetManager am=null;
	
	public AndroidTextureLoader()
	{
		textPaint = new Paint();
		textPaint.setAntiAlias(true);
		textPaint.setARGB(0xff, 0x00, 0x00, 0x00);
		
		textureIDHash=new Hashtable<String,TextureInfo>();
	} 
	 
	public void ClearCachedTextures()
	{
		textureIDHash.clear();
	}
	
	public TextureInfo CreateTextTexture(String fontName, int size, String text,int maxwidth)
	{
		Log.d("Create Text Texture map","Font: "+fontName+" Size: "+size+" Text: "+text+" Max Width: "+maxwidth);
		
        String hashKey=fontName+text+size;
        
        if(textureIDHash.containsKey(hashKey))
        {
        	TextureInfo ti=textureIDHash.get(hashKey);  
            
            Log.d("After Created texture","textureID: "+ti.textureID+" width "+ti.width+" height "+ti.height+" textWidth "+ti.textWidth+" textHeight "+ti.textHeight);
            
    		return ti;
        }
		    
	 
		textPaint.setTextSize(size);
		     
		int  ascent = (int) Math.ceil(-textPaint.ascent());
        int  descent = (int) Math.ceil(textPaint.descent());
        int  textWidth = (int) Math.ceil(textPaint.measureText(text));
        int textHeight = ascent + descent;
  

        
    	if(maxwidth > 0 && maxwidth < textWidth)
    	{
    		float ratio = (float)((float)maxwidth/(float)textWidth);
    		
    		int newLength = (int) (text.length()*ratio - 3);
    		String newText = text.substring(0, newLength) + "...";
     
    		textWidth=(int) Math.ceil(textPaint.measureText(newText));
    		text=newText;
    	}
    	
    /*	if(m_textureids[textureindex])
    	{
    		return m_textureids[textureindex]->Reuse(width, height);
    	}
    	*/
    	int i=0;
    	int width = textWidth;
    	if((width != 1) && (width & (width - 1))>0) 
    	{
    		i = 1;
    		while(i < width)
    			i *= 2;
    		width = i;
    	}
  
    	int height = textHeight;

    	if((height != 1) && (height & (height - 1))>0) 
    	{
    		i = 1;
    		while(i < height)
    			i *= 2;
    		height = i;
    	}
		
    	Bitmap.Config config = Bitmap.Config.ALPHA_8;
        Bitmap mBitmap = Bitmap.createBitmap(width, height, config);
       // mBitmap. 
        Canvas mCanvas = new Canvas(mBitmap);
        mBitmap.eraseColor(0);
        //mCanvas.drawRect (0, 0, width, height,textPaint);
        mCanvas.drawText(text,0,textHeight-2,textPaint);
        int[] textures = new int[1];
        
        gl.glGenTextures(1, textures, 0);

        int textureID = textures[0];
        gl.glBindTexture(GL10.GL_TEXTURE_2D, textureID);

        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER,GL10.GL_LINEAR);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER,GL10.GL_LINEAR);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S,GL10.GL_REPEAT);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T,GL10.GL_REPEAT);
 	
        gl.glBindTexture(GL10.GL_TEXTURE_2D, textureID);
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, mBitmap, 0);
//
        
        // Reclaim storage used by bitmap and canvas.
        mBitmap.recycle();
        mBitmap = null;
        mCanvas = null;

        TextureInfo returned=new TextureInfo();
        
        returned.textureID=textureID;
        returned.width=width;
        returned.height=height; 
        returned.textWidth=textWidth;
        returned.textHeight=textHeight;
        
        Log.d("After Created texture","textureID: "+textureID+" width "+width+" height "+height+" textWidth "+textWidth+" textHeight "+textHeight);
        
        textureIDHash.put(hashKey, returned);
        
		return returned;
	}
	
	/*public static TextureInfo CreatePngTexture(String root)
	{
		Log.d("root",root);  
		return null; 
	}*/
	
	public TextureInfo CreateTextureFromPNG( String textureName,boolean clamp)
	{  
		Log.d("texture","create png texture: "+textureName);  
		
        String hashKey=textureName;
        
        if(textureIDHash.containsKey(hashKey))
        {
        	TextureInfo ti=textureIDHash.get(hashKey);
            
            Log.d("After Created texture","textureID: "+ti.textureID+" width "+ti.width+" height "+ti.height+" textWidth "+ti.textWidth+" textHeight "+ti.textHeight);
            
    		return ti;
        } 
		
        int[] textures = new int[1];
        
        gl.glGenTextures(1, textures, 0);

        int textureID = textures[0];
        gl.glBindTexture(GL10.GL_TEXTURE_2D, textureID);

    	if(clamp)
    	{
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_NEAREST);
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER,GL10. GL_NEAREST);
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_WRAP_S,GL10.GL_CLAMP_TO_EDGE);
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_WRAP_T,GL10.GL_CLAMP_TO_EDGE);
    	}
    	else 
    	{
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_LINEAR);
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_WRAP_S,GL10.GL_REPEAT);
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_WRAP_T,GL10.GL_REPEAT);	
    	}
 
        try 
        { 
        	InputStream  is= am.open(textureName); //new FileInputStream(textureName);
        	Bitmap bitmap = BitmapFactory.decodeStream(is);
            is.close();
           
            
            Matrix mtx = new Matrix();
            
            mtx.postScale(1.0f, -1.0f); 
         
            // Rotating Bitmap
           
            Bitmap flippedBitmap = Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), mtx, true);
       
           
             

        
            GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, flippedBitmap, 0);
		
    		TextureInfo info=new TextureInfo();
    		info.textureID=textureID;  
    		info.width=bitmap.getWidth();
    		info.height=bitmap.getHeight();
    	     
    		bitmap.recycle();
    		bitmap.recycle();
    		
    		textureIDHash.put(hashKey, info);
    		
            return info;
		
        } 
        catch (FileNotFoundException e1) 
        {
        	// TODO Auto-generated catch block
        	e1.printStackTrace();
        	TextureInfo info=new TextureInfo();
    		info.textureID=textureID;  
    		info.width=1;
    		info.height=1;
        }  
        catch (IOException e) 
        {
        	// TODO Auto-generated catch block
        	e.printStackTrace();
        	TextureInfo info=new TextureInfo();
    		info.textureID=0;  
    		info.width=1;
    		info.height=1;
        }
        return null;
	}; 
	
	
	public TextureInfo CreateTextureFromTiles( String filenames[],int tileWidth,int tileHeight,int width,int height,int sqr )
	{ 
		
		Log.d("filename size:",filenames.length+";");
		
		for(String s:filenames) 
		{
			Log.d("name:",s);
			
		}
		
		
		
        String hashKey="";
        
        for(String aname:filenames)
        {
        	
        	hashKey+=aname;
        }
        
        if(textureIDHash.containsKey(hashKey))
        {
        	TextureInfo ti=textureIDHash.get(hashKey);
            
            Log.d("After Created texture","textureID: "+ti.textureID+" width "+ti.width+" height "+ti.height+" textWidth "+ti.textWidth+" textHeight "+ti.textHeight);
            
    		return ti;
        }
		
        int[] textures = new int[1];
        
        gl.glGenTextures(1, textures, 0); 

        int textureID = textures[0];
        gl.glBindTexture(GL10.GL_TEXTURE_2D, textureID);

    
    	{
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_LINEAR);
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_WRAP_S,GL10.GL_REPEAT);
    		gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_WRAP_T,GL10.GL_REPEAT);		
    	}
 
 
    	
        try 
        { 
           	Bitmap composedBitmap = Bitmap.createBitmap(width, height,Config.ARGB_8888);
            Canvas canvas=new Canvas(composedBitmap);
            
            
            int h=0;
			int v=0;
			
			
		
        	for(String aname:filenames)
        	{
        		
        		
        		int positionx=h*tileWidth;
				int positiony=v*tileHeight;
				
				
				InputStream  is= am.open(aname);//new FileInputStream(aname);
        		Bitmap bitmap = BitmapFactory.decodeStream(is);
        		    
        		is.close();
           
            
          
     	   
				canvas.drawBitmap(bitmap, positionx, positiony, new Paint());
				h++;
				
				if (h>=sqr) 
				{
					h=0;
					v++;
				}
        
         
            // Rotating Bitmap
           
				bitmap.recycle();
				
           
        	}

        	  Matrix mtx = new Matrix();
              
              mtx.postScale(1.0f, -1.0f); 
              Bitmap flippedBitmap = Bitmap.createBitmap(composedBitmap, 0, 0, composedBitmap.getWidth(), composedBitmap.getHeight(), mtx, true);
        
            GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, flippedBitmap, 0);
		
    		TextureInfo info=new TextureInfo();
    		info.textureID=textureID;  
    		info.width=composedBitmap.getWidth();
    		info.height=composedBitmap.getHeight();
    	     
    	/*	FileOutputStream out=new FileOutputStream("/sdcard/TowerCommander/fuck.png");
    		flippedBitmap.compress(CompressFormat.PNG, 100, out);
    		out.close();
    		*/
    		composedBitmap.recycle();
    		flippedBitmap.recycle();    
    		
    		textureIDHash.put(hashKey, info);
    		
            return info;
		
        } 
        catch (FileNotFoundException e1) 
        {
        	// TODO Auto-generated catch block 
        	e1.printStackTrace();
        	TextureInfo info=new TextureInfo();
    		info.textureID=textureID;  
    		info.width=1;
    		info.height=1;
        }  
        catch (IOException e) 
        {
        	// TODO Auto-generated catch block
        	e.printStackTrace();
        	TextureInfo info=new TextureInfo();
    		info.textureID=0;  
    		info.width=1;
    		info.height=1;
        }
        return null;
		
		 
	}

}
