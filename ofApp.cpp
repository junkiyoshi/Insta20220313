#include "ofApp.h"	


//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->font_size = 120;

	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	
	string word = "TWIST";
	auto word_size = glm::vec2(this->font.stringWidth(word), this->font.stringHeight(word));

	auto char_path_list = this->font.getStringAsPoints(word, true, false);
	int sample_count = 120;

	for (int z = 0; z < 200; z += 10) {

		for (int char_index = 0; char_index < char_path_list.size(); char_index++) {

			vector<ofPolyline> outline = char_path_list[char_index].getOutline();

			ofFill();
			ofSetColor(0);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(word_size.x * 0.5, word_size.y * -0.5, z);
					auto angle = ofMap(ofNoise(abs(location.x) * 0.001 + ofGetFrameNum() * 0.02 - z * 0.005), 0, 1, -PI * 1, PI * 1);
					auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 0, 1));
					location = glm::vec4(location, 0) * rotation;

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(255);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(word_size.x * 0.5, word_size.y * -0.5, z);
					auto angle = ofMap(ofNoise(abs(location.x) * 0.001 + ofGetFrameNum() * 0.02 - z * 0.005), 0, 1, -PI * 1, PI * 1);
					auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 0, 1));
					location = glm::vec4(location, 0) * rotation;

					ofVertex(location);
				}
			}
			ofEndShape(true);
		}
	}
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}