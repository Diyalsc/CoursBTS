#include "ofApp.h"

ofColor ofApp::filter(ofColor color, int effectp, float p) {
	float r = color.r;
	float g = color.g;
	float b = color.b;
	float luminance = 0.299f * r + 0.587f * g + 0.114f * b;

	if (effectp == 1) {
		ofColor inversedColor = ofColor(255 - r, 255 - g, 255 - b);
		return inversedColor;
	} else if (effectp == 2) {
		float gray = (r + b + g) / 3.0f;
		ofColor grayColor = ofColor(gray, gray, gray);
		return grayColor;
	} else if (effectp == 3) {
		ofColor greyColor = ofColor(luminance, luminance, luminance);
		return greyColor;
		
	} else if (effectp == 4) {
		float k = (p - 0.5f) * 256;
		int newR = ofClamp(r + k, 0, 255);
		int newG = ofClamp(g + k, 0, 255);
		int newB = ofClamp(b + k, 0, 255);
		ofColor brightnessColor = ofColor(newR, newG, newB);
		return brightnessColor;
	} else if (effectp == 5) {
		int newR = ofClamp(0.393 * r + 0.769 * g + 0.189 * b, 0, 255);
		int newG = ofClamp(0.349 * r + 0.686 * g + 0.168 * b, 0, 255);
		int newB = ofClamp(0.272 * r + 0.534 * g + 0.131 * b, 0, 255);
		ofColor sepiaColor = ofColor(newR, newG, newB);
		return sepiaColor;
	}
	else {
		return color;
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(1200, 610);
	bool loadingOk = imgSource.load("V.jpg");
	if (!loadingOk) {
		ofLogError() << "Image non trouvée";
	}
	imgResult.allocate(imgSource.getWidth(), imgSource.getHeight(), OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
	/* int px = ofClamp(mouseX, 0, imgSource.getWidth() - 1);
	int py = ofClamp(mouseY, 0, imgSource.getHeight() - 1);*/

	float power = mouseX / (float)ofGetWidth();

	for (int y = 0; y < imgSource.getHeight(); y++) {
		for (int x = 0; x < imgSource.getWidth(); x++) {
			ofColor transferColor = imgSource.getColor(x, y);
			ofColor modifiedColor = filter(transferColor, effect, power );
			imgResult.setColor(x, y, modifiedColor);
		}
	}
	currentColor = imgSource.getColor(mouseX, mouseY);
	imgResult.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	imgSource.draw(0, 0);
	imgResult.draw(0, 0);

	ofSetColor(currentColor);
	ofDrawRectangle(mouseX + 10, mouseY + 10, 20, 20);
	;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_RIGHT){
		effect++;
	}	
	if (key == OF_KEY_LEFT) {
		effect--;
		/* if (effect < 0) {		//Si effect est strictement inferieur a 0 Alors

			effect = nbEffects - 1; //effect prendra le nombre effect - 1 
		}*/
	}
	effect = (effect + nbEffects ) % nbEffects;
	if (key == OF_MOUSE_BUTTON_1) {
		effect = 0;
	}
	if (key == OF_MOUSE_BUTTON_2) {
		effect = 1;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
