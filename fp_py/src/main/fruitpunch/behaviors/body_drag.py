'''
Created on 2012-11-13

@author: steven
'''

from fruitpunch.native.graphics.vertex import Point
from fruitpunch.native.elements.element import Element
from fruitpunch.native.common.event import Event
from fruitpunch.native.physics.body import Body

class BodyDrag(Element):
    
    def __init__(self):
        '''
        Allows an element with a body to be dragged whenever the user drags it with the mouse/finger
        
        @ivar enabled bool: whether dragging is enabled or not
        @ivar dragging bool: Whether the dragging operation is currently being performed
        @ivar enable_x bool: Whether the user can drag the element on the x axis
        @ivar enable_y bool: Whether the user can drag the element on the y axis
        @ivar off_set Point: So the user can drag a body at a point other than its center
        '''
        super(BodyDrag, self).__init__()
        self.enabled = True
        self.moving = False
        self.dragging = False
        self.enable_x = True
        self.enable_y = True
        self.off_set = Point()
        self.always_drag = False
    # _____________________________________________________________________    
    
    def on_add(self, ev):
        self.body = self.parent.find_by_class(Body)
        
        self.parent.listen({
        "pointer_down": self.pointer_down,
        "pointer_up": self.pointer_up,
        "post_render": self.on_render
        })
    # _____________________________________________________________________
        
    def pointer_down(self, ev):
        self.dragging = True
        self.moving = False
        self.off_set.x = self.scene.pointer.x - self.parent.x
        self.off_set.y = self.scene.pointer.y - self.parent.y
        self.notify(Event("drag_start"))    
    # _____________________________________________________________________
    
    def pointer_up(self, ev):
        self.dragging = False
        self.moving = False
        self.notify(Event("drag_end"))
    # _____________________________________________________________________                                              
    
    def on_render(self, ev):
        if not self.dragging and not self.always_drag:
            return
        new_velocity = Point(0,0)
        
        if self.enable_x:
            new_velocity.x = self.scene.pointer.x - self.parent.x - self.off_set.x
        
        if self.enable_y:
            new_velocity.y = self.scene.pointer.y - self.parent.y - self.off_set.y
        
        new_velocity.x = self.velocity(new_velocity.x)
        new_velocity.y = self.velocity(new_velocity.y)
        self.body.linear_velocity = new_velocity 
    # _____________________________________________________________________
    
    # function for getting the correct physics world distance
    def velocity(self, direction_to_travel):
	p = self.body.world.pixel_size

        return(direction_to_travel / p) * 60.0
    

        
