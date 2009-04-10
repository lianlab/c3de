var doc = fl.getDocumentDOM();
var lyrs = doc.getTimeline().layers;

var len = lyrs.length;
var lyr;

var layerNames = [];
var layerSizes = [];
var layerElementsArray = [];

fl.trace("D3DXVECTOR2 t_planePositions;");
fl.trace("LandscapeMesh *t_mesh;");



for (i=0; i < len; i++) {
		
		
		if(lyrs[i].name != "startpoint" && lyrs[i].name != "bg")
		{
			
			lyr = lyrs[i];
		
			layerNames[i] = lyr.name;
			layerSizes[i] = lyr.frames[0].elements.length;
			layerElementsArray[i] = lyr.frames[0].elements;
			var layerElements = lyr.frames[0].elements;
			
			var elementsSize = layerElements.length;
			//fl.trace("t_iterator = 0;");
			for(j = 0; j < elementsSize; j++)
			{
				var elementMatrix = layerElements[j].matrix;
				
				var tx = "" + elementMatrix.tx;
				var ty = "" + elementMatrix.ty;
				
				if(tx.indexOf(".") < 0)
				{
					tx += ".0f";
				}
				else
				{
					tx += "f";
				}
				
				if(ty.indexOf(".") < 0)
				{
					ty += ".0f";
				}
				else
				{
					ty += "f";
				}
				
				//fl.trace("t_" + layerNames[i] + "_ARRAY[" + j + "] = D3DXVECTOR2(" + tx + "," + ty + ");");
				//fl.trace("");
				fl.trace("t_mesh = new LandscapeMesh(" + layerNames[i] +",GetCorrespondingTextID("+ layerNames[i]+"));");
				fl.trace("t_mesh->UniformScale(GetCorrespondingScale("+layerNames[i]+"));");
				fl.trace("t_planePositions = GetPlanePositions("+tx+", "+ty+");");
				fl.trace("t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);");
				fl.trace("m_testScene->AddMesh(t_mesh);");
				fl.trace("");
				/*
				t_mesh = new LandscapeMesh(MESH_TRAFFIC_CONE_ID,GetCorrespondingTextID(MESH_TRAFFIC_CONE_ID));
		
		t_mesh->UniformScale(GetCorrespondingScale(MESH_TRAFFIC_CONE_ID));
		D3DXVECTOR2 t_planePositions = GetPlanePositions(D3DXVECTOR2(t_conesArray[i].x, t_conesArray[i].y));
		t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
		m_testScene->AddMesh(t_mesh);*/
				
			}
			fl.trace("");
			//fl.trace("for(int i = 0; i< " + elementsSize + "; i++)\n{\n}");
			
			
			/*
			for(int i = 0; i< t_totalCones; i++)
	{
		
		LandscapeMesh *t_mesh = new LandscapeMesh(MESH_TRAFFIC_CONE_ID,GetCorrespondingTextID(MESH_TRAFFIC_CONE_ID));
		
		t_mesh->UniformScale(GetCorrespondingScale(MESH_TRAFFIC_CONE_ID));
		D3DXVECTOR2 t_planePositions = GetPlanePositions(D3DXVECTOR2(t_conesArray[i].x, t_conesArray[i].y));
		t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
		m_testScene->AddMesh(t_mesh);
		
	}
			*/
			
			
		}
		
		//
	};
	
	var len2 = layerNames.length;
	
	
for(i= 0; i< len2;i++)
{
	if(layerNames[i] != "")
	{
		//fl.trace("#define t_" + layerNames[i] + "_COUNT " + layerSizes[i]);
		//fl.trace("D3DXVECTOR2 t_" + layerNames[i] + "_ARRAY[" + layerSizes[i] + "]");
		
		
		
	}
}
	
