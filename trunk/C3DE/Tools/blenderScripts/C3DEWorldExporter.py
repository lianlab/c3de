#!BPY


















"""
# Name: 'DirectX (.x)...'
# Blender: 242
# Group: 'Export'
# Tooltip: 'Export to DirectX text file format format for XNA Animation Component Library.'
"""
__author__ = "vertex color exporting feature is added by mnemoto (original:minahito (original:Arben (Ben) Omari))"
__url__ = ("blender.org", "blenderartists.org", "Adjuster's site http://sunday-lab.blogspot.com/, Author's site http://www.omariben.too.it","Adjuster's site http://ex.homeunix.net/")
__version__ = "3.1"

__bpydoc__ = """\
This script exports a Blender mesh with armature to DirectX 8's text file
format.

Notes:<br>
    Check author's site or the elYsiun forum for a new beta version of the
DX exporter.
"""
# DirectXExporter.py version 3.0
# Copyright (C) 2006  Arben OMARI -- omariarben@everyday.com 
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# This script export meshes created with Blender in DirectX8 file format
# it exports meshes,armatures,materials,normals,texturecoords and animations

# Grab the latest version here :www.omariben.too.it

# [Notice]
# This script is the custom version of Mr.Arben Omari's great work.
# If you have a question about the adjusted part, visit http://sunday-lab.blogspot.com/.

import Blender
from Blender import Types, Object, NMesh, Material,Armature,Mesh
from Blender.Mathutils import *
from Blender import Draw, BGL
from Blender.BGL import *
import math
import struct, string
from types import *

global mat_flip,index_list,space,bone_list,mat_dict
global anim,flip_norm,swap_zy,flip_z,speed,ticks,no_light,recalc_norm,Bl_norm
bone_list =[]
index_list = []
mat_dict = {}

bones_order = []
bones_matrix_combinations = []
space = 0;flip_z = 1;anim=0;swap_yz=0;flip_norm=0;speed=0;ticks= 25
Bl_norm = 1;recalc_norm = 0;no_light = 0

toggle_val = 0
toggle1_val = 0
toggle2_val = 0
toggle3_val = 1
toggle4_val = 0
toggle5_val = 1
toggle6_val = 0
toggle7_val = 0
anim_tick = Draw.Create(25)

def event(evt, val):	
		if evt == Draw.ESCKEY:
			Draw.Exit()                
			return

def button_event(evt): 
	global toggle_val,toggle1_val,toggle2_val,toggle3_val,toggle4_val,toggle5_val,toggle6_val,toggle7_val
	global flip_z,swap_yz,flip_norm,anim,ticks,speed,no_light,Bl_norm,recalc_norm
	arg = __script__['arg']
	
	if evt == 8:
		#fname = Blender.sys.makename(ext = ".x")
		#Blender.Window.FileSelector(my_callback_sel, "Export DirectX", fname)
		filename = "C:\documents and Settings\csabino\Desktop\outputMesh.txt"
		xexport = xExport(filename)
		xexport.exportSelMesh()
	if evt == 9:
		Draw.Exit()
		
	
