from fruitpunch.native.native_class import NativeClass
from fruitpunch.native.elements import Element
import libfp_core

'''
This will have to extend transformable...
Add transformable to fp_py? It's only an interface
Add transformable to python mapping?
'''

class Group(NativeClass):
    '''
    Allows objects to be grouped together and moved as a whole...
    '''

    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Group())   
            
    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    def add(self, transformable):
        '''
        adds a transformable to the group...
        
        c++ type for transformable is TransformablePtr
        '''
        
        return self.run_native("add", transformable)
    # _____________________________________________________________________
    
    def group_center(self):
        '''
        get center point of the group. Getter only.
        '''
        
        return self.run_native("group_center")
    # _____________________________________________________________________
    
    def boundaries(self):
        '''
        get boundaries of the group. Getter only.
        '''
        
        return self.run_native("boundaries")
    # _____________________________________________________________________
     
    def set_position(self, point):
        '''
        convert to native  fp_core Point object
        sets position of the group and updates all of the items in the 
        group as well
        '''
        p = libfp_core.Point()
        p.x = point.x
        p.y = point.y
        
        return self.run_native("set_position", p)
    # _____________________________________________________________________
    
    def get_position(self):
        '''
        return the coordinates of the group
        '''
        
        return self.run_native("get_poisition")
    # _____________________________________________________________________
    
    def set_rotation(self, angle):
        '''
        rotate the group (with everything inside in uniform) together
        '''
        
        return self.run_native("set_rotation", angle)
    # _____________________________________________________________________
    
    def get_rotation(self):
        '''
        get the angle of rotation
        '''
    
        return self.run_native("get_rotation")
    
    # _____________________________________________________________________
    
    def set_scale(self, value):
        '''
        convert to native fp_core Point object
        set scale 
        '''
        
        if hasattr(value, "x"):
            p = libfp_core.Point()
            p.x = value.x
            p.y = value.y
        elif isinstance(value, float):
            p = libfp_core.Point()
            p.x = value
            p.y = value
        else:
            raise Exception("Native group set_scale must take a Point or float")
            
        return self.run_native("set_scale", p)
    # _____________________________________________________________________
    
    def get_scale(self):
        '''
        returns the scale size of the group
        '''
        
        return self.run_native("get_scale")
    
    
    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------
    
    position = property(get_position, set_position)
    scale = property(get_scale, set_scale)
    rotation = property(get_rotation, set_rotation)
    
NativeClass.class_map[libfp_core.Group] = Group