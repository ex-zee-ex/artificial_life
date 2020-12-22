precision highp float;

uniform float qq;

uniform float osc0_feedback_filter;

uniform sampler2D tex0;

uniform sampler2D cam1;

uniform sampler2D osc1_mod;

varying vec2 texCoordVarying;

uniform float osc0_r_offset;
uniform float osc0_g_offset;
uniform float osc0_b_offset;
uniform float osc0_powmod;

uniform float osc0_rm;
uniform float osc0_pm;
uniform float osc0_rate;
uniform float osc0_frequency;
uniform float osc0_amp;
uniform float osc0_angle;

uniform int osc0_shape;

uniform float osc0_m_rm;
uniform float osc0_m_pm;
uniform float osc0_m_rate;
uniform float osc0_m_frequency;
uniform float osc0_m_amp;
uniform float osc0_m_angle;

uniform int osc0_m_shape;

uniform float width;
uniform float height;

uniform float pm_weight;

uniform float osc0_spiral;
uniform float osc0_rotate;
uniform float osc0_modulation_rotate;

uniform float osc0_m_spiral;
uniform float osc0_m_rotate;
uniform float osc0_m_modulation_rotate;

uniform float osc0_cam1_pm;

uniform int osc0_overflow_switch;

uniform float osc0_cutoff;

uniform float osc0_m_cam1_pm;

//lets make everything from 0-1 here for now
float oscillate(float theta,int shape,int xyz){
    float osc=0.0;
    
    if(shape==0){
        osc=(sin(theta)+1.0)*.5;
    }
    
    //squarewave..can add a dc offset for pwm too?
    if(shape==1){
        osc=sign(sin(theta));
    }
    
    
    //haha tanwave
    //osc=tan(theta);
    
    //sawtooth??
    if(shape==2){
        osc=fract(theta/6.18);
    }
    
    /*
     if(shape==3){
     //0 is x, 1 is y, 2 is z
     if(xyz==0){
     osc=texture2DRect(x_noise_image,texCoordVarying*.5).r-.5;
     }
     
     if(xyz==1){
     osc=texture2DRect(y_noise_image,texCoordVarying*.5).r-.5;
     }
     
     if(xyz==2){
     osc=texture2DRect(z_noise_image,texCoordVarying*.5).r-.5;
     }
     }
     */
    
    
    return osc;
    
}

vec2 rotate(vec2 coord,float theta){
    vec2 center_coord=vec2(coord.x-.5,coord.y-.5);
    vec2 rotate_coord=vec2(0.0,0.0);
    float spiral=abs(coord.x+coord.y)/2.0*width;
    coord.x=spiral+coord.x;
    coord.y=spiral+coord.y;
    rotate_coord.x=center_coord.x*cos(theta)-center_coord.y*sin(theta);
    rotate_coord.y=center_coord.x*sin(theta)+center_coord.y*cos(theta);
    
    
    rotate_coord=rotate_coord+vec2(.5,.5);
    
    return rotate_coord;
    
    
}//endrotate


