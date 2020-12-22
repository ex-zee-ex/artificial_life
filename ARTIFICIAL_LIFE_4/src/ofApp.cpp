/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */
#include "ofApp.h"

#include "iostream"

//0 is picaputre, 1 is usbinput
bool inputswitch=1;

bool internal_feedback_switch0=0;
bool internal_feedback_switch1=0;

int hdmi_aspect_ratio_switch=0;

float sx=1;
float ff=1.01;
float xw=1.01;
float yw=1.01;
float jj=1.01;
float kk=1.01;
float ll=1;
float tt=1;

float theta=0;



float c1=0.0;
float c2=0.0;
float c3=0.0;
float c4=0.0;
float c5=0.0;
float c6=0.0;
float c7=0.0;
float c8=0.0;
float c9=0.0;
float c10=0.0;
float c11=0.0;
float c12=0.0;
float c13=0.0;
float c14=0.0;
float c15=.0;
float c16=.0;


//keyboard controls
//probbly shift all of these to a gui
float ss=1;
float dd=1;

float gg=1;
float hh=0;

float ee=1;
float pp=1;
float ii=.01;



bool osc0_mod_switch=0;
int osc0_axis_switch=0;

int osc0_shape=0;

float osc0_spiral=0;
float osc0_rotate=0;
float osc0_modulation_rotate=0;

float osc0_rate=.1;
float osc0_rate_adder=.01;
float osc0_angle=0;
float osc0_frequency=.1;
float osc0_amp=1;
float osc0_rm=0;
float osc0_pm=0;

int osc0_m_shape=0;

float osc0_m_spiral=0;
float osc0_m_rotate=0;
float osc0_m_modulation_rotate=0;

float osc0_m_rate=.1;
float osc0_m_rate_adder=.01;
float osc0_m_angle=0;
float osc0_m_frequency=.1;
float osc0_m_amp=1;
float osc0_m_rm=0;
float osc0_m_pm=0;



bool osc1_mod_switch=0;
int osc1_axis_switch=0;

int osc1_shape=0;

float osc1_spiral=0;
float osc1_rotate=0;
float osc1_modulation_rotate=0;

float osc1_rate=.1;
float osc1_rate_adder=.01;
float osc1_angle=0;
float osc1_frequency=.1;
float osc1_amp=1;
float osc1_rm=0;
float osc1_pm=0;

int osc1_m_shape=0;

float osc1_m_spiral=0;
float osc1_m_rotate=0;
float osc1_m_modulation_rotate=0;

float osc1_m_rate=.1;
float osc1_m_rate_adder=.01;
float osc1_m_angle=0;
float osc1_m_frequency=.1;
float osc1_m_amp=1;
float osc1_m_rm=0;
float osc1_m_pm=0;
bool draw_switch=0;

int overflow_switch=0;

int small_width=320;
int small_height=240;

bool res_switch=0;


//new switches to organize later
int osc_m_rate_switch=0;

float osc0_rate_mod=0;
float osc1_rate_mod=0;

float osc0_m_rate_mod=0;
float osc1_m_rate_mod=0;

float osc0_cam_pm=0;
float osc1_cam_pm=0;

float osc0_rotate_adder=0;
float osc0_m_rotate_adder=0;


float osc1_rotate_adder=0;
float osc1_m_rotate_adder=0;


int osc0_pm_rm_switch=0;

int osc1_pm_rm_switch=0;

bool osc_cam_pm_switch=0;

int osc_rgbp_switch=0;
//p_lock biz
//maximum total size of the plock array
const int p_lock_size=240;

bool p_lock_record_switch=0;

bool p_lock_erase=0;

//maximum number of p_locks available...maybe there can be one for every knob
//for whatever wacky reason the last member of this array of arrays has a glitch
//so i guess just make an extra array and forget about it for now
const int p_lock_number=52;

//so how we will organize the p_locks is in multidimensional arrays
//to access the data at timestep x for p_lock 2 (remember counting from 0) we use p_lock[2][x]
float p_lock[p_lock_number][p_lock_size];


//smoothing parameters(i think for all of these we can array both the arrays and the floats
//for now let us just try 1 smoothing parameter for everything.
float p_lock_smooth=.5;


//and then lets try an array of floats for storing the smoothed values
float p_lock_smoothed[p_lock_number];


//turn on and off writing to the array
bool p_lock_0_switch=1;

//global counter for all the locks
int p_lock_increment=0;

float qq=0;

