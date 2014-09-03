#include "testApp.h"
#include "ofxSPK.h"

/* particle 3d spherical (engine test) */

int w,h,spclock,bgclock;
bool _wire=true;
ofxSPK::System sys;
ofxSPK::Group group;
ofxSPK::Modifier rot;
ofEasyCam cam;
ofShader shader;
ofImage sprite[8];
ofImage bgimg[5];
ofVec3f center;

ofPlanePrimitive plane;
ofVboMesh deformPlane;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(120);
	ofSetVerticalSync(true);

	w=ofGetScreenWidth();
        h=ofGetScreenHeight();

	ofDisableArbTex();
	sprite[0].loadImage("fiore1.png");
	sprite[1].loadImage("fiore2.png");
	sprite[2].loadImage("fiore3.png");
	sprite[3].loadImage("fiore4.png");
	sprite[4].loadImage("bird.png");
	sprite[5].loadImage("bird2.png");
	sprite[6].loadImage("bird3.png");
	sprite[7].loadImage("bird4.png");

	bgimg[0].loadImage("bg.jpg");
	bgimg[1].loadImage("bg1.jpg");
	bgimg[2].loadImage("bg2.jpg");
	bgimg[3].loadImage("bg3.jpg");
	bgimg[4].loadImage("bg4.jpg");

	ofEnableArbTex();

        spclock=7;
        bgclock=3;
        _wire=true;

	sys.setup();
	group.setup(sys);
	group.setColor(ofxSPK::RangeC(ofColor(255, 255), ofColor(255, 255)), ofxSPK::RangeC(ofColor(0, 0), ofColor(255, 0)));
	group.setLifeTime(4.5, 25);
	group.setFriction(0.0);
	group.setSize(20, ofxSPK::RangeF(10, 55));
	group.setGravity(ofVec3f(0.8, -10, 10));
	group.setMass(0.1, 1);	
	rot.setup( SPK::Vortex::create( SPK::Vector3D(0, 0), SPK::Vector3D(0, 1, 0), 200, 10 ), group);

	group.reserve(10000);
        plane.set(w+200,h+200);
        plane.setResolution(30, 24);
}

//--------------------------------------------------------------
void testApp::update()
{
	group.setLifeTime(4.5, 25);
	group.setFriction(0.0);
	group.setSize(20, ofxSPK::RangeF(10, 55));
	group.setGravity(ofVec3f(0.8, -10, 10));
	group.setMass(0.1, 1);	

        float radius = 100;
        center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);
        group.emitRandom(500, ofVec3f(   cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
                                         sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y, 
                                        -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z
                                    ));
	//cam.setPosition(ofVec3f(   cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
        //                           sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y, 
        //                           -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z
        //                            ));
	sys.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw()
{
    bgimg[bgclock].bind();
    plane.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    deformPlane = plane.getMesh();
    ofVec3f planeDims = plane.getResolution();
    float planeAngleX = ofGetElapsedTimef()*3.6;
    float planeAngleInc = 3.f/(float)planeDims.x;
    ofVec3f vert;
    for(int i = 0; i < deformPlane.getNumIndices(); i++ ) {
       planeAngleX += planeAngleInc;
       int ii = deformPlane.getIndex( i );
       vert = deformPlane.getVertex( ii );
       vert.z += cos(planeAngleX) * 50;
       deformPlane.setVertex( ii, vert );
    }
    plane.transformGL();
    deformPlane.draw();
    ofPushMatrix();
    ofSetColor(0);
    if(_wire) deformPlane.drawWireframe();
    ofPopMatrix();
    plane.restoreTransformGL();
    bgimg[bgclock].unbind();

    ofSetColor(255);//????
    cam.begin();
//   	ofEnableBlendMode(OF_BLENDMODE_ADD);
//	ofDisableBlendMode();
	ofPushMatrix();
        sprite[spclock].bind();
	ofEnablePointSprites();
	sys.draw();
	ofDisablePointSprites();
        sprite[spclock].unbind();
	ofPopMatrix();
//	ofDrawAxis(300);
    cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

//unsigned idx = key - '0';
//if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());

if(key == 'f')
	ofToggleFullscreen();
if(key == 'a')
	bgclock=0;
if(key == 's')
	bgclock=1;
if(key == 'd')
	bgclock=2;
if(key == 'g')
	bgclock=3;
if(key == 'j')
	bgclock=4;

if(key == 'q')
	spclock=0;
if(key == 'w')
	spclock=1;
if(key == 'e')
	spclock=2;
if(key == 'r')
	spclock=3;
if(key == 't')
	spclock=4;
if(key == 'y')
	spclock=5;
if(key == 'u')
	spclock=6;
if(key == 'i')
	spclock=7;
if(key == 'o')
	_wire=!_wire;

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
	
}
