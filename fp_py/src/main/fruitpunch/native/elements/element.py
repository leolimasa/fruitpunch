'''
Created on Oct 28, 2012

@author: leo
'''
import libfp_core
from fruitpunch.native.native_class import NativeClass
from fruitpunch.native.common.observable import Observable
from fruitpunch.native.common.node import Node
from fruitpunch.searchable import Searchable

class Element(Observable, Searchable):
    '''
    A generic container for everything that goes into a Scene.         
    '''

    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Element())
        self.listen({"add": self.on_add,
                     "remove": self.on_remove,
                     "pre_render": self.on_pre_render,
                     "post_render": self.on_render})

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    def add(self, element):
        '''
        Adds an element to the children of the current element.
        
        @return: the added element
        '''
        self.keep(element)
        return self.run_native("add", element)
    # _____________________________________________________________________

    def remove(self, element):
        '''
        Removes a child Element equals to the one passed in the argument from 
        the list of children.
        
        @return: the removed element or a null shared ptr if the element was 
        not found
        '''
        self.let_go(element)
        return self.run_native("remove", element)
    
    # _____________________________________________________________________
    
    def destroy(self):
        return self.run_native("destroy")
    
    # _____________________________________________________________________
    
    #def on_destroy(self):
        #self.parent.let_go(self)

    # _____________________________________________________________________

    def on_add(self, event):
        '''
        Called when this element has been added to a scene or another element.
        '''
        pass
    
    # _____________________________________________________________________

    def on_remove(self, event):
        '''
        Called when this element is removed from a scene or another element.
        '''
        pass
    
    # _____________________________________________________________________
    
    def import_from(self, file_path):
        '''
        Reads a resource node file - usually XML or JSON - and imports
        its tags as objects, that will be appended to the current object
        using the add() method.
        '''
        Node(file_path).inflate_children_to(self)
    # _____________________________________________________________________

    def render_frame(self):
        '''
        Called by the scene every frame.
        '''

        return self.run_native("render_frame")
    # _____________________________________________________________________

    def on_render(self, event):
        '''
        Called every frame and meant to be overridden.
        
        The difference between pre_render and render is that render is 
        limited to the frame rate, and pre_render is executed as fast as 
        possible.
        '''
        pass
    
    # _____________________________________________________________________
    def on_pre_render(self, event):
        '''
        Continuously called before rendering a frame. The difference
        between pre_render and render is that render is limited to the
        frame rate, and pre_render is executed as fast as possible.
        '''
        pass
    
    
    # _____________________________________________________________________

    def get_scene(self):
        return self.run_native("get_scene")
    # _____________________________________________________________________

    def set_scene(self, scene):
        return self.run_native("set_scene", scene)
    # _____________________________________________________________________

    def get_children(self):
        return self.run_native("get_children")
    # _____________________________________________________________________

    def get_parent(self):
        return self.run_native("get_parent")
    # _____________________________________________________________________

    def set_parent(self, parent):
        return self.run_native("set_parent", parent)
    
    # _____________________________________________________________________
    
    def stats(self):
        '''
        Outputs a summary of the object class for every children in the
        scene, recursively. This is useful for identifying memory
        leaks. It is resource intensive, and should be used only for
        diagnostic purposes.
        '''
        results = {}
        for c in self.children:
            
            # calculates the number of children of each class
            class_name = c.__class__.__name__
            if class_name not in results.keys():
                results[class_name] = 1
            else:
                results[class_name] += 1
            
            # merge child stats
            if isinstance(c, Element):
                child_results = c.stats()
                for class_name, count in child_results.iteritems():
                    if class_name not in results.keys():
                        results[class_name] = count
                    else:
                        results[class_name] += count
        return results

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    scene = property(get_scene, set_scene)
    children = property(get_children)
    parent = property(get_parent, set_parent)
    
NativeClass.class_map[libfp_core.Element] = Element