ofFbo aspect_fix_fbo;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	
	//this clamps the frame rate at 30fps
	//most usb cameras only work at 30 or 60
	//but it might be hard to get anything complex
	//to run at 60fps without framedropping or insconsistent
	//frame rates
	ofSetFrameRate(30);
    
    //this makes the background black
    ofBackground(0);
   
	//run this to hide the mouse cursor on the screen
    ofHideCursor();
	
		
	
	//shader_mixer.load("shadersES2/shader_mixer");
	
	
	
	// print input ports to console
	midiIn.listInPorts();
	
	// open port by number (you may need to change this)
	midiIn.openPort(1);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
	
	
	//shadersbiz
    shader_osc0.load("shadersES2/shader_osc0");
    shader_osc1.load("shadersES2/shader_osc1");
    //shader_blur.load("shadersGL2/shader_blur");
    
    
    
    if(res_switch==0){
			small_width=320;
			small_height=240;
	}
	
	if(res_switch==1){
			small_width=640;
			small_height=480;
	}
    
    fb_osc0.allocate(small_width,small_height);
    fb_osc0.begin();
    ofClear(0,0,0,255);
    fb_osc0.end();
    
    fb_osc1.allocate(small_width,small_height);
    fb_osc1.begin();
    ofClear(0,0,0,255);
    fb_osc1.end();
    
    fb_osc0_pp.allocate(small_width,small_height);
    fb_osc0_pp.begin();
    ofClear(0,0,0,255);
    fb_osc0_pp.end();
    
    fb_osc1_pp.allocate(small_width,small_height);
    fb_osc1.begin();
    ofClear(0,0,0,255);
    fb_osc1_pp.end();
    
    omx_settings();  
    
    
    aspect_fix_fbo.allocate(small_width,small_height);
    aspect_fix_fbo.begin();
    ofClear(0,0,0,255);
    aspect_fix_fbo.end();
    
    //pass in the settings and it will start the camera
	if(inputswitch==0){
		videoGrabber.setup(settings);
	}

	
	if(inputswitch==1){
		cam1.setDesiredFrameRate(30);
		cam1.initGrabber(640,480);
	}
    
    
    
    //do some initializing
    for(int i=0;i<p_lock_size;i++){
		p_lock[1][i]=.5;
		p_lock[8][i]=1.0;
		
		p_lock[17][i]=.5;
		p_lock[24][i]=1.0;
		
		p_lock[4][i]=.5;
		p_lock[11][i]=1.0;
		
		p_lock[20][i]=.5;
		p_lock[27][i]=1.0;
	}
    
}

