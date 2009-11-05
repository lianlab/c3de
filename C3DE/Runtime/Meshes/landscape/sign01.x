xof 0303txt 0032


template VertexDuplicationIndices { 
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}
template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array float weights[nWeights];
 Matrix4x4 matrixOffset;
}

Frame RootFrame {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,-1.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Frame sign_25mph {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,0.001400,-1.000000,0.000000,
    0.000000,1.000000,0.001400,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Mesh {
228;
0.037400; 0.037400; -0.000000;,
0.037400; -0.037400; -0.000000;,
-0.037400; -0.037400; -0.000000;,
-0.037400; 0.037400; -0.000000;,
0.037400; 0.037400; 2.930800;,
-0.037400; 0.037400; 2.930800;,
-0.037400; -0.037400; 2.930800;,
0.037400; -0.037400; 2.930800;,
0.037400; 0.037400; -0.000000;,
0.037400; 0.037400; 2.930800;,
0.037400; -0.037400; 2.930800;,
0.037400; -0.037400; -0.000000;,
0.037400; -0.037400; -0.000000;,
0.037400; -0.037400; 2.930800;,
-0.037400; -0.037400; 2.930800;,
-0.037400; -0.037400; -0.000000;,
-0.037400; -0.037400; -0.000000;,
-0.037400; -0.037400; 2.930800;,
-0.037400; 0.037400; 2.930800;,
-0.037400; 0.037400; -0.000000;,
0.037400; 0.037400; 2.930800;,
0.037400; 0.037400; -0.000000;,
-0.037400; 0.037400; -0.000000;,
-0.037400; 0.037400; 2.930800;,
-0.006600; -0.062200; 2.886800;,
-0.004900; -0.070100; 2.880700;,
0.013500; -0.070100; 2.875800;,
0.018000; -0.062200; 2.880200;,
-0.024600; -0.062200; 2.868800;,
-0.018500; -0.070100; 2.867200;,
-0.004900; -0.070100; 2.880700;,
-0.006600; -0.062200; 2.886800;,
-0.018000; -0.062200; 2.844300;,
-0.013500; -0.070100; 2.848800;,
-0.018500; -0.070100; 2.867200;,
-0.024600; -0.062200; 2.868800;,
0.006600; -0.062200; 2.837700;,
0.004900; -0.070100; 2.843800;,
-0.013500; -0.070100; 2.848800;,
-0.018000; -0.062200; 2.844300;,
0.024600; -0.062200; 2.855700;,
0.018500; -0.070100; 2.857300;,
0.004900; -0.070100; 2.843800;,
0.006600; -0.062200; 2.837700;,
0.018000; -0.062200; 2.880200;,
0.013500; -0.070100; 2.875800;,
0.018500; -0.070100; 2.857300;,
0.024600; -0.062200; 2.855700;,
0.000000; -0.073700; 2.862300;,
0.013500; -0.070100; 2.875800;,
-0.004900; -0.070100; 2.880700;,
0.000000; -0.073700; 2.862300;,
-0.004900; -0.070100; 2.880700;,
-0.018500; -0.070100; 2.867200;,
0.000000; -0.073700; 2.862300;,
-0.018500; -0.070100; 2.867200;,
-0.013500; -0.070100; 2.848800;,
0.000000; -0.073700; 2.862300;,
-0.013500; -0.070100; 2.848800;,
0.004900; -0.070100; 2.843800;,
0.000000; -0.073700; 2.862300;,
0.004900; -0.070100; 2.843800;,
0.018500; -0.070100; 2.857300;,
0.000000; -0.073700; 2.862300;,
0.018500; -0.070100; 2.857300;,
0.013500; -0.070100; 2.875800;,
-0.333800; -0.038600; 3.019700;,
0.333700; -0.038600; 3.019700;,
0.333700; -0.038600; 2.982500;,
-0.333800; -0.038600; 2.982500;,
-0.333800; -0.060500; 3.019700;,
0.333700; -0.060500; 3.019700;,
0.333700; -0.038600; 3.019700;,
-0.333800; -0.038600; 3.019700;,
-0.333800; -0.060500; 2.982500;,
-0.374400; -0.060500; 2.982500;,
-0.374400; -0.060500; 2.111000;,
-0.333800; -0.060500; 2.111000;,
-0.333800; -0.038600; 2.073700;,
-0.363200; -0.038900; 2.084900;,
-0.374400; -0.038600; 2.111000;,
-0.333800; -0.038600; 2.111000;,
-0.333800; -0.038600; 2.111000;,
-0.374400; -0.038600; 2.111000;,
-0.374400; -0.038600; 2.982500;,
-0.333800; -0.038600; 2.982500;,
-0.333800; -0.060500; 3.019700;,
-0.363200; -0.060200; 3.008600;,
-0.374400; -0.060500; 2.982500;,
-0.333800; -0.060500; 2.982500;,
-0.333800; -0.060500; 2.073700;,
-0.363200; -0.060200; 2.084900;,
-0.363200; -0.038900; 2.084900;,
-0.333800; -0.038600; 2.073700;,
-0.333800; -0.060500; 2.111000;,
-0.374400; -0.060500; 2.111000;,
-0.363200; -0.060200; 2.084900;,
-0.333800; -0.060500; 2.073700;,
0.333700; -0.038600; 3.019700;,
0.363200; -0.038900; 3.008600;,
0.374400; -0.038600; 2.982500;,
0.333700; -0.038600; 2.982500;,
0.333800; -0.060500; 2.111000;,
-0.333800; -0.060500; 2.111000;,
-0.333800; -0.060500; 2.073700;,
0.333800; -0.060500; 2.073700;,
0.333800; -0.060500; 2.073700;,
-0.333800; -0.060500; 2.073700;,
-0.333800; -0.038600; 2.073700;,
0.333800; -0.038600; 2.073700;,
0.333700; -0.060500; 3.019700;,
0.363200; -0.060200; 3.008600;,
0.363200; -0.038900; 3.008600;,
0.333700; -0.038600; 3.019700;,
0.333700; -0.060500; 3.019700;,
-0.333800; -0.060500; 3.019700;,
-0.333800; -0.060500; 2.982500;,
0.333700; -0.060500; 2.982500;,
0.333700; -0.038600; 2.111000;,
-0.333800; -0.038600; 2.111000;,
-0.333800; -0.038600; 2.982500;,
0.333700; -0.038600; 2.982500;,
0.333800; -0.038600; 2.073700;,
-0.333800; -0.038600; 2.073700;,
-0.333800; -0.038600; 2.111000;,
0.333700; -0.038600; 2.111000;,
0.333700; -0.060500; 2.982500;,
-0.333800; -0.060500; 2.982500;,
-0.333800; -0.060500; 2.111000;,
0.333800; -0.060500; 2.111000;,
0.374400; -0.060500; 2.111000;,
0.374400; -0.060500; 2.982500;,
0.333700; -0.060500; 2.982500;,
0.333800; -0.060500; 2.111000;,
-0.374400; -0.060500; 2.111000;,
-0.374400; -0.060500; 2.982500;,
-0.374400; -0.038600; 2.982500;,
-0.374400; -0.038600; 2.111000;,
0.374400; -0.060500; 2.111000;,
0.363200; -0.060200; 2.084900;,
0.363200; -0.038900; 2.084900;,
0.374400; -0.038600; 2.111000;,
0.374400; -0.038600; 2.111000;,
0.363200; -0.038900; 2.084900;,
0.333800; -0.038600; 2.073700;,
0.333700; -0.038600; 2.111000;,
0.374400; -0.038600; 2.982500;,
0.374400; -0.038600; 2.111000;,
0.333700; -0.038600; 2.111000;,
0.333700; -0.038600; 2.982500;,
0.374400; -0.060500; 2.982500;,
0.363200; -0.060200; 3.008600;,
0.333700; -0.060500; 3.019700;,
0.333700; -0.060500; 2.982500;,
-0.374400; -0.060500; 2.982500;,
-0.363200; -0.060200; 3.008600;,
-0.363200; -0.038900; 3.008600;,
-0.374400; -0.038600; 2.982500;,
0.374400; -0.060500; 2.982500;,
0.374400; -0.060500; 2.111000;,
0.374400; -0.038600; 2.111000;,
0.374400; -0.038600; 2.982500;,
0.363200; -0.038900; 3.008600;,
0.363200; -0.060200; 3.008600;,
0.374400; -0.060500; 2.982500;,
0.374400; -0.038600; 2.982500;,
-0.363200; -0.038900; 3.008600;,
-0.363200; -0.060200; 3.008600;,
-0.333800; -0.060500; 3.019700;,
-0.333800; -0.038600; 3.019700;,
-0.363200; -0.038900; 2.084900;,
-0.363200; -0.060200; 2.084900;,
-0.374400; -0.060500; 2.111000;,
-0.374400; -0.038600; 2.111000;,
0.363200; -0.038900; 2.084900;,
0.363200; -0.060200; 2.084900;,
0.333800; -0.060500; 2.073700;,
0.333800; -0.038600; 2.073700;,
0.363200; -0.060200; 2.084900;,
0.374400; -0.060500; 2.111000;,
0.333800; -0.060500; 2.111000;,
0.333800; -0.060500; 2.073700;,
-0.363200; -0.038900; 3.008600;,
-0.333800; -0.038600; 3.019700;,
-0.333800; -0.038600; 2.982500;,
-0.374400; -0.038600; 2.982500;,
0.000000; -0.073700; 2.189900;,
0.018500; -0.070100; 2.185000;,
0.013500; -0.070100; 2.203500;,
0.000000; -0.073700; 2.189900;,
0.004900; -0.070100; 2.171500;,
0.018500; -0.070100; 2.185000;,
0.000000; -0.073700; 2.189900;,
-0.013500; -0.070100; 2.176400;,
0.004900; -0.070100; 2.171500;,
0.000000; -0.073700; 2.189900;,
-0.018500; -0.070100; 2.194900;,
-0.013500; -0.070100; 2.176400;,
0.000000; -0.073700; 2.189900;,
-0.004900; -0.070100; 2.208400;,
-0.018500; -0.070100; 2.194900;,
0.000000; -0.073700; 2.189900;,
0.013500; -0.070100; 2.203500;,
-0.004900; -0.070100; 2.208400;,
0.018000; -0.062200; 2.207900;,
0.013500; -0.070100; 2.203500;,
0.018500; -0.070100; 2.185000;,
0.024600; -0.062200; 2.183400;,
0.024600; -0.062200; 2.183400;,
0.018500; -0.070100; 2.185000;,
0.004900; -0.070100; 2.171500;,
0.006600; -0.062200; 2.165400;,
0.006600; -0.062200; 2.165400;,
0.004900; -0.070100; 2.171500;,
-0.013500; -0.070100; 2.176400;,
-0.018000; -0.062200; 2.172000;,
-0.018000; -0.062200; 2.172000;,
-0.013500; -0.070100; 2.176400;,
-0.018500; -0.070100; 2.194900;,
-0.024600; -0.062200; 2.196500;,
-0.024600; -0.062200; 2.196500;,
-0.018500; -0.070100; 2.194900;,
-0.004900; -0.070100; 2.208400;,
-0.006600; -0.062200; 2.214500;,
-0.006600; -0.062200; 2.214500;,
-0.004900; -0.070100; 2.208400;,
0.013500; -0.070100; 2.203500;,
0.018000; -0.062200; 2.207900;;
60;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
4; 24, 27, 26, 25;,
4; 28, 31, 30, 29;,
4; 32, 35, 34, 33;,
4; 36, 39, 38, 37;,
4; 40, 43, 42, 41;,
4; 44, 47, 46, 45;,
3; 48, 50, 49;,
3; 51, 53, 52;,
3; 54, 56, 55;,
3; 57, 59, 58;,
3; 60, 62, 61;,
3; 63, 65, 64;,
4; 66, 69, 68, 67;,
4; 70, 73, 72, 71;,
4; 74, 77, 76, 75;,
4; 78, 81, 80, 79;,
4; 82, 85, 84, 83;,
4; 86, 89, 88, 87;,
4; 90, 93, 92, 91;,
4; 94, 97, 96, 95;,
4; 98, 101, 100, 99;,
4; 102, 105, 104, 103;,
4; 106, 109, 108, 107;,
4; 110, 113, 112, 111;,
4; 114, 117, 116, 115;,
4; 118, 121, 120, 119;,
4; 122, 125, 124, 123;,
4; 126, 129, 128, 127;,
4; 130, 133, 132, 131;,
4; 134, 137, 136, 135;,
4; 138, 141, 140, 139;,
4; 142, 145, 144, 143;,
4; 146, 149, 148, 147;,
4; 150, 153, 152, 151;,
4; 154, 157, 156, 155;,
4; 158, 161, 160, 159;,
4; 162, 165, 164, 163;,
4; 166, 169, 168, 167;,
4; 170, 173, 172, 171;,
4; 174, 177, 176, 175;,
4; 178, 181, 180, 179;,
4; 182, 185, 184, 183;,
3; 186, 188, 187;,
3; 189, 191, 190;,
3; 192, 194, 193;,
3; 195, 197, 196;,
3; 198, 200, 199;,
3; 201, 203, 202;,
4; 204, 207, 206, 205;,
4; 208, 211, 210, 209;,
4; 212, 215, 214, 213;,
4; 216, 219, 218, 217;,
4; 220, 223, 222, 221;,
4; 224, 227, 226, 225;;
  MeshMaterialList {
    2;
    60;
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1;;
  Material sign_25mph_tex {
    0.756191; 0.756191; 0.756191;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Mat1 {
    1.0; 1.0; 1.0; 1.0;;
    1.0;
    1.0; 1.0; 1.0;;
    0.0; 0.0; 0.0;;
  TextureFilename {    "sign_25mph_tex.png";  }
  }  // End of Material
    }  //End of MeshMaterialList
  MeshNormals {
228;
    0.577349; 0.577349; -0.577349;,
    0.577349; -0.577349; -0.577349;,
    -0.577349; -0.577349; -0.577349;,
    -0.577349; 0.577349; -0.577349;,
    0.577349; 0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.577349; 0.577349; -0.577349;,
    0.577349; 0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.577349; -0.577349; -0.577349;,
    0.577349; -0.577349; -0.577349;,
    0.577349; -0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    -0.577349; -0.577349; -0.577349;,
    -0.577349; -0.577349; -0.577349;,
    -0.577349; -0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.577349; 0.577349; -0.577349;,
    0.577349; 0.577349; 0.577349;,
    0.577349; 0.577349; -0.577349;,
    -0.577349; 0.577349; -0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.201392; -0.628040; 0.751640;,
    -0.152226; -0.808710; 0.568133;,
    0.415876; -0.808710; 0.415876;,
    0.550218; -0.628040; 0.550249;,
    -0.751640; -0.628040; 0.201392;,
    -0.568133; -0.808710; 0.152226;,
    -0.152226; -0.808710; 0.568133;,
    -0.201392; -0.628040; 0.751640;,
    -0.550249; -0.628010; -0.550249;,
    -0.415906; -0.808710; -0.415906;,
    -0.568133; -0.808710; 0.152226;,
    -0.751640; -0.628040; 0.201392;,
    0.201392; -0.628010; -0.751671;,
    0.152226; -0.808710; -0.568133;,
    -0.415906; -0.808710; -0.415906;,
    -0.550249; -0.628010; -0.550249;,
    0.751640; -0.628040; -0.201392;,
    0.568133; -0.808710; -0.152226;,
    0.152226; -0.808710; -0.568133;,
    0.201392; -0.628010; -0.751671;,
    0.550218; -0.628040; 0.550249;,
    0.415876; -0.808710; 0.415876;,
    0.568133; -0.808710; -0.152226;,
    0.751640; -0.628040; -0.201392;,
    0.000000; -1.000000; 0.000000;,
    0.415876; -0.808710; 0.415876;,
    -0.152226; -0.808710; 0.568133;,
    0.000000; -1.000000; 0.000000;,
    -0.152226; -0.808710; 0.568133;,
    -0.568133; -0.808710; 0.152226;,
    0.000000; -1.000000; 0.000000;,
    -0.568133; -0.808710; 0.152226;,
    -0.415906; -0.808710; -0.415906;,
    0.000000; -1.000000; 0.000000;,
    -0.415906; -0.808710; -0.415906;,
    0.152226; -0.808710; -0.568133;,
    0.000000; -1.000000; 0.000000;,
    0.152226; -0.808710; -0.568133;,
    0.568133; -0.808710; -0.152226;,
    0.000000; -1.000000; 0.000000;,
    0.568133; -0.808710; -0.152226;,
    0.415876; -0.808710; 0.415876;,
    -0.134678; 0.668935; 0.730979;,
    0.134617; 0.668935; 0.731010;,
    0.001404; 0.999969; 0.001526;,
    -0.001404; 0.999969; 0.001526;,
    -0.134861; -0.668844; 0.731040;,
    0.131748; 0.670980; 0.729637;,
    0.134617; 0.668935; 0.731010;,
    -0.134678; 0.668935; 0.730979;,
    -0.001404; -0.999969; 0.001526;,
    -0.731468; -0.664968; 0.150761;,
    -0.731468; -0.664998; -0.150670;,
    -0.001404; -0.999969; -0.001526;,
    -0.134800; 0.668874; -0.731010;,
    -0.541215; 0.623463; -0.564226;,
    -0.731468; 0.664998; -0.150670;,
    -0.001404; 0.999969; -0.001526;,
    -0.001404; 0.999969; -0.001526;,
    -0.731468; 0.664998; -0.150670;,
    -0.731468; 0.664968; 0.150761;,
    -0.001404; 0.999969; 0.001526;,
    -0.134861; -0.668844; 0.731040;,
    -0.541124; -0.623432; 0.564318;,
    -0.731468; -0.664968; 0.150761;,
    -0.001404; -0.999969; 0.001526;,
    -0.134800; -0.668874; -0.731010;,
    -0.541215; -0.623463; -0.564226;,
    -0.541215; 0.623463; -0.564226;,
    -0.134800; 0.668874; -0.731010;,
    -0.001404; -0.999969; -0.001526;,
    -0.731468; -0.664998; -0.150670;,
    -0.541215; -0.623463; -0.564226;,
    -0.134800; -0.668874; -0.731010;,
    0.134617; 0.668935; 0.731010;,
    0.541124; 0.623402; 0.564348;,
    0.731468; 0.664998; 0.150639;,
    0.001404; 0.999969; 0.001526;,
    0.001404; -0.999969; -0.001526;,
    -0.001404; -0.999969; -0.001526;,
    -0.134800; -0.668874; -0.731010;,
    0.134709; -0.668905; -0.731010;,
    0.134709; -0.668905; -0.731010;,
    -0.134800; -0.668874; -0.731010;,
    -0.134800; 0.668874; -0.731010;,
    0.134709; 0.668905; -0.731010;,
    0.131748; 0.670980; 0.729637;,
    0.541124; -0.623402; 0.564348;,
    0.541124; 0.623402; 0.564348;,
    0.134617; 0.668935; 0.731010;,
    0.131748; 0.670980; 0.729637;,
    -0.134861; -0.668844; 0.731040;,
    -0.001404; -0.999969; 0.001526;,
    0.001404; -0.999969; 0.001526;,
    0.001404; 0.999969; -0.001526;,
    -0.001404; 0.999969; -0.001526;,
    -0.001404; 0.999969; 0.001526;,
    0.001404; 0.999969; 0.001526;,
    0.134709; 0.668905; -0.731010;,
    -0.134800; 0.668874; -0.731010;,
    -0.001404; 0.999969; -0.001526;,
    0.001404; 0.999969; -0.001526;,
    0.001404; -0.999969; 0.001526;,
    -0.001404; -0.999969; 0.001526;,
    -0.001404; -0.999969; -0.001526;,
    0.001404; -0.999969; -0.001526;,
    -0.730308; -0.666921; 0.147771;,
    0.731468; -0.664998; 0.150639;,
    0.001404; -0.999969; 0.001526;,
    0.001404; -0.999969; -0.001526;,
    -0.731468; -0.664998; -0.150670;,
    -0.731468; -0.664968; 0.150761;,
    -0.731468; 0.664968; 0.150761;,
    -0.731468; 0.664998; -0.150670;,
    -0.730308; -0.666921; 0.147771;,
    0.541124; -0.623432; -0.564348;,
    0.541093; 0.623493; -0.564318;,
    0.731437; 0.665029; -0.150639;,
    0.731437; 0.665029; -0.150639;,
    0.541093; 0.623493; -0.564318;,
    0.134709; 0.668905; -0.731010;,
    0.001404; 0.999969; -0.001526;,
    0.731468; 0.664998; 0.150639;,
    0.731437; 0.665029; -0.150639;,
    0.001404; 0.999969; -0.001526;,
    0.001404; 0.999969; 0.001526;,
    0.731468; -0.664998; 0.150639;,
    0.541124; -0.623402; 0.564348;,
    0.131748; 0.670980; 0.729637;,
    0.001404; -0.999969; 0.001526;,
    -0.731468; -0.664968; 0.150761;,
    -0.541124; -0.623432; 0.564318;,
    -0.541093; 0.623493; 0.564287;,
    -0.731468; 0.664968; 0.150761;,
    0.731468; -0.664998; 0.150639;,
    -0.730308; -0.666921; 0.147771;,
    0.731437; 0.665029; -0.150639;,
    0.731468; 0.664998; 0.150639;,
    0.541124; 0.623402; 0.564348;,
    0.541124; -0.623402; 0.564348;,
    0.731468; -0.664998; 0.150639;,
    0.731468; 0.664998; 0.150639;,
    -0.541093; 0.623493; 0.564287;,
    -0.541124; -0.623432; 0.564318;,
    -0.134861; -0.668844; 0.731040;,
    -0.134678; 0.668935; 0.730979;,
    -0.541215; 0.623463; -0.564226;,
    -0.541215; -0.623463; -0.564226;,
    -0.731468; -0.664998; -0.150670;,
    -0.731468; 0.664998; -0.150670;,
    0.541093; 0.623493; -0.564318;,
    0.541124; -0.623432; -0.564348;,
    0.134709; -0.668905; -0.731010;,
    0.134709; 0.668905; -0.731010;,
    0.541124; -0.623432; -0.564348;,
    -0.730308; -0.666921; 0.147771;,
    0.001404; -0.999969; -0.001526;,
    0.134709; -0.668905; -0.731010;,
    -0.541093; 0.623493; 0.564287;,
    -0.134678; 0.668935; 0.730979;,
    -0.001404; 0.999969; 0.001526;,
    -0.731468; 0.664968; 0.150761;,
    0.000000; -1.000000; 0.000000;,
    0.568133; -0.808710; -0.152226;,
    0.415906; -0.808710; 0.415906;,
    0.000000; -1.000000; 0.000000;,
    0.152226; -0.808710; -0.568133;,
    0.568133; -0.808710; -0.152226;,
    0.000000; -1.000000; 0.000000;,
    -0.415876; -0.808710; -0.415906;,
    0.152226; -0.808710; -0.568133;,
    0.000000; -1.000000; 0.000000;,
    -0.568133; -0.808710; 0.152226;,
    -0.415876; -0.808710; -0.415906;,
    0.000000; -1.000000; 0.000000;,
    -0.152226; -0.808710; 0.568133;,
    -0.568133; -0.808710; 0.152226;,
    0.000000; -1.000000; 0.000000;,
    0.415906; -0.808710; 0.415906;,
    -0.152226; -0.808710; 0.568133;,
    0.550249; -0.628040; 0.550249;,
    0.415906; -0.808710; 0.415906;,
    0.568133; -0.808710; -0.152226;,
    0.751640; -0.628040; -0.201392;,
    0.751640; -0.628040; -0.201392;,
    0.568133; -0.808710; -0.152226;,
    0.152226; -0.808710; -0.568133;,
    0.201392; -0.628010; -0.751640;,
    0.201392; -0.628010; -0.751640;,
    0.152226; -0.808710; -0.568133;,
    -0.415876; -0.808710; -0.415906;,
    -0.550249; -0.628040; -0.550249;,
    -0.550249; -0.628040; -0.550249;,
    -0.415876; -0.808710; -0.415906;,
    -0.568133; -0.808710; 0.152226;,
    -0.751640; -0.628040; 0.201392;,
    -0.751640; -0.628040; 0.201392;,
    -0.568133; -0.808710; 0.152226;,
    -0.152226; -0.808710; 0.568133;,
    -0.201392; -0.628010; 0.751640;,
    -0.201392; -0.628010; 0.751640;,
    -0.152226; -0.808710; 0.568133;,
    0.415906; -0.808710; 0.415906;,
    0.550249; -0.628040; 0.550249;;
60;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
4; 24, 27, 26, 25;,
4; 28, 31, 30, 29;,
4; 32, 35, 34, 33;,
4; 36, 39, 38, 37;,
4; 40, 43, 42, 41;,
4; 44, 47, 46, 45;,
3; 48, 50, 49;,
3; 51, 53, 52;,
3; 54, 56, 55;,
3; 57, 59, 58;,
3; 60, 62, 61;,
3; 63, 65, 64;,
4; 66, 69, 68, 67;,
4; 70, 73, 72, 71;,
4; 74, 77, 76, 75;,
4; 78, 81, 80, 79;,
4; 82, 85, 84, 83;,
4; 86, 89, 88, 87;,
4; 90, 93, 92, 91;,
4; 94, 97, 96, 95;,
4; 98, 101, 100, 99;,
4; 102, 105, 104, 103;,
4; 106, 109, 108, 107;,
4; 110, 113, 112, 111;,
4; 114, 117, 116, 115;,
4; 118, 121, 120, 119;,
4; 122, 125, 124, 123;,
4; 126, 129, 128, 127;,
4; 130, 133, 132, 131;,
4; 134, 137, 136, 135;,
4; 138, 141, 140, 139;,
4; 142, 145, 144, 143;,
4; 146, 149, 148, 147;,
4; 150, 153, 152, 151;,
4; 154, 157, 156, 155;,
4; 158, 161, 160, 159;,
4; 162, 165, 164, 163;,
4; 166, 169, 168, 167;,
4; 170, 173, 172, 171;,
4; 174, 177, 176, 175;,
4; 178, 181, 180, 179;,
4; 182, 185, 184, 183;,
3; 186, 188, 187;,
3; 189, 191, 190;,
3; 192, 194, 193;,
3; 195, 197, 196;,
3; 198, 200, 199;,
3; 201, 203, 202;,
4; 204, 207, 206, 205;,
4; 208, 211, 210, 209;,
4; 212, 215, 214, 213;,
4; 216, 219, 218, 217;,
4; 220, 223, 222, 221;,
4; 224, 227, 226, 225;;
}  //End of MeshNormals
MeshTextureCoords {
228;
0.168091;-0.986365;,
0.131389;-0.986365;,
0.131389;-0.949663;,
0.168091;-0.949663;,
0.168104;-0.926365;,
0.131402;-0.926365;,
0.131402;-0.889663;,
0.168104;-0.889663;,
0.116803;-0.011694;,
0.116803;-0.983668;,
0.091969;-0.983668;,
0.091969;-0.011694;,
0.091969;-0.011694;,
0.091969;-0.983668;,
0.067134;-0.983668;,
0.067134;-0.011694;,
0.067134;-0.011694;,
0.067134;-0.983668;,
0.042299;-0.983668;,
0.042299;-0.011694;,
0.017464;-0.983668;,
0.017464;-0.011694;,
0.042299;-0.011694;,
0.042299;-0.983668;,
0.246094;-0.988281;,
0.248047;-0.980469;,
0.259766;-0.978516;,
0.265625;-0.982422;,
0.232422;-0.974609;,
0.240234;-0.972656;,
0.248047;-0.980469;,
0.246094;-0.988281;,
0.238281;-0.955078;,
0.244141;-0.960938;,
0.240234;-0.972656;,
0.232422;-0.974609;,
0.257813;-0.951172;,
0.255859;-0.957031;,
0.244141;-0.960938;,
0.238281;-0.955078;,
0.271484;-0.964844;,
0.263672;-0.966797;,
0.255859;-0.957031;,
0.257813;-0.951172;,
0.265625;-0.982422;,
0.259766;-0.978516;,
0.263672;-0.966797;,
0.271484;-0.964844;,
0.251953;-0.968750;,
0.259766;-0.978516;,
0.248047;-0.980469;,
0.251953;-0.968750;,
0.248047;-0.980469;,
0.240234;-0.972656;,
0.251953;-0.968750;,
0.240234;-0.972656;,
0.244141;-0.960938;,
0.251953;-0.968750;,
0.244141;-0.960938;,
0.255859;-0.957031;,
0.251953;-0.968750;,
0.255859;-0.957031;,
0.263672;-0.966797;,
0.251953;-0.968750;,
0.263672;-0.966797;,
0.259766;-0.978516;,
0.525391;-0.705078;,
0.169922;-0.705078;,
0.169922;-0.683594;,
0.525391;-0.683594;,
0.525391;-0.714844;,
0.169922;-0.714844;,
0.169922;-0.705078;,
0.525391;-0.705078;,
0.603516;-0.677734;,
0.583984;-0.677734;,
0.583984;-0.201172;,
0.603516;-0.201172;,
0.525391;-0.185547;,
0.541016;-0.195313;,
0.546875;-0.207031;,
0.525391;-0.207031;,
0.525391;-0.207031;,
0.546875;-0.207031;,
0.546875;-0.683594;,
0.525391;-0.683594;,
0.603516;-0.703125;,
0.585938;-0.695313;,
0.583984;-0.677734;,
0.603516;-0.677734;,
0.525391;-0.173828;,
0.550781;-0.185547;,
0.541016;-0.195313;,
0.525391;-0.185547;,
0.603516;-0.201172;,
0.583984;-0.201172;,
0.585938;-0.185547;,
0.603516;-0.179688;,
0.169922;-0.705078;,
0.154297;-0.699219;,
0.148438;-0.683594;,
0.169922;-0.683594;,
0.966797;-0.201172;,
0.603516;-0.201172;,
0.603516;-0.179688;,
0.966797;-0.177734;,
0.169922;-0.173828;,
0.525391;-0.173828;,
0.525391;-0.185547;,
0.169922;-0.185547;,
0.169922;-0.714844;,
0.144531;-0.705078;,
0.154297;-0.699219;,
0.169922;-0.705078;,
0.966797;-0.699219;,
0.603516;-0.703125;,
0.603516;-0.677734;,
0.966797;-0.677734;,
0.169922;-0.207031;,
0.525391;-0.207031;,
0.525391;-0.683594;,
0.169922;-0.683594;,
0.169922;-0.185547;,
0.525391;-0.185547;,
0.525391;-0.207031;,
0.169922;-0.207031;,
0.966797;-0.677734;,
0.603516;-0.677734;,
0.603516;-0.201172;,
0.966797;-0.201172;,
0.988281;-0.201172;,
0.988281;-0.677734;,
0.966797;-0.677734;,
0.966797;-0.201172;,
0.558594;-0.207031;,
0.562500;-0.683594;,
0.546875;-0.683594;,
0.546875;-0.207031;,
0.132813;-0.207031;,
0.148438;-0.185547;,
0.154297;-0.195313;,
0.148438;-0.207031;,
0.148438;-0.207031;,
0.154297;-0.195313;,
0.169922;-0.185547;,
0.169922;-0.207031;,
0.148438;-0.683594;,
0.148438;-0.207031;,
0.169922;-0.207031;,
0.169922;-0.683594;,
0.988281;-0.677734;,
0.982422;-0.693359;,
0.966797;-0.699219;,
0.966797;-0.677734;,
0.562500;-0.683594;,
0.546875;-0.705078;,
0.541016;-0.699219;,
0.546875;-0.683594;,
0.136719;-0.683594;,
0.132813;-0.207031;,
0.148438;-0.207031;,
0.148438;-0.683594;,
0.154297;-0.699219;,
0.144531;-0.705078;,
0.136719;-0.683594;,
0.148438;-0.683594;,
0.541016;-0.699219;,
0.546875;-0.705078;,
0.525391;-0.714844;,
0.525391;-0.705078;,
0.541016;-0.195313;,
0.550781;-0.185547;,
0.558594;-0.207031;,
0.546875;-0.207031;,
0.154297;-0.195313;,
0.148438;-0.185547;,
0.169922;-0.173828;,
0.169922;-0.185547;,
0.982422;-0.185547;,
0.988281;-0.201172;,
0.966797;-0.201172;,
0.966797;-0.177734;,
0.541016;-0.699219;,
0.525391;-0.705078;,
0.525391;-0.683594;,
0.546875;-0.683594;,
0.296875;-0.968750;,
0.308594;-0.966797;,
0.304688;-0.978516;,
0.296875;-0.968750;,
0.300781;-0.957031;,
0.308594;-0.966797;,
0.296875;-0.968750;,
0.289063;-0.960938;,
0.300781;-0.957031;,
0.296875;-0.968750;,
0.285156;-0.972656;,
0.289063;-0.960938;,
0.296875;-0.968750;,
0.292969;-0.980469;,
0.285156;-0.972656;,
0.296875;-0.968750;,
0.304688;-0.978516;,
0.292969;-0.980469;,
0.310547;-0.982422;,
0.304688;-0.978516;,
0.308594;-0.966797;,
0.316406;-0.964844;,
0.316406;-0.964844;,
0.308594;-0.966797;,
0.300781;-0.957031;,
0.302734;-0.951172;,
0.302734;-0.951172;,
0.300781;-0.957031;,
0.289063;-0.960938;,
0.283203;-0.955078;,
0.283203;-0.955078;,
0.289063;-0.960938;,
0.285156;-0.972656;,
0.277344;-0.974609;,
0.277344;-0.974609;,
0.285156;-0.972656;,
0.292969;-0.980469;,
0.291016;-0.988281;,
0.291016;-0.988281;,
0.292969;-0.980469;,
0.304688;-0.978516;,
0.310547;-0.982422;;
}  //End of MeshTextureCoords
MeshVertexColors {
228;
0;1.000000;1.000000;1.000000;1.000000;,
1;1.000000;1.000000;1.000000;1.000000;,
2;1.000000;1.000000;1.000000;1.000000;,
3;1.000000;1.000000;1.000000;1.000000;,
4;1.000000;1.000000;1.000000;1.000000;,
5;1.000000;1.000000;1.000000;1.000000;,
6;1.000000;1.000000;1.000000;1.000000;,
7;1.000000;1.000000;1.000000;1.000000;,
8;1.000000;1.000000;1.000000;1.000000;,
9;1.000000;1.000000;1.000000;1.000000;,
10;1.000000;1.000000;1.000000;1.000000;,
11;1.000000;1.000000;1.000000;1.000000;,
12;1.000000;1.000000;1.000000;1.000000;,
13;1.000000;1.000000;1.000000;1.000000;,
14;1.000000;1.000000;1.000000;1.000000;,
15;1.000000;1.000000;1.000000;1.000000;,
16;1.000000;1.000000;1.000000;1.000000;,
17;1.000000;1.000000;1.000000;1.000000;,
18;1.000000;1.000000;1.000000;1.000000;,
19;1.000000;1.000000;1.000000;1.000000;,
20;1.000000;1.000000;1.000000;1.000000;,
21;1.000000;1.000000;1.000000;1.000000;,
22;1.000000;1.000000;1.000000;1.000000;,
23;1.000000;1.000000;1.000000;1.000000;,
24;1.000000;1.000000;1.000000;1.000000;,
25;1.000000;1.000000;1.000000;1.000000;,
26;1.000000;1.000000;1.000000;1.000000;,
27;1.000000;1.000000;1.000000;1.000000;,
28;1.000000;1.000000;1.000000;1.000000;,
29;1.000000;1.000000;1.000000;1.000000;,
30;1.000000;1.000000;1.000000;1.000000;,
31;1.000000;1.000000;1.000000;1.000000;,
32;1.000000;1.000000;1.000000;1.000000;,
33;1.000000;1.000000;1.000000;1.000000;,
34;1.000000;1.000000;1.000000;1.000000;,
35;1.000000;1.000000;1.000000;1.000000;,
36;1.000000;1.000000;1.000000;1.000000;,
37;1.000000;1.000000;1.000000;1.000000;,
38;1.000000;1.000000;1.000000;1.000000;,
39;1.000000;1.000000;1.000000;1.000000;,
40;1.000000;1.000000;1.000000;1.000000;,
41;1.000000;1.000000;1.000000;1.000000;,
42;1.000000;1.000000;1.000000;1.000000;,
43;1.000000;1.000000;1.000000;1.000000;,
44;1.000000;1.000000;1.000000;1.000000;,
45;1.000000;1.000000;1.000000;1.000000;,
46;1.000000;1.000000;1.000000;1.000000;,
47;1.000000;1.000000;1.000000;1.000000;,
48;1.000000;1.000000;1.000000;1.000000;,
49;1.000000;1.000000;1.000000;1.000000;,
50;1.000000;1.000000;1.000000;1.000000;,
51;1.000000;1.000000;1.000000;1.000000;,
52;1.000000;1.000000;1.000000;1.000000;,
53;1.000000;1.000000;1.000000;1.000000;,
54;1.000000;1.000000;1.000000;1.000000;,
55;1.000000;1.000000;1.000000;1.000000;,
56;1.000000;1.000000;1.000000;1.000000;,
57;1.000000;1.000000;1.000000;1.000000;,
58;1.000000;1.000000;1.000000;1.000000;,
59;1.000000;1.000000;1.000000;1.000000;,
60;1.000000;1.000000;1.000000;1.000000;,
61;1.000000;1.000000;1.000000;1.000000;,
62;1.000000;1.000000;1.000000;1.000000;,
63;1.000000;1.000000;1.000000;1.000000;,
64;1.000000;1.000000;1.000000;1.000000;,
65;1.000000;1.000000;1.000000;1.000000;,
66;1.000000;1.000000;1.000000;1.000000;,
67;1.000000;1.000000;1.000000;1.000000;,
68;1.000000;1.000000;1.000000;1.000000;,
69;1.000000;1.000000;1.000000;1.000000;,
70;1.000000;1.000000;1.000000;1.000000;,
71;1.000000;1.000000;1.000000;1.000000;,
72;1.000000;1.000000;1.000000;1.000000;,
73;1.000000;1.000000;1.000000;1.000000;,
74;1.000000;1.000000;1.000000;1.000000;,
75;1.000000;1.000000;1.000000;1.000000;,
76;1.000000;1.000000;1.000000;1.000000;,
77;1.000000;1.000000;1.000000;1.000000;,
78;1.000000;1.000000;1.000000;1.000000;,
79;1.000000;1.000000;1.000000;1.000000;,
80;1.000000;1.000000;1.000000;1.000000;,
81;1.000000;1.000000;1.000000;1.000000;,
82;1.000000;1.000000;1.000000;1.000000;,
83;1.000000;1.000000;1.000000;1.000000;,
84;1.000000;1.000000;1.000000;1.000000;,
85;1.000000;1.000000;1.000000;1.000000;,
86;1.000000;1.000000;1.000000;1.000000;,
87;1.000000;1.000000;1.000000;1.000000;,
88;1.000000;1.000000;1.000000;1.000000;,
89;1.000000;1.000000;1.000000;1.000000;,
90;1.000000;1.000000;1.000000;1.000000;,
91;1.000000;1.000000;1.000000;1.000000;,
92;1.000000;1.000000;1.000000;1.000000;,
93;1.000000;1.000000;1.000000;1.000000;,
94;1.000000;1.000000;1.000000;1.000000;,
95;1.000000;1.000000;1.000000;1.000000;,
96;1.000000;1.000000;1.000000;1.000000;,
97;1.000000;1.000000;1.000000;1.000000;,
98;1.000000;1.000000;1.000000;1.000000;,
99;1.000000;1.000000;1.000000;1.000000;,
100;1.000000;1.000000;1.000000;1.000000;,
101;1.000000;1.000000;1.000000;1.000000;,
102;1.000000;1.000000;1.000000;1.000000;,
103;1.000000;1.000000;1.000000;1.000000;,
104;1.000000;1.000000;1.000000;1.000000;,
105;1.000000;1.000000;1.000000;1.000000;,
106;1.000000;1.000000;1.000000;1.000000;,
107;1.000000;1.000000;1.000000;1.000000;,
108;1.000000;1.000000;1.000000;1.000000;,
109;1.000000;1.000000;1.000000;1.000000;,
110;1.000000;1.000000;1.000000;1.000000;,
111;1.000000;1.000000;1.000000;1.000000;,
112;1.000000;1.000000;1.000000;1.000000;,
113;1.000000;1.000000;1.000000;1.000000;,
114;1.000000;1.000000;1.000000;1.000000;,
115;1.000000;1.000000;1.000000;1.000000;,
116;1.000000;1.000000;1.000000;1.000000;,
117;1.000000;1.000000;1.000000;1.000000;,
118;1.000000;1.000000;1.000000;1.000000;,
119;1.000000;1.000000;1.000000;1.000000;,
120;1.000000;1.000000;1.000000;1.000000;,
121;1.000000;1.000000;1.000000;1.000000;,
122;1.000000;1.000000;1.000000;1.000000;,
123;1.000000;1.000000;1.000000;1.000000;,
124;1.000000;1.000000;1.000000;1.000000;,
125;1.000000;1.000000;1.000000;1.000000;,
126;1.000000;1.000000;1.000000;1.000000;,
127;1.000000;1.000000;1.000000;1.000000;,
128;1.000000;1.000000;1.000000;1.000000;,
129;1.000000;1.000000;1.000000;1.000000;,
130;1.000000;1.000000;1.000000;1.000000;,
131;1.000000;1.000000;1.000000;1.000000;,
132;1.000000;1.000000;1.000000;1.000000;,
133;1.000000;1.000000;1.000000;1.000000;,
134;1.000000;1.000000;1.000000;1.000000;,
135;1.000000;1.000000;1.000000;1.000000;,
136;1.000000;1.000000;1.000000;1.000000;,
137;1.000000;1.000000;1.000000;1.000000;,
138;1.000000;1.000000;1.000000;1.000000;,
139;1.000000;1.000000;1.000000;1.000000;,
140;1.000000;1.000000;1.000000;1.000000;,
141;1.000000;1.000000;1.000000;1.000000;,
142;1.000000;1.000000;1.000000;1.000000;,
143;1.000000;1.000000;1.000000;1.000000;,
144;1.000000;1.000000;1.000000;1.000000;,
145;1.000000;1.000000;1.000000;1.000000;,
146;1.000000;1.000000;1.000000;1.000000;,
147;1.000000;1.000000;1.000000;1.000000;,
148;1.000000;1.000000;1.000000;1.000000;,
149;1.000000;1.000000;1.000000;1.000000;,
150;1.000000;1.000000;1.000000;1.000000;,
151;1.000000;1.000000;1.000000;1.000000;,
152;1.000000;1.000000;1.000000;1.000000;,
153;1.000000;1.000000;1.000000;1.000000;,
154;1.000000;1.000000;1.000000;1.000000;,
155;1.000000;1.000000;1.000000;1.000000;,
156;1.000000;1.000000;1.000000;1.000000;,
157;1.000000;1.000000;1.000000;1.000000;,
158;1.000000;1.000000;1.000000;1.000000;,
159;1.000000;1.000000;1.000000;1.000000;,
160;1.000000;1.000000;1.000000;1.000000;,
161;1.000000;1.000000;1.000000;1.000000;,
162;1.000000;1.000000;1.000000;1.000000;,
163;1.000000;1.000000;1.000000;1.000000;,
164;1.000000;1.000000;1.000000;1.000000;,
165;1.000000;1.000000;1.000000;1.000000;,
166;1.000000;1.000000;1.000000;1.000000;,
167;1.000000;1.000000;1.000000;1.000000;,
168;1.000000;1.000000;1.000000;1.000000;,
169;1.000000;1.000000;1.000000;1.000000;,
170;1.000000;1.000000;1.000000;1.000000;,
171;1.000000;1.000000;1.000000;1.000000;,
172;1.000000;1.000000;1.000000;1.000000;,
173;1.000000;1.000000;1.000000;1.000000;,
174;1.000000;1.000000;1.000000;1.000000;,
175;1.000000;1.000000;1.000000;1.000000;,
176;1.000000;1.000000;1.000000;1.000000;,
177;1.000000;1.000000;1.000000;1.000000;,
178;1.000000;1.000000;1.000000;1.000000;,
179;1.000000;1.000000;1.000000;1.000000;,
180;1.000000;1.000000;1.000000;1.000000;,
181;1.000000;1.000000;1.000000;1.000000;,
182;1.000000;1.000000;1.000000;1.000000;,
183;1.000000;1.000000;1.000000;1.000000;,
184;1.000000;1.000000;1.000000;1.000000;,
185;1.000000;1.000000;1.000000;1.000000;,
186;1.000000;1.000000;1.000000;1.000000;,
187;1.000000;1.000000;1.000000;1.000000;,
188;1.000000;1.000000;1.000000;1.000000;,
189;1.000000;1.000000;1.000000;1.000000;,
190;1.000000;1.000000;1.000000;1.000000;,
191;1.000000;1.000000;1.000000;1.000000;,
192;1.000000;1.000000;1.000000;1.000000;,
193;1.000000;1.000000;1.000000;1.000000;,
194;1.000000;1.000000;1.000000;1.000000;,
195;1.000000;1.000000;1.000000;1.000000;,
196;1.000000;1.000000;1.000000;1.000000;,
197;1.000000;1.000000;1.000000;1.000000;,
198;1.000000;1.000000;1.000000;1.000000;,
199;1.000000;1.000000;1.000000;1.000000;,
200;1.000000;1.000000;1.000000;1.000000;,
201;1.000000;1.000000;1.000000;1.000000;,
202;1.000000;1.000000;1.000000;1.000000;,
203;1.000000;1.000000;1.000000;1.000000;,
204;1.000000;1.000000;1.000000;1.000000;,
205;1.000000;1.000000;1.000000;1.000000;,
206;1.000000;1.000000;1.000000;1.000000;,
207;1.000000;1.000000;1.000000;1.000000;,
208;1.000000;1.000000;1.000000;1.000000;,
209;1.000000;1.000000;1.000000;1.000000;,
210;1.000000;1.000000;1.000000;1.000000;,
211;1.000000;1.000000;1.000000;1.000000;,
212;1.000000;1.000000;1.000000;1.000000;,
213;1.000000;1.000000;1.000000;1.000000;,
214;1.000000;1.000000;1.000000;1.000000;,
215;1.000000;1.000000;1.000000;1.000000;,
216;1.000000;1.000000;1.000000;1.000000;,
217;1.000000;1.000000;1.000000;1.000000;,
218;1.000000;1.000000;1.000000;1.000000;,
219;1.000000;1.000000;1.000000;1.000000;,
220;1.000000;1.000000;1.000000;1.000000;,
221;1.000000;1.000000;1.000000;1.000000;,
222;1.000000;1.000000;1.000000;1.000000;,
223;1.000000;1.000000;1.000000;1.000000;,
224;1.000000;1.000000;1.000000;1.000000;,
225;1.000000;1.000000;1.000000;1.000000;,
226;1.000000;1.000000;1.000000;1.000000;,
227;1.000000;1.000000;1.000000;1.000000;;
228;1.000000;1.000000;1.000000;1.000000;,
229;1.000000;1.000000;1.000000;1.000000;,
230;1.000000;1.000000;1.000000;1.000000;,
231;1.000000;1.000000;1.000000;1.000000;,
232;1.000000;1.000000;1.000000;1.000000;,
233;1.000000;1.000000;1.000000;1.000000;,
234;1.000000;1.000000;1.000000;1.000000;,
235;1.000000;1.000000;1.000000;1.000000;,
236;1.000000;1.000000;1.000000;1.000000;,
237;1.000000;1.000000;1.000000;1.000000;,
238;1.000000;1.000000;1.000000;1.000000;,
239;1.000000;1.000000;1.000000;1.000000;,
}  //End of MeshVertexColors
 }
}
}