void main()
{
	
	vec4 color=vec4(0.0,0.0,0.0,1.0);
    
    //vec4 osc_mod_1=texture2D(osc1_mod,texCoordVarying);
    
    vec4 osc_mod_1=texture2D(tex0,texCoordVarying+vec2(.0025,.0025));
    
    vec4 cam1_color=texture2D(cam1,fract(texCoordVarying+vec2(.005,.005)));
    
    float om1_bright=.299*osc_mod_1.r+.587*osc_mod_1.g+.114*osc_mod_1.b;
    /*
    vec2 axis=rotate(texCoordVarying, osc0_angle);
    
    float osc0_arg=osc0_rate+axis.x*(osc0_frequency+osc0_pm*om1_bright);

    color.rgb=(osc0_amp+osc0_rm*om1_bright)*vec3(oscillate(osc0_arg+,0,0));
    */
    
    
    vec2 m_axis=vec2(0.0,0.0);
    
    
    float osc0_spiral_new=osc0_spiral*distance(texCoordVarying, vec2(.5,.5));
    
    float osc0_m_spiral_new=osc0_m_spiral*distance(texCoordVarying, vec2(.5,.5));
    
    vec2 axis=osc0_spiral_new+rotate(texCoordVarying, osc0_angle+osc0_rotate
    +osc0_modulation_rotate*oscillate(
		osc0_m_cam1_pm*cam1_color.g+osc0_m_rate+
		osc0_m_spiral_new+(rotate(texCoordVarying, osc0_m_angle+osc0_m_rotate
		+osc0_m_modulation_rotate*oscillate(
			osc0_rate+rotate(texCoordVarying, osc0_angle).x*(osc0_frequency),osc0_shape,0)
		).x+.01)*(osc0_m_frequency+.1*osc0_m_pm*oscillate(osc0_rate+rotate(texCoordVarying, osc0_angle+osc0_spiral_new+osc0_rotate).x*(osc0_frequency)+
	osc0_m_cam1_pm*cam1_color.g,osc0_shape,0)),osc0_m_shape,0));
    
    //+rotate(texCoordVarying, osc0_m_angle+osc0_m_spiral*distance(texCoordVarying, vec(.5,.5))+osc0_m_rotate+osc0_m_modulation_rotate*oscillate(osc0_rate+rotate(texCoordVarying, osc0_angle).x*(osc0_frequency),osc0_shape,0)).x*(osc0_m_frequency),osc0_m_shape,0));
	
	m_axis=osc0_m_spiral_new+rotate(texCoordVarying, osc0_m_angle+osc0_m_rotate
	+osc0_m_modulation_rotate*oscillate(osc0_rate+rotate(texCoordVarying, osc0_angle+osc0_spiral_new+osc0_rotate).x*(osc0_frequency)+
	osc0_m_cam1_pm*cam1_color.g,osc0_shape,0)
	);
	
    float osc0_m_arg=osc0_m_rate+(m_axis.x+.01)*(osc0_m_frequency+.1*osc0_m_pm*om1_bright);
    
    float osc0_m=osc0_m_amp*oscillate(osc0_m_arg+osc0_m_cam1_pm*cam1_color.g,osc0_m_shape,0);
    
    
    
    
    //try out this new filter thing
   
    
    float clampit=clamp(om1_bright-osc0_cutoff,0.0,1.0);
    
    
    float filtered=om1_bright*(1.0-clampit)+.5*clampit;
    
    //filtered=om1_bright;
    
    
    
    float osc0_arg=osc0_rate+axis.x*(osc0_frequency+osc0_m_pm*osc0_m+osc0_pm*filtered);


	float filtered_rm=om1_bright*om1_bright;
	
	color.rgb=(osc0_amp+osc0_rm*filtered_rm+osc0_m_rm*osc0_m)*vec3(oscillate(osc0_arg+cam1_color.g*osc0_cam1_pm,osc0_shape,0));
	
	
	if(osc0_overflow_switch==1){
        //color.rgb=2.0*fract(color.rgb*.5);
        
        color.rgb=fract(color.rgb);
    }
    
    if(osc0_overflow_switch==2){
        if(color.r>1.0){
            color.rgb=vec3((1.0-fract(color.r)));
        }
    }
    
    if(osc0_overflow_switch==3){
        if(color.r>1.0){
            color.rgb=vec3(fract(color.r-tan(color.r*.25+osc0_arg)));
        }
    }
	
	
	color.r=color.r+osc0_r_offset;
	color.g=color.g+osc0_g_offset;
	color.b=color.b+osc0_b_offset;
	
	if(osc0_shape==1){
		color.rgb=clamp(color.rgb,vec3(0.0),vec3(1.0));
	}
	
	color.rgb=pow(color.rgb,vec3(1.0+osc0_powmod));
	
	
	
	color.rgb=mix(color.rgb,cam1_color.rgb,osc0_feedback_filter);
	
	gl_FragColor = color;
	
	//gl_FragColor = osc_mod_1;
	
	
}