//--------------------------------------------------------------
void ofApp::update() {
	
	midibiz();
	
	if(inputswitch==1){
		cam1.update();
		
		if(hdmi_aspect_ratio_switch==1){
			aspect_fix_fbo.begin();
			cam1.draw(0,0,426,240);
			aspect_fix_fbo.end();
			
		}
		
	}
	
	if(inputswitch==0){
		
		omx_updates();
		
	}
	
	
	//p-lock biz
	for(int i=0;i<p_lock_number;i++){
        p_lock_smoothed[i]=p_lock[i][p_lock_increment]*(1.0f-p_lock_smooth)+p_lock_smoothed[i]*p_lock_smooth;
        
        if(abs(p_lock_smoothed[i])<.001){p_lock_smoothed[i]=0;}
        
        
    }
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	float osc0_pm_scale=5;
	float osc0_rm_scale=5;
	float osc0_cutoff=.5;
	
	
	
	if(osc0_pm_rm_switch==0){
		osc0_pm_scale=5;
		osc0_rm_scale=5;
		osc0_cutoff=.75;
	}
		
	if(osc0_pm_rm_switch==1){
		osc0_pm_scale=10;
		osc0_rm_scale=10;
		osc0_cutoff=.5;
	}
	
	if(osc0_pm_rm_switch==2){
		osc0_pm_scale=20;
		osc0_rm_scale=10;
		osc0_cutoff=.15;
	}
	
	if(osc0_pm_rm_switch==3){
		osc0_pm_scale=50;
		osc0_rm_scale=10;
		osc0_cutoff=.05;
	}
	
	
	float osc1_pm_scale=5;
	float osc1_rm_scale=5;
	float osc1_cutoff=.5;
	
	if(osc1_pm_rm_switch==0){
		osc1_pm_scale=5;
		osc1_cutoff=.75;
	}
		
	if(osc1_pm_rm_switch==1){
		osc1_pm_scale=10;
		osc1_cutoff=.5;
	}
	
	
	if(osc1_pm_rm_switch==2){
		osc1_pm_scale=20;
		osc1_cutoff=.25;
	}
	
	if(osc1_pm_rm_switch==3){
		osc1_pm_scale=50;
		osc1_cutoff=.15;
	}
	ofSetColor(255);

	float osc_pm_scale=5;
    
    //float osc_pm_scale=10;
    
    float osc_rm_scale=5;
    
    float osc_frequency_scale=50.0;
    
    
    float osc_rate_scale=.15;
   
    
    float angle_scale=3.14;
    
    float modulation_rotate_scale=10.0;
    
    float spiral_scale=ofGetWidth()*.0075f;
    
    float cam_pm_scale=20.0;
    
    float osc_rate_mod_scale=.15;
    
    float osc_rotate_scale=.01;
    //osc1
    
    fb_osc0.begin();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    shader_osc0.begin();
    
    
    
    
    //pass the textures
    fb_osc1_pp.draw(0,0);
    
    if(internal_feedback_switch0==0){
		if(inputswitch==1){
			
			
			if(hdmi_aspect_ratio_switch==0){
				shader_osc0.setUniformTexture("cam1", cam1.getTexture(),2);
			}
			
			if(hdmi_aspect_ratio_switch==1){
				shader_osc0.setUniformTexture("cam1", aspect_fix_fbo.getTexture(),2);
			}
		}
    
		if(inputswitch==0){
			
		
			shader_osc0.setUniformTexture("cam1", videoGrabber.getTextureReference(),2);
				
		}
    }
    
    if(internal_feedback_switch0==1){
		shader_osc0.setUniformTexture("cam1", fb_osc0_pp.getTexture(),1);
    }
    
    
    //plock_block
    osc0_rate+=osc_rate_scale*p_lock_smoothed[0]+sin(osc1_rate)*p_lock_smoothed[7]*osc_rate_mod_scale;
    osc0_m_rate+=osc_rate_scale*p_lock_smoothed[16]+sin(osc1_m_rate)*p_lock_smoothed[23]*osc_rate_mod_scale;
    
    osc0_rotate+=osc_rotate_scale*p_lock_smoothed[33];
    
    osc0_m_rotate+=osc_rotate_scale*p_lock_smoothed[39];
    
    shader_osc0.setUniform1f("osc0_rate",osc0_rate);
    shader_osc0.setUniform1f("osc0_amp",p_lock_smoothed[8]);
    shader_osc0.setUniform1f("osc0_frequency",p_lock_smoothed[1]*osc_frequency_scale);
    shader_osc0.setUniform1f("osc0_angle",p_lock_smoothed[9]*angle_scale);
    shader_osc0.setUniform1f("osc0_rm",osc0_rm_scale*p_lock_smoothed[2]);
    shader_osc0.setUniform1f("osc0_pm",osc0_pm_scale*p_lock_smoothed[10]);
    
    shader_osc0.setUniform1f("osc0_rotate",fmod(osc0_rotate,2.0f*PI)); 
    shader_osc0.setUniform1f("osc0_spiral",p_lock_smoothed[32]*spiral_scale);
    shader_osc0.setUniform1f("osc0_modulation_rotate",p_lock_smoothed[34]*modulation_rotate_scale);
    
    shader_osc0.setUniform1f("osc0_m_rate",osc0_m_rate);
    shader_osc0.setUniform1f("osc0_m_amp",p_lock_smoothed[24]);
    shader_osc0.setUniform1f("osc0_m_frequency",p_lock_smoothed[17]*osc_frequency_scale);
    shader_osc0.setUniform1f("osc0_m_angle",p_lock_smoothed[25]*angle_scale);
    shader_osc0.setUniform1f("osc0_m_rm",10*p_lock_smoothed[18]);
    shader_osc0.setUniform1f("osc0_m_pm",100*p_lock_smoothed[26]);
    
    shader_osc0.setUniform1f("osc0_m_rotate",fmod(osc0_m_rotate,2.0f*PI));
    shader_osc0.setUniform1f("osc0_m_spiral",p_lock_smoothed[38]*spiral_scale);
    shader_osc0.setUniform1f("osc0_m_modulation_rotate",p_lock_smoothed[40]*modulation_rotate_scale);
    
    shader_osc0.setUniform1f("osc0_cam1_pm",p_lock_smoothed[6]*cam_pm_scale);
    
    shader_osc0.setUniform1f("osc0_m_cam1_pm",p_lock_smoothed[22]*cam_pm_scale);
    
    shader_osc0.setUniform1f("osc0_feedback_filter",p_lock_smoothed[6]*.75);
    
    //filtercutoffs
    shader_osc0.setUniform1f("osc0_cutoff",osc0_cutoff);
    
    //nonplocked_block
    
    
    
    
    
    
    shader_osc0.setUniform1i("osc0_shape",osc0_shape);
    
   
    
    
    
    
    
    
   
    
    
    shader_osc0.setUniform1i("osc0_m_shape",osc0_m_shape);
    
    
    
    shader_osc0.setUniform1f("width",ofGetWidth());
    shader_osc0.setUniform1f("height",ofGetHeight());
    
    shader_osc0.setUniform1i("osc0_overflow_switch",overflow_switch);
    
    //shader_osc0.setUniformTexture("cam1", cam1.getTexture(),1);
    
    
    shader_osc0.setUniform1f("osc0_r_offset",p_lock_smoothed[44]);
    shader_osc0.setUniform1f("osc0_g_offset",p_lock_smoothed[45]);
    shader_osc0.setUniform1f("osc0_b_offset",p_lock_smoothed[46]);
    
    float osc0_powmod_adjust=p_lock_smoothed[47];
    if(osc0_powmod_adjust>0.0f){
		osc0_powmod_adjust=ofMap(osc0_powmod_adjust,0.0f,1.0f,0.0f,8.0f);
	}
	
	 if(osc0_powmod_adjust<0.0f){
		osc0_powmod_adjust=ofMap(osc0_powmod_adjust,-1.0f,.0f,-.25f,0.0f);
	}
    
    shader_osc0.setUniform1f("osc0_powmod",osc0_powmod_adjust);
    
    //cout<<p_lock_smoothed[44]<<endl;
    
    
    shader_osc0.setUniform1f("qq",qq);
    
    shader_osc0.end();
  
    fb_osc0.end();
    
   
    
    //osc2
    
    fb_osc1.begin();
 
    
    
    shader_osc1.begin();
    
   
    fb_osc0_pp.draw(0,0);
    
   
    
    
    if(internal_feedback_switch1==0){
		if(inputswitch==1){
			
			
			if(hdmi_aspect_ratio_switch==0){
				shader_osc1.setUniformTexture("cam1", cam1.getTexture(),2);
			}
			
			if(hdmi_aspect_ratio_switch==1){
				shader_osc1.setUniformTexture("cam1", aspect_fix_fbo.getTexture(),2);
			}
		}
    
		if(inputswitch==0){
			shader_osc1.setUniformTexture("cam1", videoGrabber.getTextureReference(),2);
				
		}
    }
    
    if(internal_feedback_switch1==1){
		shader_osc1.setUniformTexture("cam1", fb_osc1_pp.getTextureReference(),1);
    }
   
   
   //p_lock_block
   
	osc1_rate+=osc_rate_scale*p_lock_smoothed[3]+sin(osc0_rate)*p_lock_smoothed[15]*osc_rate_mod_scale;
    osc1_m_rate+=osc_rate_scale*p_lock_smoothed[19]+sin(osc0_m_rate)*p_lock_smoothed[31]*osc_rate_mod_scale;
    
    osc1_rotate+=osc_rotate_scale*p_lock_smoothed[36];
    osc1_m_rotate+=osc_rotate_scale*p_lock_smoothed[42];
    
    shader_osc1.setUniform1f("osc1_rate",osc1_rate);
    shader_osc1.setUniform1f("osc1_amp",p_lock_smoothed[11]);
    shader_osc1.setUniform1f("osc1_frequency",p_lock_smoothed[4]*osc_frequency_scale);
    shader_osc1.setUniform1f("osc1_angle",p_lock_smoothed[12]*angle_scale);
    shader_osc1.setUniform1f("osc1_rm",osc1_rm_scale*p_lock_smoothed[5]);
    shader_osc1.setUniform1f("osc1_pm",osc1_pm_scale*p_lock_smoothed[13]);
    
    shader_osc1.setUniform1f("osc1_rotate",fmod(osc1_rotate,2.0f*PI));
    shader_osc1.setUniform1f("osc1_spiral",p_lock_smoothed[35]*spiral_scale);
    shader_osc1.setUniform1f("osc1_modulation_rotate",p_lock_smoothed[37]*modulation_rotate_scale);
    
    shader_osc1.setUniform1f("osc1_m_rate",osc1_m_rate);
    shader_osc1.setUniform1f("osc1_m_amp",p_lock_smoothed[27]);
    shader_osc1.setUniform1f("osc1_m_frequency",p_lock_smoothed[20]*osc_frequency_scale);
    shader_osc1.setUniform1f("osc1_m_angle",p_lock_smoothed[28]*angle_scale);
    shader_osc1.setUniform1f("osc1_m_rm",10*p_lock_smoothed[21]);
    shader_osc1.setUniform1f("osc1_m_pm",100*p_lock_smoothed[29]);
   
   
	shader_osc1.setUniform1f("osc1_cam1_pm",p_lock_smoothed[14]*cam_pm_scale);
	
	shader_osc1.setUniform1f("osc1_m_cam1_pm",p_lock_smoothed[30]*cam_pm_scale);
	
	shader_osc1.setUniform1f("osc1_m_rotate",fmod(osc1_m_rotate,2.0f*PI));
	shader_osc1.setUniform1f("osc1_m_spiral",p_lock_smoothed[41]*spiral_scale);
    shader_osc1.setUniform1f("osc1_m_modulation_rotate",p_lock_smoothed[43]*modulation_rotate_scale);
   
    shader_osc1.setUniform1f("osc1_feedback_filter",p_lock_smoothed[14]*.75);
   
   
   
   //non_p_locked
	
    
    
    shader_osc1.setUniform1i("osc1_shape",osc1_shape);
    
    
    
    

    shader_osc1.setUniform1i("osc1_m_shape",osc1_m_shape);
    
    shader_osc1.setUniform1f("osc1_cutoff",osc1_cutoff);
    
    
    
    shader_osc1.setUniform1f("width",ofGetWidth());
    shader_osc1.setUniform1f("height",ofGetHeight());
    
    shader_osc1.setUniform1i("osc1_overflow_switch",overflow_switch);
    
    //shader_osc1.setUniformTexture("cam1", cam1.getTexture(),1);
    
    
    shader_osc1.setUniform1f("osc1_r_offset",p_lock_smoothed[48]);
    shader_osc1.setUniform1f("osc1_g_offset",p_lock_smoothed[49]);
    shader_osc1.setUniform1f("osc1_b_offset",p_lock_smoothed[50]);
    
    float osc1_powmod_adjust=p_lock_smoothed[51];
    if(osc1_powmod_adjust>0.0f){
		osc1_powmod_adjust=ofMap(osc1_powmod_adjust,0.0f,1.0f,0.0f,8.0f);
	}
	
	 if(osc1_powmod_adjust<0.0f){
		osc1_powmod_adjust=ofMap(osc1_powmod_adjust,-1.0f,.0f,-.25f,0.0f);
	}
    
    shader_osc1.setUniform1f("osc1_powmod",osc1_powmod_adjust);
    
    shader_osc1.end();
    
    fb_osc1.end();
    
    
    
    
    //fb_osc1.draw(0,0);
    //shader_blur.begin();
   // shader_blur.setUniform1f("blurAmnt",10*c7);
    if(draw_switch==0){
        // fb_osc1.draw(0,0,ofGetWidth()/4,ofGetHeight()/4);
        fb_osc0.draw(0,0,720,480);
        
    }
    
    if(draw_switch==1){
       // fb_osc1.draw(0,0,ofGetWidth()/4,ofGetHeight()/4);
        fb_osc1.draw(0,0,720,480);
        
    }
    
    
   // shader_blur.end();
    
    
    //cam1.draw(0,0,80,60);
    
    //don't actually need all of these buffers around, can instead
    //just feed the fb direct into each one and then clear the buffer in between each feedback draw
    
    
    fb_osc0_pp.begin();
    fb_osc0.draw(0,0);
    fb_osc0_pp.end();
    
    fb_osc0.begin();
    ofClear(0,0,0,255);
    fb_osc0.end();
    
    fb_osc1_pp.begin();
    fb_osc1.draw(0,0);
    fb_osc1_pp.end();
    
    fb_osc1.begin();
    ofClear(0,0,0,255);
    fb_osc1.end();

    
    ofSetColor(255,255,0);
    string msg="fps="+ofToString(ofGetFrameRate(),2)+"blend amount= "+ofToString(qq,2);//+" clear switch"+ofToString(clear_switch,5);//+" z="+ofToString(az,5);
    ofDrawBitmapString(msg,10,10);
    
    
    
    
     if(p_lock_record_switch==1){
        p_lock_increment++;
        p_lock_increment=p_lock_increment%p_lock_size;
    }
    
}

