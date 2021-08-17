#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>

#include <stdio.h>

#include "heightfield.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "objloader.hpp"


  utils::NoiseMap heightMap;

bool HeightField::Init(){
	
	terrainMVP = engine->getGraphicsManager()->getMVP();
	return true;
}

void HeightField::MoveRotateScale(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	
	
	glm::mat4 T = glm::translate(glm::mat4(1.0f),pos);
	glm::mat4 Rx = glm::rotate(T, rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 Ry = glm::rotate(Rx, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 AlmostModel = glm::rotate(Ry, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Model = glm::scale(AlmostModel, glm::vec3(1.0, 1.0, 1.0));

	terrainMVP = engine->getGraphicsManager()->getProjection() * engine->getGraphicsManager()->getView() * Model;
	modelM = Model;

}

//Auto generated hightfield vertices/uvs/normals from internet.
void HeightField::SolidSphere(double r, int lats, int longs)
    {
    int i = 0, j = 0;
         
    for(i = 0; i <= lats; i++)
    {
		double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats) ;
        double z0  = sin(lat0) ;
        double zr0 =  cos(lat0)   ;
 
        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);
 
        double tx1 = 0;
        double ty1 = 0;
        double tx2 = 0;
        double ty2 = 0;

        for(j = 0; j <= longs; j++)
        {    
            double lng = (2 * M_PI * (double) (j - 1) / longs);
            double x = cos(lng);
            double y = sin(lng);
 
            tx1 = atan2(x * zr0, z0) / (2. * M_PI) + 0.5;
            ty1 = asin(y * zr0) / M_PI + .5;
            if(tx1 < 0.75 && tx2 > 0.75)
            {
                tx1 += 1.0;
            }
            else if(tx1 > 0.75 && tx2 < 0.75)
            {
                tx1 -= 1.0;
            }
 
            tx2 = atan2(x * zr1, z1) / (2. * M_PI) + 0.5;
            ty2 = asin(y * zr1) / M_PI + .5;
            if(tx2 < 0.75 && tx1 > 0.75)
            {
                tx2 += 1.0;
            }
            else if(tx2 > 0.75 && tx1 < 0.75)
            {
                tx2 -= 1.0;
            }
			
			vertices.push_back(glm::vec3(x  * zr0 * (r+(heightMap.GetValue(i,j) * 15)) , y * zr0 * (r+(heightMap.GetValue(i,j) * 15)) , z0 * (r+(heightMap.GetValue(i,j) * 15))));
			uvs.push_back(glm::vec2((float)(tx1),(float)(ty1)));
            normals.push_back(glm::vec3(x * zr0, y * zr0, z0));

		//	std::cout << heightMap.GetValue(i, j) << std::endl;
		//	std::cout << (r+heightMap.GetValue(i,j)) << std::endl;
		
 			vertices.push_back(glm::vec3(x * zr1 * (r+(heightMap.GetValue(i,j) * 15)), y * zr1 * (r+(heightMap.GetValue(i,j) * 15)), z1 * (r+(heightMap.GetValue(i,j) * 15))));
			uvs.push_back(glm::vec2((float)(tx2),(float)(ty2)));
            normals.push_back(glm::vec3(x * zr1, y * zr1, z1));

        }
    }
}

bool HeightField::CreateFromFractal( const int hWidth, const int hHeight)
{
	/*
	noise::module::Perlin myModule;
	myModule.SetOctaveCount (6);
	myModule.SetFrequency (4.0);
	myModule.SetPersistence (0.25);

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule (myModule);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetDestSize (hWidth, hHeight);
	heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
	heightMapBuilder.Build ();
	*/
	/*
	  module::RidgedMulti mountainTerrain;
	  module::Billow baseFlatTerrain;
	  baseFlatTerrain.SetFrequency (2.0);
	  module::ScaleBias flatTerrain;
	  flatTerrain.SetSourceModule (0, baseFlatTerrain);
	  flatTerrain.SetScale (0.925);
	  flatTerrain.SetBias (-0.95);
	  module::Perlin terrainType;
	  terrainType.SetFrequency (0.5);
	  terrainType.SetPersistence (0.25);
	  module::Select terrainSelector;
	  terrainSelector.SetSourceModule (0, flatTerrain);
	  terrainSelector.SetSourceModule (1, mountainTerrain);
	  terrainSelector.SetControlModule (terrainType);
	  terrainSelector.SetBounds (0.0, 1000.0);
	  terrainSelector.SetEdgeFalloff (0.125);
	  
	  module::Turbulence finalTerrain;
	  finalTerrain.SetSourceModule (0, terrainSelector);
	  finalTerrain.SetFrequency (1.0);
	  finalTerrain.SetPower (0.025);
	  	*/
	/*
		 module::Billow baseFlatTerrain;
		 baseFlatTerrain.SetFrequency (2.0);


		 module::ScaleBias flatTerrain;
		 flatTerrain.SetSourceModule (0, baseFlatTerrain);
		 flatTerrain.SetScale (0.125);
		 flatTerrain.SetBias (-0.75);

	*/	 module::Billow baseFlatTerrain;
		 baseFlatTerrain.SetFrequency (2.0);
		 module::ScaleBias flatTerrain;
		 flatTerrain.SetSourceModule (0, baseFlatTerrain);
		 flatTerrain.SetScale (0.225);
		 flatTerrain.SetBias (-0.75);

		 module::Perlin perlin;
	//	 perlin.SetLacunarity(0.1);
		 perlin.SetOctaveCount(6);
		 perlin.SetFrequency(2);
		 perlin.SetPersistence (0.5);

		 module::Perlin perlin2;
	//	 perlin.SetLacunarity(0.1);
		 perlin.SetOctaveCount(6);
		 perlin.SetFrequency(3);
		 perlin.SetPersistence (0.5);


		 module::Perlin terrainType;
		 terrainType.SetFrequency (0.5);
		 terrainType.SetPersistence (0.25);

		  module::Select terrainSelector;
		  terrainSelector.SetSourceModule (0, flatTerrain);
		//  terrainSelector.SetSourceModule (1, perlin);
		  terrainSelector.SetSourceModule (1, perlin2);
		  terrainSelector.SetControlModule (terrainType);
		  terrainSelector.SetBounds (0.0, 1000.0);
		  terrainSelector.SetEdgeFalloff (0.325);
		 
	

	  /*
	  utils::NoiseMap heightMap;
	  utils::NoiseMapBuilderPlane heightMapBuilder;
	  heightMapBuilder.SetSourceModule (finalTerrain);
	  heightMapBuilder.SetDestNoiseMap (heightMap);
	  heightMapBuilder.SetDestSize (hWidth, hHeight);
	  heightMapBuilder.SetBounds (12.0 + bound, 14.0 + bound, 14.0, 16.0);
	  heightMapBuilder.Build ();
	  */


	  utils::NoiseMapBuilderPlane heightMapBuilder;
	  heightMapBuilder.SetSourceModule (terrainSelector);
	  heightMapBuilder.SetDestNoiseMap (heightMap);
	  heightMapBuilder.SetDestSize (1024, 1024);
	  heightMapBuilder.SetBounds (0.0, 4.0, 0.0, 4.0);
	  // heightMapBuilder.SetBounds (-90.0, 90.0, -180.0, 180.0);
	  heightMapBuilder.Build ();
	
	  utils::RendererImage renderer;
	  utils::Image image;
	  renderer.SetSourceNoiseMap (heightMap);
	  renderer.SetDestImage (image);
	/*
	//  renderer.ClearGradient ();
	//  renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
	//  renderer.AddGradientPoint ( 0.4500, utils::Color (128, 128, 128, 255)); // rock
	
	  renderer.ClearGradient ();
	  renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
	  renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
	  renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
	  renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
	  renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
	  renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
	  renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
	  renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
	  
	 renderer.EnableLight ();
	  renderer.SetLightContrast (3.0);
	  renderer.SetLightBrightness (2.0);
	  */
	  /*
	  renderer.Render ();
	  
	  utils::WriterBMP writer;
	  writer.SetSourceImage (image);
	  writer.SetDestFilename ("tutorial.bmp");
	  writer.WriteDestFile ();	
	  
	  heightMapBuilder.SetBounds (0 + 4, 4.0 + 4, 0, 4);
	  heightMapBuilder.Build ();
	  renderer.Render ();
	  writer.SetDestFilename ("tutorial2.bmp");
	  writer.WriteDestFile ();	

	  heightMapBuilder.SetBounds (0 + 8, 4 + 8, 0, 4);
	  heightMapBuilder.Build ();
	  renderer.Render ();
	  writer.SetDestFilename ("tutorial3.bmp");
	  writer.WriteDestFile ();	

	  heightMapBuilder.SetBounds (0 + 12, 4 + 12, 0, 4);
	  heightMapBuilder.Build ();
	  renderer.Render ();
	  writer.SetDestFilename ("tutorial4.bmp");
	  writer.WriteDestFile ();	
	  
	  heightMapBuilder.SetBounds (0 + 4, 4 + 4 , 0 + 4, 4 + 4);
	  heightMapBuilder.Build ();
	  renderer.Render ();
	  writer.SetDestFilename ("tutorial5.bmp");
	  writer.WriteDestFile ();	

	  	  heightMapBuilder.SetBounds (0 + 4, 4 + 4 , 0 - 4, 4 - 4);
	  heightMapBuilder.Build ();
	  renderer.Render ();
	  writer.SetDestFilename ("tutorial6.bmp");
	  writer.WriteDestFile ();	
	  */
	  hmHeight = hHeight;
	  hmWidth = hWidth;
	bool res = loadOBJ("DATA/Models/box.obj", vertices, uvs, normals);

	for(int i = 0; i < vertices.size(); i++)
	{
		
		glm::vec3 oldVec = vertices[i];
		glm::vec3 newVec = glm::normalize(oldVec);
		vertices[i] = newVec * glm::vec3(2000, 2000, 2000);

	}

	/*
	for ( unsigned int i = 0; i < normals.size(); ++i )
	{
	   normals[i] = glm::normalize( normals[i] );
	}*/
	for(int i = 0; i < vertices.size(); i+=3)
	{

		  // get the three vertices that make the faces
		  glm::vec3 p1 = vertices[i+0];
		  glm::vec3 p2 = vertices[i+1];
		  glm::vec3 p3 = vertices[i+2];

		  glm::vec3 v1 = p2 - p1;
		  glm::vec3 v2 = p3 - p1;
		  glm::vec3 normal = glm::cross( v1,v2 );

		  normal = glm::normalize(normal);

		  normals[i+0] = normal;
		  normals[i+1] = normal;
		  normals[i+2] = normal;
		
	}
/*	for ( unsigned int i = 0; i < normals.size(); i+=3 )
	{
	//	glm::vec3 normal = normals[i] + normals[i+1] + normals[i+2];
		//glm::normalize( normal );
	//	normals[i] = normal;

		

	   //normals[i] = glm::normalize( normals[i] );
	  // normals[i+1] = glm::normalize( normals[i] );
	  // normals[i+2] = glm::normalize( normals[i] );
	}*/
/*	for ( unsigned int i = 0; i < normals.size(); ++i )
	{
	   normals[i] = glm::normalize( normals[i] );
	}*/


	std::cout << "Terrain has: " << vertices.size() << " vertices!" << std::endl;

	/*
	tID[0] = engine->getGraphicsManager()->loadTexture("grass.jpg");
	tID[1] = engine->getGraphicsManager()->loadTexture("sand.jpg");
	tID[2] = engine->getGraphicsManager()->loadTexture("stone.jpg");
	tID[3] = engine->getGraphicsManager()->loadTexture("snow.jpg");

	*/
/*	tID[0] = engine->getGraphicsManager()->loadTexture("tutorial.bmp");
	tID[1] = engine->getGraphicsManager()->loadTexture("tutorial.bmp");
	tID[2] = engine->getGraphicsManager()->loadTexture("tutorial.bmp");
	tID[3] = engine->getGraphicsManager()->loadTexture("tutorial.bmp");
*/

		// Six sides of a cube map      1				3	   			T0P				BOTTOM			4				  2
	// const char *cubeFaces[6] = { "DATA/Images/tutorial.bmp", "DATA/Images/tutorial3.bmp", "DATA/Images/tutorial6.bmp", "DATA/Images/tutorial5.bmp", "DATA/Images/tutorial4.bmp", "DATA/Images/tutorial2.bmp" };
	// const char *Texture[6] = { "grass.jpg", "grass.jpg", "grass.jpg", "grass.jpg", "grass.jpg", "grass.jpg" };
	//const char *cubeFaces[6] = { "tutorial.bmp", "tutorial.bmp", "tutorial.bmp", "tutorial.bmp", "tutorial.bmp", "tutorial.bmp" };
	//tID[0] = engine->getGraphicsManager()->loadCubeMapTexture(cubeFaces);
	tID[1] = engine->getGraphicsManager()->loadTexture("DATA/Images/snow.jpg");
	tID[2] = engine->getGraphicsManager()->loadTexture("DATA/Images/stone.jpg");
	tID[3] = engine->getGraphicsManager()->loadTexture("DATA/Images/grass.jpg");
	tID[4] = engine->getGraphicsManager()->loadTexture("DATA/Images/sand.jpg");

	//tID[3] = engine->getGraphicsManager()->loadTexture(cubeFaces);

	glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &uvbuffer);
	glGenBuffers(1, &normalbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);


	MoveRotateScale(position, glm::vec3(0, 0, 0), glm::vec3(1,1,1));

	return true;
}


