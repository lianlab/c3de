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
from Blender import Window

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

#***********************************************
# DirectX file spec only allows letters, digits, and 
# underscore in Names.

#***********************************************
# MAIN
#***********************************************

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
		Draw.Text("DirectX Exporter ",'large')
		Draw.Text("(for Blender 2.41)", 'small')
		
		sel_butt = Draw.Button("Export Sel",8,120, 155, 75, 30, "export the selected object")
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
		
		Window.EditMode(0)
		
		#print("objs %s" & (objs[0]))
		iterator = 0
		
				
		for obj in objs:
			print("pass")
			if obj.type == 'Mesh':
				print("found a mesh")
				mesh = obj.data
				#self.writeTextures(obj, tex)		
				self.writeMeshcoordArm(obj, mesh, iterator)
				iterator += 1
			else:
				print("not a mesh %s" % obj.type)
				#self.writeMeshMaterialList(obj, mesh, tex)
				#self.writeMeshNormals(obj, mesh)
				#self.writeMeshTextureCoords(obj, mesh)
				#self.writeMeshVertexColors(obj, mesh)
				#self.file.write(" }\n")
				#self.file.write("}\n")
				#ind = objs.index(obj)
				#if ind == len(objs)-1:
					#self.file.write("}\n")
				#ip_list = obj.ipo
				#if ip_list != None :
				#	self.file.write("AnimationSet AnimationSet0 {\n")
				#	self.writeAnimationObj(obj)
				#	self.file.write("}\n")
			#if obj.type == 'Armature':
			#	self.writeMeshcoordArm2(obj, arm_ob = None)
			#else :
			#	print "The selected object is not a mesh"
		for obj2 in objs:
			if obj2.type == 'Armature':
				print("found an armature")
				self.writeMeshcoordArm2(obj2, arm_ob = None)
		print "...finished"
		Draw.Exit()
		
	

	#***********************************************
	#EXPORT MESH DATA with Armature
	#***********************************************
	def writeMeshcoordArm(self, obj ,arm_ob, objectIndex):
		global index_list,flip_z
		
		mesh = NMesh.GetRawFromObject(obj.name)
		
		
		print "Here we go\n"
		
		#path = ("C:\documents and Settings\csabino\Desktop\exportedMeshes\out%d.c3d" % objectIndex)
		#path2 = ("C:\documents and Settings\csabino\Desktop\exportedMeshes\out.txt")
		
		#file = open(path, "wb")
		
		#file2 = open(path2, "wb")
		
		
		
		me = Mesh.New()              # Create a new mesh
		
		me.getFromObject(obj.name)    # Get the object's mesh data
		
		hasTexture = me.faceUV
		print "has " , me.faceUV
		
		vert_coords =[]
		vert_normals =[]
		vert_uvsU =[]
		vert_uvsV =[]
		vert_indices = []
		
		
		vertex_groups_names = arm_ob.getVertGroupNames()
		
		
		
		vertices_groups = []
		
		vertice_group_iterator = 0
		for vertex_group_name in vertex_groups_names:
			bones_order.append(vertex_group_name)
			
			vertice_group_indices = arm_ob.getVertsFromGroup(vertex_group_name)
			
			vertices_groups.append(vertice_group_indices)
		
		verts = me.verts[:]          # Save a copy of the vertices
		
		iterator = 0
		
		for v in me.verts:
			
			vert_coords.append(v.co)
			vert_normals.append(v.no)
			vert_uvsU.append(0)
			vert_uvsV.append(0)
			
			
			
			iterator += 1
			
			
		me.verts = verts             # Restore the original verts
		
		
		indices = []
		new_vert = []
		new_vert_normals = []
		new_vert_uvs = []
		
		indice_it = 0;
		
		g_bone_indices = []

		vert_objs = []
		
		for f in me.faces:
			for vertice in f.v:		
				
				vert_indices.append(vertice.index)
				
				vert_objs.append(vertice)
				new_vert.append(vertice.co)
				new_vert_normals.append(vertice.no)
				indices.append(indice_it)
				indice_it += 1
				
				bone_indices = []
				bone_indices_iterator = 0
				
				bone_indices.append(-1)
				bone_indices.append(-1)
				bone_indices.append(-1)
				bone_indices.append(-1)
				bone_indices.append(-1)
				
				valid_entry_iterator = 0
				
				for vertex_group in vertices_groups:
					for vertex_group_entry in vertex_group:
						if(vertice.index == vertex_group_entry) :
							bone_indices[valid_entry_iterator] = bone_indices_iterator
							valid_entry_iterator += 1
					bone_indices_iterator += 1
					
				g_bone_indices.append(bone_indices)
				
			iterator2 = 0
			if hasTexture:
				for tt in f.uv:
					#print "tt: " , tt	
					vert_uvsU[f.v[iterator2].index] = round(tt[0],2)
					vert_uvsV[f.v[iterator2].index] = (1.0 - round(tt[1],2))
					iterator2 += 1
					new_vert_uvs.append(tt)
					
					
				
		
		format = "i"                   # one integer
		data = struct.pack(format, indice_it) # pack integer in a binary string
		
		#file.write(data)
					
		vert_iterator = 0;
		"""
		for vv in new_vert:
			
			if hasTexture:
				
				if(vert_objs[vert_iterator].sel == 1):
					file2.write("\n//is selected below belngs to bone %i %i %ff %ff %ff:\n" % (g_bone_indices[vert_iterator][0], vert_objs[vert_iterator].sel, vert_objs[vert_iterator].co[0], vert_objs[vert_iterator].co[1], vert_objs[vert_iterator].co[2]))	
				file2.write("m_vertices3->push_back(VertexPosBones(%ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %i, %i));\n"	% (vv[0], vv[1], vv[2], new_vert_normals[vert_iterator][0], new_vert_normals[vert_iterator][1], new_vert_normals[vert_iterator][2], new_vert_uvs[vert_iterator][0], 1.0 - new_vert_uvs[vert_iterator][1], 1.0, g_bone_indices[vert_iterator][0], g_bone_indices[vert_iterator][1]))
			else:
				
				file2.write("m_vertices3->push_back(VertexPosBones(%ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %i, %i));\n"	% (vv[0], vv[1], vv[2], new_vert_normals[vert_iterator][0], new_vert_normals[vert_iterator][1], new_vert_normals[vert_iterator][2], 0.0, 0.0, 1.0, g_bone_indices[vert_iterator][0], g_bone_indices[vert_iterator][1]))
				
			
			format = "ffffffff"                   # one integer
			if hasTexture:
				data = struct.pack(format, vv[0], vv[1], vv[2], new_vert_normals[vert_iterator][0], new_vert_normals[vert_iterator][1], new_vert_normals[vert_iterator][2], new_vert_uvs[vert_iterator][0], (1.0 - new_vert_uvs[vert_iterator][1])) # pack integer in a binary string
			else:
				data = struct.pack(format, vv[0], vv[1], vv[2], new_vert_normals[vert_iterator][0], new_vert_normals[vert_iterator][1], new_vert_normals[vert_iterator][2], 0.0, 0.0) # pack integer in a binary string
			
				
			file.write(data)
			vert_iterator += 1
			
		
		file2.write("\n\n")
		
		for ii in indices:
			
			file2.write("m_indices->push_back(%d);\n" % (ii))
			
			format = "i"                   # one integer
			data = struct.pack(format, ii) # pack integer in a binary string
			
			file.write(data)
			
		"""
		
			
		
		print "here we end\n"
		
		
		
		
	def writeMeshcoordArm2(self, obj ,arm_ob):
		global index_list,flip_z
		
		
		
		#path3 = ("C:\documents and Settings\csabino\Desktop\exportedMeshes\outBones.txt")
		
		#path4 = ("C:\documents and Settings\csabino\Desktop\exportedMeshes\picles.txt")
		path5 = ("C:\documents and Settings\csabino\Desktop\exportedMeshes\outBones.txt")
		
		
		
		#file3 = open(path3, "wb")
		#file4 = open(path4, "wb")
		file5 = open(path5, "wb")
		
		
		armature_obj = obj.getData()
		
		
		
		bones = armature_obj.bones.values()
		
		bones_offset_x = []
		bones_offset_y = []
		bones_offset_z = []
		
		total = len(bones_order)
		
		totalFrames = 8
		
		file5.write("m_totalFrames = %i;\n" % totalFrames)
		file5.write("m_totalBones = %i;\n" % total)
		file5.write("m_roots = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * m_totalBones);\n")
		file5.write("m_currentFrameToRoots = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * m_totalBones);\n")
		file5.write("m_bonesBegin = (D3DXVECTOR3*)malloc(sizeof(D3DXVECTOR3) * m_totalBones);\n")
		file5.write("m_bonesEnd = (D3DXVECTOR3*)malloc(sizeof(D3DXVECTOR3) * m_totalBones);\n")		
		file5.write("D3DXMATRIX *t_frameMatrices;\n")
		file5.write("D3DXMATRIX t_toRoot;\n")
		file5.write("D3DXMATRIX t_currentFrameMatrix;\n\n")
		
		print "Here we are for amarmature\n"
		
		iterator = 0
		
		
		
		
		
		
		
		framesIteration = range(1,totalFrames + 1)
		
		Blender.Set('curframe', 1)
		for count in framesIteration:
		#	file5.write("t_frameMatrices = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * m_totalBones);\n")
			file5.write("t_frameMatrices = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * m_totalBones);\n")
			Blender.Set('curframe', count)
			poseObject = obj.getPose()
			poseObjects = poseObject.bones
			
			iterator = 0
			
			for bone_name in bones_order:
				
			
				ancestors = []
				
				parent = armature_obj.bones[bone_name].parent
				
				localPose = poseObjects[bone_name]
				
				finalMatrix = localPose.localMatrix
				
				
				
				while parent != None:							
					parentPose = poseObjects[parent.name]								
					ancestors.append(parent)
					parent = parent.parent
					
					
				
				file5.write("//%s\n" % bone_name)
				file5.write("D3DXMatrixIdentity(&t_toRoot);\n")			
				file5.write("D3DXMatrixTranslation(&t_toRoot, %ff, %ff, %ff);\n" % (armature_obj.bones[bone_name].head["ARMATURESPACE"][0], armature_obj.bones[bone_name].head["ARMATURESPACE"][1], armature_obj.bones[bone_name].head["ARMATURESPACE"][2]))
				file5.write("m_roots[%i] = t_toRoot;\n" % (iterator))	
				file5.write("D3DXMatrixIdentity(&t_currentFrameMatrix);\n\n")
				
				file5.write("t_currentFrameMatrix._11 = %ff;\n" % ( finalMatrix[0][0]))
				file5.write("t_currentFrameMatrix._12 = %ff;\n" % ( finalMatrix[0][1]))
				file5.write("t_currentFrameMatrix._13 = %ff;\n" % ( finalMatrix[0][2]))
				file5.write("t_currentFrameMatrix._14 = %ff;\n" % ( finalMatrix[0][3]))
				file5.write("t_currentFrameMatrix._21 = %ff;\n" % ( finalMatrix[1][0]))
				file5.write("t_currentFrameMatrix._22 = %ff;\n" % ( finalMatrix[1][1]))
				file5.write("t_currentFrameMatrix._23 = %ff;\n" % ( finalMatrix[1][2]))
				file5.write("t_currentFrameMatrix._24 = %ff;\n" % ( finalMatrix[1][3]))
				file5.write("t_currentFrameMatrix._31 = %ff;\n" % ( finalMatrix[2][0]))
				file5.write("t_currentFrameMatrix._32 = %ff;\n" % ( finalMatrix[2][1]))
				file5.write("t_currentFrameMatrix._33 = %ff;\n" % ( finalMatrix[2][2]))
				file5.write("t_currentFrameMatrix._34 = %ff;\n" % ( finalMatrix[2][3]))
				file5.write("t_currentFrameMatrix._41 = %ff;\n" % ( finalMatrix[3][0]))
				file5.write("t_currentFrameMatrix._42 = %ff;\n" % ( finalMatrix[3][1]))
				file5.write("t_currentFrameMatrix._43 = %ff;\n" % ( finalMatrix[3][2]))
				file5.write("t_currentFrameMatrix._44 = %ff;\n\n" % ( finalMatrix[3][3]))
				
				file5.write("m_currentFrameToRoots[%i] = t_currentFrameMatrix;//for now\n" % (iterator))
				file5.write("t_frameMatrices[%i] = t_currentFrameMatrix;//for now\n" % ( iterator))
				file5.write("m_bonesBegin[%i] = D3DXVECTOR3(%ff, %ff, %ff);\n" % (iterator, armature_obj.bones[bone_name].head["ARMATURESPACE"][0], armature_obj.bones[bone_name].head["ARMATURESPACE"][1], armature_obj.bones[bone_name].head["ARMATURESPACE"][2]))
				file5.write("m_bonesEnd[%i] = D3DXVECTOR3(%ff, %ff, %ff);\n\n" % (iterator, armature_obj.bones[bone_name].tail["ARMATURESPACE"][0], armature_obj.bones[bone_name].tail["ARMATURESPACE"][1], armature_obj.bones[bone_name].tail["ARMATURESPACE"][2]))
				
				
				iterator += 1
				
			file5.write("m_poseMatrices->push_back(t_frameMatrices);\n")
			file5.write("m_animationFramesDuration->push_back(100);\n\n")
			
			#file5.write("free(t_frameMatrices);\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
			
		
		
		print "here we end for armature\n"
		Draw.Exit()
		
		