//--------------------------------------------------------------
void ofApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}


void ofApp::omx_settings(){
	
	settings.sensorWidth = 640;
    settings.sensorHeight = 480;
    settings.framerate = 30;
    settings.enableTexture = true;
    settings.sensorMode=7;
    
    settings.whiteBalance ="Off";
    settings.exposurePreset ="Off";
    settings.whiteBalanceGainR = 1.0;
    settings.whiteBalanceGainB = 1.0;
	
	}
//------------------------------------------------------------

void ofApp::omx_updates(){
	
		videoGrabber.setSharpness(50);
		videoGrabber.setBrightness(40);
		videoGrabber.setContrast(100);
		videoGrabber.setSaturation(0);
	
	}
//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while(midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(key=='q'){qq+=.01;}
	if(key=='w'){qq-=.01;}
	
	
	//if(key=='1'){draw_switch=!draw_switch;}
	
	//if(key=='2'){internal_feedback_switch0=!internal_feedback_switch0;}
	
	//if(key=='2'){internal_feedback_switch1=!internal_feedback_switch1;}
	
	if(key=='1'){osc0_pm_rm_switch=0; osc1_pm_rm_switch=0;}
	
	if(key=='2'){osc0_pm_rm_switch=1; osc1_pm_rm_switch=1;}
	
	if(key=='3'){osc0_pm_rm_switch=2; osc1_pm_rm_switch=2;}
	
	if(key=='4'){osc0_pm_rm_switch=3; osc1_pm_rm_switch=3;}
        
        
    if(key=='0'){
		 osc0_axis_switch=0;

		osc0_shape=0;

		osc0_spiral=0;
		osc0_rotate=0;
		osc0_modulation_rotate=0;

		osc0_rate=.1;
		osc0_rate_adder=.01;
		osc0_angle=0;
		osc0_frequency=.1;
		osc0_amp=1;
		osc0_rm=0;
		osc0_pm=0;

		osc0_m_shape=0;

		osc0_m_spiral=0;
		osc0_m_rotate=0;
		osc0_m_modulation_rotate=0;

		osc0_m_rate=.1;
		osc0_m_rate_adder=.01;
		osc0_m_angle=0;
		osc0_m_frequency=.1;
		osc0_m_amp=1;
		osc0_m_rm=0;
		osc0_m_pm=0;



		
		osc1_axis_switch=0;

		osc1_shape=0;

		osc1_spiral=0;
		osc1_rotate=0;
		osc1_modulation_rotate=0;

		osc1_rate=.1;
		osc1_rate_adder=.01;
		osc1_angle=0;
		osc1_frequency=.1;
		osc1_amp=1;
		osc1_rm=0;
		osc1_pm=0;

		osc1_m_shape=0;

		osc1_m_spiral=0;
		osc1_m_rotate=0;
		osc1_m_modulation_rotate=0;

		osc1_m_rate=.1;
		osc1_m_rate_adder=.01;
		osc1_m_angle=0;
		osc1_m_frequency=.1;
		osc1_m_amp=1;
		osc1_m_rm=0;
		osc1_m_pm=0;
		

		

		
		

	    osc0_rate_mod=0;
		osc1_rate_mod=0;

		osc0_m_rate_mod=0;
		osc1_m_rate_mod=0;
		
		osc0_cam_pm=0;
		osc1_cam_pm=0;
		
		}    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	
	
	
}

