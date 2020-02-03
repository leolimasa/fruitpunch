'''
Created on 2012-09-23

@author: leo
'''
from fruitpunch.native.elements import Element
from fruitpunch.native.graphics.vertex import Point
import weakref

class Collector(Element):
    '''
    Allows the parent element to be removed out of the scene once it is out
    of the defined bounds. Very useful when dealing with objects that have
    to be destroyed when the user can no longer see it.
    
    @ivar time The time, in frames, that the element has to stay out of bounds 
               to be collected
               
    @ivar min_bounds The minimum boundary where, if the element position goes out, it will 
                     be collected. It is defaulted to 0.
                     
    @ivar max_bounds The maximum boundary where, if the element position goes out, it will 
                     be collected. It is defaulted to the window width and height.
    '''

    def __init__(self, reference=None):
        '''
        @param reference: where the collector will go to get the x and y 
                          coordinates. If not set, it will get from the parent.
        '''
        super(Collector,self).__init__()
        self.time = 1
        self.min_bounds = Point(0,0)
        self.max_bounds = Point(0,0)
        self.timer = 0
        
        # If a reference is set, we will use that to get the position instead
        # of the parent during the on_render
        self.reference = reference
            
        
    def on_add(self, e):
        if self.max_bounds.x == self.min_bounds.x \
        and self.max_bounds.y == self.min_bounds.y:
            self.max_bounds = Point(self.scene.width, self.scene.height)
            
    def on_render(self, e):
        
        # Check if we have a reference with the correct x and y or if we
        # need to use the object's parent
        if self.reference is not None:
            obj = self.reference
        else:
            obj = self.parent
            
        if obj.x < self.min_bounds.x or obj.y < self.min_bounds.y \
        or obj.x > self.max_bounds.x or obj.y > self.max_bounds.y:
            self.timer += 1
            
            
            if self.timer >= self.time:
                # Set reference to none to avoid cyclical references
                self.reference = None
                
                # Destroy everything
                self.destroy()
                obj.destroy()
                self.parent = None
                
            return
        
        self.timer = 0
             
            
        
    
        