def draw():
		global animsg,flipmsg,swapmsg,anim_tick
		global flip_z,swap_yz,flip_norm,anim,ticks,speed,recalc_norm,Bl_norm,no_light
		glClearColor(0.55,0.6,0.6,1)
		glClear(BGL.GL_COLOR_BUFFER_BIT)
		#external box
		glColor3f(0.2,0.3,0.3)
		rect(10,402,300,382)
		#--
		#glColor3f(0.3,0.4,0.4)
		#rect(11,399,298,398)
		#--
		glColor3f(0.5,0.75,0.65)
		rect(14,398,292,30)
		#--
		glColor3f(0.5,0.75,0.65)
		rect(14,366,292,160)
		#--
		glColor3f(0.5,0.75,0.65)
		rect(14,202,292,60)
		#--
		glColor3f(0.5,0.75,0.65)
		rect(14,138,292,40)
		#--
		glColor3f(0.5,0.75,0.65)
		rect(14,94,292,70)
		
		glColor3f(0.8,.8,0.6)
		glRasterPos2i(20, 380)
		Draw.Text("C3DE Exporter ",'large')
		#Draw.Text("(for Blender 2.41)", 'small')
		#-------Aniamtion toggle---------------------------------------------
		
		#---Flip normals toggle-----------------------------------------------
		
		#------Swap yz toggle----------------------------------------------------------------
		
		#------Flip z toggle----------------------------------------------------------------
		
		#------Speed toggle----------------------------------------------------------------
		
		#------Blender Normals toggle----------------------------------------------------------------
		
		#------Recalculute Normals toggle----------------------------------------------------------------
		
		#------Recalculute Normals toggle----------------------------------------------------------------
		
		#------Draw Button export----------------------------------------------------------------
		
		sel_butt = Draw.Button("Start",8,120, 155, 75, 30, "Start")
		exit_butt = Draw.Button("Exit",9,220, 155, 75, 30, "exit")
		
		
def rect(x,y,width,height):
		glBegin(GL_LINE_LOOP)
		glVertex2i(x,y)
		glVertex2i(x+width,y)
		glVertex2i(x+width,y-height)
		glVertex2i(x,y-height)
		glEnd()
		
def rectFill(x,y,width,height):
		glBegin(GL_POLYGON)
		glVertex2i(x,y)
		glVertex2i(x+width,y)
		glVertex2i(x+width,y-height)
		glVertex2i(x,y-height)
		glEnd()
		
		
		
Draw.Register(draw, event, button_event)


















#***********************************************
#***********************************************
#                EXPORTER
#***********************************************
#***********************************************

class xExport:
	def __init__(self, filename):
		self.file = open(filename, "wb")

