#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "CameraAdapter.h"
#include "cinder/Timeline.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define _SCL_SECURE_NO_WARNINGS

class CanonSDKApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	Anim<float> alphaFlash;
	void photoTakenHandler();
	void photoDownloadHandler();
	void deviceConnectHandler();
	void deviceDisconnectHandler();
	void photoErrorHandler();
};

void CanonSDKApp::setup()
{
	setWindowSize(1020, 680);
	alphaFlash = 0;
	gl::enableAlphaBlending();	

	cameraCanon().deviceConnectEvent.connect(bind(&CanonSDKApp::deviceConnectHandler, this));
	cameraCanon().deviceDisconnectEvent.connect(bind(&CanonSDKApp::deviceDisconnectHandler, this));

	cameraCanon().photoErrorEvent.connect(bind(&CanonSDKApp::photoErrorHandler, this));

	cameraCanon().photoTakenEvent.connect(bind(&CanonSDKApp::photoTakenHandler, this));
	cameraCanon().photoDownloadedEvent.connect(bind(&CanonSDKApp::photoDownloadHandler, this));

	cameraCanon().setup();
}

void CanonSDKApp::deviceConnectHandler()
{
	console()<<"deviceConnectHandler "<<endl;
}

void CanonSDKApp::deviceDisconnectHandler()
{
	console()<<"deviceDisconnectHandler "<<endl;
}

void CanonSDKApp::photoErrorHandler()
{
	console()<<"photoErrorHandler "<<endl;
}

void CanonSDKApp::photoTakenHandler()
{
	console()<<"photoTakenHandler "<<endl;
}

void CanonSDKApp::photoDownloadHandler()
{
	console()<<"photoDownloadHandler "<<endl;
} 

void CanonSDKApp::mouseDown( MouseEvent event )
{
	cameraCanon().takePicture();	
	timeline().apply( &alphaFlash, 1.0f, 0.0f, 1.2f, EaseInCubic());
}

void CanonSDKApp::update()
{
}

void CanonSDKApp::draw()
{
	gl::clear( Color::black()); 
	//cameraCanon().draw();

	gl::color(ColorA(1.0f, 1.0f, 1.0f, alphaFlash));
	gl::drawSolidRect(Rectf(getWindowBounds()));
}

CINDER_APP_NATIVE( CanonSDKApp, RendererGl )
