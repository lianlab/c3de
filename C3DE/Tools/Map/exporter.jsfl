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
contents += "Tree0 *t_tree0;\n";
contents += "Tree1 *t_tree1;\n";
contents += "Tree2 *t_tree2;\n";
contents += "Tree3 *t_tree3;\n";
contents += "LandscapeWall1 *t_wall1;\n";
contents += "LandscapeWall2 *t_wall2;\n";
contents += "LandscapeWall3 *t_wall3;\n";

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
				var t_width = "" + layerElements[j].width;
				
				//only for the walls
				if(layerElements[j].rotation != 0)
				{
					var t_width = "" + layerElements[j].height;
				}
				
				if(t_width.indexOf(".") < 0)
				{
					t_width += ".0f";
				}
				else
				{
					t_width += "f";
				}
				
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
				
				if(layerNames[i] == "MESH_TREE_0_ID")
				{
					contents += "t_tree0 = new Tree0();\n";
					contents += "t_tree0->UniformScale(GetCorrespondingScale("+layerNames[i]+"));" + "\n";
					contents += "t_planePositions = GetPlanePositions("+tx+", "+ty+");" + "\n";
					contents += "t_tree0->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);" + "\n";
					contents += "t_tree0->Rotate(0.0f,"+t_rotation+", 0.0f);" + "\n";
					contents += "m_testScene->AddMesh(t_tree0);" + "\n";
					contents += "m_loadedObjects++;\n";
					contents += "UpdateLoadingBar(m_loadedObjects, m_totalObjects);\n\n"
				}
				else if(layerNames[i] == "MESH_TREE_1_ID")
				{
					contents += "t_tree1 = new Tree1();\n";
					contents += "t_tree1->UniformScale(GetCorrespondingScale("+layerNames[i]+"));" + "\n";
					contents += "t_planePositions = GetPlanePositions("+tx+", "+ty+");" + "\n";
					contents += "t_tree1->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);" + "\n";
					contents += "t_tree1->Rotate(0.0f,"+t_rotation+", 0.0f);" + "\n";
					contents += "m_testScene->AddMesh(t_tree1);" + "\n";
					contents += "m_loadedObjects++;\n";
					contents += "UpdateLoadingBar(m_loadedObjects, m_totalObjects);\n\n"
				}
				else if(layerNames[i] == "MESH_TREE_2_ID")
				{
					contents += "t_tree2 = new Tree2();\n";
					contents += "t_tree2->UniformScale(GetCorrespondingScale("+layerNames[i]+"));" + "\n";
					contents += "t_planePositions = GetPlanePositions("+tx+", "+ty+");" + "\n";
					contents += "t_tree2->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);" + "\n";
					contents += "t_tree2->Rotate(0.0f,"+t_rotation+", 0.0f);" + "\n";
					contents += "m_testScene->AddMesh(t_tree2);" + "\n";
					contents += "m_loadedObjects++;\n";
					contents += "UpdateLoadingBar(m_loadedObjects, m_totalObjects);\n\n"
				}
				else if(layerNames[i] == "MESH_TREE_3_ID")
				{
					contents += "t_tree3 = new Tree3();\n";
					contents += "t_tree3->UniformScale(GetCorrespondingScale("+layerNames[i]+"));" + "\n";
					contents += "t_planePositions = GetPlanePositions("+tx+", "+ty+");" + "\n";
					contents += "t_tree3->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);" + "\n";
					contents += "t_tree3->Rotate(0.0f,"+t_rotation+", 0.0f);" + "\n";
					contents += "m_testScene->AddMesh(t_tree3);" + "\n";
					contents += "m_loadedObjects++;\n";
					contents += "UpdateLoadingBar(m_loadedObjects, m_totalObjects);\n\n"
				}
				else if(layerNames[i] == "WALL_1")
				{
					contents += "t_wall1 = new LandscapeWall1();\n";
					contents += "t_wall1->Scale(GetRelativeScale(" + t_width + "), 0.0f, 0.0f);\n";
					//contents += "t_tree3->UniformScale(GetCorrespondingScale("+layerNames[i]+"));" + "\n";
					contents += "t_planePositions = GetPlanePositions("+tx+", "+ty+");" + "\n";
					contents += "t_wall1->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);" + "\n";
					contents += "t_wall1->Rotate(0.0f,"+t_rotation+", 0.0f);" + "\n";
					contents += "m_testScene->AddMesh(t_wall1);" + "\n";
					contents += "m_loadedObjects++;\n";
					contents += "UpdateLoadingBar(m_loadedObjects, m_totalObjects);\n\n"
				}
				else if(layerNames[i] == "WALL_2")
				{
					contents += "t_wall2 = new LandscapeWall2();\n";
					contents += "t_wall2->Scale(GetRelativeScale(" + t_width + "), 0.0f, 0.0f);\n";
					//contents += "t_tree3->UniformScale(GetCorrespondingScale("+layerNames[i]+"));" + "\n";
					contents += "t_planePositions = GetPlanePositions("+tx+", "+ty+");" + "\n";
					contents += "t_wall2->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);" + "\n";
					contents += "t_wall2->Rotate(0.0f,"+t_rotation+", 0.0f);" + "\n";
					contents += "m_testScene->AddMesh(t_wall2);" + "\n";
					contents += "m_loadedObjects++;\n";
					contents += "UpdateLoadingBar(m_loadedObjects, m_totalObjects);\n\n"
				}
				else if(layerNames[i] == "WALL_3")
				{
					contents += "t_wall3 = new LandscapeWall3();\n";
					contents += "t_wall3->Scale(GetRelativeScale(" + t_width + "), 0.0f, 0.0f);\n";
					//contents += "t_tree3->UniformScale(GetCorrespondingScale("+layerNames[i]+"));" + "\n";
					contents += "t_planePositions = GetPlanePositions("+tx+", "+ty+");" + "\n";
					contents += "t_wall3->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);" + "\n";
					contents += "t_wall3->Rotate(0.0f,"+t_rotation+", 0.0f);" + "\n";
					contents += "m_testScene->AddMesh(t_wall3);" + "\n";
					contents += "m_loadedObjects++;\n";
					contents += "UpdateLoadingBar(m_loadedObjects, m_totalObjects);\n\n"
				}
				else
				{					
					contents += "t_mesh = new LandscapeMesh(" + layerNames[i] +",GetCorrespondingTextID("+ layerNames[i]+"));" + "\n";
					contents += "t_mesh->UniformScale(GetCorrespondingScale("+layerNames[i]+"));" + "\n";
					contents += "t_planePositions = GetPlanePositions("+tx+", "+ty+");" + "\n";
					contents += "t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);" + "\n";
					contents += "t_mesh->Rotate(0.0f,"+t_rotation+", 0.0f);" + "\n";
					contents += "m_testScene->AddMesh(t_mesh);" + "\n";
					contents += "m_loadedObjects++;\n";
					contents += "UpdateLoadingBar(m_loadedObjects, m_totalObjects);\n\n"
				}
				
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
	
	