#*********************************************************************************************************************************************
	#***********************************************
	#Select Scene objects
	#***********************************************
	def analyzeScene(self):
			parent_list = []
			for obj in Blender.Scene.GetCurrent().objects:
				#if obj.type in ('Mesh', 'Armature', 'Empty'):
				#print("here is a object %s" % obj.type)
				if obj.type in ('Mesh', 'Armature'):
					#if obj.parent == None :
					#	print("adding %s" % obj)
					parent_list.append(obj)
						
			return parent_list
		
	
		
					
	#***********************************************
	#Export the Selected Mesh
	#***********************************************
	def exportSelMesh(self):
		print "exporting ..."
		#self.writeHeader()
		#self.writeRootFrame()
		tex = []
		#objs = Object.GetSelected()
		objs = self.analyzeScene()
		
		path = ("C:\documents and Settings\csabino\Desktop\exportedMeshes\outWorld.c3d")				
		file = open(path, "wb")
		file.write("m_sceneTotalObjects = %i;\n" % (len(objs) - 2))
		file.write("int iterator = 0;\n")
		file.write("m_sceneStaticObjectsList = (int*)malloc(sizeof(int) * m_sceneTotalObjects);\n")
		file.write("m_sceneStaticObjectsTransforms = (C3DETransform**)malloc(sizeof(C3DETransform) * m_sceneTotalObjects);\n")
		file.write("D3DXMATRIX *t_matrix = new D3DXMATRIX();\n\n")
		
		
	
		path2 = ("C:\documents and Settings\csabino\Desktop\exportedMeshes\outScene.c3d")	
		file2 = open(path2, "wb")
		
		format = "i"                   # one integer
		data = struct.pack(format, (len(objs) - 2)) # pack integer in a binary string		
		file2.write(data)
		
	
	
		#print("objs %s" & (objs[0]))
		iterator = 0
		for obj in objs:			
			mesh = obj.data
			#self.writeTextures(obj, tex)		
			self.writeMeshcoordArm(obj, mesh, iterator, file, file2)
			iterator += 1
			
		Draw.Exit()
	
				
	
			
	
				
				
					
	

	#***********************************************
	#EXPORT MESH DATA with Armature
	#***********************************************
	def writeMeshcoordArm(self, obj ,arm_ob, objectIndex, file, file2):
		global index_list,flip_z
		#TransformMatrix
		#mat = self.getLocMat(obj)
		#self.writeArmFrames(mat, make_legal_name(obj.name))
		mesh = NMesh.GetRawFromObject(obj.name)
		
		
		#print "Here we go\n"
		
		
		
		
		
		
		
		me = Mesh.New()              # Create a new mesh
		
		me.getFromObject(obj.name)    # Get the object's mesh data
		
		meshes_ids = []
		meshes_ids.append("character")
		meshes_ids.append("ground")
		meshes_ids.append("skybox")		
		meshes_ids.append("tree0")
		meshes_ids.append("tree1")
		meshes_ids.append("tree2")
		meshes_ids.append("tree3")
		meshes_ids.append("wall1")
		meshes_ids.append("wall2")
		meshes_ids.append("wall3")
		meshes_ids.append("streetLight1")
		meshes_ids.append("streetLight2")
		meshes_ids.append("house")
		meshes_ids.append("house2")
		meshes_ids.append("house3")
		meshes_ids.append("house4")
		meshes_ids.append("house5")
		meshes_ids.append("house0")
		meshes_ids.append("house1")
		meshes_ids.append("bench")
		meshes_ids.append("sign")
		meshes_ids.append("sign2")
		meshes_ids.append("sign3")
		meshes_ids.append("sidewalkBarrier")
		meshes_ids.append("mailbox1")
		meshes_ids.append("mailbox2")
		meshes_ids.append("gardenBorder")
		meshes_ids.append("cafeTable")
		meshes_ids.append("parkingBarrier")
		meshes_ids.append("trafficCone")
		meshes_ids.append("lowHouse1Main")
		meshes_ids.append("lowHouse1Roof")
		meshes_ids.append("lowHouse1Garage")
		meshes_ids.append("lowHouse0")
	
		
		
		meshes_real_ids = []
		meshes_real_ids.append("NULL")
		meshes_real_ids.append("NULL")
		meshes_real_ids.append("NULL")
		
		meshes_real_ids.append("m_tree0")
		meshes_real_ids.append("m_tree1")
		meshes_real_ids.append("m_tree2")
		meshes_real_ids.append("m_tree3")
		meshes_real_ids.append("m_wall1")
		meshes_real_ids.append("m_wall2")
		meshes_real_ids.append("m_wall3")
		meshes_real_ids.append("m_streetLight01")
		meshes_real_ids.append("m_streetLight02")
		meshes_real_ids.append("m_house")
		meshes_real_ids.append("m_house2")
		meshes_real_ids.append("m_house3")
		meshes_real_ids.append("m_house4")
		meshes_real_ids.append("m_house5")
		meshes_real_ids.append("m_house0")
		meshes_real_ids.append("m_house1")
		meshes_real_ids.append("m_bench")
		meshes_real_ids.append("m_sign")
		meshes_real_ids.append("m_sign2")
		meshes_real_ids.append("m_sign3")
		meshes_real_ids.append("m_sidewalkBarrier")
		meshes_real_ids.append("m_mailbox")
		meshes_real_ids.append("m_mailbox2")
		meshes_real_ids.append("m_gardenBorder")
		meshes_real_ids.append("m_cafeTable")
		meshes_real_ids.append("m_parkingBarrier")
		meshes_real_ids.append("m_trafficCone")
		meshes_real_ids.append("m_lowHouse1Main")
		meshes_real_ids.append("m_lowHouse1Roof")
		meshes_real_ids.append("m_lowHouse1Garage")
		meshes_real_ids.append("m_lowHouse0")
		
		
		
		dotIndex = obj.name.find(".")
		
		mesh_str = obj.name.split(".")[0]
		
		print("mesh main: %s" % mesh_str)
		
		
		final_mesh_str = meshes_real_ids[meshes_ids.index(mesh_str)]
		
		
		
		
		#print("mesh is %s" % final_mesh_str)
		
		if final_mesh_str != "NULL":
			#file.write("t_mesh = new LandscapeMesh(%s,GetCorrespondingTextID(%s));\n" % (final_mesh_str, final_mesh_str))		
			#file.write("t_mesh->SetPosition(%ff,%ff, %ff);\n" % (-obj.matrixWorld[3][0], obj.matrixWorld[3][1], obj.matrixWorld[3][2]))
			#file.write("t_mesh->Rotate(0.0f,0.0f, 0.0f);\n")
			file.write("m_sceneStaticObjectsList[iterator] = GetMeshIndex(%s);\n" % final_mesh_str)
			file.write("m_sceneStaticObjectsTransforms[iterator] = new C3DETransform();\n")
			file.write("t_matrix->_11 = %ff;\n" % obj.matrixWorld[0][0])
			file.write("t_matrix->_12 = %ff;\n" % obj.matrixWorld[0][1])
			file.write("t_matrix->_13 = %ff;\n" % obj.matrixWorld[0][2])
			file.write("t_matrix->_14 = %ff;\n" % obj.matrixWorld[0][3])
			file.write("t_matrix->_21 = %ff;\n" % obj.matrixWorld[1][0])
			file.write("t_matrix->_22 = %ff;\n" % obj.matrixWorld[1][1])
			file.write("t_matrix->_23 = %ff;\n" % obj.matrixWorld[1][2])
			file.write("t_matrix->_24 = %ff;\n" % obj.matrixWorld[1][3])
			file.write("t_matrix->_31 = %ff;\n" % obj.matrixWorld[2][0])
			file.write("t_matrix->_32 = %ff;\n" % obj.matrixWorld[2][1])
			file.write("t_matrix->_33 = %ff;\n" % obj.matrixWorld[2][2])
			file.write("t_matrix->_34 = %ff;\n" % obj.matrixWorld[2][3])
			file.write("t_matrix->_41 = %ff;\n" % -obj.matrixWorld[3][0])
			file.write("t_matrix->_42 = %ff;\n" % obj.matrixWorld[3][1])
			file.write("t_matrix->_43 = %ff;\n" % obj.matrixWorld[3][2])
			file.write("t_matrix->_44 = %ff;\n" % obj.matrixWorld[3][3])
			file.write("m_sceneStaticObjectsTransforms[iterator]->Set(t_matrix);\n")
			
			file.write("\nSIZE %ff %ff %ff %ff %ff %ff;\n" % (obj.SizeX, obj.SizeY, obj.SizeZ, obj.RotX, obj.RotY, obj.RotZ))
			#file.write("m_sceneStaticObjectsTransforms[iterator]->Translate(%ff, %ff, %ff);\n" % (-obj.matrixWorld[3][0], obj.matrixWorld[3][1], obj.matrixWorld[3][2]))
			file.write("iterator++;\n\n")
			
			format = "i"                   # one integer
			data = struct.pack(format, meshes_ids.index(mesh_str)) # pack integer in a binary string		
			file2.write(data)						
			
			format = "ffffffffffffffff"                   # one integer
			data = struct.pack(format, obj.matrixWorld[0][0],obj.matrixWorld[0][1],obj.matrixWorld[0][2], obj.matrixWorld[0][3],obj.matrixWorld[1][0],obj.matrixWorld[1][1],obj.matrixWorld[1][2],obj.matrixWorld[1][3],obj.matrixWorld[2][0],obj.matrixWorld[2][1],obj.matrixWorld[2][2],obj.matrixWorld[2][3],-obj.matrixWorld[3][0],obj.matrixWorld[3][1],obj.matrixWorld[3][2],obj.matrixWorld[3][3]) # pack integer in a binary string		
			file2.write(data) 
		
			format = "ffffff"                  
			
			data = struct.pack(format, obj.SizeX, obj.SizeY, obj.SizeZ, obj.RotX, obj.RotY, obj.RotZ) # pack integer in a binary string		
			file2.write(data) 
			
			
			
			
		
			
		
		#print "here we end\n"
		
	