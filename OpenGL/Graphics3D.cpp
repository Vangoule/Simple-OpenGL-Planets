#include <GL/glew.h>
#include "Graphics3D.h"
#include "Globals.h"
#include "shader.hpp"

#define ILUT_USE_OPENGL	// This MUST be defined before calling the DevIL headers or we don't get OpenGL functionality
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include "Model.h"

#include "heightfield.h"
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
HeightField hf;
//HeightField hf2[5];

GLuint programID;
GLuint TextureID;
GLuint MatrixID;
GLuint boolCubeMapID;
GLuint cubeMapTextureID;

GLuint lightShader;
GLuint lightMatrixID;
GLuint lightTextureID1;
GLuint lightModelMatrixID;
GLuint lightViewMatrixID;
GLuint lightLightID;

GLuint terrainShader;
GLuint terrainMatrixID;
GLuint terrainTextureID1;
GLuint terrainTextureID2;
GLuint terrainTextureID3;
GLuint terrainTextureID4;
GLuint terrainTextureID5;
GLuint terrainTextureID6;
GLuint terrainTextureID7;
GLuint terrainModelMatrixID;
GLuint terrainViewMatrixID;
GLuint terrainLightID;
GLuint terrainTimeID;
GLuint VertexArrayID;

GLuint vertexbuffer;
GLuint uvbuffer;



glm::mat4 Projection;
glm::mat4 View ;
glm::mat4 MVP;

Graphics3D::Graphics3D(void)
{
}

glm::mat4 Graphics3D::getProjection()
{
	return Projection;
}

glm::mat4 Graphics3D::getView()
{
	return View;
}

GLuint Graphics3D::getTextureID()
{
	return TextureID;
}


GLuint Graphics3D::getMatrixID()
{
	return MatrixID;
}

GLuint Graphics3D::getCubeMapTextureID()
{
	return cubeMapTextureID;
}

GLuint Graphics3D::getBoolCubeMapID()
{
	return boolCubeMapID;
}

GLuint Graphics3D::getVertexBuffer()
{
	return vertexbuffer;
}

GLuint Graphics3D::getUvBuffer()
{
	return uvbuffer;
}

GLuint Graphics3D::getLightTextureID()
{
	 return lightTextureID1; 

}

GLuint Graphics3D::getLightLightID()
{
	return lightLightID;
}
GLuint Graphics3D::getLightMatrixID()
{
	return lightMatrixID;
}
GLuint Graphics3D::getLightModelMatrixID()
{
	return lightModelMatrixID;
}
GLuint Graphics3D::getLightViewMatrixID()
{
	return lightViewMatrixID;
}

GLuint Graphics3D::getTerrainTextureID(int id)
{
	if(id == 1){ return terrainTextureID1; }
	else if(id == 2){return terrainTextureID2;}
	else if(id == 3){return terrainTextureID3;}
	else if(id == 4){return terrainTextureID4;}
	else if(id == 5){return terrainTextureID5;}
	else if(id == 6){return terrainTextureID6;}
	else if(id == 7){return terrainTextureID7;}
}

GLuint Graphics3D::getTerrainLightID()
{
	return terrainLightID;
}
GLuint Graphics3D::getTerrainTimeID()
{
	return terrainTimeID;
}
GLuint Graphics3D::getTerrainMatrixID()
{
	return terrainMatrixID;
}
GLuint Graphics3D::getTerrainModelMatrixID()
{
	return terrainModelMatrixID;
}
GLuint Graphics3D::getTerrainViewMatrixID()
{
	return terrainViewMatrixID;
}



