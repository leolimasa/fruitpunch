'''
Created on Oct 24, 2012

@author: leo
'''
import unittest
import fruitpunch.native
from fruitpunch.native.native_class import NativeClass
from libfp_core import Event, Observable
from fruitpunch import Observer, Observable, Sprite, Scene, App
import inspect

# -----------------------------------------------------------------------------
# Helper Classes
# -----------------------------------------------------------------------------

class TestScene(Scene):
    def on_init(self, ev):
        pass

class TestApp(App):
    def on_init(self, event):
        self.go_to_scene(self.scene)

class NativeEvent(NativeClass):
    def __init__(self, event_name):
        self.store(Event(event_name))
    
    def get_name(self):
        return self.run_native("get_name")

class MyObserver(Observer):    
    def action(self, event):
        self.ev = event

# -----------------------------------------------------------------------------
# Tests
# -----------------------------------------------------------------------------
    
class TestNativeClass(unittest.TestCase):

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def testStore(self):
        e = NativeEvent("jump")
        e.myvar = "a"
        
        o = MyObserver()
        
        obj = Observable()
        obj.attach_observer("jump", o)
        obj.notify(e)
        
        self.assertEqual("jump", o.ev.get_name())
        self.assertEqual("a",o.ev.myvar)
        
    def testInit(self):
        '''
        Checks if all native implementations are
        calling NativeClass.__init__()
        '''
        
        for name, obj in inspect.getmembers(fruitpunch.native):
            for mod_name, mod in inspect.getmembers(obj):
                for class_name, clazz in inspect.getmembers(mod):
                    if inspect.isclass(clazz) and issubclass(clazz, NativeClass):
                        cl = clazz()
                        self.assertTrue(cl.keep_instances is not None)
            
if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()