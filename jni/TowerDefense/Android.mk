LOCAL_PATH := $(call my-dir)
LOCAL_ARM_MODE := arm
include $(CLEAR_VARS)

LOCAL_MODULE := towerdefense

LOCAL_CFLAG := -O3

LOCAL_SRC_FILES :=AirEnemy.cpp\
Bullet.cpp\
CoinAnimation.cpp\
Enemy.cpp\
EnemyFactory.cpp\
FlameAnimation.cpp\
FlameTower.cpp\
Game.cpp\
GameButton.cpp\
GameMap.cpp\
GameScreen.cpp\
GameTimeManager.cpp\
HotSpot.cpp\
InGameMenu.cpp\
LevelSelectorScreen.cpp\
LifeBar.cpp\
LostDialog.cpp\
MainMenuButton.cpp\
MainMenuScreen.cpp\
MoneyBar.cpp\
NextWaveBar.cpp\
NotificationAnimation.cpp\
QuadHelper.cpp\
QuitDialog.cpp\
Screen.cpp\
SlowTower.cpp\
SmallAnimation.cpp\
SmallAnimationManager.cpp\
Sprite.cpp\
Texture.cpp\
TextureAnimation.cpp\
TextureAtlas.cpp\
TextureAtlasManager.cpp\
AndroidTextureLoader.cpp\
Tower.cpp\
TowerFactory.cpp\
UIItem.cpp\
UpgradeMenu.cpp\
WalkableEnemy.cpp\
Wave.cpp\
WinDialog.cpp\
AndroidMain.cpp\
ResearchScreen.cpp\
AchievementsScreen.cpp\
TowerIconButton.cpp\
FailedDialog.cpp\
AndroidSoundManager.cpp\
AndroidControlManager.cpp\
PlayerInfo.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/

LOCAL_LDLIBS := -llog -lGLESv1_CM -lz

LOCAL_STATIC_LIBRARIES := 

include $(BUILD_SHARED_LIBRARY)
