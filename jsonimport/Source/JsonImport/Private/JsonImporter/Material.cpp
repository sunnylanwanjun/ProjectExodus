#include "JsonImportPrivatePCH.h"

#include "JsonImporter.h"

#include "Engine/PointLight.h"
#include "Engine/SpotLight.h"
#include "Engine/DirectionalLight.h"
#include "Engine/Classes/Components/PointLightComponent.h"
#include "Engine/Classes/Components/SpotLightComponent.h"
#include "Engine/Classes/Components/DirectionalLightComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "LevelEditorViewport.h"
#include "Factories/TextureFactory.h"
#include "Factories/MaterialFactoryNew.h"

#include "Materials/Material.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "Materials/MaterialExpressionSubtract.h"
#include "Materials/MaterialExpressionMultiply.h"
#include "Materials/MaterialExpressionAdd.h"
#include "Materials/MaterialExpressionTextureCoordinate.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "Materials/MaterialExpressionConstant.h"
	
#include "RawMesh.h"

#include "DesktopPlatformModule.h"

using namespace JsonObjects;

UMaterial* JsonImporter::loadMaterial(int32 id){
	UE_LOG(JsonLog, Log, TEXT("Looking for material %d"), id);
	if (id < 0){
		UE_LOG(JsonLog, Log, TEXT("Invalid id %d"), id);
		return 0;
	}

	if (!matIdMap.Contains(id)){
		UE_LOG(JsonLog, Log, TEXT("Id %d is not in the map"), id);
		return 0;
	}

	auto matPath = matIdMap[id];
	UMaterial *mat = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), 0, *matPath));
	UE_LOG(JsonLog, Log, TEXT("Material located"));
	return mat;
}

void JsonImporter::importMaterial(JsonObjPtr obj, int32 matId){
	materialBuilder.importMaterial(obj, this, matId);
}
