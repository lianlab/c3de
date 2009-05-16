D3DXVECTOR2 t_planePositions;
LandscapeMesh *t_mesh;
Tree0 *t_tree0;
Tree1 *t_tree1;
Tree2 *t_tree2;
Tree3 *t_tree3;
LandscapeWall1 *t_wall1;
LandscapeWall2 *t_wall2;
LandscapeWall3 *t_wall3;
t_wall3 = new LandscapeWall3();
t_wall3->Scale(GetRelativeScale(112.2f), 0.0f, 0.0f);
t_planePositions = GetPlanePositions(454.95f, 366.7f);
t_wall3->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_wall3->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_wall3);

t_wall2 = new LandscapeWall2();
t_wall2->Scale(GetRelativeScale(112.2f), 0.0f, 0.0f);
t_planePositions = GetPlanePositions(454.95f, 456.7f);
t_wall2->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_wall2->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_wall2);

t_wall1 = new LandscapeWall1();
t_wall1->Scale(GetRelativeScale(112.2f), 0.0f, 0.0f);
t_planePositions = GetPlanePositions(454.95f, 225.7f);
t_wall1->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_wall1->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_wall1);

t_wall1 = new LandscapeWall1();
t_wall1->Scale(GetRelativeScale(112.2f), 0.0f, 0.0f);
t_planePositions = GetPlanePositions(454.95f, 61.7f);
t_wall1->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_wall1->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_wall1);

t_wall1 = new LandscapeWall1();
t_wall1->Scale(GetRelativeScale(112.2f), 0.0f, 0.0f);
t_planePositions = GetPlanePositions(454.95f, 148.7f);
t_wall1->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_wall1->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_wall1);

t_wall1 = new LandscapeWall1();
t_wall1->Scale(GetRelativeScale(112.2f), 0.0f, 0.0f);
t_planePositions = GetPlanePositions(454.95f, 313.7f);
t_wall1->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_wall1->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_wall1);

t_wall1 = new LandscapeWall1();
t_wall1->Scale(GetRelativeScale(40.0f), 0.0f, 0.0f);
t_planePositions = GetPlanePositions(399.0f, 333.85f);
t_wall1->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_wall1->Rotate(0.0f,90.0f, 0.0f);
m_testScene->AddMesh(t_wall1);

t_tree3 = new Tree3();
t_tree3->UniformScale(GetCorrespondingScale(MESH_TREE_3_ID));
t_planePositions = GetPlanePositions(63.5f, 16.95f);
t_tree3->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_tree3->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_tree3);

t_tree2 = new Tree2();
t_tree2->UniformScale(GetCorrespondingScale(MESH_TREE_2_ID));
t_planePositions = GetPlanePositions(50.45f, 17.95f);
t_tree2->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_tree2->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_tree2);

t_tree1 = new Tree1();
t_tree1->UniformScale(GetCorrespondingScale(MESH_TREE_1_ID));
t_planePositions = GetPlanePositions(37.5f, 17.95f);
t_tree1->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_tree1->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_tree1);

