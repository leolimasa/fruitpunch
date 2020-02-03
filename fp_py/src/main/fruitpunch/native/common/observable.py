import libfp_core
from fruitpunch.native.native_class import NativeClass
class Observable(NativeClass):
    '''
    Allows a class to handle events.
    
    When a class extends Observable, it is able to fire an event, and register
    handlers to events.
 
    Example:
  
    if I have a class called Square and I want
    an event fired every time someone clicks that Square, I would extend Square
    with an Observable. Then, whenever I detect a click, I can call
    square.notify(Event("click")) and that will execute the action() method of all the
    observers registered in Square.
    '''
    
    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Observable())
    
    # _________________________________________________________________________
    
    def attach_observer(self, event_name, observer):
        '''
        Attaches an Observer instance that will handle the event.
        The observer will be fired every time this class fires the event
        specified
        
        @param event_name: a string with the name of the event
        @param observer: an Observer object that will receive the event
        '''
        self.run_native("attach_observer", event_name, observer)
        
    # _________________________________________________________________________
    
    def detach_observer(self, observer):
        self.run_native("detach_observer", observer)
        
    # _________________________________________________________________________
        
    def notify(self, event):
        self.run_native("notify", event)
    
    # _________________________________________________________________________
    
    def listen(self, event_function_map):
        from fruitpunch.native.function_observer import FunctionObserver
        for k in event_function_map.keys():
            self.attach_observer(k, FunctionObserver(event_function_map[k]))
            
NativeClass.class_map[libfp_core.Observable] = Observable