GLenum  cube[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                     GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                     GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                     GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                     GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                     GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

GLuint Graphics3D::loadCubeMapTexture(const char* theFileName[6])
{
	ILuint imageID;				// Create an image ID as a ULuint
 
	GLuint textureID;			// Create a texture ID as a GLuint
 
	ILboolean success;			// Create a flag to keep track of success/failure
 
	ILenum error;				// Create a flag to keep track of the IL error state
 
	ilGenImages(1, &imageID); 		// Generate the image ID
 
	ilBindImage(imageID); 			// Bind the image
 
	 	// Load the image file
 
		std::cout << "TextureCreating" << std::endl;
		// Generate a new texture
		glGenTextures(1, &textureID);
 
		// Bind the texture to a name
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);      
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);     
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		for(int i = 0; i < 6; i++)
        {      

		success = ilLoadImage(theFileName[i]);
		// If managed to load the image, then start to do things with it...
		if (success)
		{
			// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
			ILinfo ImageInfo;
			iluGetImageInfo(&ImageInfo);
			if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
			{
				iluFlipImage();
			}
 
			success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		// Specify the texture specification
		glTexImage2D(cube[i], 				// Type of texture
					 0,				// Pyramid level (for mip-mapping) - 0 is the top level
					 ilGetInteger(IL_IMAGE_BPP),	// Image colour depth
					 ilGetInteger(IL_IMAGE_WIDTH),	// Image width
					 ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
					 0,				// Border width in pixels (can either be 1 or 0)
					 ilGetInteger(IL_IMAGE_FORMAT),	// Image format (i.e. RGB, RGBA, BGR etc.)
					 GL_UNSIGNED_BYTE,		// Image data type
					 ilGetData());			// The actual image data itself
		  }	else 
  			{
				error = ilGetError();
				std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		
  			}
 
	 }
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
 	ilDeleteImages(1, &imageID); 
 
	std::cout << "Texture creation successful." << std::endl;
 
	return textureID; 

 }


GLuint Graphics3D::loadTexture(const char* theFileName)
{
	ILuint imageID;				// Create an image ID as a ULuint
 
	GLuint textureID;			// Create a texture ID as a GLuint
 
	ILboolean success;			// Create a flag to keep track of success/failure
 
	ILenum error;				// Create a flag to keep track of the IL error state
 
	ilGenImages(1, &imageID); 		// Generate the image ID
 
	ilBindImage(imageID); 			// Bind the image
 
	success = ilLoadImage(theFileName); 	// Load the image file
 
	// If managed to load the image, then start to do things with it...
	if (success)
	{
		// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}
 
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
 
		//if failed the conversion
		if (!success)
		{
			error = ilGetError();
			std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		}
 
		// Generate a new texture
		glGenTextures(1, &textureID);
 
		// Bind the texture to a name
		glBindTexture(GL_TEXTURE_2D, textureID);

				// Specify the texture specification
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
					 0,				// Pyramid level (for mip-mapping) - 0 is the top level
					 ilGetInteger(IL_IMAGE_BPP),	// Image colour depth
					 ilGetInteger(IL_IMAGE_WIDTH),	// Image width
					 ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
					 0,				// Border width in pixels (can either be 1 or 0)
					 ilGetInteger(IL_IMAGE_FORMAT),	// Image format (i.e. RGB, RGBA, BGR etc.)
					 GL_UNSIGNED_BYTE,		// Image data type
					 ilGetData());			// The actual image data itself
 /*
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
		*/
		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		if(GLEW_EXT_texture_filter_anisotropic)
		{
			GLfloat maximumAnisotropy;
			//get the value
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maximumAnisotropy);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maximumAnisotropy);
		}
					// Set texture interpolation method to use linear interpolation (no MIPMAPS)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        glGenerateMipmap(GL_TEXTURE_2D);
 

 	}
  	else 
  	{
		error = ilGetError();
		std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		
  	}
 
 	ilDeleteImages(1, &imageID); 
 
	std::cout << "Texture creation successful." << std::endl;
 
	return textureID; 

}
Model box;

Model sphere;
void Graphics3D::Init()
{

	std::cout << "Initiating Graphics" << std::endl << std::endl;
   
	glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
          fprintf(stderr, "Failed to initialize GLEW\n");
    }

		 //  ----- Initialise DevIL -----
	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);


