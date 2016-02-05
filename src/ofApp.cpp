#include "ofApp.h"

ofImage image;		//Original image
ofImage image2;		//Modified image

////////////////////
const int N = 6;		//Number of bands in spectrum
float spectrum[ N ];	//Smoothed spectrum values
float Rad = 700;		//Cloud raduis parameter
float Vel = 0.2;		//Cloud points velocity parameter
int bandRad = 2;		//Band index in spectrum, affecting Rad value
int bandVel = 16;		//Band index in spectrum, affecting Vel value

const int n = 180;		//Number of cloud points

//Offsets for Perlin noise calculation for points
float tx[n], ty[n];
ofPoint p[n];			//Cloud's points positions

float time0 = 0;		//Time value, used for dt computing

//--------------------------------------------------------------
void ofApp::setup(){
    
    //image.loadImage( "image/gCircle.jpg" );	//Load image
    
    //image.loadImage( "image/monroe2.jpg" );
    
    image.loadImage( "image/mouse.jpg" );
    image2.clone( image );
    ofSetWindowShape(image.getWidth()/2, image.getHeight()/2);
				
    //////////////
    sound.loadSound( "music/uto.mp3" );
    //sound.loadSound( "music/mouse.wav" );

    //sound.loadSound( "4B.mp3" );

    sound.setLoop( true );
    sound.play();
    
    
    for (int i=0; i<N; i++) {
        spectrum[i] = 0.0f;
    }//Copy image to image2
}

//--------------------------------------------------------------
void ofApp::update(){
 
    
    /////////////////////////////////////////////////
    float time = ofGetElapsedTimef();
    
    //Build image2 using image
    for (int y=0; y<image.height; y++) {
        for (int x=0; x<image.width; x++) {
            //Use y and time for computing shifted x1
            float sinAmp = sin(spectrum[0] * 30)*0.05;
            float cosAmp = tanf(spectrum[1] * 200)*0.05;
            float cosAmp2 = tanf(spectrum[2] * 200)*0.05;

            float amp = sin( y * sinAmp );
            float amp2 = cos( x * cosAmp );
            int x1 = x + sin(10)*25*amp;
            int y1 = y + cos(20 )*25*amp2;
            
            //Clamp x1 to range [0, image.width-1]
            x1 = ofClamp( x1, 0, image.width - 1 );
              y1 = ofClamp( y1, 0, image.height - 1 );
            
            //Set image2(x, y) equal to image(x1, y)
            ofColor color = image.getColor( x1, y1 );
            image2.setColor( x, y, color );
        }
    }
    image2.update();
    ////////////////////////////////////////////////////
    ofSoundUpdate();
    
    
    float *val = ofSoundGetSpectrum( N );
    
    for ( int i=0; i<N; i++ ) {
        spectrum[i] *= 0.9599;	//Slow decreasing
        spectrum[i] = max( spectrum[i], val[i] );
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    /////////////////////////////////////////////
    ofBackground( 255, 255, 255 );
    ofSetColor( 255, 255, 255 );
    //ofScale(4.0, 4.0);
    image2.draw( 0, 0 );
    ///////////////////////////////////////////////
    
    ofSetColor( mouseX/4, 230, 230 );
    ofFill();
    //	ofRect( 10, 700, N * 6, -100 );
    
    //Draw spectrum
    ofSetColor( 23, 0, 0 );
    for (int i=0; i<N; i++) {
        //Draw bandRad and bandVel by black color,
        //and other by gray color
        if ( i == bandRad || i == bandVel ) {
            ofSetColor( 0, 0, 0 ); //Black color
        }
        else {
            ofSetColor( 128, 128, 128 ); //Gray color
        }
        ofRect( 10 + i * 5, 700, 5, -spectrum[i] * 200 );
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}