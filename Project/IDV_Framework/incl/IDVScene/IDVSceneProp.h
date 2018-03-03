#ifndef IDV_SCENEPROPS_H
#define IDV_SCENEPROPS_H

#include <IDV_Maths.h>

#include <vector>

struct Light{
	XVECTOR3 Position;
	XVECTOR3 Color;
	int		 Type;
	int		 Enabled;
};

struct SceneProps{
	SceneProps() : ActiveCamera(0) , ActiveLights(1), ActiveLightCamera(0), ActiveGaussKernel(0), Exposure(0.3f) , BloomFactor(1.1f) {}

	void	AddLight(XVECTOR3 Pos, XVECTOR3 Color,bool enabled);
	void	RemoveLight(unsigned int index);
	void	SetLightPos(unsigned int index, XVECTOR3);

	std::vector<Light>	   Lights;

	XVECTOR3			AmbientColor;

	int ActiveCamera;
	int	ActiveLights;
	int ActiveLightCamera;
	int ActiveGaussKernel;
	
	// HDR
	float	Exposure;
	float	BloomFactor;
};

#endif
