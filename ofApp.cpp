#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");
	
	ofBackground(239);

	ofTrueTypeFontSettings font_settings("fonts/EmojiSymbols-Regular.ttf", 30);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Emoji);
	this->font.load(font_settings);

	// Initialize ofxBox2d
	this->box2d.init();
	this->box2d.setGravity(0, 5);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();

	this->eage_1 = ofxBox2dEdge();
	this->eage_1.addVertex(ofGetWidth() / 2 - 150, ofGetHeight() / 2 + 100);
	this->eage_1.addVertex(ofGetWidth() / 2, ofGetHeight() / 2);
	this->eage_1.create(this->box2d.getWorld());

	this->eage_2 = ofxBox2dEdge();
	this->eage_2.addVertex(ofGetWidth() / 2 + 150, ofGetHeight() / 2 + 100);
	this->eage_2.addVertex(ofGetWidth() / 2, ofGetHeight() / 2);
	this->eage_2.create(this->box2d.getWorld());
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 10 == 0) {

		float radius = 15;
		auto circle = make_shared<ofxBox2dCircle>();
		circle->setPhysics(1.0, 0.63, 0.1);
		circle->setup(this->box2d.getWorld(), ofRandom(ofGetWidth() * 0.5 - 50, ofGetWidth() * 0.5 + 50), 15, radius);
		this->circles.push_back(circle);

		ofColor circle_color;
		circle_color.setHsb(ofRandom(255), 255, 239);
		this->circles_color.push_back(circle_color);

		vector<string> emojis = { u8"😁", u8"😍", u8"😂", u8"😱", u8"😎" };
		this->words.push_back(emojis[(int)ofRandom(emojis.size())]);
	}

	this->box2d.update();
}	

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->circles.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->circles[i]->getPosition().x, this->circles[i]->getPosition().y);
		ofRotate(this->circles[i]->getRotation());

		ofSetColor(this->circles_color[i]);
		this->font.drawString(this->words[i], -15, 15);

		ofPopMatrix();
	}

	ofSetColor(39);
	this->eage_1.draw();
	this->eage_2.draw();
}

//========================================================================
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}