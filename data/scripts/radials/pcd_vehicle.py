import swgpy
from swgpy.object import *
from swgpy.sui import RadialMenu, RadialOptions, RadialOptionsList, RadialIdentifier
from swgpy.static import ElevatorData, ElevatorDataList
from swgpy.utility import vector3, quat

class PyRadialMenu(RadialMenu):
	def buildRadial(self, owner, target, radials):
		radial_list = RadialOptionsList()
		if (radials):
			radial_list.extend(radials)

		return radial_list
		
	def handleRadial(self, owner, target, action):
		pass
		
def call():
	pass
	
def store():
	pass
	
def mount():
	pass
	
def unmount():
	pass

def destroy():
	pass
	
