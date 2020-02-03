'''
Created on 2012-08-12

@author: leo
'''
from fruitpunch.native.graphics.vertex import Point
from fruitpunch.native.elements.element import Element
from fruitpunch.native.common.event import Event

class Drag(Element):
    '''
    Allows an element to be dragged whenever the user drags it with the mouse/finger.
    
    @ivar enabled bool: whether dragging is enabled or not
    @ivar delta Point: The difference in position between the current pointer position and the position of the pointer in the last frame
    @ivar last_pos Point: The position of the pointer in the last frame
    @ivar dragging bool: Whether the dragging operation is currently being performed
    @ivar enable_x bool: Whether the user can drag the element on the x axis
    @ivar enable_y bool: Whether the user can drag the element on the y axis
    '''

    def __init__(self):
        '''
        Constructor
        '''
        super(Drag, self).__init__()
        self.enabled = True
        self.delta = Point()
        self.last_pos = Point()
        self.dragging = False
        self.enable_x = True
        self.enable_y = True
        
    def on_add(self, ev):
        self.parent.listen({
            "pointer_down": self.pointer_down,
            "pointer_up": self.pointer_up,
            "post_render": self.on_render
        })
    
    def pointer_down(self, ev):
        self.dragging = True
        self.last_pos = self.scene.pointer
        self.notify(Event("drag_start"))
    
    def pointer_up(self, ev):
        self.dragging = False
        self.notify(Event("drag_end"))
        
    def on_render(self, ev):
        if not self.dragging:
            return
        
        self.delta.x = self.scene.pointer.x - self.last_pos.x
        self.delta.y = self.scene.pointer.y - self.last_pos.y 
        
        if self.enable_x:
            self.parent.move(self.delta.x, 0)
        
        if self.enable_y:
            self.parent.move(0, self.delta.y)
        
        self.last_pos = self.scene.pointer
            