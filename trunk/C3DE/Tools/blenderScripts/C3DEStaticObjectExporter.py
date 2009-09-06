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
				if obj.type in ('Mesh', 'Armature', 'Empty'):
					if obj.parent == None :
						parent_list.append(obj)
						
			return parent_list
		
		
			
	
	
	
		
					
	#***********************************************
	#Export the Selected Mesh
	#***********************************************
	def exportSelMesh(self):
		print "exporting ..."
		tex = []
		#objs = Object.GetSelected()
		objs = self.analyzeScene()
		iterator = 0
		for obj in objs:
			if obj.type == 'Mesh':
				mesh = obj.data
				#self.writeTextures(obj, tex)		
				self.writeMeshcoordArm(obj, None, iterator)
				iterator += 1
				
			#if obj.type == 'Armature':
			#	self.writeMeshcoordArm2(obj, arm_ob = None)
			else :
				print "The selected object is not a mesh"
		print "...finished"
		Draw.Exit()
	


	#***********************************************
	#EXPORT MESH DATA with Armature
	#***********************************************
	def writeMeshcoordArm(self, obj ,arm_ob, objectIndex):
		global index_list,flip_z		
		mesh = NMesh.GetRawFromObject(obj.name)
		
		
		print "Here we go\n"
		
		path = ("C:\documents and Settings\csabino\Desktop\exportedMeshes\out%d.c3d" % objectIndex)
		
		file = open(path, "wb")
		
		
		
		me = Mesh.New()              # Create a new mesh
		
		me.getFromObject(obj.name)    # Get the object's mesh data
		
		print "has " , me.faceUV
		
		vert_coords =[]
		vert_normals =[]
		vert_uvsU =[]
		vert_uvsV =[]
		vert_indices = []
		
		verts = me.verts[:]          # Save a copy of the vertices
		
		iterator = 0
		#me.transform(obj.matrix)      # Convert verts to world space
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

		for f in me.faces:
			for vertice in f.v:		
				#print ("face: %d;, vertice: %d;" % (f.index, vertice.index))
				vert_indices.append(vertice.index)
				new_vert.append(vertice.co)
				new_vert_normals.append(vertice.no)
				indices.append(indice_it)
				indice_it += 1
			iterator2 = 0
			for tt in f.uv:
				#print "tt: " , tt	
				vert_uvsU[f.v[iterator2].index] = round(tt[0],2)
				vert_uvsV[f.v[iterator2].index] = (1.0 - round(tt[1],2))
				iterator2 += 1
				new_vert_uvs.append(tt)
					
		#data=struct.pack(indice_it)
		format = "i"                   # one integer
		data = struct.pack(format, indice_it) # pack integer in a binary string
		#self.file.write(data)
		file.write(data)
					
		vert_iterator = 0;
		for vv in new_vert:
			print("m_vertices->push_back(VertexPos(%ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff));"	% (vv[0], vv[1], vv[2], new_vert_normals[vert_iterator][0], new_vert_normals[vert_iterator][1], new_vert_normals[vert_iterator][2], new_vert_uvs[vert_iterator][0], 1.0 - new_vert_uvs[vert_iterator][1]))
			#self.file.write("m_vertices->push_back(VertexPos(%ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff));\n"	% (vv[0], vv[1], vv[2], new_vert_normals[vert_iterator][0], new_vert_normals[vert_iterator][1], new_vert_normals[vert_iterator][2], new_vert_uvs[vert_iterator][0], 1.0 - new_vert_uvs[vert_iterator][1]))
			
			
			format = "ffffffff"                   # one integer
			data = struct.pack(format, vv[0], vv[1], vv[2], new_vert_normals[vert_iterator][0], new_vert_normals[vert_iterator][1], new_vert_normals[vert_iterator][2], new_vert_uvs[vert_iterator][0], (1.0 - new_vert_uvs[vert_iterator][1])) # pack integer in a binary string
			#self.file.write(data)
			file.write(data)
			vert_iterator += 1
			
		for ii in indices:
			#print("m_indices->push_back(%d);" % (ii))
			#self.file.write("m_indices->push_back(%d);\n" % (ii))
			format = "i"                   # one integer
			data = struct.pack(format, ii) # pack integer in a binary string
			#self.file.write(data)
			file.write(data)
			
			
		
			
		
		print "here we end\n"
		
	
	
		
#***********************************************#***********************************************#***********************************************



	
	
