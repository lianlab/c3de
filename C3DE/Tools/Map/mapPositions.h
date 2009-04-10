D3DXVECTOR2 t_planePositions;
LandscapeMesh *t_mesh;
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

