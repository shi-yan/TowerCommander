package com.AnimalCrackers.TowerCommanderTest;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.GestureDetector.OnGestureListener;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

class GLView extends GLSurfaceView 
{
	private static String TAG = "GL2JNIView";    
	private static final boolean DEBUG = false;
	
	public boolean exitFlag=false;
	
	private MainActivity parent=null;

	private class UpdateTimeTask extends TimerTask 
	{
		public void run() 
		{
			
			if(exitFlag)
			{
				if(!parent.isFinishing())
					parent.finish();
			}
			else
			{
			
				final Runnable event = new Runnable() 
				{
					public void run()    
					{	
				
					
				//	if(NativeLock.isAvailable)
					//{
    	            	//NativeLock.isAvailable=false;
    	            	//libTowerDefense.updateScene();
    	            	//NativeLock.isAvailable=true;
    	            //}
    	            //FFRuntime.init(300, 300);
    	            requestRender();
					}    
				}; 
    	    
				queueEvent( event );   
			}
		}	
	}
   
	Timer timer;
   
	public void beginAnimation()
	{ 
		timer=new Timer();
		timer.schedule(new UpdateTimeTask(), 1000, 30);
	}  
 
    public boolean onTouchEvent(MotionEvent e)
    {
    
    	int action=e.getAction();
    	int actionCode=action&MotionEvent.ACTION_MASK;
    	
    	if(actionCode==MotionEvent.ACTION_DOWN)
    	{ 
    		touchBegin(1, e.getX(),e.getY(), 0,0);
    	}
    	else if(actionCode==MotionEvent.ACTION_UP)
    	{
    		touchEnd(1,e.getX(),e.getY(),0,0);	
    	}
    	else if(actionCode==MotionEvent.ACTION_POINTER_DOWN)
    	{	
    		float x0=e.getX(0);
    		float y0=e.getY(0);
    		
    		float x1=0.0f;
    		float y1=0.0f;
    		
    		if(e.getPointerCount()>1)
    		{
    			x1=e.getX(1);
    			y1=e.getY(1);
    			
    		}
    		
    		touchBegin(e.getPointerCount(), x0, y0, x1, y1);
    		
    	}
    	else if(actionCode==MotionEvent.ACTION_POINTER_UP)
    	{
    		
    	//	Log.d("ddd","pointer up");
    		
    		
    		float x0=e.getX(0);
    		float y0=e.getY(0);
    		
    		float x1=0.0f;
    		float y1=0.0f;
    		
    		if(e.getPointerCount()>1)
    		{
    			x1=e.getX(1);
    			y1=e.getY(1);
    		
    		}
    		
    		touchEnd(e.getPointerCount(), x0, y0, x1, y1);
    	}
    	else if(actionCode==MotionEvent.ACTION_MOVE)
    	{
    		
    	//	Log.d("ddd","move");
   
    	 
    		float x0=e.getX(0);
    		float y0=e.getY(0);
    		
    		float x1=0.0f;
    		float y1=0.0f;
    		
    		if(e.getPointerCount()>1)
    		{
    			x1=e.getX(1);
    			y1=e.getY(1);
    			
    		}
    		
    		touchMove(e.getPointerCount(), x0, y0, x1, y1);
    	}
    	
    	
    	try 
    	{
			Thread.sleep(30);
		} 
    	catch (InterruptedException e1) 
    	{
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
  
    	return true;
    }
    
    public void touchBegin( final int count, final float x0, final float y0, final float x1, final float y1 )
    {
        final Runnable event = new Runnable() 
        {
            public void run()
            {
            	if(NativeLock.isAvailable)
            	{
            		NativeLock.isAvailable=false;
            		libTowerDefense.touchBegin( count, x0, y0, x1, y1 );
            		NativeLock.isAvailable=true;
            	}
            	//FFRuntime.init(300, 300);
            }
        };
        
      //  Log.d("asdf","touch begin");

        queueEvent( event ); 
    }

    public void touchEnd( final int count, final float x0, final float y0, final float x1, final float y1 )
    {
        final Runnable event = new Runnable() 
        {
            public void run()
            {
              	if(NativeLock.isAvailable)
              	{
                	NativeLock.isAvailable=false;
                	libTowerDefense.touchEnd( count, x0, y0, x1, y1 );
                	NativeLock.isAvailable=true;
              	}
            }
        };  
        
   
        queueEvent( event );
    }

    public void touchMove( final int count, final float x0, final float y0, final float x1, final float y1 )
    {
        final Runnable event = new Runnable() 
        {
            public void run()
            { 
            	if(NativeLock.isAvailable)
            	{
            		NativeLock.isAvailable=false;
            		libTowerDefense.touchMove( count, x0, y0, x1, y1 );
            	
            		NativeLock.isAvailable=true;
            	}
            	//requestRender();
            }
        };
 
        
        queueEvent( event );
    }

    public GLView(MainActivity _parent,Context context) 
    {
        super(context);
        parent=_parent;
      
        setEGLConfigChooser(5,6,5,0,24,2);
        setRenderer(new Renderer(this,parent));
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }
    
    public void onDestroy()
    {
    	
    	
    }

      

    private void init(boolean translucent, int depth, int stencil) 
    {
     
    }   

    private static class ContextFactory implements GLSurfaceView.EGLContextFactory 
    {
        private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
    
        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) 
        {
            Log.w(TAG, "creating OpenGL ES 2.0 context");
            checkEglError("Before eglCreateContext", egl);
            int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 11, EGL10.EGL_NONE };
            EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
            checkEglError("After eglCreateContext", egl);
            return context;
        } 

        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) 
        {
            egl.eglDestroyContext(display, context);
        }
    }

    private static void checkEglError(String prompt, EGL10 egl) 
    {
        int error;
        while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) 
        {
            Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
        }
    }

    private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser 
    {

        public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) 
        {
            mRedSize = r;
            mGreenSize = g;
            mBlueSize = b;
            mAlphaSize = a;
            mDepthSize = depth; 
            mStencilSize = stencil;
        }

        /* This EGL config specification is used to specify 2.0 rendering.
         * We use a minimum size of 4 bits for red/green/blue, but will
         * perform actual matching in chooseConfig() below.
         */
        private static int EGL_OPENGL_ES2_BIT = 4;
        private static int[] s_configAttribs2 =
        {
            EGL10.EGL_RED_SIZE, 4,
            EGL10.EGL_GREEN_SIZE, 4,
            EGL10.EGL_BLUE_SIZE, 4,
            EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL10.EGL_NONE
        };

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) 
        {

            /* Get the number of minimally matching EGL configurations
             */
            int[] num_config = new int[1];
            egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

            int numConfigs = num_config[0];

            if (numConfigs <= 0) 
            {
                throw new IllegalArgumentException("No configs match configSpec");
            }

            /* Allocate then read the array of minimally matching EGL configs
             */
            EGLConfig[] configs = new EGLConfig[numConfigs];
            egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

            if (DEBUG) 
            {
                 printConfigs(egl, display, configs);
            }
            /* Now return the "best" one
             */
            return chooseConfig(egl, display, configs);
        }  

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display, EGLConfig[] configs) 
        {
            for(EGLConfig config : configs) 
            {
                int d = findConfigAttrib(egl, display, config,
                        EGL10.EGL_DEPTH_SIZE, 0);
                int s = findConfigAttrib(egl, display, config,
                        EGL10.EGL_STENCIL_SIZE, 0);

                // We need at least mDepthSize and mStencilSize bits
                if (d < mDepthSize || s < mStencilSize)
                    continue;

                // We want an *exact* match for red/green/blue/alpha
                int r = findConfigAttrib(egl, display, config,
                        EGL10.EGL_RED_SIZE, 0);
                int g = findConfigAttrib(egl, display, config,
                            EGL10.EGL_GREEN_SIZE, 0);
                int b = findConfigAttrib(egl, display, config,
                            EGL10.EGL_BLUE_SIZE, 0);
                int a = findConfigAttrib(egl, display, config,
                        EGL10.EGL_ALPHA_SIZE, 0);

                if (r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize)
                    return config;
            }
            return null;  
        }

        private int findConfigAttrib(EGL10 egl, EGLDisplay display,  EGLConfig config, int attribute, int defaultValue) 
        {

            if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) 
            {
                return mValue[0];
            }
            return defaultValue;
        }
 
        private void printConfigs(EGL10 egl, EGLDisplay display, EGLConfig[] configs) 
        {
            int numConfigs = configs.length;
            Log.w(TAG, String.format("%d configurations", numConfigs));
            for (int i = 0; i < numConfigs; i++) 
            {
                Log.w(TAG, String.format("Configuration %d:\n", i));
                printConfig(egl, display, configs[i]);
            }
        }

        private void printConfig(EGL10 egl, EGLDisplay display,  EGLConfig config) 
        {
            int[] attributes = 
            {
                    EGL10.EGL_BUFFER_SIZE,
                    EGL10.EGL_ALPHA_SIZE,
                    EGL10.EGL_BLUE_SIZE,
                    EGL10.EGL_GREEN_SIZE,
                    EGL10.EGL_RED_SIZE,
                    EGL10.EGL_DEPTH_SIZE,
                    EGL10.EGL_STENCIL_SIZE,
                    EGL10.EGL_CONFIG_CAVEAT,
                    EGL10.EGL_CONFIG_ID,
                    EGL10.EGL_LEVEL,
                    EGL10.EGL_MAX_PBUFFER_HEIGHT,
                    EGL10.EGL_MAX_PBUFFER_PIXELS,
                    EGL10.EGL_MAX_PBUFFER_WIDTH,
                    EGL10.EGL_NATIVE_RENDERABLE,
                    EGL10.EGL_NATIVE_VISUAL_ID,
                    EGL10.EGL_NATIVE_VISUAL_TYPE,
                    0x3030, // EGL10.EGL_PRESERVED_RESOURCES,
                    EGL10.EGL_SAMPLES,
                    EGL10.EGL_SAMPLE_BUFFERS,
                    EGL10.EGL_SURFACE_TYPE,
                    EGL10.EGL_TRANSPARENT_TYPE,
                    EGL10.EGL_TRANSPARENT_RED_VALUE,
                    EGL10.EGL_TRANSPARENT_GREEN_VALUE,
                    EGL10.EGL_TRANSPARENT_BLUE_VALUE,
                    0x3039, // EGL10.EGL_BIND_TO_TEXTURE_RGB,
                    0x303A, // EGL10.EGL_BIND_TO_TEXTURE_RGBA,
                    0x303B, // EGL10.EGL_MIN_SWAP_INTERVAL,
                    0x303C, // EGL10.EGL_MAX_SWAP_INTERVAL,
                    EGL10.EGL_LUMINANCE_SIZE,
                    EGL10.EGL_ALPHA_MASK_SIZE,
                    EGL10.EGL_COLOR_BUFFER_TYPE,
                    EGL10.EGL_RENDERABLE_TYPE,
                    0x3042 // EGL10.EGL_CONFORMANT
            };
            
            String[] names = 
            {
                    "EGL_BUFFER_SIZE",
                    "EGL_ALPHA_SIZE",
                    "EGL_BLUE_SIZE",
                    "EGL_GREEN_SIZE",
                    "EGL_RED_SIZE",
                    "EGL_DEPTH_SIZE",
                    "EGL_STENCIL_SIZE",
                    "EGL_CONFIG_CAVEAT",
                    "EGL_CONFIG_ID",
                    "EGL_LEVEL",
                    "EGL_MAX_PBUFFER_HEIGHT",
                    "EGL_MAX_PBUFFER_PIXELS",
                    "EGL_MAX_PBUFFER_WIDTH",
                    "EGL_NATIVE_RENDERABLE",
                    "EGL_NATIVE_VISUAL_ID",
                    "EGL_NATIVE_VISUAL_TYPE",
                    "EGL_PRESERVED_RESOURCES",
                    "EGL_SAMPLES",
                    "EGL_SAMPLE_BUFFERS",
                    "EGL_SURFACE_TYPE",
                    "EGL_TRANSPARENT_TYPE",
                    "EGL_TRANSPARENT_RED_VALUE",
                    "EGL_TRANSPARENT_GREEN_VALUE",
                    "EGL_TRANSPARENT_BLUE_VALUE",
                    "EGL_BIND_TO_TEXTURE_RGB",
                    "EGL_BIND_TO_TEXTURE_RGBA",
                    "EGL_MIN_SWAP_INTERVAL",
                    "EGL_MAX_SWAP_INTERVAL",
                    "EGL_LUMINANCE_SIZE",
                    "EGL_ALPHA_MASK_SIZE",
                    "EGL_COLOR_BUFFER_TYPE",
                    "EGL_RENDERABLE_TYPE",
                    "EGL_CONFORMANT"  
            };
            
            int[] value = new int[1];
            
            for (int i = 0; i < attributes.length; i++) 
            {
                int attribute = attributes[i];
                String name = names[i];
                if ( egl.eglGetConfigAttrib(display, config, attribute, value)) 
                {
                    Log.w(TAG, String.format("  %s: %d\n", name, value[0]));
                } 
                else 
                {
                    // Log.w(TAG, String.format("  %s: failed\n", name));
                    while (egl.eglGetError() != EGL10.EGL_SUCCESS);
                }
            }
        }

        // Subclasses can adjust these values:
        protected int mRedSize;
        protected int mGreenSize;
        protected int mBlueSize;
        protected int mAlphaSize;
        protected int mDepthSize;
        protected int mStencilSize;
        private int[] mValue = new int[1];
    }  

    private static class Renderer implements GLSurfaceView.Renderer 
    {
    	
    	GLView glView=null;
    	MainActivity parent=null;
    	AndroidTextureLoader textureLoader;
    	SoundManager soundManager;
    	
        public Renderer(GLView gv,MainActivity _parent) { 
			// TODO Auto-generated constructor stub
        	super();
        	glView=gv;
        	textureLoader=new AndroidTextureLoader();
        	soundManager=new SoundManager();
        	parent=_parent;
		} 

		public void onDrawFrame(GL10 gl) {
        	if(NativeLock.isAvailable)
        	{
        		NativeLock.isAvailable=false;
        		boolean flag;
        		if(flag=libTowerDefense.step())
        		{
        			glView.exitFlag=true;
        		};
        		
        	//	Log.d("towre commander",flag+";");
        		NativeLock.isAvailable=true;
            }
        } 

     
        
        public void onSurfaceChanged(GL10 gl, int width, int height) {
      
        	AndroidTextureLoader.gl=gl;
        	
        	if(NativeLock.isAvailable)
        	{
        		NativeLock.isAvailable=false;
        		textureLoader.ClearCachedTextures();
      
        		libTowerDefense.init(width, height,"name",textureLoader,soundManager,parent);
        		glView.beginAnimation();
        		NativeLock.isAvailable=true;
        	}
        	
        
        
        }
 
        public void onSurfaceCreated(GL10 gl, EGLConfig config) 
        {
        	
        }
        
        public void shutdown()
        {
        	if(NativeLock.isAvailable)
        	{
        		NativeLock.isAvailable=false;
        		libTowerDefense.cleanup();
        		NativeLock.isAvailable=true;
        	}
        } 
   
    }

    
 
}