t_tree0 = new Tree0();
t_tree0->UniformScale(GetCorrespondingScale(MESH_TREE_0_ID));
t_planePositions = GetPlanePositions(23.6f, 19.95f);
t_tree0->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_tree0->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_tree0);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(267.45f, 294.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(207.45f, 294.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(167.45f, 294.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(50.45f, 292.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(10.45f, 292.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(80.45f, 332.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(80.45f, 362.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(50.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(10.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(129.45f, 331.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(139.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(169.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(199.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(229.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(259.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(289.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(399.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(429.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(459.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(489.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(362.45f, 356.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(362.45f, 326.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(412.45f, 430.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(382.45f, 430.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(492.45f, 430.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(362.45f, 450.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(362.45f, 480.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(315.45f, 480.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(294.45f, 429.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(234.45f, 429.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(208.45f, 459.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(208.45f, 489.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(161.45f, 489.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(161.45f, 459.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(141.45f, 427.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(111.45f, 427.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_02_ID));
t_planePositions = GetPlanePositions(71.45f, 427.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_HOUSE_5_ID,GetCorrespondingTextID(MESH_HOUSE_5_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_HOUSE_5_ID));
t_planePositions = GetPlanePositions(418.45f, 175.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_HOUSE_4_ID,GetCorrespondingTextID(MESH_HOUSE_4_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_HOUSE_4_ID));
t_planePositions = GetPlanePositions(238.45f, 465.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_HOUSE_3_ID,GetCorrespondingTextID(MESH_HOUSE_3_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_HOUSE_3_ID));
t_planePositions = GetPlanePositions(258.45f, 175.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_HOUSE_2_ID,GetCorrespondingTextID(MESH_HOUSE_2_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_HOUSE_2_ID));
t_planePositions = GetPlanePositions(255.45f, 207.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_HOUSE_ID,GetCorrespondingTextID(MESH_HOUSE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_HOUSE_ID));
t_planePositions = GetPlanePositions(429.55f, 338.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(14.5f, 243.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(44.5f, 243.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(74.5f, 243.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(104.5f, 243.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(154.5f, 213.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(154.5f, 183.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(154.5f, 153.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(154.5f, 123.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(154.5f, 93.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(154.5f, 63.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(154.5f, 33.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(209.5f, 53.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(209.5f, 83.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(209.5f, 113.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(209.5f, 143.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(209.5f, 173.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(209.5f, 203.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(311.5f, 203.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(311.5f, 173.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(311.5f, 143.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(311.5f, 113.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(311.5f, 83.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(361.5f, 83.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(361.5f, 113.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(361.5f, 143.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(361.5f, 173.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(361.5f, 203.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(416.5f, 248.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(476.5f, 295.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(436.5f, 295.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,GetCorrespondingTextID(MESH_STREET_LIGHT_01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_STREET_LIGHT_01_ID));
t_planePositions = GetPlanePositions(396.5f, 295.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_BENCH_ID,GetCorrespondingTextID(MESH_BENCH_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_BENCH_ID));
t_planePositions = GetPlanePositions(35.5f, 102.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_BENCH_ID,GetCorrespondingTextID(MESH_BENCH_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_BENCH_ID));
t_planePositions = GetPlanePositions(65.5f, 82.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_BENCH_ID,GetCorrespondingTextID(MESH_BENCH_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_BENCH_ID));
t_planePositions = GetPlanePositions(105.5f, 62.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_BENCH_ID,GetCorrespondingTextID(MESH_BENCH_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_BENCH_ID));
t_planePositions = GetPlanePositions(105.5f, 202.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,180.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_BENCH_ID,GetCorrespondingTextID(MESH_BENCH_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_BENCH_ID));
t_planePositions = GetPlanePositions(65.5f, 182.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,180.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_BENCH_ID,GetCorrespondingTextID(MESH_BENCH_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_BENCH_ID));
t_planePositions = GetPlanePositions(35.5f, 153.0f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,180.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIGN03_ID,GetCorrespondingTextID(MESH_SIGN03_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIGN03_ID));
t_planePositions = GetPlanePositions(447.45f, 37.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,-90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIGN03_ID,GetCorrespondingTextID(MESH_SIGN03_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIGN03_ID));
t_planePositions = GetPlanePositions(263.5f, 33.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,-90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIGN03_ID,GetCorrespondingTextID(MESH_SIGN03_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIGN03_ID));
t_planePositions = GetPlanePositions(453.45f, 248.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,-90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIGN02_ID,GetCorrespondingTextID(MESH_SIGN02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIGN02_ID));
t_planePositions = GetPlanePositions(311.45f, 294.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIGN02_ID,GetCorrespondingTextID(MESH_SIGN02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIGN02_ID));
t_planePositions = GetPlanePositions(265.5f, 427.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIGN02_ID,GetCorrespondingTextID(MESH_SIGN02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIGN02_ID));
t_planePositions = GetPlanePositions(449.45f, 429.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIGN01_ID,GetCorrespondingTextID(MESH_SIGN01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIGN01_ID));
t_planePositions = GetPlanePositions(362.45f, 246.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIGN01_ID,GetCorrespondingTextID(MESH_SIGN01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIGN01_ID));
t_planePositions = GetPlanePositions(358.45f, 386.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIGN01_ID,GetCorrespondingTextID(MESH_SIGN01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIGN01_ID));
t_planePositions = GetPlanePositions(130.5f, 294.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIDEWALK_BARRIER_ID,GetCorrespondingTextID(MESH_SIDEWALK_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIDEWALK_BARRIER_ID));
t_planePositions = GetPlanePositions(14.5f, 427.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIDEWALK_BARRIER_ID,GetCorrespondingTextID(MESH_SIDEWALK_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIDEWALK_BARRIER_ID));
t_planePositions = GetPlanePositions(16.0f, 427.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIDEWALK_BARRIER_ID,GetCorrespondingTextID(MESH_SIDEWALK_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIDEWALK_BARRIER_ID));
t_planePositions = GetPlanePositions(17.5f, 427.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIDEWALK_BARRIER_ID,GetCorrespondingTextID(MESH_SIDEWALK_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIDEWALK_BARRIER_ID));
t_planePositions = GetPlanePositions(19.0f, 427.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIDEWALK_BARRIER_ID,GetCorrespondingTextID(MESH_SIDEWALK_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIDEWALK_BARRIER_ID));
t_planePositions = GetPlanePositions(21.0f, 427.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIDEWALK_BARRIER_ID,GetCorrespondingTextID(MESH_SIDEWALK_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIDEWALK_BARRIER_ID));
t_planePositions = GetPlanePositions(23.0f, 427.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIDEWALK_BARRIER_ID,GetCorrespondingTextID(MESH_SIDEWALK_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIDEWALK_BARRIER_ID));
t_planePositions = GetPlanePositions(24.5f, 427.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_SIDEWALK_BARRIER_ID,GetCorrespondingTextID(MESH_SIDEWALK_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_SIDEWALK_BARRIER_ID));
t_planePositions = GetPlanePositions(26.0f, 427.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX01_ID,GetCorrespondingTextID(MESH_MAILBOX01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX01_ID));
t_planePositions = GetPlanePositions(308.45f, 296.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX01_ID,GetCorrespondingTextID(MESH_MAILBOX01_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX01_ID));
t_planePositions = GetPlanePositions(150.5f, 241.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(145.5f, 442.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(301.45f, 444.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(380.45f, 449.0f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(382.45f, 368.0f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(145.5f, 368.0f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(63.5f, 309.0f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(382.45f, 225.7f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(382.45f, 177.7f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(382.45f, 121.7f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_MAILBOX02_ID,GetCorrespondingTextID(MESH_MAILBOX02_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_MAILBOX02_ID));
t_planePositions = GetPlanePositions(232.45f, 56.7f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_GARDEN_BORDER_ID,GetCorrespondingTextID(MESH_GARDEN_BORDER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_GARDEN_BORDER_ID));
t_planePositions = GetPlanePositions(16.6f, 440.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_GARDEN_BORDER_ID,GetCorrespondingTextID(MESH_GARDEN_BORDER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_GARDEN_BORDER_ID));
t_planePositions = GetPlanePositions(23.6f, 440.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_GARDEN_BORDER_ID,GetCorrespondingTextID(MESH_GARDEN_BORDER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_GARDEN_BORDER_ID));
t_planePositions = GetPlanePositions(27.6f, 440.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_GARDEN_BORDER_ID,GetCorrespondingTextID(MESH_GARDEN_BORDER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_GARDEN_BORDER_ID));
t_planePositions = GetPlanePositions(30.6f, 440.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_GARDEN_BORDER_ID,GetCorrespondingTextID(MESH_GARDEN_BORDER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_GARDEN_BORDER_ID));
t_planePositions = GetPlanePositions(34.6f, 440.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_GARDEN_BORDER_ID,GetCorrespondingTextID(MESH_GARDEN_BORDER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_GARDEN_BORDER_ID));
t_planePositions = GetPlanePositions(37.6f, 440.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_GARDEN_BORDER_ID,GetCorrespondingTextID(MESH_GARDEN_BORDER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_GARDEN_BORDER_ID));
t_planePositions = GetPlanePositions(40.6f, 440.9f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_CAFE_TABLE_ID,GetCorrespondingTextID(MESH_CAFE_TABLE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_CAFE_TABLE_ID));
t_planePositions = GetPlanePositions(225.3f, 242.85f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_CAFE_TABLE_ID,GetCorrespondingTextID(MESH_CAFE_TABLE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_CAFE_TABLE_ID));
t_planePositions = GetPlanePositions(237.05f, 242.85f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_CAFE_TABLE_ID,GetCorrespondingTextID(MESH_CAFE_TABLE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_CAFE_TABLE_ID));
t_planePositions = GetPlanePositions(250.9f, 244.35f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_CAFE_TABLE_ID,GetCorrespondingTextID(MESH_CAFE_TABLE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_CAFE_TABLE_ID));
t_planePositions = GetPlanePositions(262.9f, 241.7f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_CAFE_TABLE_ID,GetCorrespondingTextID(MESH_CAFE_TABLE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_CAFE_TABLE_ID));
t_planePositions = GetPlanePositions(273.9f, 243.2f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_CAFE_TABLE_ID,GetCorrespondingTextID(MESH_CAFE_TABLE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_CAFE_TABLE_ID));
t_planePositions = GetPlanePositions(285.8f, 243.95f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_CAFE_TABLE_ID,GetCorrespondingTextID(MESH_CAFE_TABLE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_CAFE_TABLE_ID));
t_planePositions = GetPlanePositions(293.9f, 243.6f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_PARKING_BARRIER_ID,GetCorrespondingTextID(MESH_PARKING_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_PARKING_BARRIER_ID));
t_planePositions = GetPlanePositions(2.3f, 406.5f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,-90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_PARKING_BARRIER_ID,GetCorrespondingTextID(MESH_PARKING_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_PARKING_BARRIER_ID));
t_planePositions = GetPlanePositions(509.55f, 407.5f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_PARKING_BARRIER_ID,GetCorrespondingTextID(MESH_PARKING_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_PARKING_BARRIER_ID));
t_planePositions = GetPlanePositions(509.55f, 269.5f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_PARKING_BARRIER_ID,GetCorrespondingTextID(MESH_PARKING_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_PARKING_BARRIER_ID));
t_planePositions = GetPlanePositions(509.55f, 14.5f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,90.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_PARKING_BARRIER_ID,GetCorrespondingTextID(MESH_PARKING_BARRIER_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_PARKING_BARRIER_ID));
t_planePositions = GetPlanePositions(186.55f, 509.5f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,180.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_TRAFFIC_CONE_ID,GetCorrespondingTextID(MESH_TRAFFIC_CONE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_TRAFFIC_CONE_ID));
t_planePositions = GetPlanePositions(330.3f, 504.3f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_TRAFFIC_CONE_ID,GetCorrespondingTextID(MESH_TRAFFIC_CONE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_TRAFFIC_CONE_ID));
t_planePositions = GetPlanePositions(343.3f, 504.3f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_TRAFFIC_CONE_ID,GetCorrespondingTextID(MESH_TRAFFIC_CONE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_TRAFFIC_CONE_ID));
t_planePositions = GetPlanePositions(6.7f, 262.0f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

t_mesh = new LandscapeMesh(MESH_TRAFFIC_CONE_ID,GetCorrespondingTextID(MESH_TRAFFIC_CONE_ID));
t_mesh->UniformScale(GetCorrespondingScale(MESH_TRAFFIC_CONE_ID));
t_planePositions = GetPlanePositions(6.7f, 275.5f);
t_mesh->SetPosition(t_planePositions.x,0.0f, t_planePositions.y);
t_mesh->Rotate(0.0f,0.0f, 0.0f);
m_testScene->AddMesh(t_mesh);

