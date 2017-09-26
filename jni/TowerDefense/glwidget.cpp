/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include <QPainter>
#include <math.h>
#include "QtTextureLoader.h"
#include "TextureAtlasManager.h"
#include <QtGui/QkeyEvent>
#include "Game.h"
#include "GameTimeManager.h"
const int bubbleNum = 8;


GLWidget::GLWidget(QWidget *parent): QGLWidget(parent)
{
    frames = 0;
	setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoBufferSwap(false);
}

GLWidget::~GLWidget()
{
}

int texid=0;

void GLWidget::initializeGL ()
{
	int width;
	int height;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
	
	AnimalCrackers::TowerDefense::Game::getSingleton().init();
	
	
}

bool isKeyup=true;

void GLWidget::keyPressEvent ( QKeyEvent * event )
{

	printf("\nkey: %d\n",event->key());
	
	switch (event->key()) {
		case 46:
			break;
		case 65:
			break;
		case 68:
			break;
		case 16777219:
			break;
		default:
			//AnimalCrackers::JumpNRun::Game::getSingleton().mariowalkleft();
			break;
	}
}

void GLWidget::keyReleaseEvent ( QKeyEvent * event )
{

	printf("%d\n",event->key());
	
	switch (event->key()) 
	{
		case 46:
			
			break;
			
		case 65:
			break;
		case 68:
			break;
		case 16777219:
			AnimalCrackers::TowerDefense::Game::getSingleton().handleBackEvent();
			break;
		default:
			break;
	}

}


void GLWidget::mousePressEvent ( QMouseEvent * event )
{
	AnimalCrackers::TowerDefense::Game::getSingleton().handlePressEvent(event->x(),event->y());
}

void GLWidget::mouseReleaseEvent(QMouseEvent * event)
{
	AnimalCrackers::TowerDefense::Game::getSingleton().handleReleaseEvent(event->x(),event->y());
}

void GLWidget:: mouseMoveEvent ( QMouseEvent * event ) 
{
	AnimalCrackers::TowerDefense::Game::getSingleton().handleMoveEvent(event->x(),event->y());
}

void GLWidget::paintGL()
{
	
	
    QPainter painter;
    painter.begin(this);
	
	glViewport(0, 0, 800, 480);
	
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	glOrtho(0.0f, 800.0f, 480.0f, 0.0f, -2.0f, 2.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	AnimalCrackers::TowerDefense::TextureAtlasManager::getSingleton().setLastTextureID(-1);

	AnimalCrackers::TowerDefense::Game::getSingleton().draw();
	
	swapBuffers();

    frames ++;
}