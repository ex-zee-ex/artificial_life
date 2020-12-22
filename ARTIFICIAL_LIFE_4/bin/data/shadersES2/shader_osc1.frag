precision highp float;


uniform sampler2D tex0;

uniform sampler2D cam1;

uniform sampler2D osc0_mod;

varying vec2 texCoordVarying;

uniform float osc1_feedback_filter;

uniform float osc1_r_offset;
uniform float osc1_g_offset;
uniform float osc1_b_offset;
uniform float osc1_powmod;


uniform float osc1_rm;
uniform float osc1_pm;
uniform float osc1_rate;
uniform float osc1_frequency;
uniform float osc1_amp;
uniform float osc1_angle;

uniform int osc1_shape;

uniform float osc1_m_rm;
uniform float osc1_m_pm;
uniform float osc1_m_rate;
uniform float osc1_m_frequency;
uniform float osc1_m_amp;
uniform float osc1_m_angle;

uniform int osc1_m_shape;

uniform float width;
uniform float height;

uniform float pm_weight;

uniform float osc1_spiral;
uniform float osc1_rotate;
uniform float osc1_modulation_rotate;

uniform float osc1_m_spiral;
uniform float osc1_m_rotate;
uniform float osc1_m_modulation_rotate;

uniform float osc1_cam1_pm;

uniform int osc1_overflow_switch;


uniform float osc1_m_cam1_pm;

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
    
    vec4 mod_osc=texture2D(tex0,texCoordVarying+vec2(.0025,.0025));
    
    float om_bright=.299*mod_osc.r+.587*mod_osc.g+.114*mod_osc.b;
    
    vec4 cam1_color=texture2D(cam1,fract(texCoordVarying+vec2(.005,.005)));
    /*
    vec2 axis=rotate(texCoordVarying, osc1_angle);
    
    float osc1_arg=osc1_rate+axis.x*(osc1_frequency+osc1_pm*om_bright);

    color.rgb=(osc1_amp+osc1_rm*om_bright)*vec3(oscillate(osc1_arg+,0,0));
    */
    
    
    vec2 m_axis=vec2(0.0,0.0);
    
    float osc1_spiral_new=osc1_spiral*distance(texCoordVarying, vec2(.5,.5));
    
    float osc1_m_spiral_new=osc1_m_spiral*distance(texCoordVarying, vec2(.5,.5));
    
    
    vec2 axis=osc1_spiral_new+rotate(texCoordVarying, osc1_angle+osc1_rotate
    +osc1_modulation_rotate*oscillate(osc1_m_cam1_pm*cam1_color.g+osc1_m_rate+
	+osc1_m_spiral_new+(rotate(texCoordVarying, osc1_m_angle+osc1_m_rotate
    +osc1_m_modulation_rotate*oscillate(osc1_rate+rotate(texCoordVarying, osc1_angle).y*(osc1_frequency),osc1_shape,0)
    ).y+.01)*(osc1_m_frequency+.1*osc1_m_pm*oscillate(osc1_rate+osc1_spiral_new+rotate(texCoordVarying, osc1_angle+osc1_rotate).y*(osc1_frequency),osc1_shape,0)
    ),osc1_m_shape,0));
    
    //+rotate(texCoordVarying, osc1_m_angle+osc1_m_spiral*distance(texCoordVarying, vec(.5,.5))+osc1_m_rotate+osc1_m_modulation_rotate*oscillate(osc1_rate+rotate(texCoordVarying, osc1_angle).x*(osc1_frequency),osc1_shape,0)).x*(osc1_m_frequency),osc1_m_shape,0));
	
	m_axis=osc1_m_spiral_new+rotate(texCoordVarying, osc1_m_angle+osc1_m_rotate
	+osc1_m_modulation_rotate*oscillate(osc1_rate+osc1_spiral_new+rotate(texCoordVarying, osc1_angle+osc1_rotate).y*(osc1_frequency),osc1_shape,0)
	);//+osc1_m_modulation_rotate*oscillate(osc1_rate+rotate(texCoordVarying, +osc1_spiral*distance(texCoordVarying, vec2(.5,.5))+osc1_rotate).x*(osc1_frequency),osc1_shape,0));
    
    float osc1_m_arg=osc1_m_rate+(m_axis.y+.01)*(osc1_m_frequency+.1*osc1_m_pm*oscillate(osc1_rate+osc1_spiral_new+rotate(texCoordVarying, osc1_angle+osc1_rotate).y*(osc1_frequency),osc1_shape,0));
    
    float osc1_m=osc1_m_amp*oscillate(osc1_m_arg+osc1_m_cam1_pm*cam1_color.g,osc1_m_shape,0);
    
    
    
    
    
    
    
    float cutoff=.25;
    
    float clampit=clamp(om_bright-cutoff,0.0,1.0);
    
    
    
    float filtered=om_bright*(1.0-clampit)+.5*clampit;
    
    //filtered=om_bright;
    
    
    float osc1_arg=osc1_rate+axis.y*(osc1_frequency+osc1_m_pm*osc1_m+osc1_pm*filtered);

	float filtered_rm=om_bright*om_bright;
	
	color.rgb=(osc1_amp+osc1_rm*filtered_rm+osc1_m_rm*osc1_m)*vec3(oscillate(osc1_arg+cam1_color.g*osc1_cam1_pm,osc1_shape,0));
	
	
	if(osc1_overflow_switch==1){
        //color.rgb=2.0*fract(color.rgb*.5);
        
        color.rgb=fract(color.rgb);
    }
    
    if(osc1_overflow_switch==2){
        if(color.r>1.0){
            color.rgb=vec3((1.0-fract(color.r)));
        }
    }
    
    if(osc1_overflow_switch==3){
        if(color.r>1.0){
            color.rgb=vec3(fract(color.r-tan(color.r*.25+osc1_arg)));
        }
    }
    
    
    
    color.r=color.r+osc1_r_offset;
	color.g=color.g+osc1_g_offset;
	color.b=color.b+osc1_b_offset;
	
	if(osc1_shape==1){
		color.rgb=clamp(color.rgb,vec3(0.0),vec3(1.0));
	}
	
	color.rgb=pow(color.rgb,vec3(1.0+osc1_powmod));
	
	color.rgb=mix(color.rgb,cam1_color.rgb,osc1_feedback_filter);
	
	gl_FragColor = color;
	
	
}
