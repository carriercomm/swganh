#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *

class Template(BaseTemplate):
	name = "object/installation/battlefield/destructible/shared_bfield_target_power_generator.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Installation()
	
		result.template = "object/installation/battlefield/destructible/shared_bfield_target_power_generator.iff"
		result.attribute_template_id = -1
		result.stfName("battlefield","power_generator")		
		
		#### BEGIN MODIFICATIONS ####
		####  END MODIFICATIONS  ####
		
		return result

def loadTemplates(addTemplate):
	addTemplate(Template())