void HeightField::Render(void){


/*
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tID[0]); 
	glUniform1i(engine->getGraphicsManager()->getTerrainTextureID(1), 0);
*/	

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, tID[1]); 
	glUniform1i(engine->getGraphicsManager()->getTerrainTextureID(2), 1);

	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, tID[2]); 
	glUniform1i(engine->getGraphicsManager()->getTerrainTextureID(3), 2);

	glActiveTexture(GL_TEXTURE0 + 3);
	glBindTexture(GL_TEXTURE_2D, tID[3]); 
	glUniform1i(engine->getGraphicsManager()->getTerrainTextureID(4), 3);	

	glActiveTexture(GL_TEXTURE0 + 4);
	glBindTexture(GL_TEXTURE_2D, tID[4]); 
	glUniform1i(engine->getGraphicsManager()->getTerrainTextureID(5), 4);	

	glActiveTexture(GL_TEXTURE0 + 5);
	glBindTexture(GL_TEXTURE_2D, tID[5]); 
	glUniform1i(engine->getGraphicsManager()->getTerrainTextureID(6), 5);	

//	std::cout << position.x << " " << position.y << " " << position.z << std::endl;


	MoveRotateScale(position, glm::vec3(0, 0, 0), glm::vec3(1,1,1));
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
   // glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);


	glUniformMatrix4fv(engine->getGraphicsManager()->getTerrainModelMatrixID(), 1, GL_FALSE, &modelM[0][0]);
	glUniformMatrix4fv(engine->getGraphicsManager()->getTerrainViewMatrixID(), 1, GL_FALSE, &engine->getGraphicsManager()->getView()[0][0]);
	glUniformMatrix4fv(engine->getGraphicsManager()->getTerrainMatrixID(), 1, GL_FALSE, &terrainMVP[0][0]);

	glUniform3f(engine->getGraphicsManager()->getTerrainLightID(), 4200, 4400, 4200);
	glUniform1f(engine->getGraphicsManager()->getTerrainTimeID(), engine->getWindow()->getTime() * 0.0001);
//	glUniform1f(engine->getGraphicsManager()->getTerrainTimeID(), 10 + position.x *0.0001);
		//vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	   0,                  
	   3,                  
	   GL_FLOAT,           
	   GL_FALSE,           
	   0,                  
	   (char*)0           
	);



     //UVs
     glEnableVertexAttribArray(1);
     glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
     glVertexAttribPointer(
       1,                                // attribute
	   2,                                // size
       GL_FLOAT,                         // type
       GL_FALSE,                         // normalized?
       0,                                // stride
       (char*)0                          // array buffer offset
     );
	 
	 //Normal
     glEnableVertexAttribArray(2);
     glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
     glVertexAttribPointer(
       2,                                // attribute
	   3,                                // size
       GL_FLOAT,                         // type
       GL_FALSE,                         // normalized?
       0,                                // stride
       (void*)0                          // array buffer offset
     );
	 

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
	//glDrawArrays(GL_TRIANGLE_STRIP, 0,  vertices.size());
	glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
 

	glBindTexture(GL_TEXTURE_2D, 0); 

}