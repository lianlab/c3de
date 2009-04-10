var lastIndex = document.path.lastIndexOf("\\");
var documentRoot = document.path.substr(0, lastIndex + 1);

while(documentRoot.indexOf("\\") > 0)
{
	documentRoot = documentRoot.replace("\\", "/");
}

var doc = fl.getDocumentDOM();
var lyrs = doc.getTimeline().layers;

var len = lyrs.length;
var lyr;

var layerNames = [];
var layerSizes = [];
var layerElementsArray = [];

var contents = "";
contents += "D3DXVECTOR2 t_planePositions;\n";
contents += "LandscapeMesh *t_mesh;\n";

for (i=0; i < len; i++) {		
		
		if(lyrs[i].name != "startpoint" && lyrs[i].name != "bg" && lyrs[i].visible)
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
				
				var t_rotation = "" + layerElements[j].rotation;
				
				if(t_rotation.indexOf(".") < 0)
				{
					t_rotation += ".0f";
				}
				else
				{
					t_rotation += "f";
				}
				
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
				contents += "t_mesh = new LandscapeMesh(" + layerNames[i] +",GetCorrespondingTextID("+ layerNames[i]+"));" + "\n";
				contents += "t_mesh->UniformScale(GetCorrespondingScale("+layerNames[i]+"));" + "\n";
				contents += "t_planePositions = GetPlanePositions("+tx+", "+ty+");" + "\n";
				contents += "t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);" + "\n";
				contents += "t_mesh->Rotate(0.0f,"+t_rotation+", 0.0f);" + "\n";
				contents += "m_testScene->AddMesh(t_mesh);" + "\n\n";
				
				/*
				fl.trace("t_mesh = new LandscapeMesh(" + layerNames[i] +",GetCorrespondingTextID("+ layerNames[i]+"));");
				fl.trace("t_mesh->UniformScale(GetCorrespondingScale("+layerNames[i]+"));");
				fl.trace("t_planePositions = GetPlanePositions("+tx+", "+ty+");");
				fl.trace("t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);");
				fl.trace("m_testScene->AddMesh(t_mesh);");
				fl.trace("");
				*/
				
				
			}
			//fl.trace("");
			//fl.trace("for(int i = 0; i< " + elementsSize + "; i++)\n{\n}");
			
			
			
			
			
		}
		
		//
	};
	
	var len2 = layerNames.length;

fl.trace("CONTENTS:\n" + contents)
FLfile.write("file:///"+documentRoot + "/mapPositions.h", contents);
	
	
