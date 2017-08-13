//////////////////////////////////////////////////////////////////////////////////////////
//	ARB_texture_cube_map_extension.cpp
//	ARB_texture_cube_map extension setup
//	Downloaded from: www.paulsprojects.net
//	Created:	26th August 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	
#include <windows.h>
#include <stdio.h>
#include <GL\gl.h>
#include <GL\glext.h>
#include <GL\wglext.h>
#include "ARB_texture_cube_map_extension.h"

bool ARB_texture_cube_map_supported=false;

bool SetUpARB_texture_cube_map()
{
	//Check for support
	char * extensionString=(char *)glGetString(GL_EXTENSIONS);
	char * extensionName="GL_ARB_texture_cube_map";

	char * endOfString;									//store pointer to end of string
	unsigned int distanceToSpace;						//distance to next space

	endOfString=extensionString+strlen(extensionString);

	//loop through string
	while(extensionString<endOfString)
	{
		//find distance to next space
		distanceToSpace=strcspn(extensionString, " ");

		//see if we have found extensionName
		if((strlen(extensionName)==distanceToSpace) &&
			(strncmp(extensionName, extensionString, distanceToSpace)==0))
		{
			ARB_texture_cube_map_supported=true;
		}

		//if not, move on
		extensionString+=distanceToSpace+1;
	}

	//also check for EXT_texture_cube map, since they are the same
	extensionString=(char *)glGetString(GL_EXTENSIONS);
	extensionName="GL_EXT_texture_cube_map";

	endOfString;									//store pointer to end of string
	distanceToSpace;								//distance to next space

	endOfString=extensionString+strlen(extensionString);

	//loop through string
	while(extensionString<endOfString)
	{
		//find distance to next space
		distanceToSpace=strcspn(extensionString, " ");

		//see if we have found extensionName
		if((strlen(extensionName)==distanceToSpace) &&
			(strncmp(extensionName, extensionString, distanceToSpace)==0))
		{
			ARB_texture_cube_map_supported=true;
		}

		//if not, move on
		extensionString+=distanceToSpace+1;
	}

	if(!ARB_texture_cube_map_supported)
	{
		printf("ARB_texture_cube_map unsupported!\n");
		return false;
	}

	printf("ARB_texture_cube_map supported!\n");

	//get function pointers
	//none specified

	return true;
}
