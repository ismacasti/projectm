//video_init.c - SDL/Opengl Windowing Creation/Resizing Functions
//
//by Peter Sperl
//
//Opens an SDL Window and creates an OpenGL session
//also able to handle resizing and fullscreening of windows
//just call init_display again with differant variables

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

extern SDL_Surface *screen;
extern int texsize;
void setup_opengl( int w, int h );
//init_display
//
//Sets screen to new width and height (w,h)
//Also switches between fullscreen and windowed
//with the boolean f (fullscreen)
void init_display(int w, int h, int f)
{
  
  /* Information about the current video settings. */
  const SDL_VideoInfo* info = NULL;
  int bpp = 0;
  /* Flags we will pass into SDL_SetVideoMode. */
  int flags = 0;
  /* First, initialize SDL's video subsystem. */
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    /* Failed, exit. */
    printf( stderr, "Video initialization failed: %s\n",
             SDL_GetError( ) );
    //projectM_vtable.disable_plugin (&projectM_vtable);
    return;
    
  }
  /* Let's get some video information. */
  info = SDL_GetVideoInfo( );
  if( !info ) {
    /* This should probably never happen. */
    printf( stderr, "Video query failed: %s\n",
             SDL_GetError( ) );
    //    projectM_vtable.disable_plugin (&projectM_vtable);
    return;
  }
  
  bpp = info->vfmt->BitsPerPixel;
  
  //SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
  //SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
  //SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );

  // SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 8 );
  //  SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 8 );
  //  SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 8 );
  // SDL_GL_SetAttribute( SDL_GL_APLHA_SIZE, 8 );
  //SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  if (f==0)
     flags = SDL_OPENGL|SDL_HWSURFACE|SDL_RESIZABLE;
  else flags = SDL_OPENGL|SDL_HWSURFACE|SDL_FULLSCREEN;

  screen= SDL_SetVideoMode( w, h, bpp, flags ) ;

  if(screen == 0 ) {
    /* 
     * This could happen for a variety of reasons,
     * including DISPLAY not being set, the specified
     * resolution not being available, etc.
     */
   printf( stderr, "Video mode set failed: %s\n",
	     SDL_GetError( ) );
    
   // projectM_vtable.disable_plugin (&projectM_vtable);
    return;
    
  }
  
  
  setup_opengl(w,h);
  //gluOrtho2D(0, w, 0, h);
}


 void setup_opengl( int w, int h )
{
   
    /* Our shading model--Gouraud (smooth). */
     glShadeModel( GL_SMOOTH);
    /* Culling. */
    //    glCullFace( GL_BACK );
    //    glFrontFace( GL_CCW );
    //    glEnable( GL_CULL_FACE );
    /* Set the clear color. */
    glClearColor( 0, 0, 0, 0 );
    /* Setup our viewport. */
     glViewport( 0, 0, w, h );
    /*
     * Change to the projection matrix and set
     * our viewing volume.
     */
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    //    gluOrtho2D(0.0, (GLfloat) width, 0.0, (GLfloat) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
   
    //    glFrustum(0.0, height, 0.0,width,10,40);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

glDrawBuffer(GL_BACK); 
  glReadBuffer(GL_BACK); 
  glEnable(GL_BLEND); 

     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
     // glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
 
  // glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB,0,0,texsize,texsize,0);
  //glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0,texsize,texsize);
   glLineStipple(2, 0xAAAA);
  
    
}
#if 0
void CreateRenderTarget(int texsize,int *RenderTargetTextureID, int *RenderTarget )
{
    /* Create the texture that will be bound to the render target */
    glGenTextures(1, RenderTargetTextureID);
    glBindTexture(GL_TEXTURE_2D, *RenderTargetTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    /* Create the render target */
    *RenderTarget = SDL_GL_CreateRenderTarget(texsize,texsize, NULL);
        if ( *RenderTarget ) {
    
	int value;
	//printf("Created render target:\n");
	SDL_GL_GetRenderTargetAttribute( *RenderTarget, SDL_GL_RED_SIZE, &value );
	//	printf( "SDL_GL_RED_SIZE: %d\n", value);
	SDL_GL_GetRenderTargetAttribute( *RenderTarget, SDL_GL_GREEN_SIZE, &value );
	//	printf( "SDL_GL_GREEN_SIZE: %d\n", value);
	SDL_GL_GetRenderTargetAttribute( *RenderTarget, SDL_GL_BLUE_SIZE, &value );
	//	printf( "SDL_GL_BLUE_SIZE: %d\n", value);
	SDL_GL_GetRenderTargetAttribute( *RenderTarget, SDL_GL_ALPHA_SIZE, &value );
	//	printf( "SDL_GL_ALPHA_SIZE: %d\n", value);
	SDL_GL_GetRenderTargetAttribute( *RenderTarget, SDL_GL_DEPTH_SIZE, &value );
	//	printf( "SDL_GL_DEPTH_SIZE: %d\n", value );

	SDL_GL_BindRenderTarget(*RenderTarget, *RenderTargetTextureID);
       
    } else {
        /* We can fake a render target in this demo by rendering to the
         * screen and copying to a texture before we do normal rendering.
         */
	printf("Failed to create render target, using screen buffer\n");

        glBindTexture(GL_TEXTURE_2D, *RenderTargetTextureID);
        glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGB,
			texsize, texsize,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			NULL);
    }


}
#endif