//--------------------------------------------------------------
//---------------------
void ofApp:: midibiz(){
    
    for(unsigned int i = 0; i < midiMessages.size(); ++i) {
        
        ofxMidiMessage &message = midiMessages[i];
        
        
        //cout << "envcount="<< envcount<< endl;
        
        if(message.status < MIDI_SYSEX) {
            //text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {
                //  cout << "message.control"<< message.control<< endl;
                //  cout << "message.value"<< message.value<< endl;
                
                if(message.control==45){
					if(message.value==127){
						p_lock_record_switch=1;
						
						
						for(int i=0;i<p_lock_number;i++){
								p_lock_smoothed[i]=0;
								for(int j=0;j<p_lock_size;j++){
                                
									p_lock[i][j]=p_lock[i][p_lock_increment];
                                
								}//endplocksize
                            
							}//endplocknumber
						
					}
					
					
					if(message.value==0){
						p_lock_record_switch=0;
					}
				}
                
                
                
                
                //swap cam input pm for internal feedback pm
                
                if(message.control==43){
                    if(message.value==127){
                        internal_feedback_switch0=1;
                       
                    }
                    
                    if(message.value==0){
                        internal_feedback_switch0=0;
                        
                    }
                }
                
                
                if(message.control==44){
                    if(message.value==127){
                        internal_feedback_switch1=1;
                    }
                    
                    if(message.value==0){
                        internal_feedback_switch1=0;
                    }
                }
                
                
                //osc rgbp switches
                
                if(message.control==38){
                    if(message.value==127){
                        osc_rgbp_switch=1;
                    }
                    
                    if(message.value==0){
                        osc_rgbp_switch=0;
                    }
                }
                
                if(message.control==54){
                    if(message.value==127){
                        osc_rgbp_switch=2;
                    }
                    
                    if(message.value==0){
                        osc_rgbp_switch=0;
                    }
                }
                
                if(message.control==70){
                    if(message.value==127){
                        osc_rgbp_switch=3;
                    }
                    
                    if(message.value==0){
                        osc_rgbp_switch=0;
                    }
                }
                
                //rm/pm scaling switches
                
               
                
				//osc0	
                 if(message.control==34){
                    if(message.value==127){
                         osc0_pm_rm_switch=1;
                    }
                    
                    if(message.value==0){
                         osc0_pm_rm_switch=0;
                    }
                }
                
                if(message.control==50){
                    if(message.value==127){
                         osc0_pm_rm_switch=2;
                    }
                    
                    if(message.value==0){
                         osc0_pm_rm_switch=0;
                    }
                }
                
                 if(message.control==66){
                    if(message.value==127){
                         osc0_pm_rm_switch=3;
                    }
                    
                    if(message.value==0){
                         osc0_pm_rm_switch=0;
                    }
                }
                
                //osc1	
                 if(message.control==37){
                    if(message.value==127){
                         osc1_pm_rm_switch=1;
                    }
                    
                    if(message.value==0){
                         osc1_pm_rm_switch=0;
                    }
                }
                
                if(message.control==53){
                    if(message.value==127){
                         osc1_pm_rm_switch=2;
                    }
                    
                    if(message.value==0){
                         osc1_pm_rm_switch=0;
                    }
                }
                
                 if(message.control==69){
                    if(message.value==127){
                         osc1_pm_rm_switch=3;
                    }
                    
                    if(message.value==0){
                         osc1_pm_rm_switch=0;
                    }
                }
                
                
                
                //overflow switches
                if(message.control==60){
                    if(message.value==127){
                        overflow_switch=1;
                    }
                    
                    if(message.value==0){
                        overflow_switch=0;
                    }
                }
                
                if(message.control==61){
                    if(message.value==127){
                        overflow_switch=2;
                    }
                    
                    if(message.value==0){
                        overflow_switch=0;
                    }
                }
                
                if(message.control==62){
					
                    if(message.value==127){
                         hdmi_aspect_ratio_switch=1;
                        //overflow_switch=3;
                    }
                    
                    if(message.value==0){
						hdmi_aspect_ratio_switch=0;
                        //overflow_switch=0;
                    }
                }

                
                
                
                if(message.control==46){
                    if(message.value==127){
                        draw_switch=1;
                    }
                    
                    if(message.value==0){
                        draw_switch=0;
                    }
                }
                
                
                if(message.control==32){
                    if(message.value==127){
                        osc0_mod_switch=1;
                        
                    }
                    
                    if(message.value==0){
                        osc0_mod_switch=0;
                        
                    }
                }
                
                if(message.control==35){
                    if(message.value==127){
                        osc1_mod_switch=1;
                        
                    }
                    
                    if(message.value==0){
                        osc1_mod_switch=0;
                        
                    }
                }
                
                
                
                //osc0 axis switches
                if(message.control==33){
                    if(message.value==127){
                        osc0_axis_switch=1;
                        
                    }
                    
                    if(message.value==0){
                       osc0_axis_switch=0;
                        
                    }
                }
                
                if(message.control==49){
                    if(message.value==127){
                        osc0_axis_switch=2;
                        
                    }
                    
                    if(message.value==0){
                        osc0_axis_switch=0;
                        
                    }
                }
                
                if(message.control==65){
                    if(message.value==127){
                        osc0_axis_switch=3;
                        
                    }
                    
                    if(message.value==0){
                        osc0_axis_switch=0;
                        
                    }
                }
                
                //osc1_m axis switches
                if(message.control==36){
                    if(message.value==127){
                        osc1_axis_switch=1;
                        
                        
                    }
                    
                    if(message.value==0){
                        osc1_axis_switch=0;
                        
                    }
                }
                
                if(message.control==52){
                    if(message.value==127){
                        osc1_axis_switch=2;
                        
                    }
                    
                    if(message.value==0){
                        osc1_axis_switch=0;
                        
                    }
                }
                
                if(message.control==68){
                    if(message.value==127){
                        osc1_axis_switch=3;
                        //cout<<"YOOOOO"<<endl;
                        
                    }
                    
                    if(message.value==0){
                        osc1_axis_switch=0;
                        
                    }
                }
                
                
                //shapes
                
                //osc0
                if(message.control==48){
                    if(osc0_mod_switch==0){
                        if(message.value==127){
                            osc0_shape=1;
                        
                        }
                    
                        if(message.value==0){
                            osc0_shape=0;
                        
                        }
                    }
                    
                    if(osc0_mod_switch==1){
                        if(message.value==127){
                            osc0_m_shape=1;
                            
                        }
                        
                        if(message.value==0){
                            osc0_m_shape=0;
                            
                        }
                    }
                }
                
                if(message.control==64){
                    if(osc0_mod_switch==0){
                        if(message.value==127){
                            osc0_shape=2;
                            
                        }
                        
                        if(message.value==0){
                            osc0_shape=0;
                            
                        }
                    }
                    
                    if(osc0_mod_switch==1){
                        if(message.value==127){
                            osc0_m_shape=2;
                            
                        }
                        
                        if(message.value==0){
                            osc0_m_shape=0;
                            
                        }
                    }
                }
                
                //osc1
                if(message.control==51){
                    if(osc1_mod_switch==0){
                        if(message.value==127){
                            osc1_shape=1;
                            
                        }
                        
                        if(message.value==0){
                            osc1_shape=0;
                            
                        }
                    }
                    
                    if(osc1_mod_switch==1){
                        if(message.value==127){
                            osc1_m_shape=1;
                            
                        }
                        
                        if(message.value==0){
                            osc1_m_shape=0;
                            
                        }
                    }
                }
                
                if(message.control==67){
                    if(osc1_mod_switch==0){
                        if(message.value==127){
                            osc1_shape=2;
                            
                        }
                        
                        if(message.value==0){
                            osc1_shape=0;
                            
                        }
                    }
                    
                    if(osc1_mod_switch==1){
                        if(message.value==127){
                            osc1_m_shape=2;
                            
                        }
                        
                        if(message.value==0){
                            osc1_m_shape=0;
                            
                        }
                    }
                }

				//osc_rate_swithce //cam pm switches
				
				if(message.control==39){
					if(message.value==127){
						osc_m_rate_switch=1;
					}
					if(message.value==0){
						osc_m_rate_switch=0;
					}
				}
                
                if(message.control==55){
					if(message.value==127){
						osc_m_rate_switch=2;
					}
					if(message.value==0){
						osc_m_rate_switch=0;
					}
				}
				
				  if(message.control==71){
					if(message.value==127){
						osc_m_rate_switch=3;
					}
					if(message.value==0){
						osc_m_rate_switch=0;
					}
				}
                
                //nanokontrol2 controls
                if(message.control==16){

                    if(osc0_mod_switch==0){
                        p_lock[0][p_lock_increment]=(message.value-63.0)/63.0;

                    }
                    
                    if(osc0_mod_switch==1){
                        p_lock[16][p_lock_increment]=(message.value-63.0)/63.0;
                       
                    }
                    
                }
                
                
               
                
                if(message.control==17){
                   
                    if(osc0_mod_switch==0){
                      
                        
                        p_lock[1][p_lock_increment]=(message.value)/127.00;
                    }
                    
                    if(osc0_mod_switch==1){
                    
                        
                        p_lock[17][p_lock_increment]=(message.value)/127.00;
                      

                    }
                }
                
                
                if(message.control==18){
                   
                    if(osc0_mod_switch==0){
						
						p_lock[2][p_lock_increment]=(message.value-63.0)/63.00;
                       
                    }
                    
                    if(osc0_mod_switch==1){
						
						p_lock[18][p_lock_increment]=(message.value-63.0)/63.00;
                       
                       

                    }
                }
                
                
                if(message.control==19){
                   
                    if(osc1_mod_switch==0){
                       
                        
                        p_lock[3][p_lock_increment]=(message.value-63.0)/63.00;
                        
                    }
                    
                    if(osc1_mod_switch==1){
                        p_lock[19][p_lock_increment]=(message.value-63.0)/63.00;
                    }
                }
                
                
                if(message.control==20){
                 
                    if(osc1_mod_switch==0){
                       p_lock[4][p_lock_increment]=(message.value)/127.00;
                    }
                    if(osc1_mod_switch==1){
                       p_lock[20][p_lock_increment]=(message.value)/127.00;
                    }
                }
                
                
                if(message.control==21){
                   
                    if(osc1_mod_switch==0){
                       
                        
                        p_lock[5][p_lock_increment]=(message.value-63.0)/63.00;
                    }
                    
                    if(osc1_mod_switch==1){
                      
                        
                        p_lock[21][p_lock_increment]=(message.value-63.0)/63.00;
                    }
                }
                
                
                if(message.control==22){
                 
                    if(osc_rgbp_switch==0){
						p_lock[44][p_lock_increment]=(message.value-63.0f)/63.0f;
                    }
                    
                    if(osc_rgbp_switch==1){
						p_lock[45][p_lock_increment]=(message.value-63.0f)/63.0f;
                    }
                    
                    if(osc_rgbp_switch==2){
						p_lock[46][p_lock_increment]=(message.value-63.0f)/63.0f;
                    }
                    
                    if(osc_rgbp_switch==3){
						p_lock[47][p_lock_increment]=(message.value-63.0f)/63.0f;
                    }
                    
                    
                }
                
                
                if(message.control==23){
					if(osc_m_rate_switch==0){
						
						
						p_lock[7][p_lock_increment]=(message.value-63.0)/63.00;
                    }
                    if(osc_m_rate_switch==1){
						
						
						p_lock[23][p_lock_increment]=(message.value-63.0)/63.00;
                    }
                    
                    if(osc_m_rate_switch==2){
						
						
						p_lock[6][p_lock_increment]=(message.value)/127.00;
						
					
                    }
                    if(osc_m_rate_switch==3){
						
						
						p_lock[22][p_lock_increment]=(message.value)/127.00;
						
                    }
                    //osc0_rate_mod=(message.value)/127.0;
                    
                }
                
                if(message.control==120){
                  
                    if(osc0_mod_switch==0){
                        p_lock[8][p_lock_increment]=(message.value)/127.00;
                   }
                    
                    if(osc0_mod_switch==1){
                   
                        p_lock[24][p_lock_increment]=(message.value)/127.0f;
                    }
                    
                    
                    
                }
                
                if(message.control==121){
                    
                    if(osc0_axis_switch==0){
                        if(osc0_mod_switch==0){
                          
                            
                            p_lock[9][p_lock_increment]=(message.value)/127.0;
                        }
                    
                        if(osc0_mod_switch==1){
                           
                            
                            p_lock[25][p_lock_increment]=(message.value)/127.0;
                        }
                    }
                    
                    if(osc0_axis_switch==1){
                        if(osc0_mod_switch==0){
                            osc0_spiral=.05*(message.value)/127.0;
                            
                            p_lock[32][p_lock_increment]=(message.value)/127.0;
                        }
                        
                        if(osc0_mod_switch==1){
                            p_lock[38][p_lock_increment]=(message.value)/127.0;
                        }
                    }
                    
                    if(osc0_axis_switch==2){
                        if(osc0_mod_switch==0){
                            p_lock[33][p_lock_increment]=(message.value-63.0)/63.0;
                        }
                        
                        if(osc0_mod_switch==1){
                            p_lock[39][p_lock_increment]=(message.value-63.0)/63.0;
                        }
                    }
                    
                    if(osc0_axis_switch==3){
                        if(osc0_mod_switch==0){
                            //osc0_modulation_rotate=(message.value-63.0)/63.0;
                            
                            p_lock[34][p_lock_increment]=(message.value)/127.0;
                            
                        }
                        
                        if(osc0_mod_switch==1){
                            //osc0_m_modulation_rotate=(message.value-63.0)/63.0;
                            
                            p_lock[40][p_lock_increment]=(message.value)/127.0;
                        }
                        
                    }
                }
                
                if(message.control==122){
                    //c11=(message.value-63.0)/63.00;
                    c11=(message.value)/127.00;
                    if(osc0_mod_switch==0){
                        osc0_pm=(message.value)/127.00;
                        
                        p_lock[10][p_lock_increment]=(message.value)/127.00;
                        
                        //osc0_pm=(message.value-63.0)/63.0;
                    }
                    
                    if(osc0_mod_switch==1){
                        osc0_m_pm=(message.value)/127.00;
                        
                        p_lock[26][p_lock_increment]=(message.value)/127.00;
                    }
                }
                
                
                if(message.control==123){
                    // c12=(message.value-63.0)/63.00;
                    c12=(message.value)/127.00;
                    if(osc1_mod_switch==0){
                        osc1_amp=(message.value)/127.00;
                        
                        p_lock[11][p_lock_increment]=(message.value)/127.00;
                    }
                    
                    if(osc1_mod_switch==1){
                        osc1_m_amp=(message.value)/127.00;
                        
                       p_lock[27][p_lock_increment]=(message.value)/127.00;
                    }
                }
                
               
                
                if(message.control==124){
                    c10=(message.value-63.0)/63.0;
                    //c10=(message.value)/127.00;
                    if(osc1_axis_switch==0){
                        if(osc1_mod_switch==0){
                            osc1_angle=(message.value-63.0)/63.0;
                            
                            p_lock[12][p_lock_increment]=(message.value-63.0f)/63.0f;
                            
                        }
                        
                        if(osc1_mod_switch==1){
                            osc1_m_angle=(message.value-63.0)/63.0;
                            
                            p_lock[28][p_lock_increment]=(message.value-63.0f)/63.0f;
                            

                        }
                    }
                    
                    if(osc1_axis_switch==1){
                        if(osc1_mod_switch==0){
                            p_lock[35][p_lock_increment]=(message.value)/127.0;
                           
                        }
                        
                        if(osc1_mod_switch==1){
                            //osc1_m_spiral=.05*(message.value-63.0)/63.0;
                            p_lock[41][p_lock_increment]=(message.value)/127.0;
                        }
                    }
                    
                    if(osc1_axis_switch==2){
                        if(osc1_mod_switch==0){
                            p_lock[36][p_lock_increment]=(message.value-63.0)/63.0;
                        }
                        
                        if(osc1_mod_switch==1){
                            p_lock[42][p_lock_increment]=(message.value-63.0)/63.0;
                        }
                    }
                    
                    if(osc1_axis_switch==3){
                        if(osc1_mod_switch==0){
                            p_lock[37][p_lock_increment]=(message.value)/127.0;
                        }
                        
                        if(osc1_mod_switch==1){
                            p_lock[43][p_lock_increment]=(message.value)/127.0;
                        }
                        
                    }
                    
                    
                }
                
                if(message.control==125){
                   // c14=(message.value-63.0)/63.0;
                    c14=(message.value)/127.00;
                    if(osc1_mod_switch==0){
                        osc1_pm=(message.value)/127.00;
                        
                        p_lock[13][p_lock_increment]=(message.value)/127.00;
                         //osc1_pm=(message.value-63.0)/63.0;
                    }
                    
                    if(osc1_mod_switch==1){
                        osc1_m_pm=(message.value)/127.00;
                        
                        p_lock[29][p_lock_increment]=(message.value)/127.00;
                        //osc1_pm=(message.value-63.0)/63.0;
                    }
                }
                
                if(message.control==126){
					
                    if(osc_rgbp_switch==0){
						p_lock[48][p_lock_increment]=(message.value-63.0f)/63.0f;
                    }
                    
                    if(osc_rgbp_switch==1){
						p_lock[49][p_lock_increment]=(message.value-63.0f)/63.0f;
                    }
                    
                    if(osc_rgbp_switch==2){
						p_lock[50][p_lock_increment]=(message.value-63.0f)/63.0f;
                    }
                    
                    if(osc_rgbp_switch==3){
						p_lock[51][p_lock_increment]=(message.value-63.0f)/63.0f;
                    }
                    
                    
                    
                }
                
                if(message.control==127){
                   if(osc_m_rate_switch==0){
						osc1_rate_mod=(message.value-63.0)/63.00;
						
						p_lock[15][p_lock_increment]=(message.value-63.0)/63.00;
                    }
                    if(osc_m_rate_switch==1){
						osc1_m_rate_mod=(message.value-63.0)/63.00;
						
						p_lock[31][p_lock_increment]=(message.value-63.0)/63.00;
                    }
                    
                    if(osc_m_rate_switch==2){
						p_lock[14][p_lock_increment]=(message.value)/127.00;
						
                    }
                    if(osc_m_rate_switch==3){
						p_lock[30][p_lock_increment]=(message.value)/127.00;
                    }
                    
                }
                
                
               
                
               

                
                
				if(message.control==58){
					if(message.value==127){
						for(int i=0;i<p_lock_number;i++){
							for(int j=0;j<p_lock_size;j++){
								p_lock[i][j]=0;
								
								p_lock[1][j]=.5;
								p_lock[8][j]=1.0;
						
								p_lock[17][j]=.5;
								p_lock[24][j]=1.0;
						
								p_lock[4][j]=.5;
								p_lock[11][j]=1.0;
						
								p_lock[20][j]=.5;
								p_lock[27][j]=1.0;
							}
							
							
						}
											
						//do some initializing
						
					}	
				}
              
                
                //text << "\tctl: " << message.control;
                //ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
                //	ofMap(message.control, 0, 127, 0, ofGetWidth()*0.2), 10);
            }
            
            
            //text << " "; // pad for delta print
        }//
        
        
    }
    
    
    /******* endmidimessagesbiz*********/
    
    
}