//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_LINE_SMOOTH); 
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	// Enable depth test
 //   glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
 //   glDepthFunc(GL_LESS); 

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);	     
    programID = LoadShaders( "DATA/Shaders/SimpleVertexShader.vertexshader", "DATA/Shaders/SimpleFragmentShader.fragmentshader" );
    MatrixID = glGetUniformLocation(programID, "MVP");
	TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	cubeMapTextureID  = glGetUniformLocation(programID, "cubeMapTexture");
	boolCubeMapID = glGetUniformLocation(programID, "boolCubeMap");

	lightShader = LoadShaders( "DATA/Shaders/light.vert", "DATA/Shaders/light.frag" );
    lightMatrixID = glGetUniformLocation(lightShader, "MVP");
	lightModelMatrixID = glGetUniformLocation(lightShader, "M");
	lightViewMatrixID = glGetUniformLocation(lightShader, "V");
	lightLightID = glGetUniformLocation(lightShader, "LightPosition_worldspace");
	lightTextureID1  = glGetUniformLocation(lightShader, "myTextureSampler");

	terrainShader = LoadShaders( "DATA/Shaders/planet.vertexshader", "DATA/Shaders/planet.fragmentshader" );
    terrainMatrixID = glGetUniformLocation(terrainShader, "MVP");
	terrainModelMatrixID = glGetUniformLocation(terrainShader, "M");
	terrainViewMatrixID = glGetUniformLocation(terrainShader, "V");
	terrainLightID = glGetUniformLocation(terrainShader, "LightPosition_worldspace");
	terrainTimeID = glGetUniformLocation(terrainShader, "time");
	terrainTextureID1  = glGetUniformLocation(terrainShader, "cubeTexture");
	terrainTextureID2  = glGetUniformLocation(terrainShader, "snow");
	terrainTextureID3  = glGetUniformLocation(terrainShader, "stone");
	terrainTextureID4  = glGetUniformLocation(terrainShader, "grass");
	terrainTextureID5  = glGetUniformLocation(terrainShader, "sand");
	terrainTextureID6  = glGetUniformLocation(terrainShader, "water");
	terrainTextureID7  = glGetUniformLocation(terrainShader, "cubeTexture");


	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &uvbuffer);

    /* Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
   // Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 500.0f);
    // Camera matrix
    View       = glm::lookAt(
                                                                glm::vec3(0,6,-15), // Camera is at (4,3,3), in World Space
                                                                glm::vec3(0,0,0), // and looks at the origin
                                                                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                                   );
   */
    glm::mat4 Model      = glm::mat4(1.0f);
  
    MVP        = Projection * View * Model;
	
	//box.Setup("skydome.obj", "night.png");	
	// Six sides of a cube map      1								3	   					T0P						BOTTOM						4				  2
//	const char *cube[6] = { "DATA/Images/space6.png", "DATA/Images/space5.png", "DATA/Images/space4.png", "DATA/Images/space3.png", "DATA/Images/space1.png", "DATA/Images/space2.png" };
//	const char *cube[6] = { "DATA/Images/blue6.png", "DATA/Images/blue5.png", "DATA/Images/blue4.png", "DATA/Images/blue3.png", "DATA/Images/blue1.png", "DATA/Images/blue2.png" };
	const char *cube[6] = { "DATA/Images/stars6.png", "DATA/Images/stars5.png", "DATA/Images/stars4.png", "DATA/Images/stars3.png", "DATA/Images/stars1.png", "DATA/Images/stars2.png" };
//	box.Setup("DATA/Models/skydome.obj", "DATA/Images/sky.jpg");
//	box.Setup("DATA/Models/skydome.obj", "DATA/Images/sky.jpg");
	box.Setup("DATA/Models/skybox.obj",cube);
	sphere.Setup("DATA/Models/skydome.obj", "DATA/Images/tutorial.bmp");
	
//	hf.hLOD = 4;
	hf.Init();
//	hf.bound = 0;
	hf.CreateFromFractal(1024,1024);
	hf.position = glm::vec3(0, 0, 0);	
	/*
	for(int i = 0; i < 5; i++)
	{
	hf2[i].Init();
	hf2[i].CreateFromFractal(1024,1024);
	hf2[i].position = glm::vec3(5000 + i*5000, 0, 0);
	}
	*/

	

}
glm::mat4 Graphics3D::getMVP()
{
	return MVP;
}
void Graphics3D::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.f,0.f,0.f,0.f);
	View = engine->getInputManager()->getViewMatrix();
	Projection = engine->getInputManager()->getProjectionMatrix();
	glUseProgram(programID);
	
//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glDepthMask(0); 
	box.MoveRotateScale(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(20000,20000, 20000));
	box.Render();
	glDepthMask(1);
	sphere.MoveRotateScale(glm::vec3(4200, 4400, 4200), glm::vec3(0, 0, 0), glm::vec3(50,50, 50));
	sphere.Render();
	

	if(engine->getInputManager()->line == true)
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}else{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
	glUseProgram(terrainShader);

	hf.Render();
/*	for(int i = 0; i<5; i++)
	{
		hf2[i].Render();
	}*/
	glUseProgram(0);


	

//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
	

	

	engine->getWindowHandle()->display();
	
}
	

