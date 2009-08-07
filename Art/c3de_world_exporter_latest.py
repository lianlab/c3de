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

#***********************************************
# DirectX file spec only allows letters, digits, and 
# underscore in Names.
#***********************************************
def make_legal_name(starting_name):
    new_name = starting_name.replace('.','_')
    new_name = new_name.replace(' ','_')
    if new_name[0].isdigit():
        new_name = '_' + new_name
    return new_name

#***********************************************
# MAIN
#***********************************************

def my_callback(filename):
	if filename.find('.x', -2) <= 0: filename += '.x' 
	print "filename: ", filename
	xexport = xExport(filename)
	xexport.SelectObjs()

def my_callback_sel(filename):
	#if filename.find('.x', -2) <= 0: filename += '.x' 
	filename = "C:\outputMesh.x"
	xexport = xExport(filename)
	xexport.exportSelMesh()
def event(evt, val):	
		if evt == Draw.ESCKEY:
			Draw.Exit()                
			return

def button_event(evt): 
	global toggle_val,toggle1_val,toggle2_val,toggle3_val,toggle4_val,toggle5_val,toggle6_val,toggle7_val
	global flip_z,swap_yz,flip_norm,anim,ticks,speed,no_light,Bl_norm,recalc_norm
	arg = __script__['arg']
	if evt == 1:
		toggle_val = 1 - toggle_val
		anim = toggle_val
		Draw.Redraw(1)
	if evt == 2:
		toggle1_val = 1 - toggle1_val
		flip_norm = toggle1_val
		Draw.Redraw(1)
	if evt == 3:
		toggle2_val = 1 - toggle2_val
		swap_yz = toggle2_val
		Draw.Redraw(1)
	if evt == 4:
		toggle3_val = 1 - toggle3_val
		flip_z = toggle3_val
		Draw.Redraw(1)
	if evt == 5:
		toggle4_val = 1 - toggle4_val
		speed = toggle4_val
		Draw.Redraw(1)
	if evt == 10:
		toggle5_val = 1 - toggle5_val
		if toggle5_val==1:
			toggle6_val = 0
			toggle7_val = 0
		else :
			toggle6_val = 1
			toggle7_val = 1
		no_light = toggle7_val
		recalc_norm = toggle6_val
		Bl_norm = toggle5_val
		Draw.Redraw(1)
	if evt == 11:
		toggle6_val = 1 - toggle6_val
		if toggle6_val==1:
			toggle5_val = 0
			toggle7_val = 0
		else :
			toggle5_val = 1
			toggle7_val = 1
		no_light = toggle7_val
		recalc_norm = toggle6_val
		Bl_norm = toggle5_val
		Draw.Redraw(1)
	if evt == 12:
		toggle7_val = 1 - toggle7_val
		if toggle7_val==1:
			toggle6_val = 0
			toggle5_val = 0
		else :
			toggle6_val = 1
			toggle5_val = 1
		no_light = toggle7_val
		recalc_norm = toggle6_val
		Bl_norm = toggle5_val
		Draw.Redraw(1)
	if evt == 6:
		ticks = anim_tick.val
	if evt == 7:
		fname = Blender.sys.makename(ext = ".x")
		Blender.Window.FileSelector(my_callback, "Export DirectX", fname)
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
		#-------Aniamtion toggle---------------------------------------------
		Draw.Toggle("Anim", 1, 20, 330, 55, 20, toggle_val,"export animations")
		if toggle_val :
			anim = 1
			animsg = "animation will be exported"
		else:
			anim = 0
			animsg = "animation will be not exported"
		glRasterPos2i(100,335)
		Draw.Text(animsg)
		#---Flip normals toggle-----------------------------------------------
		Draw.Toggle("Flip norm", 2, 20, 300, 55, 20, toggle1_val,"invert normals")
		if toggle1_val :
			flip_norm = 1
			flipmsg = "flipped normals"
		else:
			flip_norm = 0
			flipmsg = "not flipped normals"
		glRasterPos2i(100,305)
		Draw.Text(flipmsg)
		#------Swap yz toggle----------------------------------------------------------------
		Draw.Toggle("Swap zy", 3, 20, 270, 55, 20, toggle2_val,"swap z,y axis(y up)")
		if toggle2_val :
			swap_yz = 1
			swapmsg = "Y-axis up"
		else:
			swap_yz = 0
			swapmsg = "Z-axis up"
		glRasterPos2i(100,275)
		Draw.Text(swapmsg)
		#------Flip z toggle----------------------------------------------------------------
		Draw.Toggle("Flip z", 4, 20, 240, 55, 20, toggle3_val,"flip z axis")
		if toggle3_val :
			flip_z = 1
			zmsg = "left handed system"
		else:
			flip_z = 0
			zmsg = "right handed system"
		glRasterPos2i(100,245)
		Draw.Text(zmsg)
		#------Speed toggle----------------------------------------------------------------
		Draw.Toggle("Speed", 5, 20, 210, 55, 20, toggle4_val,"Animation speed")
		if toggle4_val :
			speed = 1
			spedmsg = "set speed"
			anim_tick = Draw.Number("", 6,200, 210, 85, 20, anim_tick.val,1,100000,"ticks per second")
		else:
			speed = 0
			spedmsg = ""
		glRasterPos2i(100,215)
		Draw.Text(spedmsg)
		#------Blender Normals toggle----------------------------------------------------------------
		Draw.Toggle("Bl.normals", 10, 20, 105, 75, 25, toggle5_val,"export normals as in Blender")
		if toggle5_val :
			Bl_norm = 1
		#------Recalculute Normals toggle----------------------------------------------------------------
		Draw.Toggle("recalc.no", 11, 120, 105, 75, 25, toggle6_val,"export recalculated normals")
		if toggle6_val :
			recalc_norm = 1
		#------Recalculute Normals toggle----------------------------------------------------------------
		Draw.Toggle("no smooth", 12, 220, 105, 75, 25, toggle7_val,"every vertex has the face normal,no smoothing")
		if toggle7_val :
			no_light = 1
		#------Draw Button export----------------------------------------------------------------
		exp_butt = Draw.Button("Export All",7,20, 155, 75, 30, "export all the scene objects")
		sel_butt = Draw.Button("Export Sel",8,120, 155, 75, 30, "export the selected object")
		exit_butt = Draw.Button("Exit",9,220, 155, 75, 30, "exit")
		glRasterPos2i(20,75)
		Draw.Text("(C) 2006  Arben OMARI ")
		glRasterPos2i(20,55)
		Draw.Text("http://www.omariben.too.it")
		glRasterPos2i(20,35)
		Draw.Text("aromar@tin.it")
		
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
		
	def getChildren(self,obj):	
		obs = Blender.Scene.GetCurrent().objects
		return [ ob for ob in obs if ob.parent == obj ]
	
	def getArmChildren(self,obj):		
		for ob in Blender.Scene.GetCurrent().objects: #Object.Get():
			if ob.parent == obj :
				return ob
	
	def getLocMat(self, obj):
		pare = obj.parent
		mat = obj.matrixWorld
		mat_id = Matrix([1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1])
		if pare:
			mat_p = pare.matrixWorld
			mat_c = Matrix(mat_p)
			mat_c.invert()
			mat_f = mat * mat_c
		else :
			mat_id.invert()
			mat_f = mat * mat_id
		return mat_f
	
	def writeObjFrames(self,obj):
		global space,chld_obj,ch_list
		mesh = obj.getData()
		if obj.type == "Empty" :
			mat = self.getLocMat(obj)
			mat_c = Matrix(mat)
			self.writeArmFrames(mat_c, make_legal_name(obj.name))
		if type(mesh) == Types.ArmatureType :
			Child_obj = self.getArmChildren(obj)
			chld_obj = obj
			ch_list.append(Child_obj)
			self.writeRootBone(obj, Child_obj)	
		if obj.type == 'Mesh' and obj not in ch_list:
			self.exportMesh(obj)
			
			
	def writeChildObj(self,obj):
		global space,ch_list
		space += 1
		if obj :
			for ob in obj:
				if ob not in ch_list:
					self.writeObjFrames(ob)
					ch_list.append(ob)
					ch_ob = self.getChildren(ob)
					self.writeChildObj(ch_ob)
					self.closeBrackets()
					self.file.write(" // End of the Object %s \n" % (ob.name))
					
					
	def writeRootFrame(self):
		global flip_z,swap_yz,speed
		if speed:
			self.writeAnimTicks()
		if flip_z:
			mat_flip = Matrix([1, 0, 0, 0], [0, 1, 0, 0], [0, 0, -1, 0], [0, 0, 0, 1])
		else :
			mat_flip = Matrix([1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1])
		if swap_yz :
			mat_rot = RotationMatrix(-90, 4, 'x')
			mat_flip = mat_rot * mat_flip
		self.writeArmFrames(mat_flip, "RootFrame")		
			
	##################################################################	
	def SelectObjs(self):
		global space,chld_obj,ch_list,flip_z,swap_yz,speed
		print "exporting..."
		self.writeHeader()
		self.writeRootFrame()
		obj_list = self.analyzeScene()
		space += 1
		ch_list = []
		for obj in obj_list:
			self.writeObjFrames(obj)
			ch_l = self.getChildren(obj)
			for ch in ch_l:
			
			
				if ch and ch.type == "Armature":
					ch_list.append(ch)
					self.writeObjFrames(ch)
				else :	
					self.writeChildObj(ch_l)
			if obj.type != "Armature":
				self.file.write("  }  // SI End of the Object %s \n" % (obj.name))	
				
				
				
		self.file.write("}  // End of the Root Frame\n")		
		if anim :
			self.file.write("AnimationSet AnimationSet0 {\n")
			for obj in Blender.Scene.GetCurrent().objects:
				if obj.type in ('Mesh', 'Empty'):
					ip_list = obj.ipo
					if ip_list != None :
						self.writeAnimationObj(obj)
				elif obj.type == 'Armature':
					act_list = obj.getAction()
					if act_list != None :
						self.writeAnimation(obj)
					#ip_list = obj.ipo
					#if ip_list != None :
					#	self.writeAnimationObj(obj)

			self.file.write("} // End of Animation Set\n")
		self.writeEnd()
		#######################################################
		
				
	def writeAnimTicks(self):
		global ticks
		self.file.write("AnimTicksPerSecond {\n")
		self.file.write("%d; \n" % (ticks))
		self.file.write("}\n")
	
	#***********************************************
	#Export Mesh without Armature
	#***********************************************
	def exportMesh(self, obj):
		tex = []
		mesh = obj.getData()
		self.writeTextures(obj, tex)		
		self.writeMeshcoordArm(obj, None, 0)
		self.writeMeshMaterialList(obj, mesh, tex)
		self.writeMeshNormals(obj, mesh)
		self.writeMeshTextureCoords(obj, mesh)
		self.writeMeshVertexColors(obj, mesh)
		self.file.write("  }  // End of the Mesh %s \n" % (obj.name))
		
					
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
		file.write("LandscapeMesh *t_mesh;\n")
		file.write("D3DXMATRIX t_matrix;\n\n")
		#print("objs %s" & (objs[0]))
		iterator = 0
		for obj in objs:			
			mesh = obj.data
			#self.writeTextures(obj, tex)		
			self.writeMeshcoordArm(obj, mesh, iterator, file)
			iterator += 1
			
		Draw.Exit()
	
				
	
			
	
				
				
					
	

	#***********************************************
	#EXPORT MESH DATA with Armature
	#***********************************************
	def writeMeshcoordArm(self, obj ,arm_ob, objectIndex, file):
		global index_list,flip_z
		#TransformMatrix
		mat = self.getLocMat(obj)
		#self.writeArmFrames(mat, make_legal_name(obj.name))
		mesh = NMesh.GetRawFromObject(obj.name)
		
		
		print "Here we go\n"
		
		
		
		
		
		
		
		me = Mesh.New()              # Create a new mesh
		
		me.getFromObject(obj.name)    # Get the object's mesh data
		
		meshes_ids = []
		meshes_ids.append("ground")
		meshes_ids.append("character")
		meshes_ids.append("cafeTable")
		
		meshes_real_ids = []
		meshes_real_ids.append("NULL")
		meshes_real_ids.append("NULL")
		meshes_real_ids.append("MESH_CAFE_TABLE_ID")
		
		dotIndex = obj.name.find(".")
		
		mesh_str = obj.name.split(".")[0]
		
		print("mesh main: %s" % mesh_str)
		
		
		final_mesh_str = meshes_real_ids[meshes_ids.index(mesh_str)]
		
		
		print("mesh is %s" % final_mesh_str)
		
		if final_mesh_str != "NULL":
			file.write("t_mesh = new LandscapeMesh(%s,GetCorrespondingTextID(%s));\n" % (final_mesh_str, final_mesh_str))		
			#file.write("t_mesh->SetPosition(%ff,%ff, %ff);\n" % (-obj.matrixWorld[3][0], obj.matrixWorld[3][1], obj.matrixWorld[3][2]))
			#file.write("t_mesh->Rotate(0.0f,0.0f, 0.0f);\n")
			file.write("t_matrix._11 = %ff;\n" % obj.matrixWorld[0][0])
			file.write("t_matrix._12 = %ff;\n" % obj.matrixWorld[0][1])
			file.write("t_matrix._13 = %ff;\n" % obj.matrixWorld[0][2])
			file.write("t_matrix._14 = %ff;\n" % obj.matrixWorld[0][3])
			file.write("t_matrix._21 = %ff;\n" % obj.matrixWorld[1][0])
			file.write("t_matrix._22 = %ff;\n" % obj.matrixWorld[1][1])
			file.write("t_matrix._23 = %ff;\n" % obj.matrixWorld[1][2])
			file.write("t_matrix._24 = %ff;\n" % obj.matrixWorld[1][3])
			file.write("t_matrix._31 = %ff;\n" % obj.matrixWorld[2][0])
			file.write("t_matrix._32 = %ff;\n" % obj.matrixWorld[2][1])
			file.write("t_matrix._33 = %ff;\n" % obj.matrixWorld[2][2])
			file.write("t_matrix._34 = %ff;\n" % obj.matrixWorld[2][3])
			file.write("t_matrix._41 = %ff;\n" % -obj.matrixWorld[3][0])
			file.write("t_matrix._42 = %ff;\n" % obj.matrixWorld[3][1])
			file.write("t_matrix._43 = %ff;\n" % obj.matrixWorld[3][2])
			file.write("t_matrix._44 = %ff;\n" % obj.matrixWorld[3][3])
			file.write("t_mesh->SetTransformMatrix(t_matrix);\n")		
			
			
			file.write("m_testScene->AddMesh(t_mesh);\n")
			file.write("m_loadedObjects++;\n")
			file.write("UpdateLoadingBar(m_loadedObjects, m_totalObjects);\n\n")

		
		
		
			
			
		
			
		
		print "here we end\n"
		
	