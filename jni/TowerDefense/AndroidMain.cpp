#include <jni.h>


#include <GLES/gl.h>
#include <GLES/glext.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <android/log.h>
#define  LOG_TAG    "libtowerdefense"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#include "AndroidTextureLoader.h"
#include "AndroidSoundManager.h"
#include "AndroidControlManager.h"
#include "Game.h"

extern "C"
{
    JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring filename, jobject textureobj,jobject soundobj,jobject mainactobj);
    JNIEXPORT bool JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_cleanup(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_touchBegin(JNIEnv * env, jobject obj,  jint count, jfloat x0, jfloat y0, jfloat x1, jfloat y1 );
    JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_touchEnd(JNIEnv * env, jobject obj,  jint count, jfloat x0, jfloat y0, jfloat x1, jfloat y1 );
    JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_touchMove(JNIEnv * env, jobject obj,  jint count, jfloat x0, jfloat y0, jfloat x1, jfloat y1 );
	JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_updateScene(JNIEnv *env, jobject obj);
	JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_onBack(JNIEnv *env, jobject obj);
	
	
};

static int offsetX=0;
static int offsetY=0;

static JavaVM *jVM=0;
static double m_starttime=0.0;

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
		 = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

static double CFAbsoluteTimeGetCurrent()
{
	timeval tim;
	gettimeofday(&tim, NULL);
	double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
	return t1;
}

int JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env;
    jVM = vm;
	
#ifdef DEBUG
    __android_log_print(ANDROID_LOG_DEBUG, "TowerCommanderTest_JNI", "JNI_OnLoad called");
#endif
	
    if( vm->GetEnv( (void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        __android_log_print(ANDROID_LOG_ERROR, "TowerCommanderTest_JNI", "Failed to get the environment using GetEnv()");
        return -1;
    }
	
    AnimalCrackers::TowerDefense::TextureLoader::jVM=vm;
	AnimalCrackers::TowerDefense::SoundManager::jVM=vm;
	AnimalCrackers::TowerDefense::AndroidControlManager::jVM=vm;
	
    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring filename, jobject textureobj, jobject soundobj,jobject mainactobj)
{    
	
	m_starttime=CFAbsoluteTimeGetCurrent();
	
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);
	
    LOGI("Getting viewport (%d,%d)\n", width,height);

	
	if (width>800) {
		offsetX=(width-800)/2;
	}
	
	if (height>480) {
		offsetY=(height-480)/2;
	}
	
    glViewport(offsetX, 0, 800, 480);
    LOGI("Got viewport (%d,%d)\n", width,height);
    checkGlError("glViewport");
	
	
	AnimalCrackers::TowerDefense::TextureLoader::Android_textureLoaderObject = textureobj;
    
	jclass Android_textureClass;
	
	AnimalCrackers::TowerDefense::TextureLoader::Android_textureLoaderObject  = env->NewGlobalRef(textureobj);
    Android_textureClass = env->GetObjectClass( AnimalCrackers::TowerDefense::TextureLoader::Android_textureLoaderObject );
	AnimalCrackers::TowerDefense::TextureLoader::Android_createTextureFromPNG =  env->GetMethodID(Android_textureClass,"CreateTextureFromPNG",  "(Ljava/lang/String;Z)Lcom/AnimalCrackers/TowerCommanderTest/TextureInfo;");
	AnimalCrackers::TowerDefense::TextureLoader::Android_createTextureFromTiles= env->GetMethodID(Android_textureClass,"CreateTextureFromTiles","([Ljava/lang/String;IIIII)Lcom/AnimalCrackers/TowerCommanderTest/TextureInfo;");
	
	LOGI("init 3");
	
	
	jclass textureInfoClass = env->FindClass("com/AnimalCrackers/TowerCommanderTest/TextureInfo");
	AnimalCrackers::TowerDefense::TextureLoader::Android_textureID = env->GetFieldID( textureInfoClass, "textureID", "I");
	AnimalCrackers::TowerDefense::TextureLoader::Android_textWidth=env->GetFieldID( textureInfoClass, "textWidth", "I");
	AnimalCrackers::TowerDefense::TextureLoader::Android_textHeight=env->GetFieldID( textureInfoClass, "textHeight", "I");
	AnimalCrackers::TowerDefense::TextureLoader::Android_width=env->GetFieldID( textureInfoClass, "width", "I");
	AnimalCrackers::TowerDefense::TextureLoader::Android_height=env->GetFieldID( textureInfoClass, "height", "I");
	
	LOGI("init 1");
	
	AnimalCrackers::TowerDefense::AndroidControlManager::Android_mainActivityObject =mainactobj;
	jclass activityClass;
	AnimalCrackers::TowerDefense::AndroidControlManager::Android_mainActivityObject = env->NewGlobalRef(mainactobj);
	activityClass = env->GetObjectClass( AnimalCrackers::TowerDefense::AndroidControlManager::Android_mainActivityObject );
	AnimalCrackers::TowerDefense::AndroidControlManager::Android_showHelpDialog=env->GetMethodID(activityClass,"popupHelpDialog",  "()V");
		
	LOGI("init 2");
	

	
	AnimalCrackers::TowerDefense::SoundManager:: Android_soundClass = env->GetObjectClass(soundobj);
	AnimalCrackers::TowerDefense::SoundManager::Android_playMethodID  = env->GetStaticMethodID( AnimalCrackers::TowerDefense::SoundManager:: Android_soundClass , "play", "(I)V");
	
	if (AnimalCrackers::TowerDefense::Game::getSingleton().initializedBefore()==false) {
		
	
	
	AnimalCrackers::TowerDefense::Game::getSingleton().init();
	}else {
		AnimalCrackers::TowerDefense::Game::getSingleton().restoreOpenGLContext();
	}

	//env->DeleteGlobalRef( 	FY::AndroidTextureLoader::Android_textureObject );
	
	
/*	jstring js = env->NewStringUTF("hahahahahahahahahahahahahahahahahah");
	
    jobject returned = env->CallObjectMethod( FY::AndroidTextureLoader::Android_textureObject, FY::AndroidTextureLoader::Android_createPngTexture,js);
	
	int textureid=env->GetIntField(returned,FY::AndroidTextureLoader::Android_textureID);
	int texturewidth=env->GetIntField(returned,FY::AndroidTextureLoader::Android_textureWidth);
	int textureheight=env->GetIntField(returned,FY::AndroidTextureLoader::Android_textureHeight);
	
	LOGI("returned from java %d,%d,%d",textureid,texturewidth,textureheight);
*/	


}


JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_cleanup(JNIEnv * env, jobject obj)
{
   // LOGI("Cleaning");

}

JNIEXPORT bool JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_step(JNIEnv * env, jobject obj)
{
	
	glViewport(offsetX, offsetY, 800, 480);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	glOrthof(0.0f, 800.0f, 480.0f, 0.0f, -2.0f, 2.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	AnimalCrackers::TowerDefense::TextureAtlasManager::getSingleton().setLastTextureID(-1);
	
	AnimalCrackers::TowerDefense::Game::getSingleton().draw();
	
	return AnimalCrackers::TowerDefense::Game::getSingleton().getExitFlag();	
}


JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_updateScene(JNIEnv *env, jobject obj)
{
//	LOGI("update scene");
	/*if(!m_context->IsAnimating())
	{
		m_context->StartAnimation(true);
		return;
	}
	*/
	//m_context->GetScene()->SetDirty();

}

JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_touchBegin(JNIEnv * env, jobject obj,  jint count, jfloat x0, jfloat y0, jfloat x1, jfloat y1 )
{
	
AnimalCrackers::TowerDefense::Game::getSingleton().handlePressEvent(x0,y0);
}

JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_touchEnd(JNIEnv * env, jobject obj,  jint count, jfloat x0, jfloat y0, jfloat x1, jfloat y1 )
{
	AnimalCrackers::TowerDefense::Game::getSingleton().handleReleaseEvent(x0,y0);
}

JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_touchMove(JNIEnv * env, jobject obj,  jint count, jfloat x0, jfloat y0, jfloat x1, jfloat y1 )
{
  AnimalCrackers::TowerDefense::Game::getSingleton().handleMoveEvent(x0,y0);
}

JNIEXPORT void JNICALL Java_com_AnimalCrackers_TowerCommanderTest_libTowerDefense_onBack(JNIEnv * env, jobject obj )
{
	AnimalCrackers::TowerDefense::Game::getSingleton().handleBackEvent();

	
}
